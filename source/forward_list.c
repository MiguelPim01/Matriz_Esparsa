#include <stdio.h>
#include <stdlib.h>

#include "../headers/forward_list.h"

struct ForwardList {
    Node *head;
    int size;
};

struct ForwardListIterator {
    Node *current;
};


ForwardList *forward_list_construct()
{
    ForwardList *l = (ForwardList *)malloc(sizeof(ForwardList));

    l->head = NULL;
    l->size = 0;

    return l;
}

void forward_list_destroy(ForwardList *l, int path)
{
    ForwardListIterator *it = forward_list_front_iterator(l);
    Node *n;

    if (path == PATH_COL)
    {
        forward_list_iterator_destroy(it);
        free(l);
        return;
    }

    while (!forward_list_iterator_is_over(it))
    {
        n = it->current;
        forward_list_next(it, path);
        node_destroy(n);

        l->head = it->current;
    }

    forward_list_iterator_destroy(it);
    free(l);
}


ForwardListIterator *forward_list_front_iterator(ForwardList *l)
{
    ForwardListIterator *it = (ForwardListIterator *)malloc(sizeof(ForwardListIterator));

    it->current = l->head;

    return it;
}

data_type *forward_list_next(ForwardListIterator *it, int path)
{
    data_type *data = node_value(it->current);

    it->current = node_next(it->current, path);

    return data;
}

int forward_list_iterator_is_over(ForwardListIterator *it)
{
    if (it->current == NULL)
        return 1;
    
    return 0;
}

void forward_list_iterator_destroy(ForwardListIterator *it)
{
    free(it);
}