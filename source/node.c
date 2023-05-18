#include <stdio.h>
#include <stdlib.h>

#include "../headers/node.h"

struct Node {
    data_type *data;
    Node *next_lin;
    Node *next_col;
};

// O(1): Apenas aloca espaço para um node e faz atribuições
Node *node_construct(data_type *d, Node *next_lin, Node *next_col)
{
    Node *n = (Node *)malloc(sizeof(Node));

    n->data = d;
    n->next_lin = next_lin;
    n->next_col = next_col;

    return n;
}

// O(1): Faz apenas atribuições simples
Node *node_set_next(Node *n, Node *next, int path)
{
    if (path == PATH_LIN)
        n->next_lin = next;
    else
        n->next_col = next;
    
    return n;
}

// O(1): Acessa o conteudo da struct node e retorna
Node *node_next(Node *n, int path)
{
    if (path == PATH_LIN)
        return n->next_lin;
    
    return n->next_col;
}

// O(1): Libera o espaço na memoria de data_type que é uma função O(1) e da free no ponteiro de n
data_type *node_value(Node *n)
{
    if (n == NULL)
        return NULL;
    return n->data;
}

// O(1): Realiza atribuições e utiliza uma funcao que é O(1)
void node_swap_nexts(Node *n)
{
    Node *n_aux = n->next_lin;
    n->next_lin = n->next_col;
    n->next_col = n_aux;

    data_type_swap_position(n->data);
}

// O(1): Libera o espaço na memoria de data_type que é uma função O(1) e da free no ponteiro de n
void node_destroy(Node *n)
{
    data_type_destroy(n->data);
    free(n);
}