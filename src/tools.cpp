#include <algorithm>
#include <iostream>
#include <assert.h>
#include <map>
#include <cstring>
#include <time.h> /* time */
#include <iomanip>

#include "tools.hpp"
#include "algorithms.hpp"

int **makeUnorderedList(const int listsize, const int maxtests, bool permutated)
{
    assert(maxtests > 0);

    int **matrix = new int *[maxtests];
    const int lastIdx = maxtests - 1;

    //Cria uma lista ordenada para o primeiro elemento do array
    matrix[0] = new int[listsize];
    matrix[lastIdx] = new int[listsize];

    for (int i = 0; i < listsize; ++i)
    {
        matrix[0][i] = i;
        matrix[lastIdx][i] = i;
    }
    if (permutated)
    {
        int i = 0;
        while (std::next_permutation(matrix[lastIdx], matrix[lastIdx] + listsize) && i < maxtests)
        {
            i++;
            matrix[i] = new int[listsize];
            std::copy(matrix[lastIdx], matrix[lastIdx] + listsize, matrix[i]);
        };
    }
    else
    { //random
        srand(time(NULL));
        for (int j = 1; j < maxtests - 1; j++)
            for (int i = 0; i < listsize; ++i)
            {
                matrix[j] = new int[listsize];
                matrix[j][i] = rand() % listsize + 1;
            }
    }

    return matrix;
}

int *safeSort(const int *list, const int &size)
{
    int *listCopy = new int[size];
    std::copy(list, list + size, listCopy);
    bubbleSort(listCopy, size);
    return listCopy;
}

void printList(const int *list, const int &size)
{
    std::cout << "Listagem:";
    for (auto j = 0; j < size; j++)
    {
        std::cout << list[j] << " ";
    }
    std::cout << std::endl;
}

bool isEquals(int *lista, int *listb, const int listsize)
{
    for (int i = 0; i < listsize; ++i)
    {
        if (lista[i] != listb[i])
        {
            return false;
        }
    }
    return true;
}

std::map<const char *, std::map<OperationType, int>> operationsBySorted;
std::map<const char *, std::map<OperationType, int>>::iterator it;
std::map<OperationType, int>::iterator operationsIt;

void addOperationCount(const char *sortedName, const OperationType &operationType, const int &amount)
{
    operationsBySorted[sortedName][operationType] += amount;
}

const char *parseString(const OperationType operationType)
{
    switch (operationType)
    {
    case OperationType::Compare:
        return "Compare";
    case OperationType::Swap:
        return "Swap";
    case OperationType::Conditional:
        return "Conditional";
    case OperationType::AcumulatorChange:
        return "Acumulator";
    case OperationType::Loop:
        return "Loop";
    case OperationType::Others:
        return "Others";
    default:
        return "N/D";
        break;
    }
}

void printTotalOperations()
{
    int total;
    for (it = operationsBySorted.begin(); it != operationsBySorted.end(); ++it)
    {
        total = 0;
        std::cout << "Sorter: " << std::setw(10) << it->first;
        for (operationsIt = it->second.begin(); operationsIt != it->second.end(); ++operationsIt)
        {
            std::cout << " " << parseString(operationsIt->first) << ": " << std::setw(4) << operationsIt->second;
            total += operationsIt->second;
        }
        std::cout << " T.:" << total;

        std::cout << std::endl;
    }
}

unsigned long long factorial(int n)
{
    unsigned long long f = 1;

    while (n > 0)
        f *= n--;

    return f;
}

void print_byte_as_bits(char val)
{
    for (int i = 7; 0 <= i; i--)
    {
        printf("%c", (val & (1 << i)) ? '1' : '0');
    }
}

void print_bits(unsigned char *bytes, std::size_t num_bytes)
{
    printf("[");
    for (std::size_t i = 0; i < num_bytes; i++)
    {
        print_byte_as_bits(bytes[i]);
        printf(" ");
        if (i % 8 == 7 && i != num_bytes - 1)
        {
            printf("\n ");
        }
    }
    printf("]\n");
}
