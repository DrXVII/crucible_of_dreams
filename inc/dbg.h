#include <stdio.h>
#include <stdarg.h>

// make sure we can call this from c++
#ifdef __cplusplus
extern "C" {
#endif //#ifdef __cplusplus

void dbg(const char *_txt);
void dbgf(const char *_txt, ...);

//end of extern "C" block
#ifdef __cplusplus
}
#endif //#ifdef __cplusplus
