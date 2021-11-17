#pragma once

#include <stdlib.h>
#include <stdint.h>
#include "libcount.h"

int init_all_series(all_series* all);
int find_pos_by_length(all_series* all, unsigned int length);
int append_to_series(char_series* series, const unsigned int* cbits, unsigned int freq);
