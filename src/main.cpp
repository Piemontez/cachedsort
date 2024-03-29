#include <stdio.h>
#include <iostream>
#include <chrono>
#include <map>
#include <assert.h>
#include <iomanip>
#include <pthread.h>

#include "cachedsort.hpp"
#include "algorithms.hpp"
#include "tools.hpp"

#define LIST_SIZE 6
#define TESTS_QTD 0
#define TESTS_RETAKE 2

int main(int argc, char **argv)
{
    //Caso informado 0 cria todas as possibilidades de ordem para o tamanho da lista
    const unsigned long long listAmount = TESTS_QTD ? TESTS_QTD : factorial(LIST_SIZE);

    std::cout << "Start tests with sorted lists."
              << std::endl
              << "List size: " << LIST_SIZE
              << std::endl
              << "List Amount (List!):" << listAmount
              << std::endl
              << "Tests Amount:" << TESTS_RETAKE
              << std::endl
              << "Total Tests:" << (TESTS_RETAKE * listAmount)
              << std::endl;

    std::cout << "Creating cached tree." << std::endl;
    makeTree(LIST_SIZE);
    makeTree2(LIST_SIZE);

    std::cout << "Creating unordered lists." << std::endl;
    //Listagem à ordenar
    int **unordered = makeUnorderedList(LIST_SIZE, listAmount, !TESTS_QTD);

    std::cout << "Lining up algorithms." << std::endl;
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
    sorts["CPP"] = cppSort;
    //sorts["CACHED"] = cachedSort;
    //sorts["CACHED2"] = cachedSort2;
    sorts["CACHED3"] = cachedSort3;
    //Listagem retornado pelo ordenador;
    int *tocheck;
    //Listagem ordenada corretamente
    int *safeOrder;
    //Totalizador
    std::clock_t startTime, endTime;
    float totalTime;
    std::map<const char *, float> totalTimes;

    { //Altera para a prioridade máximo do pc
        int policy;
        struct sched_param param;
        pthread_getschedparam(pthread_self(), &policy, &param);
        param.sched_priority = sched_get_priority_max(policy);
        pthread_setschedparam(pthread_self(), policy, &param);
    }
    std::cout << "Starting sorting lists." << std::endl;
    for (sortsIt = sorts.begin(); sortsIt != sorts.end(); ++sortsIt)
    {
        auto sort = sortsIt->second;

        totalTime = 0;
        for (int k = 0; k < TESTS_RETAKE; k++)
        {
            for (unsigned long long j = 0; j < listAmount; j++)
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
        }
        totalTimes[sortsIt->first] = totalTime;
    }

    //Exibe o tempo médio por algorítmo
    for (auto &time : totalTimes)
    {
        std::cout << "Alg:  " << std::setw(10) << time.first
                  << " Average Time: " << std::setw(8) << (time.second / (TESTS_RETAKE * listAmount))
                  << " Total Time: " << time.second
                  << std::endl;
    }


    //Limpando a memória
    for (unsigned long long i = 0; i < listAmount; ++i)
    {
        delete[] unordered[listAmount];
    }
    delete[] unordered;
    return 0;

#ifdef COUNT_OPERATION
    printTotalOperations();
#endif
}
