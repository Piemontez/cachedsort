#ifndef TOOLS_H
#define TOOLS_H

//interface da função chamada para ordenar a listagem
typedef void(*sort)(int *list, const int &size);

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
bool isEquals(int* lista, int* listb, const int listsize);


/**
 * Ordena a listagem com buble Sorte comparação
 * @size: quantidade de itens na lista
 */ 
int *safeSort(const int *list, const int &size);

/**
 * Imprime a listagem
 * @size: quantidade de itens na lista
 */ 
void printList(const int *list, const int &size);


#endif // TOOLS_H