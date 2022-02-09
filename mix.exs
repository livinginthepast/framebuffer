defmodule Framebuffer.MixProject do
  @moduledoc false
  use Mix.Project

  @github_url "https://github.com/livinginthepast/framebuffer"
  @version "0.0.1"

  def project do
    [
      app: :framebuffer,
      compilers: [:elixir_make] ++ Mix.compilers(),
      deps: deps(),
      description: "Interact with Linux framebuffers",
      elixir: "~> 1.12",
      homepage_url: @github_url,
      make_targets: ["all"],
      make_clean: ["clean"],
      make_executable: :default,
      make_makefile: "Makefile",
      package: package(),
      preferred_cli_env: [credo: :test, dialyzer: :test, docs: :doc],
      source_url: @github_url,
      start_permanent: Mix.env() == :prod,
      version: @version
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
      {:elixir_make, "~> 0.6", runtime: false},
      {:ex_doc, "~> 0.28", only: [:dev, :doc], runtime: false}
    ]
  end

  defp package do
    [
      files: [
        ".formatter.exs",
        "LICENSE.md",
        "Makefile",
        "README.md",
        "c_src",
        "lib",
        "mix.exs"
      ],
      licenses: ["MIT"],
      links: %{
        "GitHub" => @github_url
      },
      maintainers: ["Eric Saxby"]
    ]
  end
end
