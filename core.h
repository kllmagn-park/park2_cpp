#pragma once

#include <stdlib.h>
#include <string.h>

#define N_SYMBOLS 256
#define CBITS_SIZE 8

typedef struct {
    unsigned int length; // длина серии
    unsigned int cbits[CBITS_SIZE]; // подсвеченные биты сериии
    int freq; // частота появления серии
} char_series; // серии одной длины

typedef struct {
    char_series* arr; // все серии символов
    int size; // текущее количество всех серий
    int bsize; // размер буфера
} all_series;

char* fsrc(char* str, int size);