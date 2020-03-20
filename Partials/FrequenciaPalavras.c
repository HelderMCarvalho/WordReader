/**
 * Estrutura que guarda o número de ocorrências de cada palavra
 * Utilizada no Ex. 6                                                                   todo: Helder
 */
typedef struct _frequenciaPalavras {
    char *palavra;
    int quantidade;
    struct _frequenciaPalavras *next;
} FrequenciaPalavras;

/**
 * Função que procura Frequencia de Palavras
 * @param listaFrequenciaPalavras -> lista de Frequencia Palavras existente
 * @param palavra -> palavra a encontrar
 * @return -> FrequenciaPalavras caso encontre || NULL caso não encontre
 */
FrequenciaPalavras *
ProcurarFrequenciaPalavras(FrequenciaPalavras *listaFrequenciaPalavras, char *palavra) {
    if (!listaFrequenciaPalavras) {
        return NULL;
    } else if (strcmp(palavra, listaFrequenciaPalavras->palavra) == 0) { //todo: comparação demora muuuuuuuuuito
        return listaFrequenciaPalavras;
    }
    return ProcurarFrequenciaPalavras(listaFrequenciaPalavras->next, palavra);
}

/**
 * Função que insere/atualiza Frequencia de Palavras
 * @param listaFrequenciaPalavras -> lista de Frequencia de Palavras existentes
 * @param palavra -> palavra a inserir/atualizar
 * @return -> lista de Frequencia de Palavras atualizada
 */
FrequenciaPalavras *InserirFrequenciaPalavras(FrequenciaPalavras *listaFrequenciaPalavras, char *palavra) {
    FrequenciaPalavras *aux = ProcurarFrequenciaPalavras(listaFrequenciaPalavras, palavra);
    if (aux) {
        aux->quantidade++;
    } else {
        FrequenciaPalavras *node = MALLOC(FrequenciaPalavras);
        node->palavra = strdup(palavra);
        node->quantidade = 1;
        node->next = listaFrequenciaPalavras;
        return node;
    }
    return listaFrequenciaPalavras;
}

/**
 * Função que insere Frequências de Palavras ordenadas por Quantidade de forma crescente
 * @param listaFrequenciaPalavrasOrdenada -> lista de Frequências de Palavras ordenadas existentes
 * @param palavra -> palavra a inserir
 * @return -> lista de Frequências de Palavras ordenadas atualizadda
 */
FrequenciaPalavras *
InserirFrequenciaPalavrasOrdenadas(FrequenciaPalavras *listaFrequenciaPalavrasOrdenada, FrequenciaPalavras *palavra) {
    if (!listaFrequenciaPalavrasOrdenada || listaFrequenciaPalavrasOrdenada->quantidade >= palavra->quantidade) {
        FrequenciaPalavras *node = MALLOC(FrequenciaPalavras);
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
 * Procedimento que lista as Frequências de Palavras ordenadas por ordem crescente de Quantidade
 * Verifica qual o Quartil ao qual uma Palavra introduzida pertence
 * @param listaFrequenciaPalavras -> lista de Frequências de Palavras
 * @param palavraProcurada -> palavra a verificar posição de Quartil
 */
void ListarFrequenciaPalavras(FrequenciaPalavras *listaFrequenciaPalavras, FrequenciaPalavras *palavraProcurada) {
    int *quantidades = NULL, countQuantidades = 0;
    float *quartis = NULL;
    printf("\n\n----- LISTA DE FREQUÊNCIA DE PALAVRAS -----\n\n");
    FrequenciaPalavras *listaFrequenciaPalavrasOrdenada = NULL;
    while (listaFrequenciaPalavras) {
        listaFrequenciaPalavrasOrdenada = InserirFrequenciaPalavrasOrdenadas(listaFrequenciaPalavrasOrdenada,
                                                                             listaFrequenciaPalavras);
        listaFrequenciaPalavras = listaFrequenciaPalavras->next;
    }
    while (listaFrequenciaPalavrasOrdenada) {
        quantidades = (countQuantidades == 0) ? MALLOC(int) : realloc(quantidades, sizeof(int) * countQuantidades + 1);
        quantidades[countQuantidades++] = listaFrequenciaPalavrasOrdenada->quantidade;
        printf("\tPalavra: %s\n", listaFrequenciaPalavrasOrdenada->palavra);
        printf("\tQuantidade: %d\n\n", listaFrequenciaPalavrasOrdenada->quantidade);
        listaFrequenciaPalavrasOrdenada = listaFrequenciaPalavrasOrdenada->next;
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

    //todo: free quantidades

    //todo: free listaFrequenciaPalavrasOrdenada
    // Cuidado com o free da ->palavra, esta pode apontar para a palavra na variável original (do main) (verificar)
}
