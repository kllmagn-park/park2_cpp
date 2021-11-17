#include "libcount.h"

int init_all_series(all_series* all) {
    if (all == NULL) return -1;
    if (all->arr == NULL) {
        all->arr = (char_series*)calloc(sizeof(char_series), 8);
        if (all->arr == NULL) return -1;
        all->bsize = 8;
        all->size = 0;
    }
    if (all->size >= all->bsize) return -1;
    if (all->size == all->bsize - 1) {
        char_series* newbuf = (char_series*)realloc(all->arr, sizeof(char_series) * all->bsize*2); // увеличиваем буфер вдвое
        if (newbuf == NULL) {
            return -2;
        }
        all->arr = newbuf;
        all->bsize *= 2;
    }
    return 0;
}

int remove_series(char_series* series) {
    if (series == NULL) return -1;
    series->length = 0;
    series->freq = 0;
    int size = sizeof(series->cbits) / sizeof(series->cbits[0]);
    for (int i = 0; i < size; i++) series->cbits[i] = 0; // зануляем биты
    return 0;
}

int append_to_series(char_series* series, const unsigned int* cbits, unsigned int freq) {
    if (series == NULL) return -1;
    if (cbits == NULL) return -1;
    for (int i = 0; i < CBITS_SIZE; i++) series->cbits[i] |= cbits[i];
    series->freq += freq;
    return 0;
}

int set_char(unsigned char c, unsigned int* cbits) {
    if (cbits == NULL) return -1;
    size_t size = sizeof(int) * CBITS_SIZE;
    unsigned int int_part = c / size;
    unsigned int rem = c - (int_part * size);
    memset(cbits, 0, size);
    cbits[int_part] |= 1 << rem;
    return 0;
}

char get_char(char_series* series) {
    if (series == NULL) return 0;
    unsigned int selected = series->cbits[2];
    for (int i = 'A'; i <= 'Z'; i++) {
        if ((selected >> (i - 64)) & 0x1) return (char)i;
    }
    selected = series->cbits[3];
    for (int i = 'a'; i <= 'z'; i++) {
        if ((selected >> (i - 96)) & 0x1) return (char)i;
    }
    return 0;
}

int find_pos_by_length(all_series* all, unsigned int length) {
    if (all == NULL) return -1;
    if (all->size == 0) return 0;
    int li = 0; int ri = all->size;
    int ind;
    while (li < ri) {
        ind = (li+ri)/2;
        if (all->arr[ind].length < length) {
            li = ind + 1;
        }
        else {
            ri = ind;
        }
    }
    return li;
}

int handle_series(all_series* all, unsigned int length, const unsigned int* cbits, unsigned int freq) {
    if (all == NULL) return -1;
    if (cbits == NULL) return -1;
    int result = init_all_series(all);
    if (result != 0) return result;
    int pos = find_pos_by_length(all, length);
    char_series* selected = &all->arr[pos];
    if (pos >= all->size) {
        remove_series(selected);
        selected->length = length;
        all->size++;
    }
    else if (selected->length != length) {
        size_t move_size = sizeof(char_series) * (all->size - pos);
        memmove(selected+1, selected, move_size);
        remove_series(selected);
        selected->length = length;
        all->size++;
    }
    int res = append_to_series(selected, cbits, freq);
    return res;
}

all_series* get_all(char* str, int size) {
    if ((str == NULL) || (size <= 0)) return NULL;
    all_series* all = (all_series*)malloc(sizeof(all_series));
    if (all == NULL) return NULL;
    all->arr = NULL;
    int s_size;
    unsigned int cbits[8];
    int li = 0;
    for (int ri = 1; ri < size; ri++) {
        if ((str[li] != str[ri]) || (ri == size - 1)) { // окончание серии повт.символов
            s_size = ri - li;
            if (s_size > 1) {
                int res = set_char(str[li], cbits);
                if (res != 0) {
                    free(all->arr); free(all);
                    return NULL;
                }
                res = handle_series(all, s_size, cbits, 1);
                if (res != 0) {
                    free(all->arr); free(all);
                    return NULL;
                }
            }
            li = ri;
        }
    }
    return all;
}

char_series* mfrcs(all_series* all) {
    if (all == NULL) return NULL;
    if (all->size <= 0) return NULL;
    unsigned int max_freq = 0;
    int max_i = 0;
    for (int i = 0; i < all->size; i++) {
        unsigned int freq = all->arr[i].freq;
        if (freq > max_freq) {
            max_freq = freq;
            max_i = i;
        }
    }
    return &all->arr[max_i];
}
