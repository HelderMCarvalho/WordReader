#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./Headers/Categorias.h"
#include "./Headers/helpers.h"

#define CALLOC(quantidade, tipo)    (tipo*) calloc(quantidade, sizeof(tipo))

/**
 * Função que procura Categorias
 * @param listaCategorias -> lista de Categorias existentes
 * @param nome -> nome da Categoria a encontrar
 * @return -> Categoria caso encontre || NULL caso não encontre
 */
Categorias *ProcurarCategoria(Categorias *listaCategorias, char *nome) {
    if (!listaCategorias) {
        return NULL;
    } else if (strcmp(nome, listaCategorias->nome) == 0) {
        return listaCategorias;
    }
    return ProcurarCategoria(listaCategorias->next, nome);
}

/**
 * Função que insere/atualiza uma Categoria
 * @param listaCategorias -> lista de Categorias existentes
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
        Categorias *node = CALLOC(1, Categorias);
        node->nome = strdup(nome);
        node->totalCerteza = certeza;
        node->quantidade = 1;
        node->certezas = NULL;
        node->certezas = CALLOC(1, float);
        node->certezas[0] = certeza;
        node->next = listaCategorias;
        return node;
    }
    return listaCategorias;
}

/**
 * Função que insere Categorias ordenadas por Frequência Absoluta de forma crescente
 * @param listaAuxCategoriasOrdenadas -> lista de Categorias ordenadas existentes
 * @param nome -> nome a inserir
 * @param frequenciaAbsoluta -> Frequência Absoluta a inserir
 * @param frequenciaRelativa -> Frequência Relativa a inserir
 * @return -> lista de Categorias Ordenadas atualizada
 */
CategoriasOrdenadas *
InserirCategoriaOrdenada(CategoriasOrdenadas *listaAuxCategoriasOrdenadas, char *nome, int frequenciaAbsoluta,
                         float frequenciaRelativa, float mediaCerteza, float desvioPadrao) {
    if (!listaAuxCategoriasOrdenadas || listaAuxCategoriasOrdenadas->frequenciaAbsoluta >= frequenciaAbsoluta) {
        CategoriasOrdenadas *node = CALLOC(1, CategoriasOrdenadas);
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
 * Ex. 2 e Ex. 4
 * Procedimento que lista as Categorias ordenadas por ordem crescente de Frequência Absoluta
 * Lista a Frequência Absoluta, Relativa e Acumulada das Categorias
 * Lista a Média e Desvio Padrão da Certeza das Categorias
 * @param listaCategorias -> lista de Categorias
 * @param totalQuantidadesCategorias -> total de ocorrências de Categorias no ficheiro (contando repetidas)
 */
void ListarCategorias(Categorias *listaCategorias, int totalQuantidadesCategorias) {
    int frequenciaAcumulada = 0;
    printf("\n\n----- LISTA DE CATEGORIAS -----\n\n");
    CategoriasOrdenadas *listaCategoriasOrdenadas = NULL;
    while (listaCategorias) {
        float frequenciaRelativa = FrequenciaRelativa((float) listaCategorias->quantidade,
                                                      (float) totalQuantidadesCategorias);
        float mediaCerteza = Media(listaCategorias->totalCerteza, (float) listaCategorias->quantidade);
        float somatorioDesvios = 0;
        for (int i = 0; i < listaCategorias->quantidade; i++) {
            somatorioDesvios += Quadrado(listaCategorias->certezas[i] - mediaCerteza);
        }
        float desvioPadrao = DesvioPadrao(somatorioDesvios, (float) listaCategorias->quantidade);
        listaCategoriasOrdenadas = InserirCategoriaOrdenada(listaCategoriasOrdenadas, listaCategorias->nome,
                                                            listaCategorias->quantidade, frequenciaRelativa,
                                                            mediaCerteza, desvioPadrao);
        listaCategorias = listaCategorias->next;
    }
    while (listaCategoriasOrdenadas) {
        printf("\nCategoria: %s\n", listaCategoriasOrdenadas->nome);
        printf("\tFrequência Absoluta: %d\n", listaCategoriasOrdenadas->frequenciaAbsoluta);
        printf("\tFrequência Relativa: %f%c\n", listaCategoriasOrdenadas->frequenciaRelativa, '%');
        printf("\tFrequência Acumulada: %d\n", frequenciaAcumulada += listaCategoriasOrdenadas->frequenciaAbsoluta);
        printf("\tMédia Certeza: %f\n", listaCategoriasOrdenadas->mediaCerteza);
        printf("\tDesvio Padrão Certeza: %f\n", listaCategoriasOrdenadas->desvioPadrao);
        CategoriasOrdenadas *next = listaCategoriasOrdenadas->next;
        free(listaCategoriasOrdenadas->nome);
        free(listaCategoriasOrdenadas);
        listaCategoriasOrdenadas = next;
    }
}
