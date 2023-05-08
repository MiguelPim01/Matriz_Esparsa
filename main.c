#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

int main()
{
    Matriz *m = matriz_construct(10, 10);

    matriz_destroy(m);

    return 0;
}