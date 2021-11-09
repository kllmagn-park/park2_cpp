#pragma once
#include <stdlib.h>

struct NodeList
{
    struct NodeList* parent;
    char c; int count;

};
typedef struct NodeList NodeList;

typedef struct Node
{
    int index, left, right, link;
    NodeList* next;
} Node;

int get_count(NodeList* list, char c);
char** build_suffix_tree(char* S, int n);