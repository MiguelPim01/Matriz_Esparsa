#include <stdio.h>
#include <stdlib.h>

#include "../headers/data_type.h"

struct data_type {
    int lin;
    int col;
    float data;
};

// O(1): Pois aloca apenas um espaço para data_type, faz atribuições diretas e retorna um ponteiro
data_type *data_type_construct(int lin, int col, float value)
{
    data_type *d = (data_type *)malloc(sizeof(data_type));

    d->col = col;
    d->lin = lin;
    d->data = value;

    return d;
}

// O(1): Apenas printa os valores de data_type na tela
void data_type_print_esparso(data_type *d)
{
    printf("(%d, %d): %.1f", d->lin, d->col, d->data);
}

// O(1): Faz uma atribuição e encerra a função
void data_type_atribui_value(data_type *d, float value)
{
    d->data = value;
}

// O(1): Apenas retorna um valor
float data_type_value(data_type *d)
{
    if (d == NULL)
        return -1;
    return d->data;
}

// O(1): Apenas retorna um valor
int data_type_lin(data_type *d)
{
    if (d == NULL)
        return -1;
    return d->lin;
}

// O(1): Apenas retorna um valor
int data_type_col(data_type *d)
{
    if (d == NULL)
        return -1;
    return d->col;
}

// O(1): Realiza apenas atribuições
void data_type_swap_position(data_type *d)
{
    int a = d->lin;
    d->lin = d->col;
    d->col = a;
}

// O(1): Sempre escreve 3 valores int em um arquivo
void data_type_save_bin(data_type *d, FILE *pFile)
{
    fwrite(&d->lin, sizeof(int), 1, pFile);
    fwrite(&d->col, sizeof(int), 1, pFile);
    fwrite(&d->data, sizeof(float), 1, pFile);
}

// O(1): Da free() no ponteiro de data_type
void data_type_destroy(data_type *d)
{
    free(d);
}