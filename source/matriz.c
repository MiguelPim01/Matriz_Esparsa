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

void matriz_atribuir(Matriz *m, int lin, int col, float value)
{
    int ind_lin, ind_col;

    if (lin + 1 > m->qtd_lin || lin < 0 || col < 0 || col + 1 > m->qtd_col)
    {
        printf("Erro: Indice nao existe na matriz (matriz_atribuir)\n");
        return;
    }

    data_type *data = matriz_find_position(m, lin, col);

    if (data == NULL)
    {
        if (value == 0)
            return;

        data = data_type_construct(lin+1, col+1, value);
        Node *n = node_construct(data, NULL, NULL);
        

        ind_lin = forward_list_insertion_index(m->lines[lin], col+1, PATH_LIN);
        ind_col = forward_list_insertion_index(m->columns[col], lin+1, PATH_COL);

        forward_list_insert(m->lines[lin], n, ind_lin, PATH_LIN);
        forward_list_insert(m->columns[col], n, ind_col, PATH_COL);
    }
    else
    {
        if (value == 0)
        {
            ind_lin = forward_list_insertion_index(m->lines[lin], col+1, PATH_LIN);
            ind_col = forward_list_insertion_index(m->columns[col], lin+1, PATH_COL);

            forward_list_pop_index(m->lines[lin], m->columns[col], ind_lin, ind_col);
        }
        else
            data_type_atribui_value(data, value);
    }
}

Matriz *matriz_multiply_escalar(Matriz *m, float n)
{
    Matriz *mr = matriz_copy(m);
    MatrizIterator *it = matriz_iterator_create(mr);

    while (!matriz_iterator_line_is_over(it))
    {
        forward_list_multiply_escalar(matriz_iterator_next_line(it, mr), n);
    }
    matriz_iterator_destroy(it);

    return mr;
}

Matriz *matriz_multiply_point_by_point(Matriz *m1, Matriz *m2)
{
    if (m1->qtd_lin != m2->qtd_lin || m1->qtd_col != m2->qtd_col)
    {
        printf("Erro: Matrizes nao tem dimensoes iguais! (matriz_multiply_point_by_point)\n");
        return NULL;
    }

    Matriz *mr = matriz_construct(m1->qtd_lin, m1->qtd_col);
    float value1, value2;

    for (int i = 0; i < m1->qtd_lin; i++)
    {
        for (int j = 0; j < m1->qtd_col; j++)
        {
            value1 = matriz_read_value(m1, i, j);
            value2 = matriz_read_value(m2, i, j);

            if (!value1 || !value2)
                continue;

            matriz_atribuir(mr, i, j, value1*value2);
        }
    }

    return mr;
}

Matriz *matriz_multiply(Matriz *m1, Matriz *m2)
{
    if (m1->qtd_col != m2->qtd_lin)
    {
        printf("Erro: Nao é possivel multiplicar as duas matrizes!\n");
        return NULL;
    }

    Matriz *mr = matriz_construct(m1->qtd_lin, m2->qtd_col);
    float value = 0;

    for (int i = 0; i < m1->qtd_lin; i++) // anda nas linhas de m1
    {
        for (int j = 0; j < m2->qtd_col; j++) // anda nas colunas de m2
        {
            for (int q = 0; q < m1->qtd_col; q++) // anda por cada ponto da linha m1 e cada ponto da coluna de m2
            {
                value += matriz_read_value(m1, i, q)*matriz_read_value(m2, q, j);
            }
            if (value == 0)
                continue;

            matriz_atribuir(mr, i, j, value);
            value = 0;
        }
    }

    return mr;
}

Matriz *matriz_add(Matriz *m1, Matriz *m2)
{
    if (m1->qtd_lin != m2->qtd_lin || m1->qtd_col != m2->qtd_col)
    {
        printf("Erro: Nao é possivel somar as duas matrizes!\n");
        return NULL;
    }

    Matriz *mr = matriz_construct(m1->qtd_lin, m1->qtd_col);
    float value = 0;

    for (int i = 0; i < m1->qtd_lin; i++)
    {
        for (int j = 0; j < m1->qtd_col; j++)
        {
            value = matriz_read_value(m1, i, j) + matriz_read_value(m2, i, j);

            if (value == 0)
                continue;

            matriz_atribuir(mr, i, j, value);
        }
    }

    return mr;
}

Matriz *matriz_transposta(Matriz *m)
{
    Matriz *mr = matriz_copy(m);
    ForwardList **lines = mr->lines, *l;
    mr->lines = mr->columns;
    mr->columns = lines;
    mr->qtd_lin = m->qtd_col;
    mr->qtd_col = m->qtd_lin;

    MatrizIterator *it = matriz_iterator_create(mr);

    while (!matriz_iterator_line_is_over(it))
    {
        l = matriz_iterator_next_line(it, mr);

        forward_list_swap_nodes(l);
    }
    matriz_iterator_destroy(it);

    return mr;
}

Matriz *matriz_swap_lin(Matriz *m, int lin1, int lin2)
{
    Matriz *mr = matriz_copy(m);
    float value;

    if (lin1 < 0 || lin1 + 1 > m->qtd_lin || lin2 < 0 || lin2 + 1 > m->qtd_lin)
    {
        printf("Erro: Linhas passadas nao existem na matriz!\n");
        return mr;
    }

    if (lin1 == lin2)
        return mr;
    
    for (int j = 0; j < m->qtd_col; j++)
    {
        value = matriz_read_value(m, lin1, j);
        matriz_atribuir(mr, lin2, j, value);

        value = matriz_read_value(m, lin2, j);
        matriz_atribuir(mr, lin1, j, value);
    }

    return mr;
}

