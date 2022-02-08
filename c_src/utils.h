#include <erl_nif.h>
#include <stdio.h>
#include <string.h>

ERL_NIF_TERM error(ErlNifEnv* env, const char* message);
ERL_NIF_TERM ok(ErlNifEnv* env, ERL_NIF_TERM value);

#define ATOM_ERROR(env) enif_make_atom(env, "error")
#define ATOM_OK(env) enif_make_atom(env, "ok")

