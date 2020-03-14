#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MALLOC(tipo)   (tipo*) malloc(sizeof(tipo))

/**
 * Estrutura que guarda todas as categorias, as suas quantidades e certezas acululadas
 * Utilizada para o Ex. 2 e Ex. 4
 */
typedef struct _categorias {
    char *nome;
    float totalCerteza;
    int quantidade;
    struct _categorias *next;
} Categorias;

/**
 * Estrutura que guarda as Categorias e suas frequências calculadas por ordem crescente de Frequência Absoluta
 * Utilizada no Ex. 2
 */
typedef struct _auxCategoriasOrdenadas {
    char *nome;
    int frequenciaAbsoluta;
    float frequenciaRelativa;
    struct _auxCategoriasOrdenadas *next;
} AuxCategoriasOrdenadas;

/**
 * Estrutura que guarda a quantidade de palavras com um número expecífico de letras
 * Utilizada no Ex. 3 e Ex. 5
 */
typedef struct _frequenciaLetras {
    int numeroLetras, quantidade;
    struct _frequenciaLetras *next;
} FrequenciaLetras;

/**
 * Estrutura que guarda o número de ocorrências de cada palavra
 * Utilizada no Ex. 6
 */
typedef struct _frequenciaPalavras {
    char *palavra;
    int quantidade;
    struct _frequenciaPalavras *next;
} FrequenciaPalavras;

/**
 * Estrutura que guarda o número de ocorrências de cada certeza
 */
typedef struct _frequenciaCerteza {
    float certeza;
    int quantidade;
    struct _frequenciaCerteza *next;
} FrequenciaCertezas;

/**
 * Função que procura Categorias
 * @param listaCategorias -> lista de Categorias existentes
 * @param nome -> nome da Categoria a encontrar
 * @return -> Categoria caso encontre || NULL caso não encontre
 */
Categorias *ProcurarCategoria(Categorias *listaCategorias, char *nome) {
    if (!listaCategorias) {
        return NULL;
    } else if (strcasecmp(nome, listaCategorias->nome) == 0) {
        return listaCategorias;
    }
    return ProcurarCategoria(listaCategorias->next, nome);
}

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
 * Função que insere/atualiza uma Categoria
 * @param listaCategorias -> ista de Categorias existentes
 * @param nome -> nome da Categoria a inserir/atualizar
 * @param certeza -> certeza da Categoria a inserir/somar
 * @return -> lista de Categorias atualizada
 */
Categorias *InserirCategoria(Categorias *listaCategorias, char *nome, float certeza) {
    Categorias *aux = ProcurarCategoria(listaCategorias, nome);
    if (aux) {
        aux->totalCerteza += certeza;
        aux->quantidade++;
    } else {
        Categorias *node = MALLOC(Categorias);
        node->nome = strdup(nome);
        node->totalCerteza = certeza;
        node->quantidade = 1;
        node->next = listaCategorias;
        return node;
    }
    return listaCategorias;
}

/**
 * Função que insere Categorias ordenadas por Freqência Absoluta de forma crescente
 * @param listaAuxCategoriasOrdenadas -> lista de Categorias ordenadas existentes
 * @param nome -> nome a inserir
 * @param frequenciaAbsoluta -> Frequência Absoluta a inserir
 * @param frequenciaRelativa -> Frequência Relativa a inserir
 * @return -> lista de Categorias Ordenadas atualizada
 */
AuxCategoriasOrdenadas *
InserirCategoriaOrdenada(AuxCategoriasOrdenadas *listaAuxCategoriasOrdenadas, char *nome, int frequenciaAbsoluta,
                         float frequenciaRelativa) {
    if (!listaAuxCategoriasOrdenadas || listaAuxCategoriasOrdenadas->frequenciaAbsoluta >= frequenciaAbsoluta) {
        AuxCategoriasOrdenadas *node = MALLOC(AuxCategoriasOrdenadas);
        node->nome = strdup(nome);
        node->frequenciaAbsoluta = frequenciaAbsoluta;
        node->frequenciaRelativa = frequenciaRelativa;
        node->next = listaAuxCategoriasOrdenadas;
        listaAuxCategoriasOrdenadas = node;
    } else {
        listaAuxCategoriasOrdenadas->next = InserirCategoriaOrdenada(listaAuxCategoriasOrdenadas->next, nome,
                                                                     frequenciaAbsoluta, frequenciaRelativa);
    }
    return listaAuxCategoriasOrdenadas;
}

/**
 * Função que insere/atualiza Frequencia de Letras
 * @param listaFrequenciaLetras -> lista de Frequencia de Letras existentes
 * @param numeroLetras -> numero de letras a inserir/atualizar
 * @return -> lista de Frequencia de Letras atualizada
 */
