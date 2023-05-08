#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

int main()
{
    Matriz *m = matriz_construct(2, 2);

    matriz_destroy(m);

    return 0;
}