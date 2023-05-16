#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

int main()
{   
    Matriz *m = matriz_construct(5, 5), *kernel = matriz_construct(3, 3);

    float valor;
    int lin, col;

    while (scanf("%f", &valor) == 1)
    {
        scanf("%d %d", &lin, &col);

        matriz_atribuir(m, lin, col, valor);
    }
    scanf("%*[^\n]");
    scanf("%*c");

    matriz_print_denso(m);

    while (scanf("%f", &valor) == 1)
    {
        scanf("%d %d", &lin, &col);

        matriz_atribuir(kernel, lin, col, valor);
    }

    matriz_print_denso(kernel);

    Matriz *result = matriz_convolucao(m, kernel);

    matriz_print_denso(result);

    matriz_destroy(m);
    matriz_destroy(kernel);
    matriz_destroy(result);
    
    return 0;
}