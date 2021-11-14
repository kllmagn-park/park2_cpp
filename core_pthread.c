#include "core_pthread.h"

const long get_cores() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

void* handle_substr(void* args) {
    struct timespec begin, end;
    thread_args* arguments = (thread_args*)args;
    int size = arguments->size;
    int start = arguments->start;
    substring* subs = arguments->subs;
    int i = arguments->i;
    const char* str = arguments->str;
    int li = start; int ri = start + 1;
    int s_size = 1; int s_start = li;
    clock_gettime(CLOCK_MONOTONIC, &begin);
    for (; ri < start+size; ri++) {
        if (str[li] != str[ri]) { // окончание серии повт.символов
            if ((ri-li) > s_size) {
                s_size = ri - li;
                s_start = li;
            };
            li = ri;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    substring sub = {s_start, s_size};
    subs[i] = sub;
    printf("Поток: %ld.%.9ld с.\n", (end.tv_sec-begin.tv_sec), (end.tv_nsec-begin.tv_nsec));
    return NULL;
}

char* lsrc_pthread(const char* str, int size) {
    //assert(size > 0);

    char* out = NULL;
    if (size == 1) {
        out = (char*)calloc(sizeof(char), 2);
        memcpy(out, str, sizeof(char));
        return out;
    }
    const int n_cores = 10; //(const int)get_cores();
    thread_args* args = calloc(sizeof(thread_args), n_cores);
    substring* subs = calloc(sizeof(substring), n_cores);
    pthread_t thread_ids[n_cores];
    int chunk_size = size/n_cores;
    int start = 0; int end = chunk_size - 1;
    for (int i = 0; i < n_cores; i++) {
        int mid = (i+1)*chunk_size;
        char c1 = str[mid];
        int s = 2;
        char c2 = c1;
        int ind = mid;
        while (c1 == c2) {
            int sign = (int)(((float)(s % 2)-0.5)*2);
            if (mid-s/2 < start) sign = 1;
            ind = mid+sign*s/2;
            c2 = str[ind];
            s++;
        }
        if (i < n_cores - 1) end = ind + 1; else end = size;
        printf("start: %d, end: %d\n", start, end);
        thread_args arg = {str, start, end-start, subs, i};
        pthread_t thread_id;
        args[i] = arg;
        thread_ids[i] = thread_id;
        start = end + 1;
    }
    for (int i = 0; i < n_cores; i++) {
        pthread_create(&thread_ids[i], NULL, handle_substr, (void*)&args[i]);
    }
    for (int i = 0; i < n_cores; i++) {
        pthread_join(thread_ids[i], NULL);
    }
    int s_size = 0;
    int s_start = 0;
    for (int i = 0; i < n_cores; i++) {
        if (subs[i].s_size > s_size) {
            s_size = subs[i].s_size;
            s_start = subs[i].s_start;
        }
    }
    free(subs);
    out = (char*)calloc(sizeof(char), s_size+1);
    out[s_size] = '\0';
    memcpy(out, str+s_start, sizeof(char)*s_size);
    return out;
}