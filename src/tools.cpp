#include <algorithm>
#include <iostream>
#include <assert.h>
#include <map>
#include <cstring>
#include <time.h> /* time */
#include <iomanip>

#include "tools.hpp"
#include "algorithms.hpp"

int **makeUnorderedList(const int listsize, const int maxtests)
{
    assert(maxtests > 0);

    srand(time(NULL));

    int **matrix = new int *[maxtests];

    //Cria uma lista ordenada para o primeiro elemento do array
    matrix[0] = new int[listsize];
    matrix[maxtests] = new int[listsize];
    for (int i = 0; i < listsize; ++i)
    {
        matrix[0][i] = i;
        matrix[maxtests][i] = i;
    }
    int i = 0;
    while (std::next_permutation(matrix[maxtests], matrix[maxtests] + listsize) && i <= maxtests)
    {
        i++;
        matrix[i] = new int[listsize];
        std::copy(matrix[maxtests], matrix[maxtests] + listsize, matrix[i]);
    };

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