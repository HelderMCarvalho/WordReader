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

/**
 * Função que insere Frequências de Palavras ordenadas por ordem crescente de Quantidade
 * @param listaFrequenciaPalavrasOrdenada -> lista de Frequências de Palavras ordenadas existentes
 * @param palavra -> palavra a inserir
 * @return -> lista de Frequências de Palavras ordenadas atualizada
 */
FrequenciaPalavras *
InserirFrequenciaPalavrasOrdenadas(FrequenciaPalavras *listaFrequenciaPalavrasOrdenada,
                                   FrequenciaPalavrasTree *palavra) {
    if (!listaFrequenciaPalavrasOrdenada || listaFrequenciaPalavrasOrdenada->quantidade >= palavra->quantidade) {
        FrequenciaPalavras *node = CALLOC(1, FrequenciaPalavras);
        node->palavra = palavra->palavra;
        node->quantidade = palavra->quantidade;
        node->next = listaFrequenciaPalavrasOrdenada;
        listaFrequenciaPalavrasOrdenada = node;
    } else {
        listaFrequenciaPalavrasOrdenada->next = InserirFrequenciaPalavrasOrdenadas(
                listaFrequenciaPalavrasOrdenada->next,
                palavra);
    }
    return listaFrequenciaPalavrasOrdenada;
}

/**
 * Função que insere Freqências de Palavras ordenadas por ordem alfabética de A a Z
 * Sempre que encontra uma palavra duplicada aumenta a sua quantidade
 * @param frequenciaPalavrasTree -> árvore de Frequências de Palavras
 * @param palavra -> palavra a inserir
 * @return -> árvore de Frequência de Palavras atualizada
 */
FrequenciaPalavrasTree *InserirFrequenciaPalavrasTree(FrequenciaPalavrasTree *frequenciaPalavrasTree, char *palavra) {
    if (frequenciaPalavrasTree) {
        if (strcmp(palavra, frequenciaPalavrasTree->palavra) < 0) {
            frequenciaPalavrasTree->left = InserirFrequenciaPalavrasTree(frequenciaPalavrasTree->left, palavra);
        } else if (strcmp(palavra, frequenciaPalavrasTree->palavra) > 0) {
            frequenciaPalavrasTree->right = InserirFrequenciaPalavrasTree(frequenciaPalavrasTree->right, palavra);
        } else if (strcmp(palavra, frequenciaPalavrasTree->palavra) == 0) {
            frequenciaPalavrasTree->quantidade++;
        }
    } else {
        frequenciaPalavrasTree = CALLOC(1, FrequenciaPalavrasTree);
        frequenciaPalavrasTree->palavra = strdup(palavra);
        frequenciaPalavrasTree->quantidade = 1;
        frequenciaPalavrasTree->left = frequenciaPalavrasTree->right = NULL;
    }
    return frequenciaPalavrasTree;
}

/**
 * Função que procura uma Frequência de Palavra
 * @param frequenciaPalavrasTree -> árvore de Frequências de Palavras
 * @param palavra -> palavra a procurar
 * @return -> NULL se não encontrar a palavra | frequenciaPalavrasTree se encontrar a palavra
 */
FrequenciaPalavrasTree *ProcurarFrequenciaPalavrasTree(FrequenciaPalavrasTree *frequenciaPalavrasTree, char *palavra) {
    if (frequenciaPalavrasTree) {
        if (strcmp(palavra, frequenciaPalavrasTree->palavra) < 0) {
            return ProcurarFrequenciaPalavrasTree(frequenciaPalavrasTree->left, palavra);
        } else if (strcmp(palavra, frequenciaPalavrasTree->palavra) > 0) {
            return ProcurarFrequenciaPalavrasTree(frequenciaPalavrasTree->right, palavra);
        } else {
            return frequenciaPalavrasTree;
        }
    } else {
        return NULL;
    }
}

