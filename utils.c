//
// Created by jellybe on 14.11.2021.
//

#include "utils.h"


void get_random_str(char* buffer, int b_size, int size) {
    srand(time(NULL));
    if (size > b_size) size = b_size;
    int lower = 33; int upper = 126;
    for (int i = 0; i < size - 1; i++) {
        buffer[i] = (char)((rand() % (upper - lower + 1)) + lower);
    }
    buffer[size-1] = '\0';
}

void print_string(const char* str) {
    char c = str[0];
    int i = 0;
    while (c != '\0') {
        printf("%c", c);
        i++;
        c = str[i];
    }
    printf("\n");
}

struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}