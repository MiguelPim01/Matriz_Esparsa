#include <stdio.h>
#include <stdlib.h>

#include "../headers/node.h"

struct Node {
    data_type *data;
    Node *next_lin;
    Node *next_col;
};

Node *node_construct(int lin, int col, float data, Node *next_lin, Node *next_col)
{
    Node *n = (Node *)malloc(sizeof(Node));

    n->data = data_type_construct(lin, col, data);
    n->next_lin = next_lin;
    n->next_col = next_col;

    return n;
}

Node *node_next(Node *n, int path)
{
    if (path == PATH_LIN)
        return n->next_lin;
    
    return n->next_col;
}

data_type *node_value(Node *n)
{
    return n->data;
}

void node_destroy(Node *n)
{
    data_type_destroy(n->data);
    free(n);
}