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
  @type pixel_t() :: {x(), y(), color()}

  @type x() :: non_neg_integer()
  @type y() :: non_neg_integer()

  @typedoc "Color: {red, green, blue}"
  @type color() :: {non_neg_integer(), non_neg_integer(), non_neg_integer()}

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

  @spec put_pixel(Framebuffer.t(), x(), y(), color()) :: :ok | {:error, term()}
  def put_pixel(framebuffer, x, y, color) do
    cond do
      x >= framebuffer.var_screeninfo.xres ->
        {:error, "out of bounds"}

      y >= framebuffer.var_screeninfo.yres ->
        {:error, "out of bounds"}

      true ->
        line_length = framebuffer.fix_screeninfo.line_length
        bytes_per_pixel = trunc(framebuffer.var_screeninfo.bits_per_pixel / 8)
        offset = x * bytes_per_pixel + y * line_length
        Framebuffer.NIF.put_pixel(framebuffer, offset, color)
    end
  end

  @spec clear(Framebuffer.t()) :: {:ok, Framebuffer.t()}
  def clear(framebuffer) do
    framebuffer
    |> to_stream()
    |> Stream.each(fn pixel_offset ->
      :ok = Framebuffer.NIF.put_pixel(framebuffer, pixel_offset, {0, 0, 0})
    end)
    |> Stream.run()

    {:ok, framebuffer}
  end

  @spec rand(Framebuffer.t()) :: {:ok, Framebuffer.t()}
  def rand(framebuffer) do
    framebuffer
    |> to_stream()
    |> Stream.each(fn pixel_offset ->
      color = {:rand.uniform(256) - 1, :rand.uniform(256) - 1, :rand.uniform(256) - 1}
      :ok = Framebuffer.NIF.put_pixel(framebuffer, pixel_offset, color)
    end)
    |> Stream.run()

    {:ok, framebuffer}
  end

  defp to_stream(framebuffer) do
    bytes_per_pixel = trunc(framebuffer.var_screeninfo.bits_per_pixel / 8)

    Stream.unfold(
      0,
      fn prev ->
        next = prev + bytes_per_pixel

        if next > framebuffer.fix_screeninfo.smem_len,
          do: nil,
          else: {prev, next}
      end
    )
  end
end
