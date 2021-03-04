#include <iostream>

#include "tools.hpp"

int **makeUnorderedList(int listsize, int randomvaluesamout)
{
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
            *matrix[0] = i;
        }
        //Cria uma lista ordenada invertida
        if (randomvaluesamout > 1)
        {
            *matrix[1] = listsize - i - 1;
        }
    }
    for (int i = 2; i < randomvaluesamout; ++i)
    {
        matrix[i] = new int[listsize];
    }
    return matrix;
}