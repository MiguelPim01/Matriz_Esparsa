#ifndef DATATYPE_H
#define DATATYPE_H

typedef struct data_type data_type;

data_type *data_type_construct(int lin, int col, float data);

void data_type_destroy(data_type *d);

#endif