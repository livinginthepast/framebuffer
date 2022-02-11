defmodule Framebuffer.Bitfield do
  @moduledoc """
  When the device is running in `:truecolor` or `:directcolor` (found in
  `:fix_screeninfo`), then the `:red`, `:blue`, `:green`, and `:transp`
  properties of `:var_screeninfo` will be bitfields describing the memory
  layout of color components.

  Pixel values are `:bits_per_pixel` wide, split into non-overlapping
  red/green/blue/alpha. Offsets are computed from the right.

  When `:bits_per_pixel` are not a multiple of 8, pixels are padded to
  the next multiple of 8bits.
  """

  defstruct [
    :offset,
    :length,
    :msb_right
  ]

  @type t() :: %__MODULE__{
          offset: non_neg_integer(),
          length: non_neg_integer(),
          msb_right: non_neg_integer()
        }

  defimpl String.Chars do
    def to_string(bf) do
      "#{bf.length}/#{bf.offset}"
    end
  end
end
