#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include "node.h"

typedef struct ForwardList ForwardList;

typedef struct ForwardListIterator ForwardListIterator;


ForwardList *forward_list_construct();

void forward_list_print_esparso(ForwardList *l);

int forward_list_insertion_index(ForwardList *l, int i, int path);

void forward_list_insert(ForwardList *l, Node *n, int i, int path);

void forward_list_push_front(ForwardList *l, Node *n, int path);

data_type *forward_list_find(ForwardList *l, int col);

data_type *forward_list_pop_index(ForwardList *l_lin, ForwardList *l_col, int i_lin, int i_col);

void forward_list_multiply_escalar(ForwardList *l, float n);

void forward_list_swap_nodes(ForwardList *l);

float forward_list_add_all(ForwardList *l);

Node *forward_list_head(ForwardList *l);

void forward_list_save_bin(ForwardList *l, FILE *pFile);

void forward_list_destroy(ForwardList *l, int path);

ForwardListIterator *forward_list_front_iterator(ForwardList *l);

data_type *forward_list_iterator_next(ForwardListIterator *it, int path);

int forward_list_iterator_is_over(ForwardListIterator *it);

Node *forward_list_iterator_current(ForwardListIterator *it);

void forward_list_iterator_destroy(ForwardListIterator *it);

#endif