//
// Created by jellybe on 14.11.2021.
//

#include "utils.h"

void get_random_str(char* buffer, int b_size, int size) {
    srand(time(NULL));
    if (size + 1 > b_size) size = b_size - 1;
    int lower = 33; int upper = 126;
    for (int i = 0; i < size; i++) {
        buffer[i] = (char)((rand() % (upper - lower + 1)) + lower);
    }
    buffer[size] = '\0';
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