/**
 * Estrutura que guarda todas as categorias, as suas quantidades e certezas acumuladas
 * Guarda também todas as certezas num array de floats
 * Utilizada para o Ex. 2 e Ex. 4
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
} CategoriasOrdenadas;

Categorias *ProcurarCategoria(Categorias *listaCategorias, char *nome);

Categorias *InserirCategoria(Categorias *listaCategorias, char *nome, float certeza);

CategoriasOrdenadas *
InserirCategoriaOrdenada(CategoriasOrdenadas *listaAuxCategoriasOrdenadas, char *nome, int frequenciaAbsoluta,
                         float frequenciaRelativa, float mediaCerteza, float desvioPadrao);

void ListarCategorias(Categorias *listaCategorias, int totalQuantidadesCategorias);
