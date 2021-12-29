#ifndef TOOLS_H
#define TOOLS_H

#include <cstddef>

//interface da função chamada para ordenar a listagem
typedef void(*sort)(int *list, const int &size);


/**
 * Cria listagem com valores aleatórios
 * @listsize: quantidade de itens na lista
 * @testsamout: quantidade de itens aleatórios a serem testados
 */
int** makeUnorderedList(const int listsize, const int maxtests, bool permutated);

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



enum class OperationType
{
    Compare,
    Swap,
    AcumulatorChange,
    Conditional,
    Loop,
    Others
};
/**
 * Acumula a quantidade de operação realiza por determinado operador
 */
void addOperationCount(const char* sortedName, const OperationType &operationType, const int &amount);
#ifdef COUNT_OPERATION 
#define ADD_OPERATION_COUNT(sortedName, operationType, amount)   \
    addOperationCount(sortedName, operationType, amount)
#else
#define ADD_OPERATION_COUNT(sortedName, operationType, amount) 
#endif 

/**
 * Imprime o total de operações realizadas
 */
void printTotalOperations();


/**
 * Fatoria de um número
 */
unsigned long long factorial( int n );


/**
 * Print bits from variabel
 */
void print_bits(unsigned char * bytes, std::size_t num_bytes);

#endif // TOOLS_H