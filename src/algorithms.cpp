#include <iostream>
#include "tools.hpp"

/**
 * Merge Sort
 */
void merge(int vetor[], int comeco, int meio, int fim)
{
    ADD_OPERATION_COUNT("MERGE", OperationType::Others, 4);
    ADD_OPERATION_COUNT("MERGE", OperationType::AcumulatorChange, 2);
    int com1 = comeco, com2 = meio + 1, comAux = 0, tam = fim - comeco + 1;
    ADD_OPERATION_COUNT("MERGE", OperationType::Others, 2);
    int *vetAux;
    vetAux = (int *)malloc(tam * sizeof(int));

    ADD_OPERATION_COUNT("MERGE", OperationType::Conditional, 2);
    while (com1 <= meio && com2 <= fim)
    {
        ADD_OPERATION_COUNT("MERGE", OperationType::Loop, 1);
        ADD_OPERATION_COUNT("MERGE", OperationType::Compare, 1);
        if (vetor[com1] < vetor[com2])
        {
            ADD_OPERATION_COUNT("MERGE", OperationType::AcumulatorChange, 1);
            ADD_OPERATION_COUNT("MERGE", OperationType::Swap, 1);
            vetAux[comAux] = vetor[com1];
            com1++;
        }
        else
        {
            ADD_OPERATION_COUNT("MERGE", OperationType::AcumulatorChange, 1);
            ADD_OPERATION_COUNT("MERGE", OperationType::Swap, 1);
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        ADD_OPERATION_COUNT("MERGE", OperationType::AcumulatorChange, 1);
        comAux++;
        ADD_OPERATION_COUNT("MERGE", OperationType::Conditional, 1);
    }

    ADD_OPERATION_COUNT("MERGE", OperationType::Conditional, 1);
    while (com1 <= meio) //Caso ainda haja elementos na primeira metade
    {
        ADD_OPERATION_COUNT("MERGE", OperationType::Loop, 1);
        ADD_OPERATION_COUNT("MERGE", OperationType::Swap, 1);
        ADD_OPERATION_COUNT("MERGE", OperationType::AcumulatorChange, 2);
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
        ADD_OPERATION_COUNT("MERGE", OperationType::Conditional, 1);
    }

    ADD_OPERATION_COUNT("MERGE", OperationType::Conditional, 1);
    while (com2 <= fim) //Caso ainda haja elementos na segunda metade
    {
        ADD_OPERATION_COUNT("MERGE", OperationType::Loop, 1);
        ADD_OPERATION_COUNT("MERGE", OperationType::Swap, 1);
        ADD_OPERATION_COUNT("MERGE", OperationType::AcumulatorChange, 2);
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
        ADD_OPERATION_COUNT("MERGE", OperationType::Conditional, 1);
    }

    for (comAux = comeco; comAux <= fim; comAux++) //Move os elementos de volta para o vetor original
    {
        ADD_OPERATION_COUNT("MERGE", OperationType::Loop, 1);
        ADD_OPERATION_COUNT("MERGE", OperationType::Swap, 1);
        ADD_OPERATION_COUNT("MERGE", OperationType::Others, 1);
        vetor[comAux] = vetAux[comAux - comeco];
        ADD_OPERATION_COUNT("MERGE", OperationType::Compare, 1);
        ADD_OPERATION_COUNT("MERGE", OperationType::AcumulatorChange, 1);
    }

    ADD_OPERATION_COUNT("MERGE", OperationType::Others, 1);
    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim)
{
    ADD_OPERATION_COUNT("MERGE", OperationType::Conditional, 1);
    if (comeco < fim)
    {
        ADD_OPERATION_COUNT("MERGE", OperationType::Loop, 1);
        ADD_OPERATION_COUNT("MERGE", OperationType::Others, 1);
        int meio = (fim + comeco) / 2;

        ADD_OPERATION_COUNT("MERGE", OperationType::Others, 3);
        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, comeco, meio, fim);
        ADD_OPERATION_COUNT("MERGE", OperationType::Compare, 1);
    }
}

void mergeSort(int *list, const int &size)
{
    ADD_OPERATION_COUNT("MERGE", OperationType::Others, 1);
    mergeSort(list, 0, size - 1);
}

/**
 * Quick Sort
 */
