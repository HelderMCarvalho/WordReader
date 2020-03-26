/**
 * Estrutura que guarda a quantidade de palavras com um número expecífico de letras
 * Utilizada no Ex. 3 e Ex. 5
 */
typedef struct _frequenciaLetras {
    int numeroLetras, quantidade;
    struct _frequenciaLetras *next;
} FrequenciaLetras;

FrequenciaLetras *ProcurarFrequenciaLetras(FrequenciaLetras *listaFrequenciaLetras, int numeroLetras);

FrequenciaLetras *InserirFrequenciaLetraOrdenada(FrequenciaLetras *listaFrequenciaLetras, int numeroLetras);

void ListarFrequenciaLetras(FrequenciaLetras *listaFrequenciaLetras, int totalPalavras, int totalLetras);
