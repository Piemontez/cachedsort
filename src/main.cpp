#include <stdio.h>
#include <iostream>
#include <chrono>
#include <list>

#include "cachedsort.hpp"
#include "algorithms.hpp"
#include "tools.hpp"

#define LIST_SIZE 8
#define TESTS_AMOUNT 100


int main(int argc, char **argv)
{
    std::cout << "Start tests with sorted lists."
              << std::endl
              << "List size: " << LIST_SIZE
              << std::endl
              << "Unordered lists:" << TESTS_AMOUNT
              << std::endl;

    std::cout << "Creating unordered lists." << std::endl;

    //Listagem à ordenar
    int **unordered = makeUnorderedList(LIST_SIZE, TESTS_AMOUNT);
    //Algoritmos de ordenação;
    std::list<sort> sorts;
    sorts.push_back(bubbleSort);
    sorts.push_back(selectionSort);
    sorts.push_back(insertionSort);
    sorts.push_back(shellSort);
    sorts.push_back(heapSort);
    sorts.push_back(mergeSort);
    sorts.push_back(quickSort);
    sorts.push_back(timSort);
    sorts.push_back(cachedSort);
    //Listagem retornado pelo ordenador;
    int *tocheck;
    //Listagem ordenada corretamente
    int *safeOrder;
    //Totalizador
    std::clock_t startTime, endTime;
    float totalTime;
    std::list<float> totalTimes;

    makeTree(LIST_SIZE);

    for (auto &sort : sorts)
    {
        totalTime = 0;
        for (int j = 0; j < TESTS_AMOUNT; j++)
        {
            //Cópia da listagem a ser ordenada
            tocheck = new int[LIST_SIZE];
            std::copy(unordered[j], unordered[j] + LIST_SIZE, tocheck);

            //Ordena a listagem
            startTime = std::clock();
            sort(tocheck, LIST_SIZE);
            endTime = std::clock();

            //Contabiliza o tempo gasto
            totalTime += endTime - startTime;
            //Imprime a listagem
            //printList(unordered[j], LIST_SIZE);
            //printList(tocheck, LIST_SIZE);

            //Verifica se ordenou a listagem corretamente;
            safeOrder = safeSort(unordered[j], LIST_SIZE);
            bool isEqual = isEquals(safeOrder, tocheck, LIST_SIZE);

            //Dispacha memória não utilizada
            delete[] tocheck;
            delete[] safeOrder;

            std::cout << "Alg:  "
                      << " Test: " << j
                      << " Ordened: " << (isEqual ? "true" : "false")
                      << " Time: " << (endTime - startTime)
                      << std::endl;
        }
        totalTimes.push_back(totalTime);
        std::cout << ".........." << std::endl;
    }

    //Exibe o tempo médio por algorítmo
    for (auto &time : totalTimes)
    {
            std::cout << "Alg:  "
                      << " Total Time: " << time
                      << " Average Time: " << (time / TESTS_AMOUNT)
                      << std::endl;
    }
}
