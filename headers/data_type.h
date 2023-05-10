#ifndef DATATYPE_H
#define DATATYPE_H

typedef struct data_type data_type;

/**
 * @brief Constroi um novo data_type.
 *  Aloca memória para cada parametro.
 * @param lin
 * A linha em que o valor se encontra.
 * @param col
 * A coluna em que o valor se encontra.
 * @param data
 * O valor do data_type naquela linha e coluna.
 * @return data_type*
 * Ponteiro para o data_type.
 * 
 * O(1): Pois aloca apenas um espaço para data_type, faz atribuições diretas e retorna um ponteiro
 */
data_type *data_type_construct(int lin, int col, float data);

/**
 * @brief Printa os valores no formato: (lin, col): valor
 * @param d
 * Ponteiro para data_type
 * @return void
 * 
 * O(1): Apenas printa os valores de data_type na tela
 */
void data_type_print_esparso(data_type *d);

/**
 * @brief Atribui um novo valor para o data_type
 * @param d
 * Ponteiro para data_type
 * @param value
 * Valor que será atribuido
 * @return void
 * 
 * O(1): Faz uma atribuição e encerra a função
 */
void data_type_atribui_value(data_type *d, float value);

/**
 * @brief Retorna o valor que está em data_type
 * @param d
 * Ponteiro para data_type
 * @return float
 * Valor que está armazenado em data_type
 * 
 * O(1): Apenas retorna um valor
 */
float data_type_value(data_type *d);

/**
 * @brief Retorna a coluna que está em data_type
 * @param d
 * Ponteiro para data_type
 * @return int
 * Valor da coluna está armazenado em data_type
 * 
 * O(1): Apenas retorna um valor
 */
int data_type_col(data_type *d);

/**
 * @brief Libera o espaço alocado na memoria de data_type
 * @param d
 * Ponteiro para data_type
 * @return void
 * 
 * O(1): Da free() no ponteiro de data_type
 */
void data_type_destroy(data_type *d);

#endif