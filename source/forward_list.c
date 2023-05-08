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


void forward_list_destroy(ForwardList *l)
{
    ForwardListIterator *it = forward_list_front_iterator(l);

    while (!forward_list_iterator_is_over(it))
    {
        

        forward_list_next(it, PATH_LIN);
    }
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