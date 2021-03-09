#include <iostream>

/**
 * Merge Sort
 */
void merge(int vetor[], int comeco, int meio, int fim)
{
    int com1 = comeco, com2 = meio + 1, comAux = 0, tam = fim - comeco + 1;
    int *vetAux;
    vetAux = (int *)malloc(tam * sizeof(int));

    while (com1 <= meio && com2 <= fim)
    {
        if (vetor[com1] < vetor[com2])
        {
            vetAux[comAux] = vetor[com1];
            com1++;
        }
        else
        {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while (com1 <= meio)
    { //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while (com2 <= fim)
    { //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for (comAux = comeco; comAux <= fim; comAux++)
    { //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux - comeco];
    }

    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim)
{
    if (comeco < fim)
    {
        int meio = (fim + comeco) / 2;

        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, comeco, meio, fim);
    }
}

void mergeSort(int *list, const int &size)
{
    mergeSort(list, 0, size - 1);
}

/**
 * Quick Sort
 */
void quickSort(int values[], int began, int end)
{
    int i, j, pivo, aux;
    i = began;
    j = end - 1;
    pivo = values[(began + end) / 2];
    while (i <= j)
    {
        while (values[i] < pivo && i < end)
        {
            i++;
        }
        while (values[j] > pivo && j > began)
        {
            j--;
        }
        if (i <= j)
        {
            aux = values[i];
            values[i] = values[j];
            values[j] = aux;
            i++;
            j--;
        }
    }
    if (j > began)
        quickSort(values, began, j + 1);
    if (i < end)
        quickSort(values, i, end);
}

void quickSort(int *list, const int &size)
{
    quickSort(list, 0, size);
}

/**
 * Heap Sort
 */
void heapsort(int a[], int n)
{
    int i = n / 2, pai, filho, t;
    while (true)
    {
        if (i > 0)
        {
            i--;
            t = a[i];
        }
        else
        {
            n--;
            if (n <= 0)
                return;
            t = a[n];
            a[n] = a[0];
        }
        pai = i;
        filho = i * 2 + 1;
        while (filho < n)
        {
            if ((filho + 1 < n) && (a[filho + 1] > a[filho]))
                filho++;
            if (a[filho] > t)
            {
                a[pai] = a[filho];
                pai = filho;
                filho = pai * 2 + 1;
            }
            else
            {
                break;
            }
        }
        a[pai] = t;
    }
}
void heapSort(int *list, const int &size)
{
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
    int i, key, j;
    for (i = 1; i < size; i++)
    {
        key = list[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are 
        greater than key, to one position ahead 
        of their current position */
        while (j >= 0 && list[j] > key)
        {
            list[j + 1] = list[j];
            j = j - 1;
        }
        list[j + 1] = key;
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