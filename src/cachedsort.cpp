#include "cachedsort.hpp"
#include <iostream>
#include <assert.h>
#include "tools.hpp"

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
    int pos = 0;
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
    //printList(list, size);
    //printList(leaf->order, size);
}

/**
 * Criar a lista ordenada para do nó
 * @param leaf nova folha
 * @param currentLevel nivel do ramo 
 * @param lastLeafOrdered folha com a ultima ordenação
 * @param newPos posição do novo item na lista
 */
void makeCachedOrder(cachedTreeOperation *leaf, const int &currentLevel, cachedTreeOperation *lastLeafOrdered, const int &newPos)
{
    leaf->order = new int[currentLevel + 1];
    if (currentLevel == 0)
    {
        leaf->order[0] = 0;
    }
    else
    {
        std::copy(lastLeafOrdered->order, lastLeafOrdered->order + currentLevel, leaf->order);
        for (int pos = currentLevel; pos > newPos; pos--)
        {
            leaf->order[pos] = leaf->order[pos - 1];
        }
        leaf->order[newPos] = currentLevel;
    }
    //printList(leaf->order, currentLevel + 1);
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
    cachedTreeOperation *lastLeafOrdered,
    const int &newPos)
{
    //Nova operação
    auto leaf = new cachedTreeOperation;
    leaf->operation = (int)nextOperation;

    //Inicia primeira posição da arvore
    if (!lastLeafOrdered)
    {
        lastLeafOrdered = leaf;
    }

    switch (nextOperation)
    {
    //Se for um novo ramo de posições o cache de ordenação até a posição atual.
    case CachedOperation::NewBranch:
    {
        makeCachedOrder(leaf, currentLevel, lastLeafOrdered, newPos);
        lastLeafOrdered = leaf;
        //Fim do nó
        if (currentLevel + 1 > maxLevel)
        {
            return leaf;
        }
    }
    //Se não for um novo ramo cria o cache de comparação
    case CachedOperation::Compare:
    {
        //Posição do meio
        const int middle = (leftPos + rightPos) / 2;
        //Ultima comparação á esquerda
        const bool lastLeftComparison = leftPos == middle;
        //Ultima comparação á direita
        const bool lastRightComparison = rightPos == middle;

        leaf->posToCompare = middle;
        if (lastLeftComparison)
        {
            leaf->left = makeTree(CachedOperation::NewBranch, 0, currentLevel + 1, currentLevel + 1, maxLevel, lastLeafOrdered, middle);
        }
        else
        {
            leaf->left = makeTree(CachedOperation::Compare, leftPos, middle - 1, currentLevel, maxLevel, lastLeafOrdered, 0);
        }
        if (lastRightComparison)
        {
            leaf->right = makeTree(CachedOperation::NewBranch, 0, currentLevel + 1, currentLevel + 1, maxLevel, lastLeafOrdered, middle + 1);
        }
        else
        {
            leaf->right = makeTree(CachedOperation::Compare, middle + 1, rightPos, currentLevel, maxLevel, lastLeafOrdered, 0);
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
    root = makeTree(CachedOperation::NewBranch, 0, 0, 0, size - 1, nullptr, 0);
}
/*
321 231 213   312 132 123
21            12
1
*/
