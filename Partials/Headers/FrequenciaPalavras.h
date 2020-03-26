/**
 * Estrutura (lista) que guarda o número de ocorrências de cada palavra
 * Utilizada para as guardar ordenadas por ordem crescente de quantidade
 * Utilizada no Ex. 6
 */
typedef struct _frequenciaPalavras {
    char *palavra;
    int quantidade;
    struct _frequenciaPalavras *next;
} FrequenciaPalavras;

/**
 * Estrutura (árvore) que guarda o número de ocorrências de cada palavra ordenadas por ordem alfabética de A a Z
 * Utilizada para melhorar o desempenho da leitura do ficheiro
 */
typedef struct _frequenciaPalavrasTree {
    char *palavra;
    int quantidade;
    struct _frequenciaPalavrasTree *left, *right;
} FrequenciaPalavrasTree;

FrequenciaPalavras *InserirFrequenciaPalavrasOrdenadas(FrequenciaPalavras *listaFrequenciaPalavrasOrdenada,
                                                       FrequenciaPalavrasTree *palavra);

FrequenciaPalavrasTree *InserirFrequenciaPalavrasTree(FrequenciaPalavrasTree *frequenciaPalavrasTree, char *palavra);

FrequenciaPalavrasTree *ProcurarFrequenciaPalavrasTree(FrequenciaPalavrasTree *frequenciaPalavrasTree, char *palavra);

FrequenciaPalavras *CriarListaFrequenciaPalavrasOrdenada(FrequenciaPalavrasTree *frequenciaPalavrasTree,
                                                         FrequenciaPalavras *listaFrequenciaPalavrasOrdenada);

void ListarFrequenciaPalavras(FrequenciaPalavrasTree *frequenciaPalavrasTree, FrequenciaPalavrasTree *palavraProcurada);
