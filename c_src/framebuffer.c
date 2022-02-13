#include "framebuffer.h"

ERL_NIF_TERM enif_make_framebuffer(ErlNifEnv* env,
    struct fb_var_screeninfo vinfo,
    struct fb_fix_screeninfo finfo,
    ERL_NIF_TERM fd) {
  ERL_NIF_TERM framebuffer = enif_make_new_map(env);

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "__struct__"),
        enif_make_atom(env, "Elixir.Framebuffer"),
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "ref"),
        fd,
        &framebuffer)) return error(env, "Failed to create framebuffer");

  ERL_NIF_TERM fix_screeninfo = finfo_to_struct(env, finfo);
  ERL_NIF_TERM var_screeninfo = vinfo_to_struct(env, vinfo);

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "fix_screeninfo"),
        fix_screeninfo,
        &framebuffer)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "var_screeninfo"),
        var_screeninfo,
        &framebuffer)) return error(env, "Failed to create framebuffer");

  return framebuffer;
}

int fb_put_finfo(ErlNifEnv* env, struct fb_fix_screeninfo finfo, ERL_NIF_TERM* framebuffer) {
  ERL_NIF_TERM fix_screeninfo = finfo_to_struct(env, finfo);

  if (!enif_make_map_put(env, *framebuffer,
        enif_make_atom(env, "fix_screeninfo"),
        fix_screeninfo,
        framebuffer)) return 0;

  return 1;
}

int fb_put_vinfo(ErlNifEnv* env, struct fb_var_screeninfo vinfo, ERL_NIF_TERM* framebuffer) {
  ERL_NIF_TERM var_screeninfo = vinfo_to_struct(env, vinfo);

  if (!enif_make_map_put(env, *framebuffer,
        enif_make_atom(env, "var_screeninfo"),
        var_screeninfo,
        framebuffer)) return 0;

  return 1;
}
