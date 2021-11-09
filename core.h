#pragma once

struct Node
{
    struct Node* node;
    int pos;
    char* suffix_link;
};
typedef struct Node Node;

Node build_suffix_tree(char* S, int n);