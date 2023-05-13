#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

int main()
{   
    float valor;
    int lin, col;

    scanf("%d %d", &lin, &col);

    Matriz *m1 = matriz_construct(lin, col);

    while (scanf("%f", &valor) == 1)
    {
        scanf("%d %d", &lin, &col);

        matriz_atribuir(m1, lin, col, valor);
    }

    Matriz *m2 = matriz_swap_col(m1, 2, 0);

    Matriz *m3 = matriz_multiply_point_by_point(m1, m2);

    matriz_print_denso(m1);
    matriz_print_esparso(m1);
    printf("\n");
    matriz_print_denso(m2);
    matriz_print_esparso(m2);
    printf("\n");
    matriz_print_denso(m3);
    matriz_print_esparso(m3);

    matriz_destroy(m1);
    matriz_destroy(m2);
    matriz_destroy(m3);

    return 0;
}