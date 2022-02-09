defmodule Framebuffer.Screeninfo.Fix do
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
          capabilities: non_neg_integer(),
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
