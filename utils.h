#pragma once

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void get_random_str(char* buffer, int b_size, int size);
void print_string(const char* str);
struct timespec diff(struct timespec start, struct timespec end);