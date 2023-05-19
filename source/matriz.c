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

// O(m+n): Aloca uma quantidade m de forward_lists para as linhas e uma quantidade n para as colunas.
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

// O(m*n): Anda pelas linhas da matriz e pra cada linha anda em cada node.
// No pior dos casos terá andado todas as linhas m e pra cada linha todos os n nodes dela.
void matriz_print_esparso(Matriz *m)
{
    if (m == NULL)
        return;
    
    MatrizIterator *it = matriz_iterator_create(m);

    while (!matriz_iterator_line_is_over(it))
    {
        forward_list_print_esparso(it->current_lin);

        matriz_iterator_next_line(it, m);
    }

    matriz_iterator_destroy(it);
}

// O(m+n): No pior dos casos a função tem que inserir na linha m e coluna n.
// Ela tera que andar uma vez na linha e coluna para achar o indice de inserção, e depois, uma vez na linha e coluna para inserir o valor.
// Acho que poderia ter complexidade O(2*(m+n)) também, mas olhando a definição na notação O, entendi que as constantes podem ser desconsideradas.
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

// O(m*n*(m+n)): Anda pelas m linhas da matriz e, pra cada linha, anda pelos n nodes da matriz no pior caso.
// Mas, a complexidade da função matriz_copy é maior que o resto da função, portanto a função terá mesma complexidade de matriz_copy.
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

// O(m*n*(m+n)): Anda pelas m linhas das duas matrizes simultaneamente, e pelos n nodes de cada linha.
// Utiliza a função de atribuir pra cada node, que é O(m+n).
Matriz *matriz_multiply_point_by_point(Matriz *m1, Matriz *m2)
{
    if (m1->qtd_lin != m2->qtd_lin || m1->qtd_col != m2->qtd_col)
    {
        printf("Erro: Matrizes nao tem dimensoes iguais! (matriz_multiply_point_by_point)\n");
        return NULL;
    }

    Matriz *mr = matriz_construct(m1->qtd_lin, m1->qtd_col);
    ForwardListIterator *it1, *it2;
    data_type *data1 = NULL, *data2 = NULL;

    for (int i = 0; i < m1->qtd_lin; i++)
    {
        if (forward_list_head(m1->lines[i]) == NULL || forward_list_head(m2->lines[i]) == NULL)
            continue;

        it1 = forward_list_front_iterator(m1->lines[i]);
        it2 = forward_list_front_iterator(m2->lines[i]);

        while (!(forward_list_iterator_is_over(it1) && forward_list_iterator_is_over(it2)))
        {
            data1 = node_value(forward_list_iterator_current(it1));
            data2 = node_value(forward_list_iterator_current(it2));

            if (data_type_col(data1) == data_type_col(data2))
            {
                matriz_atribuir(mr, i, data_type_col(data1)-1, data_type_value(data1)*data_type_value(data2));
                forward_list_iterator_next(it1, PATH_LIN);
                forward_list_iterator_next(it2, PATH_LIN);
            }
            else if (data_type_col(data1) < data_type_col(data2))
                forward_list_iterator_next(it1, PATH_LIN);
            else
                forward_list_iterator_next(it2, PATH_LIN);

            if (forward_list_iterator_current(it1) == NULL && forward_list_iterator_current(it2) != NULL)
            {
                if (data_type_col(node_value(forward_list_iterator_current(it2))) > data_type_col(data1))
                    break;
            }
            else if (forward_list_iterator_current(it2) == NULL && forward_list_iterator_current(it1) != NULL)
            {
                if (data_type_col(node_value(forward_list_iterator_current(it1))) > data_type_col(data2))
                    break;
            }
        }

        forward_list_iterator_destroy(it1);
        forward_list_iterator_destroy(it2);
    }

    return mr;
}

