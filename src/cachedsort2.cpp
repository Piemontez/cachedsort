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

cachedTreeOperation *root2;

void cachedSort2(int *list, const int &size)
{
    ADD_OPERATION_COUNT("CACHED2", OperationType::Others, 3);
    auto leaf = root2;
    int pos = 1;
    for (;;)
    {
        ADD_OPERATION_COUNT("CACHED2", OperationType::Loop, 1);
        //Compara novos registros
        ADD_OPERATION_COUNT("CACHED2", OperationType::Conditional, 1);
        ADD_OPERATION_COUNT("CACHED2", OperationType::Compare, 1);
        if (list[leaf->posToCompare] > list[pos])
        {
            ADD_OPERATION_COUNT("CACHED2", OperationType::Others, 1);
            leaf = leaf->left;
        }
        else
        {
            ADD_OPERATION_COUNT("CACHED2", OperationType::Others, 1);
            leaf = leaf->right;
        }

        //Se trocou de ramo
        ADD_OPERATION_COUNT("CACHED2", OperationType::Conditional, 1);
        if (leaf->operation == (int)CachedOperation::NewBranch)
        {
            ADD_OPERATION_COUNT("CACHED2", OperationType::AcumulatorChange, 1);
            pos++;
            ADD_OPERATION_COUNT("CACHED2", OperationType::Conditional, 1);
            if (pos == size)
            {
                break;
            }
        }
    }
    //Reordena listagem conforme cache
    ADD_OPERATION_COUNT("CACHED2", OperationType::Others, 1);
    ADD_OPERATION_COUNT("CACHED2", OperationType::Conditional, 1);
    
    for (int pos = 0; pos < size; pos++)
    {
        ADD_OPERATION_COUNT("CACHED2", OperationType::Loop, 1);
        ADD_OPERATION_COUNT("CACHED2", OperationType::Swap, 1);
        std::swap(list[pos], list[leaf->order[pos]]);

        ADD_OPERATION_COUNT("CACHED2", OperationType::AcumulatorChange, 1);
        ADD_OPERATION_COUNT("CACHED2", OperationType::Conditional, 1);
    }
}

/**
 * Criar a lista ordenada para cada do nó
 * @param leaf nova folha
 * @param currentLevel nivel do ramo 
 * @param lastLeafOrdered folha com a ultima ordenação
 * @param newPos posição do novo item na lista
 */
void makeCachedOrder2(cachedTreeOperation *leaf, const int &currentLevel, cachedTreeOperation *lastLeafOrdered, const int &newPos)
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
}

/**
 * Modifica a lista de ordem para as movimentações necessárias para realizar a ordenação
 * Ex: uma lista com os números 321 apenas precisam mover a posição 3 para a 1 para ordenar a lista
 * @param leaf nova folha
 * @param currentLevel nivel do ramo 
 */
void makeCachedMoveOrder2(cachedTreeOperation *leaf, const int &currentLevel)
{
    int aux;
    auto order = new int[currentLevel];
    if (currentLevel != 0)
    {
        //leaf->order[0] = leaf->order[0];
        order[0] = leaf->order[0];

        for (int pos = 1; pos <= currentLevel; pos++)
        {
            //Se o próximo cache foi movido de posição consulta a posição
            if (leaf->order[pos] < pos)
            {
                aux = order[leaf->order[pos]];
                while (aux < pos && aux != order[aux])
                {
                    aux = order[aux];
                }
                order[pos] = aux;
                leaf->order[pos] = aux;
            }
            else
            {
                order[pos] = leaf->order[pos];
                //leaf->order[pos] = leaf->order[pos];
            }
        }
    }
}
/*
3210  3210
3223

*/

/**
 * 
 */
cachedTreeOperation *makeTree2(
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
        makeCachedOrder2(leaf, currentLevel, lastLeafOrdered, newPos);
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

        leaf->posToCompare = lastLeafOrdered->order[middle];
        if (lastLeftComparison)
        {
            leaf->left = makeTree2(CachedOperation::NewBranch, 0, currentLevel + 1, currentLevel + 1, maxLevel, lastLeafOrdered, middle);
            makeCachedMoveOrder2(leaf->left, currentLevel + 1);
        }
        else
        {
            leaf->left = makeTree2(CachedOperation::Compare, leftPos, middle - 1, currentLevel, maxLevel, lastLeafOrdered, 0);
        }
        if (lastRightComparison)
        {
            leaf->right = makeTree2(CachedOperation::NewBranch, 0, currentLevel + 1, currentLevel + 1, maxLevel, lastLeafOrdered, middle + 1);
            makeCachedMoveOrder2(leaf->right, currentLevel + 1);
        }
        else
        {
            leaf->right = makeTree2(CachedOperation::Compare, middle + 1, rightPos, currentLevel, maxLevel, lastLeafOrdered, 0);
        }

        break;
    }
    default:
        break;
    }

    return leaf;
}

void makeTree2(const int &size)
{
    assert(size > 1);
    root2 = makeTree2(CachedOperation::NewBranch, 0, 0, 0, size - 1, nullptr, 0);
}
/*
321 231 213   312 132 123
21            12
1
*/
