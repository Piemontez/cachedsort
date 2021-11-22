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
{                                        //Estrutura dos elementos na arvore
    int posToCompare;                    //Posição a ser comparada
    int *order{nullptr};                 //Lista com as posições ordenadas
    cachedTreeOperation *left{nullptr};  //Próximo nó com a posição a ser comparada
    cachedTreeOperation *right{nullptr}; //Próximo nó com a posição a ser comparada
    int operation;                       //Identifica se esta num novo ramo da arvore
};

cachedTreeOperation *root;

void cachedSort(int *list, const int &size)
{
    ADD_OPERATION_COUNT("CACHED", OperationType::Others, 3);
    auto leaf = root; //Nó atual com as comparações a serem realizadas
    int pos = 1;      //Indicador de posição
    for (;;)
    {
        ADD_OPERATION_COUNT("CACHED", OperationType::Loop, 1);
        //Compara novos registros
        ADD_OPERATION_COUNT("CACHED", OperationType::Conditional, 1);
        ADD_OPERATION_COUNT("CACHED", OperationType::Compare, 1);
        ADD_OPERATION_COUNT("CACHED", OperationType::Others, 1);
        //Compara o alvo a ser comparado
        //com o valor da posição indicada no cached sort
        leaf = list[leaf->posToCompare] > list[pos]
                   ? leaf->left   //Retornar a próxima comparação ou ramo
                   : leaf->right; //Retornar a próxima comparação ou ramo

        //Verifica se chegou na ultima comparação do nó
        ADD_OPERATION_COUNT("CACHED", OperationType::Conditional, 1);
        if (leaf->operation == (int)CachedOperation::NewBranch)
        {
            ADD_OPERATION_COUNT("CACHED", OperationType::AcumulatorChange, 1);
            ADD_OPERATION_COUNT("CACHED", OperationType::Conditional, 1);
            if (++pos == size)
            {
                break;
            }
        }
    }
    //Reordena listagem conforme cache
    ADD_OPERATION_COUNT("CACHED", OperationType::Others, 1);
    auto newList = new int[size];
    ADD_OPERATION_COUNT("CACHED", OperationType::Others, 1);
    ADD_OPERATION_COUNT("CACHED", OperationType::Conditional, 1);
    for (int pos = 0; pos < size; pos++)
    {
        ADD_OPERATION_COUNT("CACHED", OperationType::Loop, 1);
        ADD_OPERATION_COUNT("CACHED", OperationType::Swap, 1);
        newList[pos] = list[leaf->order[pos]];

        ADD_OPERATION_COUNT("CACHED", OperationType::AcumulatorChange, 1);
        ADD_OPERATION_COUNT("CACHED", OperationType::Conditional, 1);
    }
    ADD_OPERATION_COUNT("CACHED", OperationType::Swap, size);
    std::copy(newList, newList + size, list);
}

/**
 * Criar a lista ordenada para cada do nó
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

        leaf->posToCompare = lastLeafOrdered->order[middle];
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
