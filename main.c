#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./core.h"
#include "./core_pthread.h"
#include "./utils.h"

#define KILO 1024
#define MEGA (KILO*KILO)
#define INCREMENT 800

int main() {
    int size = INCREMENT*MEGA/sizeof(char); // размер строки в 100 Мб
    char* text = calloc(sizeof(char), size);

    get_random_str(text, INCREMENT*MEGA/sizeof(char), size-1);
    printf("Случайная строка была успешно сгенерирована.\n");

    clock_t start, stop;

    start = clock(); // НАЧАЛО ОТСЧЕТА
    char* out = NULL;
    out = lsrc(text, size);
    stop = clock(); // КОНЕЦ ОТСЧЕТА
    print_string(out);
    printf("Послед. время работы: %ld мсек.\n", (stop-start)/(CLOCKS_PER_SEC/1000));

    struct timespec begin, end;
    clock_gettime(CLOCK_MONOTONIC, &begin);; // НАЧАЛО ОТСЧЕТА
    out = lsrc_pthread(text, size);
    clock_gettime(CLOCK_MONOTONIC, &end); // КОНЕЦ ОТСЧЕТА
    print_string(out);
    printf("Паралл. время работы: %ld.%.9ld с.\n", (end.tv_sec-begin.tv_sec), (end.tv_nsec-begin.tv_nsec));
    free(out);
    free(text);
}