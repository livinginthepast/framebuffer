#include "finfo.h"

static ERL_NIF_TERM finfo_capabilities(ErlNifEnv *env, struct fb_fix_screeninfo finfo) {
  ERL_NIF_TERM capabilities = enif_make_list(env, 0);

  if (finfo.capabilities == 1) {
    capabilities = enif_make_list_cell(env, enif_make_atom(env, "fourcc"), capabilities);
  }

  return capabilities;
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