void quickSort(int values[], int began, int end)
{
    ADD_OPERATION_COUNT("QUICK", OperationType::Others, 4);
    int i, j, pivo, aux;
    ADD_OPERATION_COUNT("QUICK", OperationType::Others, 2);
    i = began;
    j = end - 1;
    ADD_OPERATION_COUNT("QUICK", OperationType::Others, 4);
    pivo = values[(began + end) / 2];
    ADD_OPERATION_COUNT("QUICK", OperationType::Conditional, 1);
    while (i <= j)
    {
        ADD_OPERATION_COUNT("QUICK", OperationType::Loop, 1);
        ADD_OPERATION_COUNT("QUICK", OperationType::Compare, 1);
        ADD_OPERATION_COUNT("QUICK", OperationType::Conditional, 1);
        while (values[i] < pivo && i < end)
        {
            ADD_OPERATION_COUNT("QUICK", OperationType::Loop, 1);
            ADD_OPERATION_COUNT("QUICK", OperationType::AcumulatorChange, 1);
            i++;
            ADD_OPERATION_COUNT("QUICK", OperationType::Compare, 1);
            ADD_OPERATION_COUNT("QUICK", OperationType::Conditional, 1);
        }
        ADD_OPERATION_COUNT("QUICK", OperationType::Compare, 1);
        ADD_OPERATION_COUNT("QUICK", OperationType::Conditional, 1);
        while (values[j] > pivo && j > began)
        {
            ADD_OPERATION_COUNT("QUICK", OperationType::Loop, 1);
            ADD_OPERATION_COUNT("QUICK", OperationType::AcumulatorChange, 1);
            j--;
            ADD_OPERATION_COUNT("QUICK", OperationType::Compare, 1);
            ADD_OPERATION_COUNT("QUICK", OperationType::Conditional, 1);
        }
        ADD_OPERATION_COUNT("QUICK", OperationType::Conditional, 1);
        if (i <= j)
        {
            ADD_OPERATION_COUNT("QUICK", OperationType::Others, 1);
            aux = values[i];
            ADD_OPERATION_COUNT("QUICK", OperationType::Swap, 2);
            values[i] = values[j];
            values[j] = aux;
            ADD_OPERATION_COUNT("QUICK", OperationType::AcumulatorChange, 2);
            i++;
            j--;
        }
        ADD_OPERATION_COUNT("QUICK", OperationType::Conditional, 1);
    }
    ADD_OPERATION_COUNT("QUICK", OperationType::Conditional, 1);
    if (j > began)
    {
        ADD_OPERATION_COUNT("QUICK", OperationType::Others, 1);
        quickSort(values, began, j + 1);
    }
    ADD_OPERATION_COUNT("QUICK", OperationType::Conditional, 1);
    if (i < end)
    {
        ADD_OPERATION_COUNT("QUICK", OperationType::Others, 1);
        quickSort(values, i, end);
    }
}

void quickSort(int *list, const int &size)
{
    ADD_OPERATION_COUNT("QUICK", OperationType::Others, 1);
    quickSort(list, 0, size);
}

/**
 * Heap Sort
 */
void heapsort(int a[], int n)
{
    ADD_OPERATION_COUNT("HEAP", OperationType::Others, 5);
    int i = n / 2, pai, filho, t;
    for (;;)
    {
        ADD_OPERATION_COUNT("HEAP", OperationType::Loop, 1);
        ADD_OPERATION_COUNT("HEAP", OperationType::Conditional, 1);
        if (i > 0)
        {
            ADD_OPERATION_COUNT("HEAP", OperationType::AcumulatorChange, 1);
            ADD_OPERATION_COUNT("HEAP", OperationType::Others, 1);
            i--;
            t = a[i];
        }
        else
        {
            ADD_OPERATION_COUNT("HEAP", OperationType::AcumulatorChange, 1);
            n--;
            ADD_OPERATION_COUNT("HEAP", OperationType::Conditional, 1);
            if (n <= 0)
                return;
            ADD_OPERATION_COUNT("HEAP", OperationType::Swap, 2);
            t = a[n];
            a[n] = a[0];
        }
        ADD_OPERATION_COUNT("HEAP", OperationType::Others, 4);
        pai = i;
        filho = i * 2 + 1;

        ADD_OPERATION_COUNT("HEAP", OperationType::Conditional, 1);
        while (filho < n)
        {
            ADD_OPERATION_COUNT("HEAP", OperationType::Loop, 1);
            ADD_OPERATION_COUNT("HEAP", OperationType::Conditional, 2);
            ADD_OPERATION_COUNT("HEAP", OperationType::Compare, 1);
            ADD_OPERATION_COUNT("HEAP", OperationType::Others, 1);
            if ((filho + 1 < n) && (a[filho + 1] > a[filho]))
            {
                ADD_OPERATION_COUNT("HEAP", OperationType::AcumulatorChange, 1);
                filho++;
            }
            if (a[filho] > t)
            {
                ADD_OPERATION_COUNT("HEAP", OperationType::Swap, 1);
                a[pai] = a[filho];
                ADD_OPERATION_COUNT("HEAP", OperationType::Others, 1);
                pai = filho;
                ADD_OPERATION_COUNT("HEAP", OperationType::Others, 3);
                filho = pai * 2 + 1;
            }
            else
            {
                break;
            }
        }
        ADD_OPERATION_COUNT("HEAP", OperationType::Swap, 1);
        a[pai] = t;
    }
}
void heapSort(int *list, const int &size)
{
    ADD_OPERATION_COUNT("HEAP", OperationType::Others, 1);
    heapsort(list, size);
}

