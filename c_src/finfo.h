#include <erl_nif.h>
#include <string.h>
#include <linux/fb.h>

#include "utils.h"

int finfo_to_struct(ErlNifEnv* env, struct fb_fix_screeninfo finfo, ERL_NIF_TERM* fix_screeninfo);
