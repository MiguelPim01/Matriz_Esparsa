#include <stdio.h>
#include <stdlib.h>

#include "../headers/matriz.h"

struct Matriz {
    ForwardList **lines;
    ForwardList **columns;
    int qtd_lin;
    int qtd_col;
};

struct MatrizIterator {
    ForwardList *current_lin;
    ForwardList *current_col;
    int lin;
    int col;
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

void matriz_print_esparso(Matriz *m)
{
    MatrizIterator *it = matriz_iterator_create(m);

    while (!matriz_iterator_line_is_over(it))
    {
        forward_list_print_esparso(it->current_lin);

        matriz_iterator_next_line(it, m);
    }

    matriz_iterator_destroy(it);
}

Matriz *matriz_atribuir(Matriz *m, int lin, int col, float value)
{
    data_type *data = matriz_find_position(m, lin, col);
    int ind_lin, ind_col;

    if (lin > m->qtd_lin || lin <= 0 || col <= 0 || col > m->qtd_col)
    {
        printf("Erro: Indice nao existe na matriz\n");
        return m;
    }

    if (data == NULL)
    {
        data = data_type_construct(lin, col, value);
        Node *n = node_construct(data, NULL, NULL);
        

        ind_lin = forward_list_insertion_index(m->lines[lin-1], col, PATH_LIN);
        ind_col = forward_list_insertion_index(m->columns[col-1], lin, PATH_COL);

        forward_list_insert(m->lines[lin-1], n, ind_lin, PATH_LIN);
        forward_list_insert(m->columns[col-1], n, ind_col, PATH_COL);
    }
    else
    {
        data_type_atribui_value(data, value);
    }

    return m;
}

float matriz_read_value(Matriz *m, int lin, int col)
{
    if (lin > m->qtd_lin || lin <= 0 || col <= 0 || col > m->qtd_col)
    {
        printf("Erro: Indice nao existe na matriz\n");
        return -1;
    }

    data_type *data = matriz_find_position(m, lin, col);

    if (data == NULL)
        return 0;
    else
        return data_type_value(data);
}

void matriz_print_denso(Matriz *m)
{
    for (int i = 1; i <= m->qtd_lin; i++)
    {
        for (int j = 1; j <= m->qtd_col; j++)
        {
            printf("%.0f  ", matriz_read_value(m, i, j));
        }
        printf("\n");
    }
}

data_type *matriz_find_position(Matriz *m, int lin, int col)
{
    data_type *data = forward_list_find(m->lines[lin-1], col);

    return data;
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

// =========== ITERADOR PARA MATRIZES ===========

MatrizIterator *matriz_iterator_create(Matriz *m)
{
    MatrizIterator *it = (MatrizIterator *)malloc(sizeof(MatrizIterator));

    it->current_lin = m->lines[0];
    it->current_col = m->columns[0];
    it->lin = 0;
    it->col = 0;

    return it;
}

Node *matriz_iterator_next_line(MatrizIterator *it, Matriz *m)
{
    Node *n = forward_list_head(it->current_lin);

    it->lin++;
    if (it->lin + 1 > m->qtd_lin)
    {
        it->current_lin = NULL;
        return n;
    }

    it->current_lin = m->lines[it->lin];

    return n;
}

Node *matriz_iterator_next_col(MatrizIterator *it, Matriz *m)
{
    Node *n = forward_list_head(it->current_col);

    it->col++;
    if (it->col + 1 > m->qtd_col)
    {
        it->current_col = NULL;
        return n;
    }

    it->current_col = m->columns[it->col];

    return n;
}

int matriz_iterator_line_is_over(MatrizIterator *it)
{
    if (it->current_lin == NULL)
        return 1;
    
    return 0;
}

int matriz_iterator_col_is_over(MatrizIterator *it)
{
    if (it->current_col == NULL)
        return 1;
    
    return 0;
}

void matriz_iterator_destroy(MatrizIterator *it)
{
    free(it);
}