#include "nif.h"

static const int FD_CLOSED = -1;

static ERL_NIF_TERM info(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  if (argc != 1) return enif_make_badarg(env);

  ErlNifBinary device;
  if (!enif_inspect_iolist_as_binary(env, argv[0], &device)) return enif_make_badarg(env);
  char *path = strndup((char*) device.data, device.size);
  enif_release_binary(&device);

  int fbfd = 0;
  struct fb_var_screeninfo var_info;
  struct fb_fix_screeninfo fix_info;

  fbfd = open(path, O_RDWR);
  free(path);

  if (fbfd == FD_CLOSED) return error(env, strerror(errno));

  // fixed screen info
  if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info)) return error(env, strerror(errno));
  // variable screen info
  if (ioctl(fbfd, FBIOGET_VSCREENINFO, &var_info)) return error(env, strerror(errno));

  close(fbfd);

  return ok(env, enif_make_framebuffer(env, var_info, fix_info));
}

static int on_load(ErlNifEnv *env, void **priv, ERL_NIF_TERM load_info) {
  return 0;
}

static int on_unload(ErlNifEnv *env, void **priv, ERL_NIF_TERM load_info) {
  return 0;
}

static ErlNifFunc exports[]= {
  { "info", 1, info }
};

ERL_NIF_INIT(Elixir.Framebuffer.NIF, exports, &on_load, NULL, NULL, &on_unload)
