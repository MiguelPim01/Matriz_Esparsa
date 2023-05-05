#include "../headers/matriz.h"
#include "../headers/forward_list.h"

struct Matriz {
    ForwardList **lines;
    ForwardList **columns;
    int qtd_lin;
    int qtd_col;
};