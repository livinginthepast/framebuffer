defmodule Framebuffer do
  defstruct [
    :bits_per_pixel,
    :capabilities,
    :id,
    :line_length,
    :ref,
    :type,
    :xres,
    :yres
  ]

  @type t() :: %__MODULE__{
          bits_per_pixel: non_neg_integer(),
          capabilities: non_neg_integer(),
          id: binary(),
          line_length: non_neg_integer(),
          ref: reference(),
          type: non_neg_integer(),
          xres: non_neg_integer(),
          yres: non_neg_integer()
        }

  defdelegate open(device \\ "/dev/fb0"), to: Framebuffer.NIF
  defdelegate info(framebuffer), to: Framebuffer.NIF
end
