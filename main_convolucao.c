#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

// Cria uma matriz nxn e uma matriz kernel pxp. O retorno esperado é a matriz resultado nxn que é a convolução de m com o kernel.

int main(int argc, char *argv[])
{   
    if (argc < 3)
    {
        printf("Erro: Argumentos insuficientes\n");
        printf("RUN: ./main_convolucao <matriz.bin> <kernel.bin>\n");
        return 1;
    }

    FILE *pFile = NULL;
    char caminho[100];

    sprintf(caminho, "%s", argv[1]);
    pFile = fopen(caminho, "rb");

    if (pFile == NULL)
    {
        printf("ERRO ao abrir arquivo %s\n", caminho);
        exit(1);
    }
    
    Matriz *m = matriz_read_bin(pFile);
    fclose(pFile);

    printf("Matriz m:\n");
    matriz_print_denso(m);

    sprintf(caminho, "%s", argv[2]);
    pFile = fopen(caminho, "rb");

    if (pFile == NULL)
    {
        printf("ERRO ao abrir arquivo %s\n", caminho);
        exit(1);
    }

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