#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

// Resultado esperado do programa é salvar uma matriz em formato binario para que o usuario possa usar nos demais programas

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Erro: Argumentos insuficientes\n");
        printf("RUN: ./main <nome_arquivo_bin>\n");
        return 1;
    }

    char caminho[100];
    caminho[0]='\0';

    FILE *pFile = NULL;

    sprintf(caminho, "%s.bin", argv[1]);
    pFile = fopen(caminho, "wb");

    float valor;
    int lin, col;

    scanf("%d %d", &lin, &col);
    Matriz *m = matriz_construct(lin, col);

    while (scanf("%f", &valor) == 1)
    {
        scanf("%d %d", &lin, &col);

        matriz_atribuir(m, lin, col, valor);
    }

    matriz_save_bin(m, pFile);

    matriz_destroy(m);

    fclose(pFile);
    return 0;
}