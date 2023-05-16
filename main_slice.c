#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

// Programa recebe um arquivo com uma matriz no argumento e printa na tela um slice dessa matriz de acordo com os pontos dados pelo usuario

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Erro: Argumentos insuficientes\n");
        printf("RUN: ./main_slice <matriz>\n");
        return 1;
    }

    FILE *pFile = NULL;
    char caminho[100];

    sprintf(caminho, "%s", argv[1]);
    pFile = fopen(caminho, "rb");

    Matriz *m = matriz_read_bin(pFile);
    fclose(pFile);

    printf("Matriz:\n");
    matriz_print_denso(m);

    int lin_ini, lin_fin, col_ini, col_fin;

    printf("Digite posicao inicial (linha, coluna) --> ");
    scanf("%d %d", &lin_ini, &col_ini);
    printf("\nDigite posicao final (linha, coluna) --> ");
    scanf("%d %d", &lin_fin, &col_fin);

    Matriz *slice = matriz_slice(m, lin_ini, col_ini, lin_fin, col_fin);

    printf("\nSlice da matriz: ponto inicial (%d, %d) ponto final (%d, %d)\n", lin_ini, col_ini, lin_fin, col_fin);

    matriz_print_denso(slice);
    matriz_print_esparso(slice);

    matriz_destroy(m);
    matriz_destroy(slice);

    return 0;
}