#pragma once

#include <stdlib.h>
#include <string.h>

#define CBITS_SIZE 8

typedef struct {
    unsigned int length; // длина серии
    unsigned int cbits[CBITS_SIZE]; // подсвеченные биты сериии
    unsigned int freq; // частота появления серии
} char_series; // серии одной длины

typedef struct {
    char_series* arr; // все серии символов
    int size; // текущее количество всех серий
    int bsize; // размер буфера
} all_series;

int remove_series(char_series* series);
int handle_series(all_series* all, unsigned int length, const unsigned int* cbits, unsigned int freq);
int set_char(unsigned char c, unsigned int* cbits);
char get_char(char_series* series);
all_series* get_all(char* str, int size);
char_series* mfrcs(all_series* all);

#define free_all(all) free(all->arr); free(all)
