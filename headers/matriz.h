#ifndef MATRIZ_H
#define MATRIZ_H

#include "forward_list.h"

typedef struct Matriz Matriz;

typedef struct MatrizIterator MatrizIterator;


Matriz *matriz_construct(int qtd_lin, int qtd_col);

void matriz_print_esparso(Matriz *m);

void matriz_atribuir(Matriz *m, int lin, int col, float value);

Matriz *matriz_multiply_escalar(Matriz *m, float n);

Matriz *matriz_multiply_point_by_point(Matriz *m1, Matriz *m2);

Matriz *matriz_multiply(Matriz *m1, Matriz *m2);

Matriz *matriz_add(Matriz *m1, Matriz *m2);

Matriz *matriz_transposta(Matriz *m);

void matriz_swap_lin(Matriz *m, int lin1, int lin2);

void matriz_swap_col(Matriz *m, int col1, int col2);

Matriz *matriz_slice(Matriz *m, int lin_ini, int col_ini, int lin_fin, int col_fin);

Matriz *matriz_convolucao(Matriz *m, Matriz *kernel);

float matriz_add_all(Matriz *m);

float matriz_read_value(Matriz *m, int lin, int col);

data_type *matriz_find_position(Matriz *m, int lin, int col);

Matriz *matriz_copy(Matriz *m);

void matriz_print_denso(Matriz *m);

void matriz_save_bin(Matriz *m, FILE *pFile);

Matriz *matriz_read_bin(FILE *pFile);

void matriz_destroy(Matriz *m);

MatrizIterator *matriz_iterator_create(Matriz *m);

ForwardList *matriz_iterator_next_line(MatrizIterator *it, Matriz *m);

ForwardList *matriz_iterator_next_col(MatrizIterator *it, Matriz *m);

int matriz_iterator_line_is_over(MatrizIterator *it);

int matriz_iterator_col_is_over(MatrizIterator *it);

void matriz_iterator_destroy(MatrizIterator *it);

#endif