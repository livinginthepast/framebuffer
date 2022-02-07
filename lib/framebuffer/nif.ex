defmodule Framebuffer.NIF do
  @on_load :init
  def init do
    path = Application.app_dir(:framebuffer, "priv/nif") |> String.to_charlist()
    :ok = :erlang.load_nif(path, 0)
  end

  def info, do: exit(:nif_not_loaded)
end