/**
 * Selection Sort
 */
void selectionSort(int *list, const int &size)
{
    int i, j, min, aux;
    for (i = 0; i < (size - 1); i++)
    {
        min = i;
        for (j = (i + 1); j < size; j++)
        {
            if (list[j] < list[min])
                min = j;
        }
        if (i != min)
        {
            aux = list[i];
            list[i] = list[min];
            list[min] = aux;
        }
    }
}

/**
 * Shell Sort
 */
int shellSort(int *list, const int &size)
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i += 1)
        {
            int temp = list[i];

            int j;
            for (j = i; j >= gap && list[j - gap] > temp; j -= gap)
                list[j] = list[j - gap];

            list[j] = temp;
        }
    }
    return 0;
}

/**
 * Insertion Sort
 */
void insertionSort(int *list, const int &size)
{
    ADD_OPERATION_COUNT("INSERTION", OperationType::Others, 3);
    int i, key, j;
    ADD_OPERATION_COUNT("INSERTION", OperationType::Others, 1);
    ADD_OPERATION_COUNT("INSERTION", OperationType::Conditional, 1);
    for (i = 1; i < size; i++)
    {
        ADD_OPERATION_COUNT("INSERTION", OperationType::Loop, 1);

        ADD_OPERATION_COUNT("INSERTION", OperationType::Others, 1);
        key = list[i];
        ADD_OPERATION_COUNT("INSERTION", OperationType::AcumulatorChange, 1);
        j = i - 1;

        ADD_OPERATION_COUNT("INSERTION", OperationType::Conditional, 2);
        ADD_OPERATION_COUNT("INSERTION", OperationType::Compare, 1);
        while (j >= 0 && list[j] > key)
        {
            ADD_OPERATION_COUNT("INSERTION", OperationType::Loop, 1);

            ADD_OPERATION_COUNT("INSERTION", OperationType::Swap, 1);
            list[j + 1] = list[j];
            ADD_OPERATION_COUNT("INSERTION", OperationType::AcumulatorChange, 1);
            j = j - 1;
            ADD_OPERATION_COUNT("INSERTION", OperationType::Conditional, 2);
            ADD_OPERATION_COUNT("INSERTION", OperationType::Compare, 1);
        }
        ADD_OPERATION_COUNT("INSERTION", OperationType::Swap, 1);
        list[j + 1] = key;
        ADD_OPERATION_COUNT("INSERTION", OperationType::AcumulatorChange, 1);
        ADD_OPERATION_COUNT("INSERTION", OperationType::Conditional, 1);
    }
}

/**
 * Bubble Sort
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void bubbleSort(int *list, const int &size)
{
    if (size < 1)
        return;

    for (int i = 0; i < (size - 1 /*timelost*/); i++)
        if (list[i] > list[i + 1])
            swap(&list[i], &list[i + 1]);
    bubbleSort(list, size - 1);
}

/**
 * Tim Sort
 */
const int RUN = 32;
void timSort(int *list, const int &size)
{
    for (int i = 0; i < size; i += RUN)
        insertionSort(list + i, std::min((i + 31), size));

    for (int idx = RUN; idx < size;
         idx = 2 * idx)
    {

        for (int left = 0; left < size;
             left += 2 * idx)
        {

            int mid = left + idx - 1;
            int right = std::min((left + 2 * idx - 1),
                                 (size - 1));

            merge(list, left, mid, right);
        }
    }
}