// O(m*q*(n+m+q)): Anda pelas m linhas da primeira matriz. Pra cada linha da primeira, anda pelas q colunas da segunda matriz.
// Anda pelos n nodes da linha e coluna simultaneamente.
// Pra cada ponto da matriz utiliza a função de atribuir que é O(m+q).
Matriz *matriz_multiply(Matriz *m1, Matriz *m2)
{
    if (m1->qtd_col != m2->qtd_lin)
    {
        printf("Erro: Nao é possivel multiplicar as duas matrizes!\n");
        return NULL;
    }

    Matriz *mr = matriz_construct(m1->qtd_lin, m2->qtd_col);
    ForwardListIterator *it1, *it2;
    data_type *data1 = NULL, *data2 = NULL;
    float value = 0;

    for (int i = 0; i < m1->qtd_lin; i++) // anda nas linhas de m1
    {
        for (int j = 0; j < m2->qtd_col; j++) // anda nas colunas de m2
        {
            if (forward_list_head(m1->lines[i]) == NULL || forward_list_head(m2->columns[j]) == NULL)
                continue;

            it1 = forward_list_front_iterator(m1->lines[i]);
            it2 = forward_list_front_iterator(m2->columns[j]);

            while (!(forward_list_iterator_is_over(it1) && forward_list_iterator_is_over(it2)))
            {
                data1 = node_value(forward_list_iterator_current(it1));
                data2 = node_value(forward_list_iterator_current(it2));

                if (data_type_col(data1) == data_type_lin(data2))
                {
                    value += data_type_value(data1)*data_type_value(data2);
                    forward_list_iterator_next(it1, PATH_LIN);
                    forward_list_iterator_next(it2, PATH_COL);
                }
                else if (data_type_col(data1) < data_type_lin(data2))
                    forward_list_iterator_next(it1, PATH_LIN);
                else
                    forward_list_iterator_next(it2, PATH_COL);

                if (forward_list_iterator_current(it1) == NULL && forward_list_iterator_current(it2) != NULL)
                {
                    if (data_type_lin(node_value(forward_list_iterator_current(it2))) > data_type_col(data1))
                        break;
                }
                else if (forward_list_iterator_current(it2) == NULL && forward_list_iterator_current(it1) != NULL)
                {
                    if (data_type_col(node_value(forward_list_iterator_current(it1))) > data_type_lin(data2))
                        break;
                }
            }
            matriz_atribuir(mr, i, j, value);
            value = 0;

            forward_list_iterator_destroy(it1);
            forward_list_iterator_destroy(it2);
        }
    }

    return mr;
}

// O(m*n*(m+n)): Anda pelas m linhas das matrizes simultaneamente, e pelos n nodes em cada linha.
// Utiliza a função de atribuição, que é O(m+n), pra cada node.
Matriz *matriz_add(Matriz *m1, Matriz *m2)
{
    if (m1->qtd_lin != m2->qtd_lin || m1->qtd_col != m2->qtd_col)
    {
        printf("Erro: Nao é possivel somar as duas matrizes!\n");
        return NULL;
    }

    Matriz *mr = matriz_construct(m1->qtd_lin, m1->qtd_col);
    ForwardListIterator *it1, *it2;
    data_type *data1 = NULL, *data2 = NULL;

    for (int i = 0; i < m1->qtd_lin; i++)
    {
        it1 = forward_list_front_iterator(m1->lines[i]);
        it2 = forward_list_front_iterator(m2->lines[i]);

        while (!(forward_list_iterator_is_over(it1) && forward_list_iterator_is_over(it2)))
        {
            data1 = node_value(forward_list_iterator_current(it1));
            data2 = node_value(forward_list_iterator_current(it2));
            
            if (data_type_col(data1) == data_type_col(data2))
            {
                matriz_atribuir(mr, i, data_type_col(data1)-1, data_type_value(data1)+data_type_value(data2));
                forward_list_iterator_next(it1, PATH_LIN);
                forward_list_iterator_next(it2, PATH_LIN);
            }
            else if (data_type_col(data1) < data_type_col(data2))
            {
                if (data_type_col(data1) == -1)
                {
                    matriz_atribuir(mr, i, data_type_col(data2)-1, data_type_value(data2));
                    forward_list_iterator_next(it2, PATH_LIN);
                }
                else
                {
                    matriz_atribuir(mr, i, data_type_col(data1)-1, data_type_value(data1));
                    forward_list_iterator_next(it1, PATH_LIN);
                }
            }
            else
            {
                if (data_type_col(data2) == -1)
                {
                    matriz_atribuir(mr, i, data_type_col(data1)-1, data_type_value(data1));
                    forward_list_iterator_next(it1, PATH_LIN);
                }
                else
                {
                    matriz_atribuir(mr, i, data_type_col(data2)-1, data_type_value(data2));
                    forward_list_iterator_next(it2, PATH_LIN);
                }
            }
        }

        forward_list_iterator_destroy(it1);
        forward_list_iterator_destroy(it2);
    }

    return mr;
}

