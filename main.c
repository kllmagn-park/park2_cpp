#include <stdio.h>

#include "core.h"

int main()
{
    char* text = calloc(sizeof(char), 10);
    scanf("%s", text);
    char** result = build_suffix_tree(text, 10);
    printf("");
}