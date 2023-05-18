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


// O(1): Aloca espaço para uma forward_list e faz atribuições
ForwardList *forward_list_construct()
{
    ForwardList *l = (ForwardList *)malloc(sizeof(ForwardList));

    l->head = NULL;
    l->size = 0;

    return l;
}

// O(n): Itera sobre uma forward_list printando cada valor contido nos nodes
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

// O(n): Itera sobre a forward_list até a posição de inserção do node
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

// O(1): Faz uso de uma função O(1) e realiza atribuições
void forward_list_push_front(ForwardList *l, Node *n, int path)
{
    n = node_set_next(n, l->head, path);

    l->head = n;
    l->size++;
}

// O(n): Itera sobre a lista até achar a posição de inserção
int forward_list_insertion_index(ForwardList *l, int i, int path)
{
    ForwardListIterator *it = forward_list_front_iterator(l);
    data_type *data;
    int index = 0;

    while (!forward_list_iterator_is_over(it))
    {
        data = forward_list_iterator_next(it, path);

        if (path == PATH_LIN)
        {
            if (data_type_col(data) >= i)
            {
                forward_list_iterator_destroy(it);
                return index;
            }
        }
        else 
        {
            if (data_type_lin(data) >= i)
            {
                forward_list_iterator_destroy(it);
                return index;
            }
        }

        index++;
    }
    forward_list_iterator_destroy(it);

    return index;
}

// O(n): Itera sobre a lista até achar o data_type desejado
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

// O(n): No pior dos casos irá iterar sobre duas forward_lists separadamente
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

// O(n): Itera sobre todos os nodes atribuindo novos valores
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

// O(n): Itera sobre todos os nodes alternando seus ponteiros de next
void forward_list_swap_nodes(ForwardList *l)
{
    ForwardListIterator *it = forward_list_front_iterator(l);

    while (!forward_list_iterator_is_over(it))
    {
        node_swap_nexts(it->current);

        forward_list_iterator_next(it, PATH_LIN);
    }
    forward_list_iterator_destroy(it);
}

// O(n): Itera sobre todos os nodes da lista somando seus valores
float forward_list_add_all(ForwardList *l)
{
    ForwardListIterator *it = forward_list_front_iterator(l);
    data_type *data;
    float value = 0;

    while (!forward_list_iterator_is_over(it))
    {
        data = forward_list_iterator_next(it, PATH_LIN);

        value += data_type_value(data);
    }
    forward_list_iterator_destroy(it);

    return value;
}

// O(1): Apenas retorna um valor
Node *forward_list_head(ForwardList *l)
{
    return l->head;
}

// O(n): Itera sobre os nodes da forward_list salvando em binario as informações dos nodes. Obs: data_type_save_bin é O(1)
void forward_list_save_bin(ForwardList *l, FILE *pFile)
{
    fwrite(&l->size, sizeof(int), 1, pFile);

    ForwardListIterator *it = forward_list_front_iterator(l);
    data_type *data;

    while(!forward_list_iterator_is_over(it))
    {
        data = forward_list_iterator_next(it, PATH_LIN);

        data_type_save_bin(data, pFile);
    }
    forward_list_iterator_destroy(it);
}

// O(n): Itera sobre cada elemento destruindo todos os nodes
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

// O(1): Cria 1 iterador de forward_list e faz uma atribuição
ForwardListIterator *forward_list_front_iterator(ForwardList *l)
{
    ForwardListIterator *it = (ForwardListIterator *)malloc(sizeof(ForwardListIterator));

    it->current = l->head;

    return it;
}

// O(1): Faz uso apenas de funções O(1) e realiza atribuições
data_type *forward_list_iterator_next(ForwardListIterator *it, int path)
{
    data_type *data = node_value(it->current);

    it->current = node_next(it->current, path);

    return data;
}

// O(1): Realiza apenas uma verificação
int forward_list_iterator_is_over(ForwardListIterator *it)
{
    if (it->current == NULL)
        return 1;
    
    return 0;
}

Node *forward_list_iterator_current(ForwardListIterator *it)
{
    return it->current;
}

// O(1): Da free() em um ponteiro
void forward_list_iterator_destroy(ForwardListIterator *it)
{
    free(it);
}