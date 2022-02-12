#include "nif.h"

static const int FD_CLOSED = -1;
ErlNifResourceType* FD_RES_TYPE = NULL;

static FileDescriptor* alloc_fd(ErlNifEnv* env, int fd) {
  FileDescriptor* fbfd = enif_alloc_resource(FD_RES_TYPE, sizeof(FileDescriptor));
  fbfd->fd = fd;
  return fbfd;
}

static void fd_destructor(ErlNifEnv* env, void* res) {
  DEBUG("closing fd.");
  FileDescriptor* fbfd = (FileDescriptor*) res;
  close(fbfd->fd);
}

//
// API
//

static ERL_NIF_TERM open_framebuffer(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  int fb = 0;
  ERL_NIF_TERM fd;
  FileDescriptor *fbfd = NULL;
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;


  // PARSE ARGS

  if (argc != 1) goto badarg;

  ErlNifBinary device;
  if (!enif_inspect_iolist_as_binary(env, argv[0], &device)) goto badarg;
  char *path = strndup((char*) device.data, device.size);
  enif_release_binary(&device);


  // OPEN FD

  fb = open(path, O_RDWR);
  free(path);
  if (fb == FD_CLOSED) goto err;

  fbfd = alloc_fd(env, fb);
  fd = enif_make_resource(env, fbfd);
  enif_release_resource(fbfd);

  // READ FB

  // fixed screen info
  if (ioctl(fbfd->fd, FBIOGET_FSCREENINFO, &finfo)) goto err;
  // variable screen info
  if (ioctl(fbfd->fd, FBIOGET_VSCREENINFO, &vinfo)) goto err;

  return ok(env, enif_make_framebuffer(env, vinfo, finfo, fd));

badarg:
  return enif_make_badarg(env);

err:
  return error(env, strerror(errno));
}

static ERL_NIF_TERM info_framebuffer(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;
  ERL_NIF_TERM ref;
  FileDescriptor* fbfd;

  // PARSE ARGS
  if (argc != 1) goto badarg;
  if (!enif_is_map(env, argv[0])) goto badarg;
  if (!enif_get_map_value(env, argv[0], enif_make_atom(env, "ref"), &ref)) goto badarg;
  if (!enif_get_resource(env, ref, FD_RES_TYPE, (void **) &fbfd)) goto badarg;

  // fixed screen info
  if (ioctl(fbfd->fd, FBIOGET_FSCREENINFO, &finfo)) goto err;
  // variable screen info
  if (ioctl(fbfd->fd, FBIOGET_VSCREENINFO, &vinfo)) goto err;

  return ok(env, enif_make_framebuffer(env, vinfo, finfo, fbfd->fd));

badarg:
  return enif_make_badarg(env);

err:
  return error(env, strerror(errno));
}

static ERL_NIF_TERM put_pixel(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;
  ERL_NIF_TERM ref;
  FileDescriptor* fbfd;
  unsigned int screensize = 0;
  unsigned int pixel_offset = 0;
  char *fbp = 0;

  int color_arity;
  const ERL_NIF_TERM *color;
  int red, green, blue;

  // PARSE ARGS
  if (argc != 3) goto badarg;
  if (!enif_is_map(env, argv[0])) goto badarg;
  if (!enif_get_map_value(env, argv[0], enif_make_atom(env, "ref"), &ref)) goto badarg;
  if (!enif_get_resource(env, ref, FD_RES_TYPE, (void **) &fbfd)) goto badarg;
  if (!enif_get_uint(env, argv[1], &pixel_offset)) goto badarg;
  // color
  if (!enif_get_tuple(env, argv[2], &color_arity, &color)) goto badarg;
  if (color_arity != 3) goto badarg;
  if (!enif_get_int(env, color[0], &red)) goto badarg;
  if (!enif_get_int(env, color[1], &green)) goto badarg;
  if (!enif_get_int(env, color[2], &blue)) goto badarg;

  // SCREENINFO
  if (ioctl(fbfd->fd, FBIOGET_FSCREENINFO, &finfo)) goto err;
  if (ioctl(fbfd->fd, FBIOGET_VSCREENINFO, &vinfo)) goto err;


  // GET DISPLAY
  screensize = finfo.smem_len;
  if (pixel_offset > screensize) return error(env, "Pixel offset out of bounds");
  fbp = (char*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd->fd, 0);

  // Hard-coded to 32bit arch; warns on 64bit
  if ((int)fbp == -1) goto err;

  // WRITE PIXEL
  // If red has 5 bits, then values from 0-255 are converted to 0-31.
  // If green has 6 bits, then values from 0-255 are converted to 0-63.
  DEBUG("offset: %d, red: %d, green: %d, blue: %d", pixel_offset, red, green, blue);
  red = (red / (1 << (8 - vinfo.red.length)));
  green = (green / (1 << (8 - vinfo.green.length)));
  blue = (blue / (1 << (8 - vinfo.blue.length)));

  unsigned int c = (red << vinfo.red.offset) \
                     + (green << vinfo.green.offset) \
                     + (blue << vinfo.blue.offset);

  // Hard-coded to 16bit on 32bit arch
  *((unsigned short*)(fbp + pixel_offset)) = c;

  DEBUG("normalized: red: %d, green: %d, blue: %d, color: %d", red, green, blue, c);

  // RELEASE
  munmap(fbp, screensize);

  return ok(env, argv[0]);
badarg:
  return enif_make_badarg(env);

err:
  return error(env, strerror(errno));
}

//
// NIF
//

static int on_load(ErlNifEnv *env, void **priv, ERL_NIF_TERM load_info) {
  (void)(env);
  (void)(priv);
  (void)(load_info);

  ErlNifResourceType* rt = enif_open_resource_type(env,
      NULL, "framebuffer_file_descriptor", fd_destructor, ERL_NIF_RT_CREATE, NULL);
  if (rt == NULL) return -1;

  assert(FD_RES_TYPE == NULL);
  FD_RES_TYPE = rt;

  return 0;
}

static ErlNifFunc exports[]= {
  { "open", 1, open_framebuffer, 0 },
  { "info", 1, info_framebuffer, 0 },
  { "put_pixel", 3, put_pixel, 0 }
};

ERL_NIF_INIT(Elixir.Framebuffer.NIF, exports, &on_load, NULL, NULL, NULL)
