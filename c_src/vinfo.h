#include <erl_nif.h>
#include <string.h>
#include <linux/fb.h>

#include "utils.h"

int vinfo_to_struct(ErlNifEnv* env, struct fb_var_screeninfo vinfo, ERL_NIF_TERM* var_screeninfo);
