#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

int main()
{
    Matriz *m = matriz_construct(5, 5);

    matriz_atribuir(m, 1, 1, 1);
    matriz_atribuir(m, 2, 2, 1);
    matriz_atribuir(m, 3, 3, 1);
    matriz_atribuir(m, 4, 4, 1);
    matriz_atribuir(m, 5, 5, 1);

    matriz_print_denso(m);
    matriz_print_esparso(m);

    matriz_destroy(m);

    return 0;
}