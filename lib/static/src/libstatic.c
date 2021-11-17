#include "count.h"

char* most_frequent(char* str, int size) {
    if (str == NULL) return NULL;

    all_series* all = get_all(str, size);

    if (all == NULL) {
        return NULL;
    }

    char_series* most_freq_series = mfrcs(all);

    if (most_freq_series == NULL) {
        return NULL;
    }

    int length = most_freq_series->length;
    int freq = most_freq_series->freq;
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