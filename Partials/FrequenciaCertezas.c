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

/**
 * Função que insere Frequência de Certezas
 * @param listaFrequenciaCerteza -> lista de Frequência de Certezas existentes
 * @param certeza -> certeza a inserir
 * @return -> lista de Frequência de Certezas atualizada
 */
FrequenciaCertezas *
InserirFrequenciaCerteza(FrequenciaCertezas *listaFrequenciaCerteza, FrequenciaCertezasTree *certeza) {
    FrequenciaCertezas *node = CALLOC(1, FrequenciaCertezas);
    node->certeza = certeza->certeza;
    node->quantidade = certeza->quantidade;
    node->next = listaFrequenciaCerteza;
    return node;
}

/**
 * Função que insere Frequências de Certezas ordenadas por ordem crescente de certeza
 * @param frequenciaCertezasTree -> árvore de Frequências de Certezas
 * @param certeza -> certeza a inserir
 * @return -> árvode de Frequências de Certezas atualizada
 */
FrequenciaCertezasTree *InserirFrequenciaCertezaTree(FrequenciaCertezasTree *frequenciaCertezasTree, float certeza) {
    if (frequenciaCertezasTree) {
        if (certeza < frequenciaCertezasTree->certeza) {
            frequenciaCertezasTree->left = InserirFrequenciaCertezaTree(frequenciaCertezasTree->left, certeza);
        } else if (certeza > frequenciaCertezasTree->certeza) {
            frequenciaCertezasTree->right = InserirFrequenciaCertezaTree(frequenciaCertezasTree->right, certeza);
        } else if (certeza == frequenciaCertezasTree->certeza) {
            frequenciaCertezasTree->quantidade++;
        }
    } else {
        frequenciaCertezasTree = CALLOC(1, FrequenciaCertezasTree);
        frequenciaCertezasTree->certeza = certeza;
        frequenciaCertezasTree->quantidade = 1;
        frequenciaCertezasTree->left = frequenciaCertezasTree->right = NULL;
    }
    return frequenciaCertezasTree;
}

/**
 * Função que cria uma lista de Frequências de Certezas
 * @param frequenciaCertezasTree -> árvore de Frequências de Certezas
 * @param listaFrequenciaCertezas -> lista de Frequências de Certezas
 * @return -> lista de Frequências de Certezas atualizada
 */
FrequenciaCertezas *CriarListaFrequenciaCertezas(FrequenciaCertezasTree *frequenciaCertezasTree,
                                                 FrequenciaCertezas *listaFrequenciaCertezas) {
    if (frequenciaCertezasTree) {
        listaFrequenciaCertezas = CriarListaFrequenciaCertezas(frequenciaCertezasTree->left, listaFrequenciaCertezas);
        listaFrequenciaCertezas = InserirFrequenciaCerteza(listaFrequenciaCertezas, frequenciaCertezasTree);
        listaFrequenciaCertezas = CriarListaFrequenciaCertezas(frequenciaCertezasTree->right, listaFrequenciaCertezas);
    }
    return listaFrequenciaCertezas;
}

/**
 * Procedimento que lista as Frequências de Certezas
 * Calcula e mostra o Histograma das Frequências de Certezas
 * @param frequenciaCertezasTree -> árvore de Frequências de Certezas
 */
void ListarFrequenciaCertezas(FrequenciaCertezasTree *frequenciaCertezasTree) {
    FrequenciaCertezas *listaFrequenciaCertezas = NULL;
    float ranges[11] = {0, (float) 0.1, (float) 0.2, (float) 0.3, (float) 0.4, (float) 0.5, (float) 0.6, (float) 0.7,
                        (float) 0.8, (float) 0.9, 1};
    int rangeCounts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    listaFrequenciaCertezas = CriarListaFrequenciaCertezas(frequenciaCertezasTree, listaFrequenciaCertezas);
    printf("\n\n----- HISTOGRAMA DE FREQUÊNCIA DE CERTEZAS -----\n");
    while (listaFrequenciaCertezas) {
        // Aqui entra se a certeza == 1
        if (listaFrequenciaCertezas->certeza == 1) {
            rangeCounts[9] += listaFrequenciaCertezas->quantidade;
        } else {
            for (int i = 0; i < 11; i++) {
                // Verifica se está dentro do intervalo
                if (listaFrequenciaCertezas->certeza >= ranges[i] && listaFrequenciaCertezas->certeza < ranges[i + 1]) {
                    rangeCounts[i] += listaFrequenciaCertezas->quantidade;
                    break;
                }
            }
        }
        FrequenciaCertezas *next = listaFrequenciaCertezas->next;
        free(listaFrequenciaCertezas);
        listaFrequenciaCertezas = next;
    }
    for (int i = 0; i < 10; i++) {
        printf("\n\t| %.1f - %.1f | %d palavras |", ranges[i], ranges[i + 1], rangeCounts[i]);
    }
}
