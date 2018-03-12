#include "dbg.h" //header for this implementation file

void dbg(int _lvl, const char *_txt)
{
    if(_lvl > DEBUG) { return; }

    //generate a time stamp
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    char time_buf[100];
    size_t rc = strftime(time_buf, sizeof time_buf,
            "%Y-%m-%d %T", localtime(&ts.tv_sec));
    snprintf(time_buf + rc, sizeof time_buf - rc, ".%06ld", ts.tv_nsec / 1000);

    fprintf(stderr, "DBG[%s]: %s", time_buf, _txt);
}

void dbgf(int _lvl, const char *_fmt, ...)
{
    if(_lvl > DEBUG) { return; }

    char buf[1024];

    va_list args;
    va_start(args, _fmt);

    vsnprintf(buf, sizeof buf, _fmt, args);
    va_end(args);

    dbg(_lvl, buf);
}

void errlog(int _lib, const char *_txt)
{
    switch (_lib) {
    case ERRLOG_SDL:
        fprintf(stderr, "ERROR: %s SDL error = %s\n",
                _txt, SDL_GetError());
        break;
    case ERRLOG_IMG:
        fprintf(stderr, "ERROR: %s SDL_img error = %s\n",
                _txt, IMG_GetError());
        break;
    case ERRLOG_TTF:
        fprintf(stderr, "ERROR: %s SDL_ttf error = %s\n",
                _txt, TTF_GetError());
        break;
    case ERRLOG_GEN:
    default:
        fprintf(stderr, "ERROR: %s\n", _txt);
        break;
    }
}

void errlogf(int _lib, const char *_fmt, ...)
{
    char buf[2048];

    va_list args;
    va_start(args, _fmt);

    vsnprintf(buf, sizeof buf, _fmt, args);
    va_end(args);

    errlog(_lib, buf);
}
