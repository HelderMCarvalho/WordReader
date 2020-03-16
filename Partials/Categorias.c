#include <math.h>

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
