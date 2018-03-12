//c std lib
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

//third party libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//general error
#define ERRLOG_GEN 0
//defines for sld error reporting
#define ERRLOG_SDL 1
#define ERRLOG_IMG 2
#define ERRLOG_TTF 3

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
