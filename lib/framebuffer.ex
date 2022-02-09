defmodule Framebuffer do
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

  defdelegate open(device \\ "/dev/fb0"), to: Framebuffer.NIF
  defdelegate info(framebuffer), to: Framebuffer.NIF
end
