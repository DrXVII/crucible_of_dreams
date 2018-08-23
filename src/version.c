#include "version.h" //header for this implementation file

int make_ver_str(char *_buf, int _max_len)
{
    char spec_str[16] = "";

    if(VER_TYPE == 0) {spec_str[0] = 0;}
    
    switch(VER_TYPE) {
    case 0: spec_str[0] = 0; break;
    case 1: strcpy(spec_str, "-alpha"); break;
    case 2: strcpy(spec_str, "-beta"); break;
    default: strcpy(spec_str, "-unknown"); break;
    }

    int len = snprintf(_buf, _max_len, "v%d.%d.%d%s",
            VER_MAJOR, VER_MINOR, VER_PATCH, spec_str);

    if(len >= _max_len) {
        dbgf(1, "WARNING: "
                "buffer used to store the version string might be too short!");
    }

    dbgf(9, "version: %s\n", _buf);

    return 0;
}
