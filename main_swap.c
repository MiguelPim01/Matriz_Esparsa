#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

// Programa recebe um arquivo com uma matriz no argumento e mostra a matriz na tela com as linhas ou colunas trocadas dependendo da escolha do usuario

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Erro: Argumentos insuficientes\n");
        printf("RUN: ./main_swap <matriz>\n");
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

    printf("Matriz:\n");
    matriz_print_denso(m);

    
    int swap1, swap2;
    char c;

    printf("Deseja trocar linhas ou colunas ?[l/c] --> ");
    scanf("%c", &c);

    switch (c)
    {
        case 'l':
            printf("\nDigite as linhas a serem trocadas: ");
            scanf("%d %d", &swap1, &swap2);

            matriz_swap_lin(m, swap1, swap2);
            break;
        case 'c':
            printf("\nDigite as colunas a serem trocadas: ");
            scanf("%d %d", &swap1, &swap2);

            matriz_swap_col(m, swap1, swap2);
            break;
        default:
            printf("\nErro: Valor digitado invalido\n");
            break;
    }

    printf("\nResultado:\n");
    matriz_print_denso(m);
    matriz_print_esparso(m);

    matriz_destroy(m);

    return 0;
}