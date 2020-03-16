#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MALLOC(tipo)   (tipo*) malloc(sizeof(tipo))

float quadrado(float numero) { return numero * numero; }

/**
 * Estrutura que guarda todas as categorias, as suas quantidades e certezas acululadas
 * Guarda também todas as certezas num array de floats
 * Utilizada para o Ex. 2 e Ex. 4                                                       todo: Helder
 */
typedef struct _categorias {
    char *nome;
    float totalCerteza;
    int quantidade;
    float *certezas;
    struct _categorias *next;
} Categorias;

/**
 * Estrutura que guarda as Categorias e suas frequências calculadas por ordem crescente de Frequência Absoluta
 * Utilizada no Ex. 2
 */
typedef struct _auxCategoriasOrdenadas {
    char *nome;
    int frequenciaAbsoluta;
    float frequenciaRelativa, mediaCerteza, desvioPadrao;
    struct _auxCategoriasOrdenadas *next;
} AuxCategoriasOrdenadas;

/**
 * Estrutura que guarda a quantidade de palavras com um número expecífico de letras
 * Utilizada no Ex. 3 e Ex. 5                                                           todo: João
 */
typedef struct _frequenciaLetras {
    int numeroLetras, quantidade;
    struct _frequenciaLetras *next;
} FrequenciaLetras;

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
 * Estrutura que guarda o número de ocorrências de cada certeza
 * Utilizada no Ex. 7                                                                   todo: João
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
        aux->certezas = realloc(aux->certezas, sizeof(float) * aux->quantidade);
        aux->certezas[aux->quantidade - 1] = certeza;
    } else {
        Categorias *node = MALLOC(Categorias);
        node->nome = strdup(nome);
        node->totalCerteza = certeza;
        node->quantidade = 1;
        node->certezas = NULL;
        node->certezas = MALLOC(float);
        node->certezas[0] = certeza;
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
                         float frequenciaRelativa, float mediaCerteza, float desvioPadrao) {
    if (!listaAuxCategoriasOrdenadas || listaAuxCategoriasOrdenadas->frequenciaAbsoluta >= frequenciaAbsoluta) {
        AuxCategoriasOrdenadas *node = MALLOC(AuxCategoriasOrdenadas);
        node->nome = strdup(nome);
        node->frequenciaAbsoluta = frequenciaAbsoluta;
        node->frequenciaRelativa = frequenciaRelativa;
        node->mediaCerteza = mediaCerteza;
        node->desvioPadrao = desvioPadrao;
        node->next = listaAuxCategoriasOrdenadas;
        listaAuxCategoriasOrdenadas = node;
    } else {
        listaAuxCategoriasOrdenadas->next = InserirCategoriaOrdenada(listaAuxCategoriasOrdenadas->next, nome,
                                                                     frequenciaAbsoluta, frequenciaRelativa,
                                                                     mediaCerteza, desvioPadrao);
    }
    return listaAuxCategoriasOrdenadas;
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
 * Ex. 2 e Ex. 4
 * Procedimento que lista as Categorias ordenadas por ordem crescente de Frequência Absoluta
 * Calcula a Frequência Absoluta, Relativa e Acumulada
 * Calcula a Média e Desvio Padrão de Certeza
 * @param palavras -> lista de Palavras
 */
void ListarCategorias(Categorias *listaCategorias) {
    printf("\n\n----- LISTA DE CATEGORIAS -----\n\n");
    AuxCategoriasOrdenadas *listaCategoriasOrdenadas = NULL;
    int totalQuantidadesCategorias = TotalQuantidadesCategorias(listaCategorias);
    while (listaCategorias) {
        float frequenciaRelativa = (((float) listaCategorias->quantidade / (float) totalQuantidadesCategorias)) * 100;
        float mediaCerteza = listaCategorias->totalCerteza / (float) listaCategorias->quantidade;
        float auxDesvioPadrao = 0;
        for (int i = 0; i < listaCategorias->quantidade; i++) {
            auxDesvioPadrao += quadrado(listaCategorias->certezas[i] - mediaCerteza);
        }
        float desvioPadrao = sqrtf(auxDesvioPadrao / (float) listaCategorias->quantidade);
        listaCategoriasOrdenadas = InserirCategoriaOrdenada(listaCategoriasOrdenadas, listaCategorias->nome,
                                                            listaCategorias->quantidade, frequenciaRelativa,
                                                            mediaCerteza, desvioPadrao);
        listaCategorias = listaCategorias->next;
    }
    int frequenciaAcumulada = 0;
    while (listaCategoriasOrdenadas) {
        printf("\nCategoria: %s\n", listaCategoriasOrdenadas->nome);
        printf("\tFrequência Absoluta: %d\n", listaCategoriasOrdenadas->frequenciaAbsoluta);
        printf("\tFrequência Relativa: %.2f%c\n", listaCategoriasOrdenadas->frequenciaRelativa, '%');
        printf("\tFrequência Acumulada: %d\n", frequenciaAcumulada += listaCategoriasOrdenadas->frequenciaAbsoluta);
        printf("\tMédia Certeza: %f\n", listaCategoriasOrdenadas->mediaCerteza);
        printf("\tDesvio Padrão Certeza: %f\n", listaCategoriasOrdenadas->desvioPadrao);
        AuxCategoriasOrdenadas *next = listaCategoriasOrdenadas->next;
        free(listaCategoriasOrdenadas->nome);
        free(listaCategoriasOrdenadas);
        listaCategoriasOrdenadas = next;
    }
}

/**
Procedimento que lista as Frequêcias de Letras
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
    int op = -1;
    int palavrasCount = 0;
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
                listaFrequenciaLetras = InserirFrequenciaLetraOrdenada(listaFrequenciaLetras, strlen(line));
                listaFrequenciaPalavras = InserirFrequenciaPalavras(listaFrequenciaPalavras, line);
                listaFrequenciaCertezas = InserirFrequenciaCerteza(listaFrequenciaCertezas, atof(aux4));

                free(aux2);
                free(aux3);
                free(aux4);
                palavrasCount++;
            }
        }
    }

    do {
        printf("\n\n ----- MENU -----\n\n");
        printf("\t1 -> Ex. 2 e 4\n");
        printf("\t2 -> Ex. 3 e 5\n");
        printf("\t3 -> Ex. 6\n");
        printf("\t4 -> Ex. 7\n");
        printf("\t0 -> Sair\n");
        printf("\tEscolha a sua opção: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                ListarCategorias(listaCategorias);
                break;
            case 2:
                ListarFrequenciaLetras(listaFrequenciaLetras, palavrasCount);
                break;
            case 3:
                break;
            case 4:
                break;
            case 0:
                exit(1);
            default:
                printf("Opcao invalida");
        }

    } while (op != 0);
//    char s;
//    scanf("%c", &s);
    return 0;
}