// O(m*n): Anda pelas m linhas da matriz, e pelos n nodes em cada linha.
void matriz_transposta(Matriz *m)
{
    ForwardList **lines = m->lines, **columns = m->columns, *l;
    m->lines = columns;
    m->columns = lines;

    int lin = m->qtd_lin, col = m->qtd_col;
    m->qtd_lin = col;
    m->qtd_col = lin;

    MatrizIterator *it = matriz_iterator_create(m);

    while (!matriz_iterator_line_is_over(it))
    {
        l = matriz_iterator_next_line(it, m);

        forward_list_swap_nodes(l);
    }
    matriz_iterator_destroy(it);
}

// O(n^2): Realiza um looping e dentro dele utiliza funções O(n).
void matriz_swap_lin(Matriz *m, int lin1, int lin2)
{
    float value1, value2;

    if (lin1 < 0 || lin1 + 1 > m->qtd_lin || lin2 < 0 || lin2 + 1 > m->qtd_lin)
    {
        printf("Erro: Linhas passadas nao existem na matriz!\n");
        return;
    }

    if (lin1 == lin2)
        return;
    
    for (int j = 0; j < m->qtd_col; j++)
    {
        value1 = matriz_read_value(m, lin1, j);
        value2 = matriz_read_value(m, lin2, j);
        matriz_atribuir(m, lin2, j, value1);
        matriz_atribuir(m, lin1, j, value2);
    }
}

// O(n^2): Realiza um looping e dentro dele utiliza funções O(n).
void matriz_swap_col(Matriz *m, int col1, int col2)
{
    float value1, value2;

    if (col1 < 0 || col1 + 1 > m->qtd_col || col2 < 0 || col2 + 1 > m->qtd_col)
    {
        printf("Erro: Colunas passadas nao existem na matriz!\n");
        return;
    }

    if (col1 == col2)
        return;
    
    for (int j = 0; j < m->qtd_col; j++)
    {
        value1 = matriz_read_value(m, j, col1);
        value2 = matriz_read_value(m, j, col2);
        matriz_atribuir(m, j, col2, value1);
        matriz_atribuir(m, j, col1, value2);
    }
}

// O(m*n*(m+n)): No pior dos casos terá que retornar o slice da própria matriz.
// Vai andar pelas m linhas, e pelas n colunas da matriz.
// Utiliza a função de atribuir, que é O(m+n), pra cada valor.
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

// O(m*n*k^3): Anda por cada elemento da matriz (m x n), e pra cada um desses elementos, anda uma quantidade equivalente a quantidade de elementos do kernel (k x k).
// A complexidade das funções slice e point_by_point são O(k^3). Obs: A constante que aparece foi omitida mais uma vez O(k*k(k+k)).
// As duas funções tem as maiores complexidades no segundo looping.
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

// O(n^2): Itera sobre as linhas da matriz e utiliza uma função O(n) para cada iteração
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

// O(n): Utiliza uma função O(n) e retorna um valor
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

