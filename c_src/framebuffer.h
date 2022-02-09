#include <erl_nif.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#include "utils.h"
#include "finfo.h"
#include "vinfo.h"


typedef struct {
  int fd;
} FileDescriptor;


ERL_NIF_TERM enif_make_framebuffer(ErlNifEnv* env,
    struct fb_var_screeninfo var_info,
    struct fb_fix_screeninfo fixed_info,
    ERL_NIF_TERM fd);

