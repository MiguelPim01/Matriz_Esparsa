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

void forward_list_print_esparso(ForwardList *l)
{
    ForwardListIterator *it = forward_list_front_iterator(l);
    data_type *data;

    while (!forward_list_iterator_is_over(it))
    {
        data = forward_list_iterator_next(it, PATH_LIN);

        data_type_print_esparso(data);
        printf("\n");
    }

    forward_list_iterator_destroy(it);
}

void forward_list_insert(ForwardList *l, Node *n, int i, int path)
{
    ForwardListIterator *it = forward_list_front_iterator(l);
    
    if (i == 0) // inicio da lista
    {
        forward_list_push_front(l, n, path);
    }
    else 
    {
        for (int q = 0; q < i-1; q++)
            forward_list_iterator_next(it, path);
        

        n = node_set_next(n, node_next(it->current, path), path);
        it->current = node_set_next(it->current, n, path);

        l->size++;
    }

    forward_list_iterator_destroy(it);
}

void forward_list_push_front(ForwardList *l, Node *n, int path)
{
    n = node_set_next(n, l->head, path);

    l->head = n;
    l->size++;
}

int forward_list_insertion_index(ForwardList *l, int i, int path)
{
    ForwardListIterator *it = forward_list_front_iterator(l);
    data_type *data;
    int index = 0;

    while (!forward_list_iterator_is_over(it))
    {
        data = forward_list_iterator_next(it, path);

        if (data_type_col(data) >= i)
        {
            forward_list_iterator_destroy(it);
            return index;
        }

        index++;
    }
    forward_list_iterator_destroy(it);

    return index;
}

data_type *forward_list_find(ForwardList *l, int col)
{
    ForwardListIterator *it = forward_list_front_iterator(l);
    data_type *data;

    while (!forward_list_iterator_is_over(it))
    {
        data = forward_list_iterator_next(it, PATH_LIN);

        if (data_type_col(data) == col)
        {
            forward_list_iterator_destroy(it);
            return data;
        }
    }
    forward_list_iterator_destroy(it);

    return NULL;
}

data_type *forward_list_pop_index(ForwardList *l_lin, ForwardList *l_col, int i_lin, int i_col)
{
    ForwardListIterator *it_lin = forward_list_front_iterator(l_lin), *it_col = forward_list_front_iterator(l_col);
    data_type *data;
    Node *n;
    
    if (i_lin == 0 || i_col == 0) // algum dos dois sera pop_front
    {
        if (!i_lin && i_col) // indice da linha é zero mas coluna nao
        {
            for (int q = 0; q < i_col-1; q++)
                forward_list_iterator_next(it_col, PATH_COL);
            
            n = l_lin->head;

            it_col->current = node_set_next(it_col->current, node_next(n, PATH_COL), PATH_COL);
            l_lin->head = node_next(n, PATH_LIN);
        }
        else if (i_lin && !i_col) // indice da coluna é zero mas linha nao
        {
            for (int q = 0; q < i_lin-1; q++)
                forward_list_iterator_next(it_lin, PATH_LIN);
            
            n = l_col->head;

            it_lin->current = node_set_next(it_lin->current, node_next(n, PATH_LIN), PATH_LIN);
            l_col->head = node_next(n, PATH_COL);
        }
        else // indice de ambos é zero
        {
            n = l_lin->head;

            l_lin->head = node_next(n, PATH_LIN);
            l_col->head = node_next(n, PATH_COL);
        }
    }
    else
    {
        for (int q = 0; q < i_col-1; q++)
            forward_list_iterator_next(it_col, PATH_COL);

        for (int q = 0; q < i_lin-1; q++)
            forward_list_iterator_next(it_lin, PATH_LIN);
        
        n = node_next(it_lin->current, PATH_LIN);

        it_lin->current = node_set_next(it_lin->current, node_next(n, PATH_LIN), PATH_LIN);
        it_col->current = node_set_next(it_col->current, node_next(n, PATH_COL), PATH_COL);
    }
    forward_list_iterator_destroy(it_lin);
    forward_list_iterator_destroy(it_col);

    data = node_value(n);
    node_destroy(n);

    l_col->size--;
    l_lin->size--;

    return data;
}

void forward_list_multiply_escalar(ForwardList *l, float n)
{
    ForwardListIterator *it = forward_list_front_iterator(l);
    data_type *data;

    while (!forward_list_iterator_is_over(it))
    {
        data = forward_list_iterator_next(it, PATH_LIN);

        data_type_atribui_value(data, data_type_value(data)*n);
    }
    forward_list_iterator_destroy(it);
}

Node *forward_list_head(ForwardList *l)
{
    return l->head;
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
        forward_list_iterator_next(it, path);
        node_destroy(n);

        l->head = it->current;
    }

    forward_list_iterator_destroy(it);
    free(l);
}

// =========== ITERADOR PARA LISTAS ENCADEADAS ===========

ForwardListIterator *forward_list_front_iterator(ForwardList *l)
{
    ForwardListIterator *it = (ForwardListIterator *)malloc(sizeof(ForwardListIterator));

    it->current = l->head;

    return it;
}

data_type *forward_list_iterator_next(ForwardListIterator *it, int path)
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