#include "cachedsort.hpp"
#include <assert.h>

struct cachedTreeOperation;
cachedTreeOperation *root;

enum class CachedOperation
{
    Compare = 1,
    ChangeLeaf,
    Order
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
void makeTree(
    cachedTreeOperation *leaf,
    const CachedOperation &nextOperation,
    const int &leftDivision,
    const int &rightDivision,
    const int &currentLevel,
    const int &maxLevel)
{
    const int middle = (leftDivision + rightDivision) / 2;
    leaf->operation = (int)nextOperation;
    leaf->posToCompare = middle;

    switch (nextOperation)
    {
    case CachedOperation::Compare: //Compara
    {
        //Ultima comparação
        if (leftDivision == rightDivision)
        {
            makeCachedOrder(leaf);
        }
        //Fim do nó
        if (currentLevel + 1 > maxLevel)
        {
            return;
        }
        //Ultima comparação á esquerda
        const bool lastLeftComparison = leftDivision == middle;
        //Ultima comparação á direita
        const bool lastRightComparison = rightDivision == middle;
        leaf->left = new cachedTreeOperation;
        leaf->right = new cachedTreeOperation;
        if (lastLeftComparison)
        {
            makeTree(leaf->left, CachedOperation::ChangeLeaf, 0, currentLevel + 1, currentLevel + 1, maxLevel);
        }
        else
        {
            makeTree(leaf->left, CachedOperation::Compare, leftDivision, middle, currentLevel, maxLevel);
        }
        if (lastRightComparison)
        {
            makeTree(leaf->right, CachedOperation::ChangeLeaf, 0, currentLevel + 1, currentLevel + 1, maxLevel);
        }
        else
        {
            makeTree(leaf->right, CachedOperation::Compare, middle, rightDivision, currentLevel, maxLevel);
        }
        break;
    }
    case CachedOperation::ChangeLeaf:
    case CachedOperation::Order:
    default:
        break;
    }
}

void makeTree(const int &size)
{
    assert(size > 1);
    root = new cachedTreeOperation;
    makeTree(root, CachedOperation::Compare, 0, 0, 0, size - 1);
}
/*
321 231 213   312 132 123
21            12
1
*/
