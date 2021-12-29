#include "cachedsort.hpp"
#include "tools.hpp"

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <bitset>

void cachedSort3(int *list, const int &size)
{
    //Aloca o espaço em memória para o cache de comparações
    const int bytesPerIdx = (int)sqrt(size - 1) / 8 + 1;
    const int bitsPerIdx = bytesPerIdx * 8;
    const int bits = bitsPerIdx * size;
    unsigned short *cachedtree = (unsigned short *)malloc(bits / 8);

    //std::cout << "\ncachedSort3.ListSize:" << size;
    //std::cout << "\ncachedSort3.BitsNeededPerIdx:" << sqrt(size);
    //std::cout << "\ncachedSort3.BitsPerIdx:" << bitsPerIdx;
    //std::cout << "\ncachedSort3.BytesPerIdx:" << bytesPerIdx;
    //std::cout << "\ncachedSort3.Bits." << bits;
    //std::cout << "\ncachedSort3.Bytes." << bits / 8;

    int left, right, middle, pos, shiftPos;

    //Inicializa a primeira comparação
    cachedtree[size - 1] |= size - 1;
    //Percorre as posições da lista do final para o começo
    for (pos = size - 2; pos > -1; pos--)
    {
        left = pos + 1;
        right = size - 1;
        //Realiza as comparações conforme cache de comparações
        while (left != right)
        {
            middle = (left + right) / 2;
            if (list[pos] < list[(int)cachedtree[middle]])
            {
                right = middle;
            }
            else
            {
                if (left == middle)
                    left = right;
                else
                    left = middle;
            }
        }
        //Identifica a posição da próxim
        shiftPos = list[pos] < list[(int)cachedtree[left]]
                       ? left - 1
                       : left;
        //Realoaca as posições do cache incluindo nova posição
        memmove(cachedtree + pos, cachedtree + pos + 1, shiftPos - pos);
        cachedtree[shiftPos] = pos;
    }
    //print_bits((unsigned char *)cachedtree, bits / 8);

    //Ordena lista conforme cache de comparações
    auto newList = new int[size];
    for (int pos = 0; pos < size; pos++)
    {
        newList[pos] = list[(int)cachedtree[pos]];
    }
    std::copy(newList, newList + size, list);

    delete[] newList;
    free(cachedtree);
}