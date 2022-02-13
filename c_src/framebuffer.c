#include "framebuffer.h"

int enif_make_framebuffer(ErlNifEnv* env,
    struct fb_fix_screeninfo finfo,
    struct fb_var_screeninfo vinfo,
    ERL_NIF_TERM fd,
    ERL_NIF_TERM* fb) {
  ERL_NIF_TERM framebuffer = enif_make_new_map(env);

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "__struct__"),
        enif_make_atom(env, "Elixir.Framebuffer"),
        &framebuffer)) return 0;

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "ref"),
        fd,
        &framebuffer)) return 0;

  ERL_NIF_TERM fix_screeninfo;
  ERL_NIF_TERM var_screeninfo;

  if (!finfo_to_struct(env, finfo, &fix_screeninfo)) return 0;
  if (!vinfo_to_struct(env, vinfo, &var_screeninfo)) return 0;

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "fix_screeninfo"),
        fix_screeninfo,
        &framebuffer)) return 0;

  if (!enif_make_map_put(env, framebuffer,
        enif_make_atom(env, "var_screeninfo"),
        var_screeninfo,
        &framebuffer)) return 0;

  *fb = framebuffer;
  return 1;
}

int fb_put_finfo(ErlNifEnv* env, struct fb_fix_screeninfo finfo, ERL_NIF_TERM* framebuffer) {
  ERL_NIF_TERM fix_screeninfo;
  if(!finfo_to_struct(env, finfo, &fix_screeninfo)) return 0;

  if (!enif_make_map_put(env, *framebuffer,
        enif_make_atom(env, "fix_screeninfo"),
        fix_screeninfo,
        framebuffer)) return 0;

  return 1;
}

int fb_put_vinfo(ErlNifEnv* env, struct fb_var_screeninfo vinfo, ERL_NIF_TERM* framebuffer) {
  ERL_NIF_TERM var_screeninfo;
  if(!vinfo_to_struct(env, vinfo, &var_screeninfo)) return 0;

  if (!enif_make_map_put(env, *framebuffer,
        enif_make_atom(env, "var_screeninfo"),
        var_screeninfo,
        framebuffer)) return 0;

  return 1;
}
