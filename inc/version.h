#ifndef VERSION_H
#define VERSION_H

#ifdef __cplusplus //let's make this callable from c++
extern "C" {
#endif

//c std lib
#include <stdio.h>

//homebrew
#include "dbg.h"

#define VER_MAJOR 0
#define VER_MINOR 0
#define VER_PATCH 0

enum {
    VER_TYPE_DEV = 0,
    VER_TYPE_ALPHA,
    VER_TYPE_BETA,
    VER_TYPE_REL
};

#define VER_TYPE VER_TYPE_DEV

int make_ver_str(char *_buf, int _max_len);

#ifdef __cplusplus //end of the extern "c" block
}
#endif

#endif //define VERSION_H
