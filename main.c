#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./core.h"
#include "./core_pthread.h"
#include "./utils.h"

#define BUF_SIZE 104857600UL
#define ARR_SIZE BUF_SIZE

int main() {
    char* text = calloc(sizeof(char), BUF_SIZE);

    get_random_str(text, BUF_SIZE, ARR_SIZE);
    printf("Случайная строка была успешно сгенерирована.\n");

    clock_t start, stop;

    start = clock(); // НАЧАЛО ОТСЧЕТА
    char* out = NULL;
    out = fsrc(text, ARR_SIZE);
    stop = clock(); // КОНЕЦ ОТСЧЕТА
    print_string(out);
    printf("Послед. время работы: %ld мсек.\n", (stop-start)/(CLOCKS_PER_SEC/1000));

    /*
    struct timespec begin, end;
    clock_gettime(CLOCK_MONOTONIC, &begin);; // НАЧАЛО ОТСЧЕТА
    out = lsrc_pthread(text, ARR_SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end); // КОНЕЦ ОТСЧЕТА
    print_string(out);
    printf("Паралл. время работы: %ld.%.9ld с.\n", (end.tv_sec-begin.tv_sec), (end.tv_nsec-begin.tv_nsec));
    */

    free(out);
    free(text);
}