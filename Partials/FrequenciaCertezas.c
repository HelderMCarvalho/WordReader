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
        FrequenciaCertezas *node = CALLOC(1, FrequenciaCertezas);
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


void ListarDadosHistograma(FrequenciaCertezas *listaFrequenciaCertezas) {

    float ranges[11] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    int rangeCounts[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    while (listaFrequenciaCertezas) {

        // aqui entra se a certeza for 1
        if (listaFrequenciaCertezas->certeza == (float) 1) {
            rangeCounts[9] += listaFrequenciaCertezas->quantidade;
        } else {
            for (int i = 0; i < 11; i++) {
                //Check if in range
                if (listaFrequenciaCertezas->certeza >= ranges[i] && listaFrequenciaCertezas->certeza < ranges[i + 1]) {
                    rangeCounts[i] += listaFrequenciaCertezas->quantidade;
                    break;
                }
            }
        }
        listaFrequenciaCertezas = listaFrequenciaCertezas->next;

    }
    // Output
    printf("\n______________________________");
    for (int i = 0; i < 10; i++) {
        printf("\n| %.1f <-> %.1f | %d \tPalavras |", ranges[i], ranges[i + 1], rangeCounts[i]);
    }
    printf("\n______________________________");

}