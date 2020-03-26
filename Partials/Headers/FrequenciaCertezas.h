/**
 * Estrutura (lista) que guarda o número de ocorrências de cada certeza
 * Utilizada no Ex. 7
 */
typedef struct _frequenciaCerteza {
    float certeza;
    int quantidade;
    struct _frequenciaCerteza *next;
} FrequenciaCertezas;

/**
 * Estrutura (árvore) que guarda o número de ocorrências de cada certeza ordenadas por ordem alfabética crescente
 * Utilizada para melhorar o desempenho da leitura do ficheiro
 */
typedef struct _frequenciaCertezaTree {
    float certeza;
    int quantidade;
    struct _frequenciaCertezaTree *left, *right;
} FrequenciaCertezasTree;

FrequenciaCertezas *
InserirFrequenciaCerteza(FrequenciaCertezas *listaFrequenciaCerteza, FrequenciaCertezasTree *certeza);

FrequenciaCertezasTree *InserirFrequenciaCertezaTree(FrequenciaCertezasTree *frequenciaCertezasTree, float certeza);

FrequenciaCertezas *CriarListaFrequenciaCertezas(FrequenciaCertezasTree *frequenciaCertezasTree,
                                                 FrequenciaCertezas *listaFrequenciaCertezas);

void ListarFrequenciaCertezas(FrequenciaCertezasTree *frequenciaCertezasTree);
