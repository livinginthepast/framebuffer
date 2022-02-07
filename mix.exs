defmodule Framebuffer.MixProject do
  use Mix.Project

  def project do
    [
      app: :framebuffer,
      compilers: [:elixir_make] ++ Mix.compilers(),
      deps: deps(),
      description: "Interact with Linux framebuffers",
      elixir: "~> 1.12",
      make_targets: ["all"],
      make_clean: ["clean"],
      make_executable: :default,
      make_makefile: "Makefile",
      start_permanent: Mix.env() == :prod,
      version: "0.1.0"
    ]
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      {:credo, "~> 1.6", only: [:dev, :test], runtime: false},
      {:dialyxir, "~> 1.1", only: [:dev, :test], runtime: false},
      {:elixir_make, "~> 0.6", runtime: false}
    ]
  end
end
