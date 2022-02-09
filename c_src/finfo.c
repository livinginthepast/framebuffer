#include "finfo.h"

static ERL_NIF_TERM finfo_capabilities(ErlNifEnv *env, struct fb_fix_screeninfo finfo) {
  ERL_NIF_TERM capabilities = enif_make_list(env, 0);

  if (finfo.capabilities == 1) {
    capabilities = enif_make_list_cell(env, enif_make_atom(env, "fourcc"), capabilities);
  }

  return capabilities;
}

static ERL_NIF_TERM finfo_type(ErlNifEnv *env, struct fb_fix_screeninfo finfo) {
  switch (finfo.type) {
    case 0:
      return enif_make_atom(env, "packed_pixels");
      break;
    case 1:
      return enif_make_atom(env, "planes");
      break;
    case 2:
      return enif_make_atom(env, "interleaved_planes");
      break;
    case 3:
      return enif_make_atom(env, "text");
      break;
    case 4:
      return enif_make_atom(env, "vga_planes");
      break;
    case 5:
      return enif_make_atom(env, "fourcc");
      break;
    default:
      return enif_make_int(env, finfo.type);
      break;
  }
}

static ERL_NIF_TERM finfo_visual(ErlNifEnv *env, struct fb_fix_screeninfo finfo) {
  switch (finfo.visual) {
    case 0:
      return enif_make_atom(env, "mono01");
      break;
    case 1:
      return enif_make_atom(env, "mono10");
      break;
    case 2:
      return enif_make_atom(env, "truecolor");
      break;
    case 3:
      return enif_make_atom(env, "pseudocolor");
      break;
    case 4:
      return enif_make_atom(env, "directcolor");
      break;
    case 5:
      return enif_make_atom(env, "static_pseudocolor");
      break;
    case 6:
      return enif_make_atom(env, "fourcc");
      break;
    default:
      return enif_make_int(env, finfo.visual);
      break;
  }
}

ERL_NIF_TERM finfo_to_struct(ErlNifEnv* env, struct fb_fix_screeninfo finfo) {
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
        finfo_type(env, finfo),
        &screeninfo)) return error(env, "Failed to create framebuffer");

  if (!enif_make_map_put(env, screeninfo,
        enif_make_atom(env, "visual"),
        finfo_visual(env, finfo),
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

