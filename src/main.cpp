#include <stdio.h>
#include <iostream>

#include "tools.hpp"

#define LIST_SIZE 8
#define TESTS_AMOUNT 10

int main(int argc, char **argv)
{
    std::cout << "Start tests with sorted lists."
              << std::endl
              << "List size: " << LIST_SIZE
              << std::endl
              << "Unordered lists:" << TESTS_AMOUNT
              << std::endl;

    std::cout << "Creating unordered lists." << std::endl;

    /*int **unordered =*/ makeUnorderedList(LIST_SIZE, TESTS_AMOUNT);
}