#include <erl_nif.h>
#include <string.h>
#include <linux/fb.h>

#include "utils.h"

ERL_NIF_TERM finfo_to_struct(ErlNifEnv* env, struct fb_fix_screeninfo finfo);
