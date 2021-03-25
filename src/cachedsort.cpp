#include "cachedsort.hpp"
#include <assert.h>

struct cachedTreeOperation;
cachedTreeOperation *root;

enum class CachedOperation
{
    Compare,
    NewBranch,
};

void cachedSort(int *list, const int &size)
{
}

struct cachedTreeOperation
{
    int operation; //0 compare, //1 trocar de folha //2 finalizar 2 ordenas
    int posToCompare;
    cachedTreeOperation *left{0};
    cachedTreeOperation *right{0};
    int *leftOrdered{0};  //Lista Ordenada
    int *rightOrdered{0}; //Lista Ordenada
};

/**
 * Criar a lista de ordenada para do nó
 */
void makeCachedOrder(cachedTreeOperation *leaf)
{
}

/**
 * 
 */
cachedTreeOperation *makeTree(
    const CachedOperation &nextOperation,
    const int &leftPos,
    const int &rightPos,
    const int &currentLevel,
    const int &maxLevel)
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
    leaf->posToCompare = middle;

    switch (nextOperation)
    {
    //Se for um novo ramo de posições o cache de ordenação até a posição atual.
    case CachedOperation::NewBranch:
    {
        makeCachedOrder(leaf);
    }
    //Se não for um novo ramo cria o cache de comparação
    case CachedOperation::Compare:
    {
        //Ultima comparação á esquerda
        const bool lastLeftComparison = leftPos == middle;
        //Ultima comparação á direita
        const bool lastRightComparison = rightPos == middle;
        leaf->left = new cachedTreeOperation;
        leaf->right = new cachedTreeOperation;
        if (lastLeftComparison)
        {
            leaf->left = makeTree(CachedOperation::NewBranch, 0, currentLevel + 1, currentLevel + 1, maxLevel);
        }
        else
        {
            leaf->left = makeTree(CachedOperation::Compare, leftPos, middle, currentLevel, maxLevel);
        }
        if (lastRightComparison)
        {
            leaf->right = makeTree(CachedOperation::NewBranch, 0, currentLevel + 1, currentLevel + 1, maxLevel);
        }
        else
        {
            leaf->right = makeTree(CachedOperation::Compare, middle + 1, rightPos, currentLevel, maxLevel);
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
    root = makeTree(CachedOperation::Compare, 0, 0, 0, size - 1);
}
/*
321 231 213   312 132 123
21            12
1
*/
