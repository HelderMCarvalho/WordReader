#define CALLOC(quantidade, tipo)   (tipo*) calloc(quantidade, sizeof(tipo))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./Partials/helpers.c"
#include "./Partials/Categorias.c"
#include "./Partials/FrequenciaLetras.c"
#include "./Partials/FrequenciaPalavras.c"
#include "./Partials/FrequenciaCertezas.c"

int main() {
    int opcaoMenu = -1, opcaoFicheiro = -1, totalPalavrasCategorias = 0, totalLetras = 0;
    Categorias *listaCategorias = NULL;
    FrequenciaLetras *listaFrequenciaLetras = NULL;
    FrequenciaPalavras *listaFrequenciaPalavras = NULL;
    FrequenciaCertezas *listaFrequenciaCertezas = NULL;

    FILE *ficheiro = NULL;
    do {
        printf("Escolha o ficheiro que pretende analisar:");
        printf("\n\t1 -> Pequeno (leitura instantânea) (todos os Exercícios disponíveis)");
        printf("\n\t2 -> Médio (leitura rápida) (todos os Exercícios disponíveis)");
        printf("\n\t3 -> Grande (leitura extremamente lenta) (Ex. 4 e Ex. 6 não disponíveis)");
        printf("\n\tOpção: ");
        scanf("%d", &opcaoFicheiro);
        switch (opcaoFicheiro) {
            case 1: {
                ficheiro = fopen("../Dados/pequeno", "r");
                break;
            }
            case 2: {
                ficheiro = fopen("../Dados/medio", "r");
                break;
            }
            case 3: {
                ficheiro = fopen("../Dados/grande", "r");
                break;
            }
            default: {
                printf("\t\tOpção inválida!\n\n");
            }
        }
    } while (opcaoFicheiro != 1 && opcaoFicheiro != 2 && opcaoFicheiro != 3);
    if (!ficheiro) {
        printf("\nNão foi possível abrir o ficheiro!\n");
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

                int tamanhoPalavra = (int) strlen(line);
                float certeza = (float)atof(aux4);

                listaCategorias = InserirCategoria(listaCategorias, aux3, certeza);
                listaFrequenciaLetras = InserirFrequenciaLetraOrdenada(listaFrequenciaLetras, tamanhoPalavra);
                if (opcaoFicheiro != 3) {
                    listaFrequenciaPalavras = InserirFrequenciaPalavras(listaFrequenciaPalavras, line);
                    listaFrequenciaCertezas = InserirFrequenciaCerteza(listaFrequenciaCertezas, certeza);
                }
                totalPalavrasCategorias++;
                totalLetras += tamanhoPalavra;

                free(aux2);
                free(aux3);
                free(aux4);
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
        scanf("%d", &opcaoMenu);
        switch (opcaoMenu) {
            case 1: {
                ListarCategorias(listaCategorias, totalPalavrasCategorias);
                break;
            }
            case 2: {
                ListarFrequenciaLetras(listaFrequenciaLetras, totalPalavrasCategorias, totalLetras);
                break;
            }
            case 3: {
                if (opcaoFicheiro != 3) {
                    printf("\n\t\tIntroduza a palavra que quer pesquisar: ");
                    char *palavra = NULL;
                    scanf("%ms", &palavra);
                    FrequenciaPalavras *palavraProcurada = ProcurarFrequenciaPalavras(listaFrequenciaPalavras, palavra);
                    while (!palavraProcurada) {
                        printf("\t\t\tPalavra inexistente! Tente de novo.");
                        printf("\n\t\tIntroduza a palavra que quer pesquisar: ");
                        scanf("%ms", &palavra);
                        palavraProcurada = ProcurarFrequenciaPalavras(listaFrequenciaPalavras, palavra);
                    }
                    free(palavra);
                    ListarFrequenciaPalavras(listaFrequenciaPalavras, palavraProcurada);
                } else {
                    printf("\n\t\tOpção indisponível!");
                }
                break;
            }
            case 4: {
                if (opcaoFicheiro != 3) {

                } else {
                    printf("\n\t\tOpção indisponível!");
                }
                break;
            }
            case 0: {
                exit(1);
            }
            default: {
                printf("\n\tOpção inválida!");
            }
        }

    } while (opcaoMenu != 0);
//    char s;
//    scanf("%c", &s);
    return 0;
}
