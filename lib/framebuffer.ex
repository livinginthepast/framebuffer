defmodule Framebuffer do
  @moduledoc """
  Abstraction over Linux framebuffer devices.

  ## Linux headers

  - [linux/fb.h](https://github.com/torvalds/linux/blob/master/include/linux/fb.h)
  - [uapi/linux/fb.h](https://github.com/torvalds/linux/blob/master/include/uapi/linux/fb.h)

  ## Linux documentation

  - [fb device API](https://github.com/torvalds/linux/blob/master/Documentation/fb/api.rst)
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

  @doc """
  Opens a framebuffer device and returns an `:ok` tuple with a `t:Framebuffer.t/0`
  including fixed and variable device information and a reference to an open
  file descriptor. This file descriptor is kept open for the lifetime of the
  reference.

  ## Arguments

  | parameter | required | default  |
  | --------- | -------- | -------- |
  | device    | false    | /dev/fb0 |
  """
  @spec open(device_t()) :: {:ok, Framebuffer.t()} | {:error, term()}
  def open(device \\ "/dev/fb0"), do: Framebuffer.NIF.open(device)

  @doc """
  Optimistic version of `open/1`. Raises on any error.
  """
  @spec open!(device_t()) :: Framebuffer.t() | no_return()
  def open!(device \\ "/dev/fb0") do
    case Framebuffer.NIF.open(device) do
      {:ok, framebuffer} -> framebuffer
      {:error, error} -> raise(error)
    end
  end

  @doc """
  Given an open framebuffer, refresh its fixed and variable device information.

  ## Arguments

  | parameter   | required | default |
  | ----------- | -------- | ------- |
  | framebuffer | true     |         |
  """
  @spec info(Framebuffer.t()) :: {:ok, Framebuffer.t()} | {:error, term()}
  def info(framebuffer), do: Framebuffer.NIF.info(framebuffer)

  @spec info!(Framebuffer.t()) :: Framebuffer.t() | no_return()
  def info!(framebuffer) do
    case Framebuffer.NIF.info(framebuffer) do
      {:ok, framebuffer} -> framebuffer
      {:error, error} -> raise(error)
    end
  end

  defimpl String.Chars do
    def to_string(framebuffer) do
      var = framebuffer.var_screeninfo

      """
      mode "#{var.xres}x#{var.yres}"
          geometry #{var.xres} #{var.yres} #{var.xres_virtual} #{var.yres_virtual} #{var.bits_per_pixel}
          timings #{var.pixclock} #{var.left_margin} #{var.right_margin} #{var.upper_margin} #{var.lower_margin} #{var.hsync_len} #{var.vsync_len}
          nonstd #{var.nonstd}
          rgba #{var.red},#{var.green},#{var.blue},#{var.transp}
      endmode
      """
    end
  end
end
