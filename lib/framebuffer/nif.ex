defmodule Framebuffer.NIF do
  @moduledoc false

  @on_load :init
  def init do
    path = Application.app_dir(:framebuffer, "priv/nif") |> String.to_charlist()
    :ok = :erlang.load_nif(path, 0)
  end

  @spec open(Framebuffer.device_t()) :: {:ok, Framebuffer.t()} | {:error, term()}
  def open(_device), do: :erlang.nif_error(:nif_not_loaded)

  @spec info(Framebuffer.t()) :: {:ok, Framebuffer.t()} | {:error, term()}
  def info(_framebuffer), do: :erlang.nif_error(:nif_not_loaded)

  @spec put_pixel(
          Framebuffer.t(),
          non_neg_integer(),
          non_neg_integer(),
          Framebuffer.color()
        ) ::
          :ok | {:error, term()}
  def put_pixel(_framebuffer, _x, _y, _color),
    do: :erlang.nif_error(:nif_not_loaded)
end
