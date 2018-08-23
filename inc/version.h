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
#define VER_MINOR 1
#define VER_PATCH 1

#define VER_TYPE_REL 0
#define VER_TYPE_ALPHA 1
#define VER_TYPE_BETA 2
#define VER_TYPE VER_TYPE_ALPHA

int make_ver_str(char *_buf, int _max_len);

#ifdef __cplusplus //end of the extern "c" block
}
#endif

#endif //define VERSION_H
