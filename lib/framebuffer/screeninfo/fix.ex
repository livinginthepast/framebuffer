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
          capabilities: [Framebuffer.capability_t()],
          line_length: non_neg_integer(),
          mmio_len: non_neg_integer(),
          mmio_start: non_neg_integer(),
          smem_len: non_neg_integer(),
          smem_start: non_neg_integer(),
          type: non_neg_integer(),
          visual: non_neg_integer(),
          xpanstep: non_neg_integer(),
          ypanstep: non_neg_integer()
        }
end
