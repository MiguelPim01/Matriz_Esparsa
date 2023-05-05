#include "../headers/node.h"
#include "../headers/data_type.h"

struct Node {
    data_type *data;
    Node *next_lin;
    Node *next_col;
};