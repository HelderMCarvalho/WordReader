#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *ficheiro = fopen("../dadosMini", "r");
    if (!ficheiro) {
        printf("Não foi possível abrir o ficheiro!\n");
        perror("fopen");
        exit(1);
    }

    while (!feof(ficheiro)) {
        char line[100];
        char *aux;
        fgets(line, 100, ficheiro);
        if (!feof(ficheiro)) {
//            Verifica se a linha lida é um sinal de pontuação ou um "\n", se não for executa
            if (!(ispunct(line[0]) || !strcmp(line, "\n"))) {
//                Lê a palavra
                for (aux = line; *aux != ' ' && *aux != '\0' && *aux != '\n'; aux++) {}
                if (*aux == '\0') { printf("\nErro na palavra"); }
                char *aux2 = strdup(aux + 1);
                *aux = '\0';
                printf("\nPalavra: \"%s\"", line); //Imprime a palavra

//                Lê o verbo
                for (aux = aux2; *aux != ' ' && *aux != '\0'; aux++) {}
                if (*aux == '\0') { printf("\nErro no verbo"); }
                char *aux3 = strdup(aux + 1);
                *aux = '\0';
                printf(" | Verbo: \"%s\"", aux2); //Imprime o verbo

//                Lê a análise
                for (aux = aux3; *aux != ' ' && *aux != '\0'; aux++) {}
                if (*aux == '\0') { printf("\nErro na análise"); }
                char *aux4 = strdup(aux + 1);
                *aux = '\0';
                printf(" | Análise: \"%s\"", aux3); //Imprime a análise

//                Lê a certeza
                for (aux = aux4; *aux != '\n' && *aux != '\0'; aux++) {}
                if (*aux == '\0') { printf("\nErro na certeza"); }
                *aux = '\0';
                printf(" | Certeza: \"%f\"", atof(aux4)); //Imprime a certeza

                //todo: Se chegou até aqui então tem de inserir na lista

            }
        }
    }
    return 0;
}