FrequenciaLetras *InserirFrequenciaLetra(FrequenciaLetras *listaFrequenciaLetras, int numeroLetras) {
    FrequenciaLetras *aux = ProcurarFrequenciaLetras(listaFrequenciaLetras, numeroLetras);
    if (aux) {
        aux->quantidade++;
    } else {
        FrequenciaLetras *node = MALLOC(FrequenciaLetras);
        node->numeroLetras = numeroLetras;
        node->quantidade = 1;
        node->next = listaFrequenciaLetras;
        return node;
    }
    return listaFrequenciaLetras;
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
 * Função que calcula a soma de todas as quantidades de Categorias
 * @param listaCategorias -> lista de Categorias a somar
 * @return -> quantidades de Categorias somadas
 */
int TotalQuantidadesCategorias(Categorias *listaCategorias) {
    int totalQuantidadesCategorias = 0;
    while (listaCategorias) {
        totalQuantidadesCategorias += listaCategorias->quantidade;
        listaCategorias = listaCategorias->next;
    }
    return totalQuantidadesCategorias;
}

/**
 * Procedimento que lista as Categorias ordenadas por ordem crescente de Frequência Absoluta
 * Calcula a Frequência Absoluta, Relativa e Acumulada
 * @param palavras -> lista de Palavras
 */
void ListarCategorias(Categorias *listaCategorias) {
    printf("\n\n----- LISTA DE CATEGORIAS -----\n\n");
    AuxCategoriasOrdenadas *listaCategoriasOrdenadas = NULL;
    int totalQuantidadesCategorias = TotalQuantidadesCategorias(listaCategorias);
    while (listaCategorias) {
        listaCategoriasOrdenadas = InserirCategoriaOrdenada(listaCategoriasOrdenadas, listaCategorias->nome,
                                                            listaCategorias->quantidade,
                                                            (((float) listaCategorias->quantidade /
                                                              (float) totalQuantidadesCategorias) * 100));
        listaCategorias = listaCategorias->next;
    }
    int frequenciaAcumulada = 0;
    while (listaCategoriasOrdenadas) {
        printf("\nNome: %s\n", listaCategoriasOrdenadas->nome);
        printf("Frequência Absoluta: %d\n", listaCategoriasOrdenadas->frequenciaAbsoluta);
        printf("Frequência Relativa: %.2f\n", listaCategoriasOrdenadas->frequenciaRelativa);
        printf("Frequência Acumulada: %d\n", frequenciaAcumulada += listaCategoriasOrdenadas->frequenciaAbsoluta);
        AuxCategoriasOrdenadas *next = listaCategoriasOrdenadas->next;
        free(listaCategoriasOrdenadas->nome);
        free(listaCategoriasOrdenadas);
        listaCategoriasOrdenadas = next;
    }
}

/**
 * Procedimento que lista as Frequêcias de Letras
 * @param listaFrequenciaLetras -> lista de Frequências de Letras
 */
void ListarFrequenciaLetras(FrequenciaLetras *listaFrequenciaLetras) {
    printf("\n\n----- LISTA DE FREQUÊNCIA DE LETRAS -----\n\n");
    while (listaFrequenciaLetras) {
        printf("Número de Letras: %d\n", listaFrequenciaLetras->numeroLetras);
        printf("Quantidade: %d\n\n", listaFrequenciaLetras->quantidade);
        listaFrequenciaLetras = listaFrequenciaLetras->next;
    }
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

int main() {
    Categorias *listaCategorias = NULL;
    FrequenciaLetras *listaFrequenciaLetras = NULL;
    FrequenciaPalavras *listaFrequenciaPalavras = NULL;
    FrequenciaCertezas *listaFrequenciaCertezas = NULL;

    FILE *ficheiro = fopen("../dadosMini", "r");
    if (!ficheiro) {
        printf("Não foi possível abrir o ficheiro!\n");
        perror("fopen");
        exit(1);
    }
    while (!feof(ficheiro)) {
        char line[512];
        char *aux;
        fgets(line, 512, ficheiro);
        if (!feof(ficheiro)) {
//            Vai processar a linha se esta começar com um "'" (apostrofe), ou se for uma palavra (se não for um sinal de pontuação ou um "\n")
            if (line[0] == '\'' || !(ispunct(line[0]) || !strcmp(line, "\n"))) {
//                Lê a palavra
                for (aux = line; *aux != ' ' && *aux != '\0' && *aux != '\n'; aux++) {}
//                if (*aux == '\0') { printf("\nErro na palavra"); }
                char *aux2 = strdup(aux + 1);
                *aux = '\0';
//                printf("\nPalavra: \"%s\"", line); //Imprime a palavra

//                Lê a raiz
                for (aux = aux2; *aux != ' ' && *aux != '\0' && *aux != '\n'; aux++) {}
//                if (*aux == '\0') { printf("\nErro na raiz"); }
                char *aux3 = strdup(aux + 1);
                *aux = '\0';
//                printf(" | Raiz: \"%s\"", aux2); //Imprime a raiz

//                Lê a categoria
                for (aux = aux3; *aux != ' ' && *aux != '\0' && *aux != '\n'; aux++) {}
//                if (*aux == '\0') { printf("\nErro na categoria"); }
                char *aux4 = strdup(aux + 1);
                *aux = '\0';
//                printf(" | Análise: \"%s\"", aux3); //Imprime a categoria

//                Lê a certeza todo: usar strtol??
                for (aux = aux4; *aux != ' ' && *aux != '\0' && *aux != '\n'; aux++) {}
//                if (*aux == '\0') { printf("\nErro na certeza"); }
                *aux = '\0';
//                printf(" | Certeza: \"%f\"", atof(aux4)); //Imprime a certeza

                listaCategorias = InserirCategoria(listaCategorias, aux3, atof(aux4));
//                listaFrequenciaLetras = InserirFrequenciaLetra(listaFrequenciaLetras, strlen(line));
//                listaFrequenciaPalavras = InserirFrequenciaPalavras(listaFrequenciaPalavras, line);
//                listaFrequenciaCertezas = InserirFrequenciaCerteza(listaFrequenciaCertezas, atof(aux4));

                free(aux2);
                free(aux3);
                free(aux4);
            }
        }
    }
    ListarCategorias(listaCategorias);
//    ListarFrequenciaLetras(listaFrequenciaLetras);
//    ListarFrequenciaPalavras(listaFrequenciaPalavras);
//    ListarFrequenciaCertezas(listaFrequenciaCertezas);
//    char s;
//    scanf("%c", &s);
    return 0;
}
