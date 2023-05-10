#ifndef DATATYPE_H
#define DATATYPE_H

typedef struct data_type data_type;

data_type *data_type_construct(int lin, int col, float data);

void data_type_print(data_type *d);

void data_type_atribui_value(data_type *d, float value);

float data_type_value(data_type *d);

int data_type_col(data_type *d);

void data_type_destroy(data_type *d);

#endif