Matriz *matriz_swap_col(Matriz *m, int col1, int col2)
{
    Matriz *mr = matriz_copy(m);
    float value;

    if (col1 < 0 || col1 + 1 > m->qtd_col || col2 < 0 || col2 + 1 > m->qtd_col)
    {
        printf("Erro: Colunas passadas nao existem na matriz!\n");
        return mr;
    }

    if (col1 == col2)
        return mr;
    
    for (int j = 0; j < m->qtd_col; j++)
    {
        value = matriz_read_value(m, j, col1);
        matriz_atribuir(mr, j, col2, value);

        value = matriz_read_value(m, j, col2);
        matriz_atribuir(mr, j, col1, value);
    }

    return mr;
}

Matriz *matriz_slice(Matriz *m, int lin_ini, int col_ini, int lin_fin, int col_fin)
{
    int a;
    if (lin_ini > lin_fin)
    {
        a = lin_ini;
        lin_ini = lin_fin;
        lin_fin = a;
    }
    if (col_ini > col_fin)
    {
        a = col_ini;
        col_ini = col_fin;
        col_fin = a;
    }
    
    int lin_mr = lin_fin - lin_ini + 1, col_mr = col_fin - col_ini + 1;
    Matriz *mr = matriz_construct(lin_mr, col_mr);

    float value;

    for (int i = lin_ini; i <= lin_fin; i++)
    {
        for (int j = col_ini; j <= col_fin; j++)
        {
            value = matriz_read_value(m, i, j);
            matriz_atribuir(mr, i-lin_ini, j-col_ini, value);
        }
    }

    return mr;
}

Matriz *matriz_convolucao(Matriz *m, Matriz *kernel)
{
    Matriz *m_slice, *m_multiplied, *mr = matriz_construct(m->qtd_lin, m->qtd_col);
    float value;
    int aux_lin = (kernel->qtd_lin-1)/2, aux_col = (kernel->qtd_col-1)/2;

    for (int i = 0; i < m->qtd_lin; i++)
    {
        for (int j = 0; j < m->qtd_col; j++)
        {
            m_slice = matriz_slice(m, i-aux_lin, j-aux_col, i+aux_lin, j+aux_col);
            m_multiplied = matriz_multiply_point_by_point(m_slice, kernel);
            value = matriz_add_all(m_multiplied);
            matriz_atribuir(mr, i, j, value);

            matriz_destroy(m_slice);
            matriz_destroy(m_multiplied);
        }
    }

    return mr;
}

float matriz_add_all(Matriz *m)
{
    MatrizIterator *it = matriz_iterator_create(m);
    ForwardList *l;
    float value = 0;

    while (!matriz_iterator_line_is_over(it))
    {
        l = matriz_iterator_next_line(it, m);

        value += forward_list_add_all(l);
    }
    matriz_iterator_destroy(it);

    return value;
}

float matriz_read_value(Matriz *m, int lin, int col)
{
    if (lin + 1 > m->qtd_lin || lin < 0 || col < 0 || col + 1 > m->qtd_col)
        return 0;

    data_type *data = matriz_find_position(m, lin, col);

    if (data == NULL)
        return 0;
    else
        return data_type_value(data);
}

void matriz_print_denso(Matriz *m)
{
    for (int i = 0; i < m->qtd_lin; i++)
    {
        for (int j = 0; j < m->qtd_col; j++)
        {
            printf("%.0f  ", matriz_read_value(m, i, j));
        }
        printf("\n");
    }
}

data_type *matriz_find_position(Matriz *m, int lin, int col)
{
    data_type *data = forward_list_find(m->lines[lin], col+1);

    return data;
}

Matriz *matriz_copy(Matriz *m)
{
    Matriz *mr = matriz_construct(m->qtd_lin, m->qtd_col);
    MatrizIterator *it_matriz = matriz_iterator_create(m);
    ForwardListIterator *it_list;
    data_type *data;

    while(!matriz_iterator_line_is_over(it_matriz))
    {
        it_list = forward_list_front_iterator(matriz_iterator_next_line(it_matriz, m));

        while (!forward_list_iterator_is_over(it_list))
        {
            data = forward_list_iterator_next(it_list, PATH_LIN);

            matriz_atribuir(mr, data_type_lin(data)-1, data_type_col(data)-1, data_type_value(data));
        }

        forward_list_iterator_destroy(it_list);
    }
    matriz_iterator_destroy(it_matriz);

    return mr;
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

ForwardList *matriz_iterator_next_line(MatrizIterator *it, Matriz *m)
{
    ForwardList *l = it->current_lin;

    it->lin++;
    if (it->lin + 1 > m->qtd_lin)
    {
        it->current_lin = NULL;
        return l;
    }

    it->current_lin = m->lines[it->lin];

    return l;
}

ForwardList *matriz_iterator_next_col(MatrizIterator *it, Matriz *m)
{
    ForwardList *l = it->current_col;

    it->col++;
    if (it->col + 1 > m->qtd_col)
    {
        it->current_col = NULL;
        return l;
    }

    it->current_col = m->columns[it->col];

    return l;
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