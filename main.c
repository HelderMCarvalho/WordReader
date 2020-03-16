#define MALLOC(tipo)   (tipo*) malloc(sizeof(tipo))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helpers.c"
#include "Categorias.c"
#include "FrequenciaLetras.c"
#include "FrequenciaPalavras.c"
#include "FrequenciaCertezas.c"

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
