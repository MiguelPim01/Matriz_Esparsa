#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

// Cria uma matriz nxn e uma matriz kernel pxp. O retorno esperado é a matriz resultado nxn que é a convolução de m com o kernel.

int main(int argc, char *argv[])
{   
    if (argc < 2)
    {
        printf("Erro: Argumentos insuficientes\n");
        printf("RUN: ./main <matriz.bin>\n");
        return 1;
    }

    FILE *pFile = NULL;
    char caminho[100];

    sprintf(caminho, "%s", argv[1]);
    pFile = fopen(caminho, "rb");
    
    float valor;
    int lin, col;

    scanf("%d %d", &lin, &col);
    Matriz *m = matriz_construct(lin, col);

    while (scanf("%f", &valor) == 1)
    {
        scanf("%d %d", &lin, &col);

        matriz_atribuir(m, lin, col, valor);
    }
    scanf("%*[^\n]");
    scanf("%*c");

    printf("Matriz m:\n");
    matriz_print_denso(m);

    Matriz *kernel = matriz_read_bin(pFile);

    printf("Matriz kernel:\n");
    matriz_print_denso(kernel);

    Matriz *result = matriz_convolucao(m, kernel);

    printf("\nResultado da convolução:\n");
    matriz_print_denso(result);

    matriz_destroy(m);
    matriz_destroy(kernel);
    matriz_destroy(result);

    fclose(pFile);
    
    return 0;
}