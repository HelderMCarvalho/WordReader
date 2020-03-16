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
ProcurarFrequenciaPalavras(FrequenciaPalavras *listaFrequenciaPalavras, char *palavra, int tamanho) {
    if (!listaFrequenciaPalavras) {
        return NULL;
    } else if (strcasecmp(palavra, listaFrequenciaPalavras->palavra) == 0) { //todo: comparação demora muuuuuuuuuito
        return listaFrequenciaPalavras;
    }
    return ProcurarFrequenciaPalavras(listaFrequenciaPalavras->next, palavra, tamanho);
}

/**
 * Função que insere/atualiza Frequencia de Palavras
 * @param listaFrequenciaPalavras -> lista de Frequencia de Palavras existentes
 * @param palavra -> palavra a inserir/atualizar
 * @return -> lista de Frequencia de Palavras atualizada
 */
FrequenciaPalavras *InserirFrequenciaPalavras(FrequenciaPalavras *listaFrequenciaPalavras, char *palavra) {
    FrequenciaPalavras *aux = ProcurarFrequenciaPalavras(listaFrequenciaPalavras, palavra, (int) strlen(palavra));
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
 * Procedimento que lista as Frequências de Palavras
 * @param listaFrequenciaPalavras -> lista de Frequências de Palavras
 */
void ListarFrequenciaPalavras(FrequenciaPalavras *listaFrequenciaPalavras) {
    printf("\n\n----- LISTA DE FREQUÊNCIA DE PALAVRAS -----\n\n");
    while (listaFrequenciaPalavras) {
        printf("Palavra: %s\n", listaFrequenciaPalavras->palavra);
        printf("Quantidade: %d\n\n", listaFrequenciaPalavras->quantidade);
        listaFrequenciaPalavras = listaFrequenciaPalavras->next;
    }
}
