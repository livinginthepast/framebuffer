#include "vinfo.h"

static ERL_NIF_TERM enif_make_bitfield(ErlNifEnv* env, struct fb_bitfield field) {
  ERL_NIF_TERM bitfield = enif_make_new_map(env);

  if (!enif_make_map_put(env, bitfield,
        enif_make_atom(env, "__struct__"),
        enif_make_atom(env, "Elixir.Framebuffer.Bitfield"),
        &bitfield)) return error(env, "Failed to create bitfield");

  if (!enif_make_map_put(env, bitfield,
        enif_make_atom(env, "offset"),
        enif_make_int(env, field.offset),
        &bitfield)) return error(env, "Failed to create biffield");

  if (!enif_make_map_put(env, bitfield,
        enif_make_atom(env, "length"),
        enif_make_int(env, field.length),
        &bitfield)) return error(env, "Failed to create biffield");

  if (!enif_make_map_put(env, bitfield,
        enif_make_atom(env, "msb_right"),
        enif_make_int(env, field.msb_right),
        &bitfield)) return error(env, "Failed to create biffield");

  return bitfield;
}

static ERL_NIF_TERM vinfo_grayscale(ErlNifEnv* env, struct fb_var_screeninfo vinfo) {
  if (vinfo.grayscale == 0) {
    return enif_make_atom(env, "color");
  } else {
    return enif_make_atom(env, "grayscale");
  }
}

ERL_NIF_TERM vinfo_to_struct(ErlNifEnv* env, struct fb_var_screeninfo vinfo) {
  ERL_NIF_TERM screeninfo = enif_make_new_map(env);

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "__struct__"),
        enif_make_atom(env, "Elixir.Framebuffer.Screeninfo.Var"),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "accel_flags"),
        enif_make_int(env, vinfo.accel_flags),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "activate"),
        enif_make_int(env, vinfo.activate),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "bits_per_pixel"),
        enif_make_int(env, vinfo.bits_per_pixel),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "blue"),
        enif_make_bitfield(env, vinfo.blue),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "colorspace"),
        enif_make_int(env, vinfo.colorspace),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "grayscale"),
        vinfo_grayscale(env, vinfo),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "green"),
        enif_make_bitfield(env, vinfo.green),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "height"),
        enif_make_int(env, vinfo.height),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "hsync_len"),
        enif_make_int(env, vinfo.hsync_len),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "left_margin"),
        enif_make_int(env, vinfo.left_margin),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "lower_margin"),
        enif_make_int(env, vinfo.lower_margin),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "nonstd"),
        enif_make_int(env, vinfo.nonstd),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "pixclock"),
        enif_make_int(env, vinfo.pixclock),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "red"),
        enif_make_bitfield(env, vinfo.red),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "right_margin"),
        enif_make_int(env, vinfo.right_margin),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "rotate"),
        enif_make_int(env, vinfo.rotate),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "sync"),
        enif_make_int(env, vinfo.sync),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "transp"),
        enif_make_bitfield(env, vinfo.transp),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "upper_margin"),
        enif_make_int(env, vinfo.upper_margin),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "vmode"),
        enif_make_int(env, vinfo.vmode),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "vsync_len"),
        enif_make_int(env, vinfo.vsync_len),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "width"),
        enif_make_int(env, vinfo.width),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "xoffset"),
        enif_make_int(env, vinfo.xoffset),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "xres"),
        enif_make_int(env, vinfo.xres),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "xres_virtual"),
        enif_make_int(env, vinfo.xres_virtual),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "yoffset"),
        enif_make_int(env, vinfo.yoffset),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "yres"),
        enif_make_int(env, vinfo.yres),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "yres_virtual"),
        enif_make_int(env, vinfo.yres_virtual),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  return screeninfo;
}

