#include "finfo.h"

static ERL_NIF_TERM finfo_accel(ErlNifEnv *env, struct fb_fix_screeninfo finfo) {
  switch (finfo.accel) {
    case 0:
      return enif_make_atom(env, "none");
      break;
    case 1:
      return enif_make_atom(env, "accel_atariblitt");
      break;
    case 2:
      return enif_make_atom(env, "accel_amigablitt");
      break;
    case 3:
      return enif_make_atom(env, "accel_s3_trio64");
      break;
    case 4:
      return enif_make_atom(env, "accel_ncr_77c32blt");
      break;
    case 5:
      return enif_make_atom(env, "accel_s3_virge");
      break;
    case 6:
      return enif_make_atom(env, "accel_ati_mach64gx");
      break;
    case 7:
      return enif_make_atom(env, "accel_dec_tga");
      break;
    case 8:
      return enif_make_atom(env, "accel_ati_mach64ct");
      break;
    case 9:
      return enif_make_atom(env, "accel_ati_mach64vt");
      break;
    case 10:
      return enif_make_atom(env, "accel_ati_mach64gt");
      break;
    case 11:
      return enif_make_atom(env, "accel_sun_creator");
      break;
    case 12:
      return enif_make_atom(env, "accel_sun_cgsix");
      break;
    case 13:
      return enif_make_atom(env, "accel_sun_leo");
      break;
    case 14:
      return enif_make_atom(env, "accel_ims_twinturbo");
      break;
    case 15:
      return enif_make_atom(env, "accel_3dlabs_permedia2");
      break;
    case 16:
      return enif_make_atom(env, "accel_matrox_mga2064w");
      break;
    case 17:
      return enif_make_atom(env, "accel_matrox_mga1064sg");
      break;
    case 18:
      return enif_make_atom(env, "accel_matrox_mga2164w");
      break;
    case 19:
      return enif_make_atom(env, "accel_matrox_mga2164w_agp");
      break;
    case 20:
      return enif_make_atom(env, "accel_matrox_mgag100");
      break;
    case 21:
      return enif_make_atom(env, "accel_matrox_mgag200");
      break;
    case 22:
      return enif_make_atom(env, "accel_sun_cg14");
      break;
    case 23:
      return enif_make_atom(env, "accel_sun_bwtwo");
      break;
    case 24:
      return enif_make_atom(env, "accel_sun_cgthree");
      break;
    case 25:
      return enif_make_atom(env, "accel_sun_tcx");
      break;
    case 26:
      return enif_make_atom(env, "accel_matrox_mgag400");
      break;
    case 27:
      return enif_make_atom(env, "accel_nv3");
      break;
    case 28:
      return enif_make_atom(env, "accel_nv4");
      break;
    case 29:
      return enif_make_atom(env, "accel_nv5");
      break;
    case 30:
      return enif_make_atom(env, "accel_ct_6555x");
      break;
    case 31:
      return enif_make_atom(env, "accel_3dfx_banshee");
      break;
    case 32:
      return enif_make_atom(env, "accel_ati_rage128");
      break;
    case 33:
      return enif_make_atom(env, "accel_igs_cyber2000");
      break;
    case 34:
      return enif_make_atom(env, "accel_igs_cyber2010");
      break;
    case 35:
      return enif_make_atom(env, "accel_igs_cyber5000");
      break;
    case 36:
      return enif_make_atom(env, "accel_sis_glamour");
      break;
    case 37:
      return enif_make_atom(env, "accel_3dlabs_permedia3");
      break;
    case 38:
      return enif_make_atom(env, "accel_ati_radeon");
      break;
    case 39:
      return enif_make_atom(env, "accel_i810");
      break;
    case 40:
      return enif_make_atom(env, "accel_sis_glamour_2");
      break;
    case 41:
      return enif_make_atom(env, "accel_sis_xabre");
      break;
    case 42:
      return enif_make_atom(env, "accel_i830");
      break;
    case 43:
      return enif_make_atom(env, "accel_nv_10");
      break;
    case 44:
      return enif_make_atom(env, "accel_nv_20");
      break;
    case 45:
      return enif_make_atom(env, "accel_nv_30");
      break;
    case 46:
      return enif_make_atom(env, "accel_nv_40");
      break;
    case 47:
      return enif_make_atom(env, "accel_xgi_volari_v");
      break;
    case 48:
      return enif_make_atom(env, "accel_xgi_volari_z");
      break;
    case 49:
      return enif_make_atom(env, "accel_omap1610");
      break;
    case 50:
      return enif_make_atom(env, "accel_trident_tgui");
      break;
    case 51:
      return enif_make_atom(env, "accel_trident_3dimage");
      break;
    case 52:
      return enif_make_atom(env, "accel_trident_blade3d");
      break;
    case 53:
      return enif_make_atom(env, "accel_trident_bladexp");
      break;
    // case 53:
      // This overlaps with FB_ACCEL_TRIDENT_BLADEXP?
      // return enif_make_atom(env, "accel_cirrus_alpine");
      // break;
    case 90:
      return enif_make_atom(env, "accel_neomagic_nm2070");
      break;
    case 91:
      return enif_make_atom(env, "accel_neomagic_nm2090");
      break;
    case 92:
      return enif_make_atom(env, "accel_neomagic_nm2093");
      break;
    case 93:
      return enif_make_atom(env, "accel_neomagic_nm2097");
      break;
    case 94:
      return enif_make_atom(env, "accel_neomagic_nm2160");
      break;
    case 95:
      return enif_make_atom(env, "accel_neomagic_nm2200");
      break;
    case 96:
      return enif_make_atom(env, "accel_neomagic_nm2230");
      break;
    case 97:
      return enif_make_atom(env, "accel_neomagic_nm2360");
      break;
    case 98:
      return enif_make_atom(env, "accel_neomagic_nm2380");
      break;
    case 99:
      return enif_make_atom(env, "accel_pxa3xx");
      break;
    case 0x80:
      return enif_make_atom(env, "accel_savage4");
      break;
    case 0x81:
      return enif_make_atom(env, "accel_savage3d");
      break;
    case 0x82:
      return enif_make_atom(env, "accel_savage3d_mv");
      break;
    case 0x83:
      return enif_make_atom(env, "accel_savage2000");
      break;
    case 0x84:
      return enif_make_atom(env, "accel_savage_mx_mv");
      break;
    case 0x85:
      return enif_make_atom(env, "accel_savage_mx");
      break;
    case 0x86:
      return enif_make_atom(env, "accel_savage_ix_mv");
      break;
    case 0x87:
      return enif_make_atom(env, "accel_savage_ix");
      break;
    case 0x88:
      return enif_make_atom(env, "accel_prosavage_pm");
      break;
    case 0x89:
      return enif_make_atom(env, "accel_prosavage_km");
      break;
    case 0x8a:
      return enif_make_atom(env, "accel_s3twister_p");
      break;
    case 0x8b:
      return enif_make_atom(env, "accel_s3twister_k");
      break;
    case 0x8c:
      return enif_make_atom(env, "accel_supersavage");
      break;
    case 0x8d:
      return enif_make_atom(env, "accel_prosavage_ddr");
      break;
    case 0x8e:
      return enif_make_atom(env, "accel_prosavage_ddrk");
      break;
    case 0xa0:
      return enif_make_atom(env, "accel_puv3_unigfx");
      break;
    default:
      return enif_make_int(env, finfo.accel);
      break;
  }
}

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
        finfo_accel(env, finfo),
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

