#include "cachedsort.hpp"
#include <iostream>
#include <assert.h>

enum class CachedOperation
{
    Compare,
    NewBranch,
};

struct cachedTreeOperation
{
    int operation; //0 compare, //1 trocar de folha //2 finalizar 2 ordenas
    int posToCompare;
    cachedTreeOperation *left{nullptr};
    cachedTreeOperation *right{nullptr};
    int *order{nullptr};
};

cachedTreeOperation *root;

void cachedSort(int *list, const int &size)
{
    int pos = 1;
    auto leaf = root;
    for (;;)
    {
        if (leaf->operation == (int)CachedOperation::NewBranch)
        {
            pos++;
            if (pos < size)
            {
                break;
            }
        }
        //Compara novos registros
        if (list[leaf->posToCompare] > list[pos])
        {
            leaf = leaf->left;
        }
        else
        {
            leaf = leaf->right;
        }
    }
}

/**
 * Criar a lista de ordenada para do nó
 */
void makeCachedOrder(cachedTreeOperation *leaf, const int &size, cachedTreeOperation *lastLeafOrdered)
{
    leaf->order = new int[size];
    if (size == 0) {
        leaf->order[0] = 0;
    } else {
        std::copy(lastLeafOrdered->order, lastLeafOrdered->order + size - 1, lastLeafOrdered->order);
    }
}

/**
 * 
 */
cachedTreeOperation *makeTree(
    const CachedOperation &nextOperation,
    const int &leftPos,
    const int &rightPos,
    const int &currentLevel,
    const int &maxLevel,
    cachedTreeOperation *lastLeafOrdered)
{
    //Fim do nó
    if (currentLevel + 1 > maxLevel)
    {
        return 0;
    }
    //Posição do meio
    const int middle = (leftPos + rightPos) / 2;
    //Nova operação
    auto leaf = new cachedTreeOperation;
    leaf->operation = (int)nextOperation;

    switch (nextOperation)
    {
    //Se for um novo ramo de posições o cache de ordenação até a posição atual.
    case CachedOperation::NewBranch:
    {
        //Inicia primeira posição da arvore
        if (!lastLeafOrdered)
        {
            lastLeafOrdered = root;
        }
        makeCachedOrder(leaf, currentLevel, lastLeafOrdered);
    }
    //Se não for um novo ramo cria o cache de comparação
    case CachedOperation::Compare:
    {
        leaf->posToCompare = middle;
        //Ultima comparação á esquerda
        const bool lastLeftComparison = leftPos == middle;
        //Ultima comparação á direita
        const bool lastRightComparison = rightPos == middle;
        leaf->left = new cachedTreeOperation;
        leaf->right = new cachedTreeOperation;
        if (lastLeftComparison)
        {
            lastLeafOrdered->posToCompare = middle;
            leaf->left = makeTree(CachedOperation::NewBranch, 0, currentLevel + 1, currentLevel + 1, maxLevel, lastLeafOrdered);
        }
        else
        {
            leaf->left = makeTree(CachedOperation::Compare, leftPos, middle - 1, currentLevel, maxLevel, lastLeafOrdered);
        }
        if (lastRightComparison)
        {
            lastLeafOrdered->posToCompare = middle + 1;
            leaf->right = makeTree(CachedOperation::NewBranch, 0, currentLevel + 1, currentLevel + 1, maxLevel, lastLeafOrdered);
        }
        else
        {
            leaf->right = makeTree(CachedOperation::Compare, middle + 1, rightPos, currentLevel, maxLevel, lastLeafOrdered);
        }
        break;
    }
    default:
        break;
    }
    return leaf;
}

void makeTree(const int &size)
{
    assert(size > 1);
    root = makeTree(CachedOperation::NewBranch, 0, 0, 0, size - 1, nullptr);
}
/*
321 231 213   312 132 123
21            12
1
*/
