#ifndef NODE_H
#define NODE_H

#include "data_type.h"

#define PATH_LIN 0
#define PATH_COL 1

typedef struct Node Node;

/**
 * @brief Constroi um novo node
 * Aloca espaço na memoria para um node
 * @param d
 * Ponteiro para data_type
 * @param next_lin
 * Ponteiro para o proximo node no sentido da linha
 * @param next_col
 * Ponteiro para o proximo node no sentido da coluna
 * @return Node*
 * Ponteiro para o novo node criado
 * 
 */
Node *node_construct(data_type *d, Node *next_lin, Node *next_col);

/**
 * @brief Atribui um proximo node para o node dado
 * @param n
 * Ponteiro para node em que sera realizada a atribuição
 * @param next
 * Ponteiro para node que sera atribuido como proximo
 * @param path
 * Variavel do tipo inteiro que ira dizer se o proximo node é no sentido da linha ou coluna
 * @return Node*
 * Ponteiro para o node com a atribuicao feita
 * 
 */
Node *node_set_next(Node *n, Node *next, int path);

/**
 * @brief Retorna o proximo node a partir de um passado como argumento
 * @param n
 * Ponteiro para node
 * @param path
 * Variavel para indicar se deve ser retornado o proximo da linha ou coluna
 * @return Node*
 * Proximo node
 * 
 */
Node *node_next(Node *n, int path);

/**
 * @brief Retorna o conteudo de um node
 * @param n
 * Ponteiro para node
 * @return data_type*
 * Retorna o ponteiro para o conteudo data_type do node
 * 
 */
data_type *node_value(Node *n);

/**
 * @brief Libera o espaço alocado na memoria de node
 * @param n
 * Ponteiro para node
 * @return void
 * 
 */
void node_destroy(Node *n);

#endif