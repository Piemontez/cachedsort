#include <algorithm>
#include <iostream>
#include <time.h> /* time */

#include "tools.hpp"
#include "algorithms.hpp"

int **makeUnorderedList(const int listsize, const int randomvaluesamout)
{
    srand(time(NULL));

    int **matrix = new int *[randomvaluesamout];
    if (randomvaluesamout > 0)
        matrix[0] = new int[listsize];
    if (randomvaluesamout > 1)
        matrix[1] = new int[listsize];

    for (int i = 0; i < listsize; ++i)
    {
        //Cria uma lista ordenada
        if (randomvaluesamout > 0)
        {
            matrix[0][i] = i;
        }
        //Cria uma lista ordenada invertida
        if (randomvaluesamout > 1)
        {
            matrix[1][i] = listsize - i - 1;
        }
    }
    for (int i = 2; i < randomvaluesamout; ++i)
    {
        matrix[i] = new int[listsize];
        for (int j = 0; j < listsize; ++j)
        {
            matrix[i][j] = rand() % 10 + 1;
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