#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

// Realiza todas as operações entre matrizes. Soma, multiplicação, multiplicação por escalar, multiplicação ponto a ponto e a transposta da matriz
// O escalar foi assumido como valendo 2 por padrao mas pode ser alterado

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Erro: Argumentos insuficientes para o programa\n");
        printf("RUN: ./main_operations <matriz_1> <matriz_2>\n");
        return 1;
    }

    FILE *pFile = NULL;
    char caminho[100];

    sprintf(caminho, "%s", argv[1]);
    pFile = fopen(caminho, "rb");

    Matriz *m1 = matriz_read_bin(pFile);
    fclose(pFile);

    sprintf(caminho, "%s", argv[2]);
    pFile = fopen(caminho, "rb");

    Matriz *m2 = matriz_read_bin(pFile);
    fclose(pFile);

    float escalar = 2; // escalar que sera multiplicado
    
    Matriz *soma = matriz_add(m1, m2);
    Matriz *mult = matriz_multiply(m1, m2);
    Matriz *mult_escalar = matriz_multiply_escalar(m1, escalar);
    Matriz *mult_ponto_a_ponto = matriz_multiply_point_by_point(m1, m2);
    matriz_transposta(m2);

    printf("A soma das matrizes m1 e m2:\n");
    matriz_print_denso(soma);
    matriz_print_esparso(soma);

    printf("A multiplicação das matrizes m1 e m2:\n");
    matriz_print_denso(mult);
    matriz_print_esparso(mult);

    printf("A multiplicação por escalar da matriz m1 por %.2f:\n", escalar);
    matriz_print_denso(mult_escalar);
    matriz_print_esparso(mult_escalar);

    printf("A multiplicação ponto a ponto das matrizes m1 e m2:\n");
    matriz_print_denso(mult_ponto_a_ponto);
    matriz_print_esparso(mult_ponto_a_ponto);

    printf("A matriz tranposta de m2:\n");
    matriz_print_denso(m2);
    matriz_print_esparso(m2);

    matriz_destroy(m1);
    matriz_destroy(m2);
    matriz_destroy(soma);
    matriz_destroy(mult);
    matriz_destroy(mult_escalar);
    matriz_destroy(mult_ponto_a_ponto);

    return 0;
}