#include "./core.h"

#include <string.h>

int current_ind;

NodeList form_default()
{
    char* chars = "ACGT$";
    NodeList* list = (NodeList*)malloc(sizeof(NodeList));
    for (int i = 0; i < 5; i++)
    {
        list->c = chars[i];
        list->count = -1;
        NodeList* nl = NULL;
        if (i != 4) nl = (NodeList*)malloc(sizeof(NodeList));
        list->parent = nl;
        list = nl;
    }
    return *list;
};

int get_count(NodeList* list, char c)
{
    while (list != NULL)
    {
        if (list->c == c) return list->count;
        list = list->parent;
    }
    return -2;
}

NodeList* set_count(NodeList* list, char c, int count)
{
    NodeList* root = list;
    while (list != NULL)
    {
      if (list->c == c){
          list->count = count;
          return root;
      }
      list = list->parent;
    }

    NodeList* list_new = (NodeList*)malloc(sizeof(NodeList));
    list_new->c = c; list_new->count = count;
    list_new->parent = list;
    return list_new;
}

int node_length(Node node)
{
    int a;
    if (node.right < current_ind)
        a = node.right;
    else
        a = current_ind;
    return a - node.left;
}

char** build_suffix_tree(char* S, int n)
{
    current_ind = -1;
    Node* suffix_tree = (Node*)calloc(sizeof(Node), n*2+2);
    int node_count = 1;
    Node root;
    NodeList* next_default = form_default();
    root.index = 0; root.left = -1; root.right = -1;
    root.next = next_default;
    root.link = 0;
    suffix_tree[0] = root;

    Node active_node = root;
    int active_edge_index = -1;
    char active_edge_char = '\0';
    int active_length = 0;

    int remainder = 0;

    for (int i = 0; i < n; i++)
    {
        current_ind = i + 1;
        char char_to_insert = S[i];
        remainder++;
        if (remainder == 1)
        {
            active_edge_index = i;
            active_edge_char = char_to_insert;
            if (active_length < 0)
            {
                active_length = 0;
            }
        }

        int prev_split_node_index = -1;
        while (remainder > 0)
        {
            if (get_count(active_node.next, active_edge_char) == -1)
            {
                Node node = {node_count, active_edge_index, n, 0, next_default};
                suffix_tree[node_count] = node;
                node.next = set_count(node.next, active_edge_char, node_count);

                if (prev_split_node_index != -1)
                    suffix_tree[prev_split_node_index].link = active_node.index;
                prev_split_node_index = node_count;
                node_count++;

                remainder--;

                if (active_node.index == 0)
                {
                    active_edge_index ++;
                    if (active_edge_index < n)
                        active_edge_char = S[active_edge_index];
                    active_length--;
                }
                else
                    active_node = suffix_tree[active_node.index];
                continue;
            }

            Node split_node = suffix_tree[get_count(active_node.next, active_edge_char)];
            if (active_length >= node_length(split_node))
            {
                active_node = split_node;
                active_length -= node_length(active_node);
                active_edge_index += node_length(active_node);
                active_edge_char = S[active_edge_index];
                continue;
            }

            if (S[split_node.left + active_length] == char_to_insert)
            {
                active_length++;
                if (prev_split_node_index != -1)
                    suffix_tree[prev_split_node_index].link = active_node.index;
                break;
            }

            Node node = {node_count, split_node.left, split_node.left + active_length, 0, next_default};
            suffix_tree[node_count] = node;
            Node mid_node = suffix_tree[node_count];
            node_count++;
            Node node2 = {node_count, i, n, 0, next_default};
            suffix_tree[node_count] = node2;
            set_count(mid_node.next, char_to_insert, node_count);
            node_count--;
            split_node.left += active_length;
            set_count(mid_node.next, S[split_node.left], split_node.index);

            remainder--;

            if (prev_split_node_index != -1)
                suffix_tree[prev_split_node_index].link = mid_node.index;
            prev_split_node_index = mid_node.index;

            if (active_node.index == 0)
            {
                active_edge_index++;
                if (active_edge_index < n)
                    active_edge_char = S[active_edge_index];
                active_length--;
            }
            else
                active_node = suffix_tree[active_node.link];
        }
    }

    char** edges = (char**)calloc(sizeof(char*), node_count-1);
    for (int i = 1; i < node_count; i++)
    {
        Node current_node = suffix_tree[i];
        char* subs = (char*)calloc(sizeof(char), current_node.right-current_node.left);
        memcpy(subs, S+current_node.left, current_node.right-current_node.left);
        edges[i] = subs;
    }
    return edges;
}