#include "framebuffer.h"

ERL_NIF_TERM enif_make_framebuffer(ErlNifEnv* env,
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

