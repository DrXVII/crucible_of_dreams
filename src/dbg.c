#include "dbg.h" //header for this implementation file

void dbg(const char *_txt)
{
    fprintf(stderr, "DBG: %s", _txt);
}

//TODO probs just format the sring and give to dbg()
void dbgf(const char *_fmt, ...)
{
    va_list args;
    va_start(args, _fmt);

    fprintf(stderr, "DBG: ");
    vfprintf(stderr, _fmt, args);
    va_end(args);
}
