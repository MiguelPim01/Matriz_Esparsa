#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include "node.h"

typedef struct ForwardList ForwardList;

typedef struct ForwardListIterator ForwardListIterator;

ForwardList *forward_list_construct();

void forward_list_destroy(ForwardList *l, int path);

ForwardListIterator *forward_list_front_iterator(ForwardList *l);

data_type *forward_list_next(ForwardListIterator *it, int path);

int forward_list_iterator_is_over(ForwardListIterator *it);

void forward_list_iterator_destroy(ForwardListIterator *it);

#endif