#include <stdio.h>
#include <iostream>
#include <chrono>
#include <map>
#include <assert.h>
#include <iomanip>

#include "cachedsort.hpp"
#include "algorithms.hpp"
#include "tools.hpp"

#define LIST_SIZE 10
#define TESTS_AMOUNT 10

int main(int argc, char **argv)
{
    std::cout << "Start tests with sorted lists."
              << std::endl
              << "List size: " << LIST_SIZE
              << std::endl
              << "Unordered lists:" << TESTS_AMOUNT
              << std::endl;

    std::cout << "Creating cached tree." << std::endl;
    makeTree(LIST_SIZE);

    std::cout << "Creating unordered lists." << std::endl;

    //Listagem à ordenar
    int **unordered = makeUnorderedList(LIST_SIZE, TESTS_AMOUNT);
    //Algoritmos de ordenação;
    std::map<const char *, sort> sorts;
    std::map<const char *, sort>::iterator sortsIt;
    sorts["BUBLE"] = bubbleSort;
    sorts["SELECTION"] = selectionSort;
    sorts["INSERTION"] = insertionSort;
    sorts["SHELL"] = shellSort;
    sorts["HEAP"] = heapSort;
    sorts["MERGE"] = mergeSort;
    sorts["QUICK"] = quickSort;
    sorts["CACHED"] = cachedSort;
    //Listagem retornado pelo ordenador;
    int *tocheck;
    //Listagem ordenada corretamente
    int *safeOrder;
    //Totalizador
    std::clock_t startTime, endTime;
    float totalTime;
    std::map<const char *, float> totalTimes;

    for (sortsIt = sorts.begin(); sortsIt != sorts.end(); ++sortsIt)
    {
        auto sort = sortsIt->second;

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
            assert(isEqual);

            /*
            std::cout << "Alg:  "
                      << " Test: " << j
                      << " Ordened: " << (isEqual ? "true" : "false")
                      << " Time: " << (endTime - startTime)
                      << std::endl;
            */
        }
        totalTimes[sortsIt->first] = totalTime;
    }

    //Exibe o tempo médio por algorítmo
    for (auto &time : totalTimes)
    {
        std::cout << "Alg:  " << std::setw(10) << time.first
                  << " Average Time: " << std::setw(8) << (time.second / TESTS_AMOUNT)
                  << " Total Time: " << time.second
                  << std::endl;
    }
#ifdef COUNT_OPERATION
    printTotalOperations();
#endif
}
