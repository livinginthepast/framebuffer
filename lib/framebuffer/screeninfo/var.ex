defmodule Framebuffer.Screeninfo.Var do
  @moduledoc """
  A representation of `fb_var_screeninfo` as defined in `linux/fb.h`. This encapsulates
  device-independent info about the buffer device, its format and video mode, and "other
  miscellaneous parameters." These properties are mutable via the `FBIOPUT_VSCREENINFO`
  ioctl.
  """

  defstruct [
    :accel_flags,
    :activate,
    :bits_per_pixel,
    :colorspace,
    :height,
    :hsync_len,
    :grayscale,
    :left_margin,
    :lower_margin,
    :nonstd,
    :pixclock,
    :right_margin,
    :rotate,
    :sync,
    :upper_margin,
    :vmode,
    :vsync_len,
    :width,
    :xoffset,
    :xres,
    :xres_virtual,
    :yoffset,
    :yres,
    :yres_virtual
  ]

  @type t() :: %__MODULE__{
          accel_flags: non_neg_integer(),
          activate: non_neg_integer(),
          bits_per_pixel: non_neg_integer(),
          colorspace: non_neg_integer(),
          grayscale: non_neg_integer(),
          height: non_neg_integer(),
          hsync_len: non_neg_integer(),
          left_margin: non_neg_integer(),
          left_margin: non_neg_integer(),
          lower_margin: non_neg_integer(),
          nonstd: non_neg_integer(),
          pixclock: non_neg_integer(),
          right_margin: non_neg_integer(),
          rotate: non_neg_integer(),
          sync: non_neg_integer(),
          upper_margin: non_neg_integer(),
          vmode: non_neg_integer(),
          vsync_len: non_neg_integer(),
          width: non_neg_integer(),
          xoffset: non_neg_integer(),
          xres: non_neg_integer(),
          xres_virtual: non_neg_integer(),
          yoffset: non_neg_integer(),
          yres: non_neg_integer(),
          yres_virtual: non_neg_integer()
        }
end
