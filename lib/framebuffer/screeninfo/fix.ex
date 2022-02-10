defmodule Framebuffer.Screeninfo.Fix do
  @moduledoc """
  A representation of `fb_fix_screeninfo` as defined in `linux/fb.h`. This encapsulates
  device-independent info about the buffer device and its current format. These properties
  are immutable from userspace by direct calls, though they may change when the format
  is changed.
  """

  defstruct [
    :id,
    :accel,
    :capabilities,
    :line_length,
    :mmio_len,
    :mmio_start,
    :smem_len,
    :smem_start,
    :type,
    :visual,
    :xpanstep,
    :ypanstep
  ]

  @type t() :: %__MODULE__{
          id: binary(),
          accel: non_neg_integer(),
          capabilities: [capability_t()],
          line_length: non_neg_integer(),
          mmio_len: non_neg_integer(),
          mmio_start: non_neg_integer(),
          smem_len: non_neg_integer(),
          smem_start: non_neg_integer(),
          type: type_t(),
          visual: visual_t(),
          xpanstep: non_neg_integer(),
          ypanstep: non_neg_integer()
        }

  @type accel_t() ::
          :none
          | :accel_atariblitt
          | :accel_amigablitt
          | :accel_s3_trio64
          | :accel_ncr_77c32blt
          | :accel_s3_virge
          | :accel_ati_mach64gx
          | :accel_dec_tga
          | :accel_ati_mach64ct
          | :accel_ati_mach64vt
          | :accel_ati_mach64gt
          | :accel_sun_creator
          | :accel_sun_cgsix
          | :accel_sun_leo
          | :accel_ims_twinturbo
          | :accel_3dlabs_permedia2
          | :accel_matrox_mga2064w
          | :accel_matrox_mga1064sg
          | :accel_matrox_mga2164w
          | :accel_matrox_mga2164w_agp
          | :accel_matrox_mgag100
          | :accel_matrox_mgag200
          | :accel_sun_cg14
          | :accel_sun_bwtwo
          | :accel_sun_cgthree
          | :accel_sun_tcx
          | :accel_matrox_mgag400
          | :accel_nv3
          | :accel_nv4
          | :accel_nv5
          | :accel_ct_6555x
          | :accel_3dfx_banshee
          | :accel_ati_rage128
          | :accel_igs_cyber2000
          | :accel_igs_cyber2010
          | :accel_igs_cyber5000
          | :accel_sis_glamour
          | :accel_3dlabs_permedia3
          | :accel_ati_radeon
          | :accel_i810
          | :accel_sis_glamour_2
          | :accel_sis_xabre
          | :accel_i830
          | :accel_nv_10
          | :accel_nv_20
          | :accel_nv_30
          | :accel_nv_40
          | :accel_xgi_volari_v
          | :accel_xgi_volari_z
          | :accel_omap1610
          | :accel_trident_tgui
          | :accel_trident_3dimage
          | :accel_trident_blade3d
          | :accel_trident_bladexp
          | :accel_cirrus_alpine
          | :accel_neomagic_nm2070
          | :accel_neomagic_nm2090
          | :accel_neomagic_nm2093
          | :accel_neomagic_nm2097
          | :accel_neomagic_nm2160
          | :accel_neomagic_nm2200
          | :accel_neomagic_nm2230
          | :accel_neomagic_nm2360
          | :accel_neomagic_nm2380
          | :accel_pxa3xx
          | :accel_savage4
          | :accel_savage3d
          | :accel_savage3d_mv
          | :accel_savage2000
          | :accel_savage_mx_mv
          | :accel_savage_mx
          | :accel_savage_ix_mv
          | :accel_savage_ix
          | :accel_prosavage_pm
          | :accel_prosavage_km
          | :accel_s3twister_p
          | :accel_s3twister_k
          | :accel_supersavage
          | :accel_prosavage_ddr
          | :accel_prosavage_ddrk
          | :accel_puv3_unigfx

  @type capability_t() :: :fourcc
  @type type_t() :: :packed_pixel | :planes | :interleaved_planes | :text | :vga_planes | :fourcc

  @type visual_t() ::
          :mono01
          | :mono10
          | :truecolor
          | :pseudocolor
          | :directcolor
          | :static_pseudocolor
          | :fourcc
end
