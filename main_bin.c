#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

// Resultado esperado do programa é salvar uma matriz em formato binario para que o usuario possa usar nos demais programas
// Aqui sao testados as funções de atribuição e de leitura e escrita de matrizes em arquivo binario

// Ao rodar o programa, passar como argumento apenas o nome do arquivo binario em que a matriz sera salva, sem o ".bin"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Erro: Argumentos insuficientes\n");
        printf("RUN: ./main_bin <nome_arquivo>\n");
        return 1;
    }

    char caminho[100];
    caminho[0]='\0';

    FILE *pFile = NULL;

    sprintf(caminho, "%s.bin", argv[1]);
    pFile = fopen(caminho, "wb");

    if (pFile == NULL)
    {
        printf("ERRO ao abrir arquivo %s\n", caminho);
        exit(1);
    }

    float valor;
    int lin, col;

    printf("Digite as dimensões da matriz (qtd linhas primeiro e qtd colunas depois): ");
    scanf("%d %d", &lin, &col);
    Matriz *m = matriz_construct(lin, col);

    printf("\nDigite o valor que será inserido (digite qualquer caracter para encerrar): ");
    while (scanf("%f", &valor) == 1)
    {
        printf("\nDigite a linha e coluna para ser inserido: ");
        scanf("%d %d", &lin, &col);

        matriz_atribuir(m, lin, col, valor);
        printf("\nDigite o valor que será inserido (digite qualquer caracter para encerrar): ");
    }

    matriz_print_denso(m);
    matriz_print_esparso(m);

    matriz_save_bin(m, pFile);

    matriz_destroy(m);

    fclose(pFile);
    return 0;
}