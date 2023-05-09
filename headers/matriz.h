#ifndef MATRIZ_H
#define MATRIZ_H

#include "forward_list.h"

typedef struct Matriz Matriz;


Matriz *matriz_construct(int qtd_lin, int qtd_col);

Matriz *matriz_insert_value(Matriz *m, int lin, int col, float value);

void matriz_destroy(Matriz *m);

#endif