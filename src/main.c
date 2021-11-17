#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "count.h"
#include "../include/utils.h"

#define BUF_SIZE 104857600UL
#define ARR_SIZE BUF_SIZE

void get_random_str(char* buffer, int b_size, int size) {
    srand(time(NULL));
    if (size > b_size) size = b_size;
    int lower = 125; int upper = 126;
    for (int i = 0; i < size - 1; i++) {
        buffer[i] = (char)((rand() % (upper - lower + 1)) + lower);
    }
    buffer[size-1] = '\0';
}

int main() {
    char* text = (char*)calloc(sizeof(char), BUF_SIZE);
    if (text == NULL) return -1;
    get_random_str(text, BUF_SIZE, ARR_SIZE);
    printf("Случайная строка была успешно сгенерирована.\n");
    char* res = most_frequent(text, ARR_SIZE);
    if (res == NULL) {
        free(text);
        printf("result is null\n");
        return -2;
    }
    printf("%s", res);
    free(res);
    free(text);
}