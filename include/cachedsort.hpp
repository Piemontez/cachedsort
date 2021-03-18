struct cachedTreeOperation {
    int operation; //0 compare, //1 trocar de ramo //2 finalizar 2 ordenas
    int posToCompare;
    cachedTreeOperation* left{0};
    cachedTreeOperation* right{0};
    int** orderedList;
};

/**
 * Cached Sorce
 */
void cachedSort(int *list, const int &size);

/**
 * Cria a arvore de posições para o cachedsort
 */
cachedTreeOperation* makeTree(const int* size);