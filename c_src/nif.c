#include <erl_nif.h>
#include "log.h"

static ERL_NIF_TERM info(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  return enif_make_atom(env, "ok");
}

static ErlNifFunc exports[]= {
  { "info", 0, info }
};

ERL_NIF_INIT(Elixir.Framebuffer.NIF, exports, NULL, NULL, NULL, NULL)
