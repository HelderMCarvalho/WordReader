/**
 * Estrutura que guarda o número de ocorrências de cada certeza
 * Utilizada no Ex. 7                                                                   todo: João
 */
typedef struct _frequenciaCerteza {
    float certeza;
    int quantidade;
    struct _frequenciaCerteza *next;
} FrequenciaCertezas;

/**
 * Função que procura Frequencia de Certezas
 * @param listaFrequenciaCerteza -> lista de Frequencia de Certezas existente
 * @param certeza -> certeza a encontrar
 * @return -> FrequenciaCertezas caso encontre || NULL caso não encontre
 */
FrequenciaCertezas *ProcurarFrequenciaCertezas(FrequenciaCertezas *listaFrequenciaCertezas, float certeza) {
    if (!listaFrequenciaCertezas) {
        return NULL;
    } else if (certeza == listaFrequenciaCertezas->certeza) { //todo: comparação demora muuuuuuuuuito (6 minutos)
        return listaFrequenciaCertezas;
    }
    return ProcurarFrequenciaCertezas(listaFrequenciaCertezas->next, certeza);
}

/**
 * Função que insere/atualiza Frequencia de Certezas
 * @param listaFrequenciaCerteza -> lista de Frequencia de Certezas existentes
 * @param certeza -> certeza a inserir/atualizar
 * @return -> lista de Frequencia de Certezas atualizada
 */
FrequenciaCertezas *InserirFrequenciaCerteza(FrequenciaCertezas *listaFrequenciaCerteza, float certeza) {
    FrequenciaCertezas *aux = ProcurarFrequenciaCertezas(listaFrequenciaCerteza, certeza);
    if (aux) {
        aux->quantidade++;
    } else {
        FrequenciaCertezas *node = MALLOC(FrequenciaCertezas);
        node->certeza = certeza;
        node->quantidade = 1;
        node->next = listaFrequenciaCerteza;
        return node;
    }
    return listaFrequenciaCerteza;
}

/**
 * Procedimento que lista as Frequências de Certezas
 * @param listaFrequenciaCertezas -> lista de Frequências de Certezas
 */
void ListarFrequenciaCertezas(FrequenciaCertezas *listaFrequenciaCertezas) {
    printf("\n\n----- LISTA DE FREQUÊNCIA DE CERTEZAS -----\n\n");
    while (listaFrequenciaCertezas) {
        printf("Certeza: %f\n", listaFrequenciaCertezas->certeza);
        printf("Quantidade: %d\n\n", listaFrequenciaCertezas->quantidade);
        listaFrequenciaCertezas = listaFrequenciaCertezas->next;
    }
}
