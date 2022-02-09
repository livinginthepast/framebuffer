#include "framebuffer.h"

static ERL_NIF_TERM finfo_capabilities(ErlNifEnv *env, struct fb_fix_screeninfo finfo) {
  ERL_NIF_TERM capabilities = enif_make_list(env, 0);

  if (finfo.capabilities == 1) {
    capabilities = enif_make_list_cell(env, enif_make_atom(env, "fourcc"), capabilities);
  }

  return capabilities;
}

static ERL_NIF_TERM finfo_to_struct(ErlNifEnv* env, struct fb_fix_screeninfo finfo) {
  ERL_NIF_TERM screeninfo = enif_make_new_map(env);

  ErlNifBinary bin_id;
  enif_alloc_binary(strlen(finfo.id), &bin_id);
  memcpy(bin_id.data, finfo.id, strlen(finfo.id));
  ERL_NIF_TERM id = enif_make_binary(env, &bin_id);

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "__struct__"),
        enif_make_atom(env, "Elixir.Framebuffer.Screeninfo.Fix"),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "id"),
        id,
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "accel"),
        enif_make_int(env, finfo.accel),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "capabilities"),
        finfo_capabilities(env, finfo),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "line_length"),
        enif_make_int(env, finfo.line_length),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "mmio_len"),
        enif_make_int(env, finfo.mmio_len),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "mmio_start"),
        enif_make_int(env, finfo.mmio_start),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "smem_len"),
        enif_make_int(env, finfo.smem_len),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "smem_start"),
        enif_make_int(env, finfo.smem_start),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "type"),
        enif_make_int(env, finfo.type),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "visual"),
        enif_make_int(env, finfo.visual),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "xpanstep"),
        enif_make_int(env, finfo.xpanstep),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "ypanstep"),
        enif_make_int(env, finfo.ypanstep),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  return screeninfo;
}

static ERL_NIF_TERM vinfo_to_struct(ErlNifEnv* env, struct fb_var_screeninfo vinfo) {
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
        enif_make_atom(env, "colorspace"),
        enif_make_int(env, vinfo.colorspace),
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
        enif_make_atom(env, "grayscale"),
        enif_make_int(env, vinfo.grayscale),
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

// PUBLIC

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

