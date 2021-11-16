#include "./core.h"

all_series init_all_series(int size) {
    char_series* arr = calloc(sizeof(char_series), size);
    char_series def = {0, '\0', 0};
    for (int i = 0; i < size; i++) {
        arr[i] = def;
    };

    all_series all = {arr, 0, size};
    return all;
}

int set_symbols_bit(unsigned char symbol, unsigned int* symbols) {
    if (symbols == NULL) return -1;
    size_t size = sizeof(int) * CBITS_SIZE;
    unsigned int integer_part = symbol / size;
    unsigned int remainder = symbol - (integer_part * size);

    memset(symbols, 0, size);

    symbols[integer_part] |= 1 << remainder; // что это
    return 0;
}

int find_pos_by_length(all_series* all, int length) {
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

void insert_at_pos(all_series* all, char_series series, int pos) {
    memmove(all+pos+1, all+pos, sizeof(char_series)*(all->size-pos));
    all->arr[pos] = series;
}

void add_to_series(all_series* all, char_series series) {
    int pos = find_pos_by_length(all, series.length);
    if (series.length != all->arr[pos].length) {
        insert_at_pos(all, series, pos);
        all->size++;
    }
}

char* fsrc(char* str, int size) {

    //assert(size > 0);

    all_series all = init_all_series(size);

    char* out;
    if (size == 1) {
        out = (char*)calloc(sizeof(char), 2);
        memcpy(out, str, sizeof(char));
        return out;
    }
    int li = 0; int ri = 1;
    for (; ri < size; ri++) {
        if (str[li] != str[ri]) { // окончание серии повт.символов
            char_series series = {ri-li, str[li], 0};
            int pos = find_series(&all, &series);
            if (series.c != all.arr[pos].c || series.length != all.arr[pos].length) {
                add_to_series(&all, series, pos);
            }
            else {
                all.arr[pos].freq++;
            }
            li = ri;
        }
    }

    int max_r = 0;
    int max_i;

    for (int i = 0; i < all.size; i++) {
        if (all.arr[i].freq > max_r) {
            max_r = all.arr[i].freq;
            max_i = i;
        }
    }

    char c = all.arr[max_i].c;
    int s_size = all.arr[max_i].length;

    free(all.arr);

    out = (char*)calloc(sizeof(char), s_size+1);
    memset(out, c, s_size*sizeof(char));
    out[s_size] = '\0';
    return out;
}