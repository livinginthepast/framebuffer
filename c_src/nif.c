#include <erl_nif.h>
#include "nif.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>


#define ATOM_ERROR(env) enif_make_atom(env, "error")
#define ATOM_OK(env) enif_make_atom(env, "ok")


static const int FD_CLOSED = -1;


static ERL_NIF_TERM error(ErlNifEnv* env, const char* message) {
  ErlNifBinary error;
  enif_alloc_binary(strlen(message), &error);
  memcpy(error.data, message, strlen(message));
  ERL_NIF_TERM err = enif_make_binary(env, &error);

  return enif_make_tuple2(env, ATOM_ERROR(env), err);
}

static ERL_NIF_TERM ok(ErlNifEnv* env, ERL_NIF_TERM value) {
  return enif_make_tuple2(env, ATOM_OK(env), value);
}

static ERL_NIF_TERM enif_make_framebuffer(ErlNifEnv* env,
    struct fb_var_screeninfo var_info,
    struct fb_fix_screeninfo fixed_info) {
  ERL_NIF_TERM framebuffer = enif_make_new_map(env);

  ErlNifBinary bin_id;
  enif_alloc_binary(strlen(fixed_info.id), &bin_id);
  memcpy(bin_id.data, fixed_info.id, strlen(fixed_info.id));
  ERL_NIF_TERM id = enif_make_binary(env, &bin_id);

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "__struct__"),
        enif_make_atom(env, "Elixir.Framebuffer"),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "id"),
        id,
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "xres"),
        enif_make_int(env, var_info.xres),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "yres"),
        enif_make_int(env, var_info.yres),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "bits_per_pixel"),
        enif_make_int(env, var_info.bits_per_pixel),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "type"),
        enif_make_int(env, fixed_info.type),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "line_length"),
        enif_make_int(env, fixed_info.line_length),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "capabilities"),
        enif_make_int(env, fixed_info.capabilities),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  return framebuffer;
}

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

  if (fbfd == FD_CLOSED) {
    return error(env, strerror(errno));
  }

  // fixed screen info
  if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info)) {
    return error(env, strerror(errno));
  }

  // variable screen info
  if (ioctl(fbfd, FBIOGET_VSCREENINFO, &var_info)) {
    return error(env, strerror(errno));
  }

  close(fbfd);

  return ok(env, enif_make_framebuffer(env, var_info, fix_info));
}


static int on_load(ErlNifEnv *env, void **priv, ERL_NIF_TERM load_info) {
  return 0;
}

static ErlNifFunc exports[]= {
  { "info", 1, info }
};

ERL_NIF_INIT(Elixir.Framebuffer.NIF, exports, &on_load, NULL, NULL, NULL)