/**
 * Função que cria uma lista de Frequências de Palavras Palavras ordenadas por ordem crescente de Quantidade
 * @param frequenciaPalavrasTree -> árvore de Frequências de Palavras
 * @param listaFrequenciaPalavrasOrdenada -> lista de Frequências de Palavras ordenadas
 * @return -> lista de Frequências de Palavras ordenadas atualizada
 */
FrequenciaPalavras *CriarListaOrdenada(FrequenciaPalavrasTree *frequenciaPalavrasTree,
                                       FrequenciaPalavras *listaFrequenciaPalavrasOrdenada) {
    if (frequenciaPalavrasTree) {
        listaFrequenciaPalavrasOrdenada = InserirFrequenciaPalavrasOrdenadas(listaFrequenciaPalavrasOrdenada,
                                                                             frequenciaPalavrasTree);
        listaFrequenciaPalavrasOrdenada = CriarListaOrdenada(frequenciaPalavrasTree->left,
                                                             listaFrequenciaPalavrasOrdenada);
        listaFrequenciaPalavrasOrdenada = CriarListaOrdenada(frequenciaPalavrasTree->right,
                                                             listaFrequenciaPalavrasOrdenada);
    }
    return listaFrequenciaPalavrasOrdenada;
}

/**
 * Ex. 6
 * Procedimento que lista as Frequências de Palavras ordenadas por ordem crescente de Quantidade
 * Verifica qual o Quartil ao qual uma Palavra introduzida pertence
 * @param frequenciaPalavrasTree -> árvore de Frequências de Palavras
 * @param palavraProcurada -> palavra a verificar posição de Quartil
 */
void
ListarFrequenciaPalavras(FrequenciaPalavrasTree *frequenciaPalavrasTree, FrequenciaPalavrasTree *palavraProcurada) {
    int *quantidades = NULL, countQuantidades = 0;
    float *quartis = NULL;
    printf("\n\n----- LISTA DE FREQUÊNCIA DE PALAVRAS -----\n\n");
    FrequenciaPalavras *listaFrequenciaPalavrasOrdenada = NULL;
    listaFrequenciaPalavrasOrdenada = CriarListaOrdenada(frequenciaPalavrasTree, listaFrequenciaPalavrasOrdenada);
    while (listaFrequenciaPalavrasOrdenada) {
        quantidades = (countQuantidades == 0) ? CALLOC(1, int) : realloc(quantidades,
                                                                         sizeof(int) * countQuantidades + 1);
        quantidades[countQuantidades++] = listaFrequenciaPalavrasOrdenada->quantidade;
        printf("\tPalavra: %s\n", listaFrequenciaPalavrasOrdenada->palavra);
        printf("\tQuantidade: %d\n\n", listaFrequenciaPalavrasOrdenada->quantidade);
        FrequenciaPalavras *next = listaFrequenciaPalavrasOrdenada->next;
        free(listaFrequenciaPalavrasOrdenada);
        listaFrequenciaPalavrasOrdenada = next;
    }
    quartis = Quartis(quantidades, countQuantidades);
    for (int i = 1; i <= 3; i++) {
        printf("\tQuartil %d: %f\n", i, quartis[i - 1]);
    }
    if ((float) palavraProcurada->quantidade < quartis[0]) {
        printf("\n\tA Palavra introduzida está entre o Mínimo e o Quartil 1.");
    } else if ((float) palavraProcurada->quantidade == quartis[0] ||
               (float) palavraProcurada->quantidade < quartis[1]) {
        printf("\n\tA Palavra introduzida pertence ao Quartil 1.");
    } else if ((float) palavraProcurada->quantidade == quartis[1]) {
        printf("\n\tA Palavra introduzida pertence ao Quartil 2 (Mediana).");
    } else if ((float) palavraProcurada->quantidade > quartis[1] &&
               (float) palavraProcurada->quantidade <= quartis[2]) {
        printf("\n\tA Palavra introduzida pertence ao Quartil 3.");
    } else {
        printf("\n\tA Palavra introduzida está entre o Quartil 3 e o Máximo.");
    }
    free(quartis);
    free(quantidades);
}
