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

void data_type_print(data_type *d)
{
    printf("(%d, %d): %.1f", d->lin, d->col, d->data);
}

void data_type_atribui_value(data_type *d, float value)
{
    d->data = value;
}

float data_type_value(data_type *d)
{
    return d->data;
}

int data_type_col(data_type *d)
{
    return d->col;
}

void data_type_destroy(data_type *d)
{
    free(d);
}