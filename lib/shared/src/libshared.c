#include "count.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    char* str;
    int start;
    int end;
    all_series* alls;
    int i;
} thread_args;

long get_cores() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

void* handle_count(void* args) {
    thread_args* arguments = (thread_args*)args;
    char* str = arguments->str;
    int start = arguments->start;
    int end = arguments->end;
    char* chunk = str;
    int chunk_size = end - start;
    all_series* all = get_all(chunk, chunk_size);
    if (all == NULL) {
        return (void*)1;
    }
    arguments->alls[arguments->i] = *all;
    return (void*)0;
}

all_series* get_all_pthread(char* str, int size) {

    const int n_cores = (const int)get_cores();
    if (n_cores <= 0) return NULL;

    int chunk_size = size/n_cores;
    int thread_rs[n_cores];

    thread_args* args = calloc(sizeof(thread_args), n_cores);
    pthread_t thread_ids[n_cores];
    int (*rs)[2] = (int(*)[2])calloc(n_cores, sizeof(int[2]));

    if (!rs || !args) {
        if (rs) free(rs);
        if (args) free(args);
        return NULL;
    }

    all_series* alls = (all_series*)calloc(sizeof(all_series), n_cores);
    if (!alls) {
        return NULL;
    }

    int start; int end;

    for (int i = 0; i < n_cores; i++) {
        start = chunk_size * i;
        if (i == n_cores - 1)
            end = size;
        else
            end = start + chunk_size;
        thread_args arg = {str, start, end, alls, i};
        args[i] = arg;
        pthread_create(&thread_ids[i], NULL, handle_count, (void*)&args[i]);
    }

    bool cleanup = false;
    for (int i = 0; i < n_cores; i++) {
        pthread_join(thread_ids[i], (void*)&thread_rs[i]);
        if (thread_rs[i] == 1) cleanup = true;
    }

    if (cleanup) {
        for (int i = 0; i < n_cores; i++) {
            if (thread_rs[i] != 1) {
                free(alls[i].arr);
            }
        }
        free(alls);
        return NULL;
    }

    int total_size = 0;
    for (int i = 0; i < n_cores; i++) {
        total_size += alls[i].size;
    }

    all_series* res_all = (all_series*)malloc(sizeof(all_series));
    char_series* res_series = (char_series*)calloc(sizeof(char_series), total_size);

    if (!res_all || !res_series) {
        if (res_all) free(res_all);
        if (res_series) free(res_series);
        return NULL;
    }

    res_all->arr = res_series;
    res_all->bsize = total_size;
    res_all->size = 0;

    if (total_size == n_cores) {
        handle_series(res_all, alls[0].arr[0].length, alls[0].arr[0].cbits, alls[0].arr[0].freq);
        for (int i = 1; i < n_cores; i++) {
            res_all->arr[0].length += alls[i].arr[0].length;
        }
    } else {
        for (int i = 0; i < n_cores; i++) {
            for (int j = 0; j < alls[i].size; j++) {
                handle_series(res_all, alls[i].arr[j].length, alls[i].arr[j].cbits, alls[i].arr[j].freq);
            }
        }
    }

    return res_all;
}

char* most_frequent(char* str, int size) {
    if (str == NULL) return NULL;

    all_series* all = get_all_pthread(str, size);

    if (all == NULL) {
        return NULL;
    }

    char_series* most_freq_series = mfrcs(all);

    if (most_freq_series == NULL) {
        return NULL;
    }

    unsigned int length = most_freq_series->length;
    unsigned int freq = most_freq_series->freq;
    char c = get_char(most_freq_series);

    char* res = (char*)calloc(sizeof(char), 90);

    if (c == '\0')
        sprintf(res, "most frequent series: '%s' x %i   (%i times)\n", "\\0",
                length, freq);
    else
        sprintf(res, "most frequent series: '%c' x %i   (%i times)\n",
                c, length, freq);

    free(all->arr);
    free(all);

    return res;
}
