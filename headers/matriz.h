#ifndef MATRIZ_H
#define MATRIZ_H

#include "forward_list.h"

typedef struct Matriz Matriz;

typedef struct MatrizIterator MatrizIterator;


Matriz *matriz_construct(int qtd_lin, int qtd_col);

void matriz_print_esparso(Matriz *m);

Matriz *matriz_atribuir(Matriz *m, int lin, int col, float value);

data_type *matriz_find_position(Matriz *m, int lin, int col);

void matriz_destroy(Matriz *m);

MatrizIterator *matriz_iterator_create(Matriz *m);

Node *matriz_iterator_next_line(MatrizIterator *it, Matriz *m);

int matriz_iterator_line_is_over(MatrizIterator *it);

void matriz_iterator_destroy(MatrizIterator *it);

#endif