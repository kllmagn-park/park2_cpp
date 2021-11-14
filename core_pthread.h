#pragma once

#include <pthread.h>
#include <unistd.h>

#include "core.h"

typedef struct {
    int s_start;
    int s_size;
} substring;

typedef struct {
    const char* str;
    int start;
    int size;
    substring* subs;
    int i;
} thread_args;

char* lsrc_pthread(const char* text, int size);