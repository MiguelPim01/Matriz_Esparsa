#include <stdio.h>
#include <stdlib.h>

#include "../headers/data_type.h"

struct data_type {
    int lin;
    int col;
    float data;
};

data_type *data_type_construct(int lin, int col, float data)
{
    data_type *d = (data_type *)malloc(sizeof(data_type));

    d->col = col;
    d->lin = lin;
    d->data = data;

    return d;
}

void data_type_destroy(data_type *d)
{
    free(d);
}