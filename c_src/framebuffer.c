#include "framebuffer.h"

ERL_NIF_TERM enif_make_framebuffer(ErlNifEnv* env,
    struct fb_var_screeninfo vinfo,
    struct fb_fix_screeninfo finfo,
    ERL_NIF_TERM fd) {
  ERL_NIF_TERM framebuffer = enif_make_new_map(env);

  ErlNifBinary bin_id;
  enif_alloc_binary(strlen(finfo.id), &bin_id);
  memcpy(bin_id.data, finfo.id, strlen(finfo.id));
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
        enif_make_int(env, vinfo.xres),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "yres"),
        enif_make_int(env, vinfo.yres),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "bits_per_pixel"),
        enif_make_int(env, vinfo.bits_per_pixel),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "type"),
        enif_make_int(env, finfo.type),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "line_length"),
        enif_make_int(env, finfo.line_length),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "capabilities"),
        enif_make_int(env, finfo.capabilities),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "ref"),
        fd,
        &framebuffer)) return error(env, "Failed to create framebuffer");

  return framebuffer;
}

