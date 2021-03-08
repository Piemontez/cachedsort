#include <stdio.h>
#include <iostream>
#include <chrono>
#include <list>

#include "tools.hpp"

#define LIST_SIZE 8
#define TESTS_AMOUNT 10

int *cachedSort(const int *list, const int &size);

int main(int argc, char **argv)
{
    std::cout << "Start tests with sorted lists."
              << std::endl
              << "List size: " << LIST_SIZE
              << std::endl
              << "Unordered lists:" << TESTS_AMOUNT
              << std::endl;

    std::cout << "Creating unordered lists." << std::endl;

    std::clock_t startTime, endTime;
    int totalTime;

    //Lista ordenada
    int *ordered = makeOrderedList(LIST_SIZE);
    //Listagem a ordenar
    int **unordered = makeUnorderedList(LIST_SIZE, TESTS_AMOUNT);
    //Algoritmos de ordenação;
    std::list<sort> sorts;
    sorts.push_back(cachedSort);
    //Listagem retornado pelo ordenador;
    int *tocheck;

    for (auto &sort : sorts)
    {
        for (int j = 0; j < TESTS_AMOUNT; j++)
        {
            startTime = std::clock();
            tocheck = sort(unordered[j], LIST_SIZE);
            endTime = std::clock();

            totalTime += endTime - startTime;

            bool isEqual = isEquals(ordered, tocheck, LIST_SIZE);
            std::cout << "Alg:  "
                      << " Test: " << j
                      << " Ordened: " << (isEqual ? "true" : "false")
                      << " Time: " << (endTime - startTime)
                      << std::endl;
        }
    }
}

int *cachedSort(const int *list, const int &size) {
    return makeOrderedList(LIST_SIZE);
}