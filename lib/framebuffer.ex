defmodule Framebuffer do
  defdelegate info, to: Framebuffer.NIF
end
