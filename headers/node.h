#ifndef NODE_H
#define NODE_H

#include "data_type.h"

#define PATH_LIN 0
#define PATH_COL 1

typedef struct Node Node;

Node *node_next(Node *n, int path);

data_type *node_value(Node *n);

#endif