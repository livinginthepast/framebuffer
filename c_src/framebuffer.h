#include <erl_nif.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#include "utils.h"
#include "finfo.h"
#include "vinfo.h"


typedef struct {
  int fd;    // file descriptor to /dev/fbX
  char *fbp; // pointer representing the front buffer
  char *bbp; // pointer representing the back buffer
  unsigned int screensize;
} FrameBuffer;


ERL_NIF_TERM enif_make_framebuffer(ErlNifEnv* env,
    struct fb_var_screeninfo var_info,
    struct fb_fix_screeninfo fixed_info,
    ERL_NIF_TERM fd);

int fb_put_finfo(ErlNifEnv* env, struct fb_fix_screeninfo finfo, ERL_NIF_TERM* framebuffer);
int fb_put_vinfo(ErlNifEnv* env, struct fb_var_screeninfo vinfo, ERL_NIF_TERM* framebuffer);
