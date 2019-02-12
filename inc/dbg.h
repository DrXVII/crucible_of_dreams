#ifndef DBG_H
#define DBG_H

//c std lib
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

//third party libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

enum sdl_error_types {
    //general error
    ERRLOG_GEN = 0,
    //defines for sld error reporting
    ERRLOG_SDL,
    ERRLOG_IMG,
    ERRLOG_TTF
};

// make sure we can call this from c++
#ifdef __cplusplus
extern "C" {
#endif //#ifdef __cplusplus

/*_lvl = verbocity level
 * (higher _lvl should be used for less important and/or more frequent spam) */
void dbg(int _lvl, const char *_txt);
void dbgf(int _lvl, const char *_fmt, ...);
void errlog(int _lib, const char *_txt);
void errlogf(int _lib, const char *_fmt, ...);

//end of extern "C" block
#ifdef __cplusplus
}
#endif //#ifdef __cplusplus

#endif //define DBG_H
