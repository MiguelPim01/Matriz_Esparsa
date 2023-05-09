#include <stdio.h>
#include <stdlib.h>

#include "../headers/matriz.h"

struct Matriz {
    ForwardList **lines;
    ForwardList **columns;
    int qtd_lin;
    int qtd_col;
};


Matriz *matriz_construct(int qtd_lin, int qtd_col)
{
    Matriz *m = (Matriz *)malloc(sizeof(Matriz));
    
    ForwardList **lines = (ForwardList **)calloc(qtd_lin, sizeof(ForwardList *));
    ForwardList **columns = (ForwardList **)calloc(qtd_col, sizeof(ForwardList *));

    m->columns = columns;
    m->lines = lines;
    m->qtd_col = qtd_col;
    m->qtd_lin = qtd_lin;

    for (int i = 0; i < m->qtd_lin; i++)
        m->lines[i] = forward_list_construct();
    for (int i = 0; i < m->qtd_col; i++)
        m->columns[i] = forward_list_construct();

    return m;
}

Matriz *matriz_insert_value(Matriz *m, int lin, int col, float value)
{
    ForwardListIterator *it_lin = forward_list_front_iterator(m->lines[lin]);
    ForwardListIterator *it_col = forward_list_front_iterator(m->columns[col]);
    data_type *data;

    int cont = 0;

    while (!forward_list_iterator_is_over(it_lin))
    {
        data = forward_list_next(it_lin, PATH_LIN);

        if (col == data_type_col(data))
        {
            data_type_set(data, value);
            forward_list_iterator_destroy(it_lin);
            return m;
        }
        else if (col > data_type_col(data))
        {
            break;
        }

        cont++;
    }

    // inserir elemento na matriz

    forward_list_iterator_destroy(it_lin);
    forward_list_iterator_destroy(it_col);
}

void matriz_destroy(Matriz *m)
{
    for (int i = 0; i < m->qtd_lin; i++)
        forward_list_destroy(m->lines[i], PATH_LIN);

    for (int i = 0; i < m->qtd_col; i++)
        forward_list_destroy(m->columns[i], PATH_COL);
    
    free(m->lines);
    free(m->columns);
    free(m);
}