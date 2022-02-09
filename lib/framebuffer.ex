defmodule Framebuffer do
  @moduledoc """
  Abstraction over Linux framebuffer devices.

  ## Linux headers

  - [linux/fb.h](https://github.com/torvalds/linux/blob/master/include/linux/fb.h)
  - [uapi/linux/fb.h](https://github.com/torvalds/linux/blob/master/include/uapi/linux/fb.h)

  ## Linux documentation

  - [fb device API](https://github.com/torvalds/linux/blob/5bfc75d92efd494db37f5c4c173d3639d4772966/Documentation/fb/api.rst)
  - [fb driver API](https://github.com/torvalds/linux/blob/master/Documentation/driver-api/frame-buffer.rst)

  """

  defstruct [
    :ref,
    :fix_screeninfo,
    :var_screeninfo
  ]

  @type t() :: %__MODULE__{
          ref: reference(),
          fix_screeninfo: Framebuffer.Screeninfo.Fix.t(),
          var_screeninfo: Framebuffer.Screeninfo.Var.t()
        }

  @type device_t() :: Path.t()

  @spec open(device_t()) :: {:ok, Framebuffer.t()} | {:error, term()}
  defdelegate open(device \\ "/dev/fb0"), to: Framebuffer.NIF

  @spec open(Framebuffer.t()) :: {:ok, Framebuffer.t()} | {:error, term()}
  defdelegate info(framebuffer), to: Framebuffer.NIF
end
