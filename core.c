#include "./core.h"

char* lsrc(char* str, int size) {
    //assert(size > 0);
    char* out;
    if (size == 1) {
        out = (char*)calloc(sizeof(char), 2);
        memcpy(out, str, sizeof(char));
        return out;
    }
    int li = 0; int ri = 1;
    int s_size = 1; int s_start = li;
    for (; ri < size; ri++) {
        if (str[li] != str[ri]) { // окончание серии повт.символов
            if ((ri-li) > s_size) {
                s_size = ri - li;
                s_start = li;
            };
            li = ri;
        }
    }

    out = (char*)calloc(sizeof(char), s_size+1);
    out[s_size] = '\0';
    memcpy(out, str+s_start, sizeof(char)*s_size);
    return out;
}