#include <stdio.h>
#include <stdlib.h>

#include "../headers/node.h"

struct Node {
    data_type *data;
    Node *next_lin;
    Node *next_col;
};

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