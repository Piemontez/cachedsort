#ifndef WINDOW_H
#define WINDOW_H

//interface da função chamada para ordenar a listagem
typedef int *(*sort)(const int *list, const int &size);

/**
 * Cria listagem com valores aleatórios
 * @listsize: quantidade de itens na lista
 * @testsamout: quantidade de itens aleatórios a serem testados
 */
int** makeUnorderedList(const int listsize, const int testsamout);

/**
 * Cria uma lista ordenada para comparação
 * @listsize: quantidade de itens na lista
 */ 
int* makeOrderedList(const int listsize);


/**
 * Cria uma lista ordenada para comparação
 * @listsize: quantidade de itens na lista
 */ 
bool isEquals(int* lista, int* listb, const int listsize);


#endif // WINDOW_H