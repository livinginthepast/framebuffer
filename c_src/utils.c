#include "utils.h"

ERL_NIF_TERM error(ErlNifEnv* env, const char* message) {
  ErlNifBinary error;
  enif_alloc_binary(strlen(message), &error);
  memcpy(error.data, message, strlen(message));
  ERL_NIF_TERM err = enif_make_binary(env, &error);

  return enif_make_tuple2(env, ATOM_ERROR(env), err);
}

ERL_NIF_TERM ok(ErlNifEnv* env, ERL_NIF_TERM value) {
  return enif_make_tuple2(env, ATOM_OK(env), value);
}

