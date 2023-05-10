#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

int main()
{
    Matriz *m = matriz_construct(10, 10);

    matriz_atribuir(m, 3, 3, 1);
    matriz_atribuir(m, 4, 5, 2);
    matriz_atribuir(m, 3, 3, 10);

    matriz_print_esparso(m);

    matriz_destroy(m);

    return 0;
}