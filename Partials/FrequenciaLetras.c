/**
 * Estrutura que guarda a quantidade de palavras com um número expecífico de letras
 * Utilizada no Ex. 3 e Ex. 5
 */
typedef struct _frequenciaLetras {
    int numeroLetras, quantidade;
    struct _frequenciaLetras *next;
} FrequenciaLetras;

/**
 * Função que procura Frequência de Letras
 * @param listaFrequenciaLetras -> lista de Frequência Letras existente
 * @param numeroLetras -> número de letras a encontrar
 * @return -> FrequenciaLetras caso encontre || NULL caso não encontre
 */
FrequenciaLetras *ProcurarFrequenciaLetras(FrequenciaLetras *listaFrequenciaLetras, int numeroLetras) {
    if (!listaFrequenciaLetras) {
        return NULL;
    } else if (listaFrequenciaLetras->numeroLetras == numeroLetras) {
        return listaFrequenciaLetras;
    }
    return ProcurarFrequenciaLetras(listaFrequenciaLetras->next, numeroLetras);
}

/**
 * Função que insere/atualiza Frequência de Letras
 * @param listaFrequenciaLetras -> lista de Frequência de Letras existentes
 * @param numeroLetras -> numero de letras a inserir/atualizar
 * @return -> lista de Frequência de Letras atualizada
 */
FrequenciaLetras *InserirFrequenciaLetraOrdenada(FrequenciaLetras *listaFrequenciaLetras, int numeroLetras) {
    FrequenciaLetras *aux = ProcurarFrequenciaLetras(listaFrequenciaLetras, numeroLetras);
    if (aux) {
        aux->quantidade++;
    } else if (!listaFrequenciaLetras || listaFrequenciaLetras->numeroLetras >= numeroLetras) {
        FrequenciaLetras *node = CALLOC(1, FrequenciaLetras);
        node->numeroLetras = numeroLetras;
        node->quantidade = 1;
        node->next = listaFrequenciaLetras;
        listaFrequenciaLetras = node;
    } else {
        listaFrequenciaLetras->next = InserirFrequenciaLetraOrdenada(listaFrequenciaLetras->next, numeroLetras);
    }
    return listaFrequenciaLetras;
}

/**
 * Ex. 3 e Ex. 5
 * Procedimento que lista as Frequências de Letras
 * Lista a Frequência Absoluta, Relativa e Acumulada de cada Frequência de Letras
 * Lista a Média, Mediana, Moda e Desvio Padrão do total de Letras das Palavras existentes no ficheiro
 * @param listaFrequenciaLetras -> lista de Frequências de Letras
 * @param totalPalavras -> total de palavras existentes no ficheiro
 * @param totalLetras -> total de letras existentes no ficheiro
 */
void ListarFrequenciaLetras(FrequenciaLetras *listaFrequenciaLetras, int totalPalavras, int totalLetras) {
    int frequenciaAcumulada = 0, posInicial = 0, moda = 0, modaQtd = 0,
            *auxMediana = calloc(totalPalavras, sizeof(int));
    float somatorioDesvios = 0;
    printf("\n\n----- LISTA DE FREQUÊNCIA DE LETRAS -----\n\n");
    float mediaLetras = Media((float) totalLetras, (float) totalPalavras);
    while (listaFrequenciaLetras) {
        if (modaQtd < listaFrequenciaLetras->quantidade) {
            modaQtd = listaFrequenciaLetras->quantidade;
            moda = listaFrequenciaLetras->numeroLetras;
        }
        for (int i = posInicial; i < (listaFrequenciaLetras->quantidade + posInicial); i++) {
            auxMediana[i] = listaFrequenciaLetras->numeroLetras;
            somatorioDesvios += Quadrado((float) listaFrequenciaLetras->numeroLetras - mediaLetras);
        }
        posInicial += listaFrequenciaLetras->quantidade;
        float frequenciaRelativa = FrequenciaRelativa((float) listaFrequenciaLetras->quantidade, (float) totalPalavras);
        printf("\nNúmero de Letras: %d\n", listaFrequenciaLetras->numeroLetras);
        printf("\tFrequência Absoluta: %d\n", listaFrequenciaLetras->quantidade);
        printf("\tFrequência Relativa: %f%c\n", frequenciaRelativa, '%');
        printf("\tFrequência Acumulada: %d\n", frequenciaAcumulada += listaFrequenciaLetras->quantidade);
        listaFrequenciaLetras = listaFrequenciaLetras->next;
    }
    printf("\nMedia: %.2f", mediaLetras);
    printf("\nMediana: %.2f", Mediana(auxMediana, totalPalavras));
    printf("\nModa: %d", moda);
    printf("\nDesvio Padrao: %f", DesvioPadrao(somatorioDesvios, (float) totalLetras));
    free(auxMediana);
}
