defmodule Framebuffer do
  defstruct [
    :capabilities,
    :line_length,
    :id,
    :xres,
    :yres,
    :bits_per_pixel,
    :type
  ]

  @type t() :: %__MODULE__{
          capabilities: non_neg_integer(),
          line_length: non_neg_integer(),
          id: binary(),
          xres: non_neg_integer(),
          yres: non_neg_integer(),
          bits_per_pixel: non_neg_integer(),
          type: non_neg_integer()
        }

  defdelegate info(device \\ "/dev/fb0"), to: Framebuffer.NIF
end
