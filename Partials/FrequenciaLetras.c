#include <math.h>

/**
 * Estrutura que guarda a quantidade de palavras com um número expecífico de letras
 * Utilizada no Ex. 3 e Ex. 5                                                           todo: João
 */
typedef struct _frequenciaLetras {
    int numeroLetras, quantidade;
    struct _frequenciaLetras *next;
} FrequenciaLetras;

/**
 * Função que procura Frequencia de Letras
 * @param listaFrequenciaLetras -> lista de Frequencia Letras existente
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
 * Função que insere/atualiza Frequencia de Letras
 * @param listaFrequenciaLetras -> lista de Frequencia de Letras existentes
 * @param numeroLetras -> numero de letras a inserir/atualizar
 * @return -> lista de Frequencia de Letras atualizada
 */
FrequenciaLetras *InserirFrequenciaLetraOrdenada(FrequenciaLetras *listaFrequenciaLetras, int numeroLetras) {
    FrequenciaLetras *aux = ProcurarFrequenciaLetras(listaFrequenciaLetras, numeroLetras);
    if (aux) {
        aux->quantidade++;
    } else if (!listaFrequenciaLetras || listaFrequenciaLetras->numeroLetras >= numeroLetras) {
        FrequenciaLetras *node = MALLOC(FrequenciaLetras);
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
 * Função que calcula a soma a quantidade total de letras de todas as palavras do ficheiro
 * @param listaFrequenciaLetras -> lista de Frequência de Letras a somar
 * @return -> quantidade total de letras
 */
int TotalQuantidadesLetras(FrequenciaLetras *listaFrequenciaLetras) {
    int totalQuantidadesLetras = 0;
    while (listaFrequenciaLetras) {
        totalQuantidadesLetras += listaFrequenciaLetras->quantidade * listaFrequenciaLetras->numeroLetras;
        listaFrequenciaLetras = listaFrequenciaLetras->next;
    }
    return totalQuantidadesLetras;
}

/**
 * Procedimento que lista as Frequêcias de Letras
 * @param listaFrequenciaLetras -> lista de Frequências de Letras
 * @param totalPalavras -> total de palavras existentes no ficheiro
 */
void ListarFrequenciaLetras(FrequenciaLetras *listaFrequenciaLetras, int totalPalavras) {
    int frequenciaAcumulada = 0, posInicial = 0, moda = 0, modaQtd = 0, *auxMediana = NULL,
            totalLetras = TotalQuantidadesLetras(listaFrequenciaLetras);
    float frequenciaRelativa = 0, auxMedia = 0, mediana = 0, auxDesvioPadrao = 0;
    auxMediana = malloc(sizeof(int) * totalPalavras);
    printf("\n\n----- LISTA DE FREQUÊNCIA DE LETRAS -----\n\n");
    float mediaLetras = (float) totalLetras / (float) totalPalavras;
    while (listaFrequenciaLetras) { // Moda
        if (modaQtd < listaFrequenciaLetras->quantidade) {
            modaQtd = listaFrequenciaLetras->quantidade;
            moda = listaFrequenciaLetras->numeroLetras;
        }
        auxMedia += (float) listaFrequenciaLetras->numeroLetras * (float) listaFrequenciaLetras->quantidade;   //Media
        for (int i = posInicial; i < (listaFrequenciaLetras->quantidade + posInicial); i++) {
            auxMediana[i] = listaFrequenciaLetras->numeroLetras;
            auxDesvioPadrao += quadrado((float) listaFrequenciaLetras->numeroLetras - mediaLetras);
        }
        posInicial += listaFrequenciaLetras->quantidade;
        frequenciaRelativa = (((float) listaFrequenciaLetras->quantidade / (float) totalPalavras)) * 100;
        printf("\nNúmero de Letras: %d\n", listaFrequenciaLetras->numeroLetras);
        printf("\tFrequência Absoluta: %d\n", listaFrequenciaLetras->quantidade);
        printf("\tFrequência Relativa: %.2f%c\n", frequenciaRelativa, '%');
        printf("\tFrequência Acumulada: %d\n", frequenciaAcumulada += listaFrequenciaLetras->quantidade);
        listaFrequenciaLetras = listaFrequenciaLetras->next;
    }

    // Calculo da mediana
    if (totalPalavras % 2 != 0) {
        // Numero do meio
        mediana = (float) auxMediana[(int) (totalPalavras / 2)];
    } else {
        // Divisão entre os dois numeros do meio :D
        mediana = (float) (auxMediana[(int) ((totalPalavras - 1) / 2)] + auxMediana[(int) (totalPalavras / 2)]) / 2;
    }

    printf("\nMedia: %.2f", auxMedia / (float) totalPalavras);
    printf("\nMediana: %.2f", mediana);
    printf("\nModa: %d", moda);
    printf("\nDesvio Padrao: %f", sqrtf(auxDesvioPadrao / (float) totalLetras));
}
