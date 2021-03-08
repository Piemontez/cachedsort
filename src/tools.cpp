#include <iostream>
#include <time.h> /* time */

#include "tools.hpp"

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

int *makeOrderedList(const int listsize)
{
    srand(time(NULL));

    int *array = new int[listsize];
    for (int i = 0; i < listsize; ++i)
    {
        array[i] = i;
    }
    return array;
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