// O(n^3): Realiza dois loopings, um dentro do outro, para leitura de cada indice, e utiliza uma função O(n) dentro do segundo looping
void matriz_print_denso(Matriz *m)
{
    if (m == NULL)
        return;
    
    for (int i = 0; i < m->qtd_lin; i++)
    {
        for (int j = 0; j < m->qtd_col; j++)
        {
            printf("%.0f  ", matriz_read_value(m, i, j));
        }
        printf("\n");
    }
}

// O(n): Utiliza uma função O(n) e faz atribuições
data_type *matriz_find_position(Matriz *m, int lin, int col)
{
    data_type *data = forward_list_find(m->lines[lin], col+1);

    return data;
}

// O(m*n*(m+n)): Anda pelas m linhas da matriz e no pior dos casos sempre anda pelas n colunas pra cada linha.
// Para cada node é usado a funcao de atribuição, que é O(m+n).
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

// O(n^2): Itera sobre as linhas da matriz e utiliza uma função O(n) para cada iteração
void matriz_save_bin(Matriz *m, FILE *pFile)
{
    fwrite(&m->qtd_lin, sizeof(int), 1, pFile);
    fwrite(&m->qtd_col, sizeof(int), 1, pFile);

    MatrizIterator *it = matriz_iterator_create(m);
    ForwardList *l;

    while(!matriz_iterator_line_is_over(it))
    {
        l = matriz_iterator_next_line(it, m);

        forward_list_save_bin(l, pFile);
    }
    matriz_iterator_destroy(it);
}

// O(n^3): Realiza dois loopings, um dentro do outro, utilizando uma função O(n) dentro do segundo looping
Matriz *matriz_read_bin(FILE *pFile)
{
    int qtd_lin, qtd_col, lin, col, size;
    float value;

    fread(&qtd_lin, sizeof(int), 1, pFile);
    fread(&qtd_col, sizeof(int), 1, pFile);

    Matriz *mr = matriz_construct(qtd_lin, qtd_col);

    for (int i = 0; i < qtd_lin; i++)
    {
        fread(&size, sizeof(int), 1, pFile);

        for (int j = 0; j < size; j++)
        {
            fread(&lin, sizeof(int), 1, pFile);
            fread(&col, sizeof(int), 1, pFile);
            fread(&value, sizeof(float), 1, pFile);

            matriz_atribuir(mr, lin-1, col-1, value);
        }
    }

    return mr;
}

// O((m*n)+n): Anda pelas m linhas da matriz, e pelos n nodes de cada linha.
// Ao fim anda pelas n colunas da matriz sem andar pelos m nodes. Outro jeito: O((m+1)*n).
void matriz_destroy(Matriz *m)
{
    if (m == NULL)
        return;
    
    for (int i = 0; i < m->qtd_lin; i++)
        forward_list_destroy(m->lines[i], PATH_LIN);

    for (int i = 0; i < m->qtd_col; i++)
        forward_list_destroy(m->columns[i], PATH_COL);
    
    free(m->lines);
    free(m->columns);
    free(m);
}

// =========== ITERADOR PARA MATRIZES ===========

// O(1): Aloca 1 iterador de matriz e faz atribuições
MatrizIterator *matriz_iterator_create(Matriz *m)
{
    MatrizIterator *it = (MatrizIterator *)malloc(sizeof(MatrizIterator));

    it->current_lin = m->lines[0];
    it->current_col = m->columns[0];
    it->lin = 0;
    it->col = 0;

    return it;
}

// O(1): Realiza apenas atribuições
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

// O(1): Realiza apenas atribuições
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

// O(1): Faz apenas uma verificação
int matriz_iterator_line_is_over(MatrizIterator *it)
{
    if (it->current_lin == NULL)
        return 1;
    
    return 0;
}

// O(1): Faz apenas uma verificação
int matriz_iterator_col_is_over(MatrizIterator *it)
{
    if (it->current_col == NULL)
        return 1;
    
    return 0;
}

// O(1): Libera um ponteiro da memoria
void matriz_iterator_destroy(MatrizIterator *it)
{
    free(it);
}