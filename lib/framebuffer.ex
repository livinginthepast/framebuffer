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
  Given an open framebuffer, refresh its fixed and variable device information.

  ## Arguments

  | parameter   | required | default |
  | ----------- | -------- | ------- |
  | framebuffer | true     |         |
  """
  @spec info(Framebuffer.t()) :: {:ok, Framebuffer.t()} | {:error, term()}
  def info(framebuffer), do: Framebuffer.NIF.info(framebuffer)
end
