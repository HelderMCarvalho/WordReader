#include <math.h>

/**
 * Função que calcula o Quadrado de um número
 * @param numero -> número para calcular o Quadrado
 * @return -> Quadrado do número
 */
float Quadrado(float numero) {
    return numero * numero;
}

/**
 * Função que calcula a Frequência Relativa
 * @param quantidadeParcial -> quantidade que queremos saber a Frequência
 * @param quantidadeTotal -> quantidade total de elementos existentes
 * @return -> Frequência Relativa multiplicada por 100 (para transformar em %)
 */
float FrequenciaRelativa(float quantidadeParcial, float quantidadeTotal) {
    return (quantidadeParcial / quantidadeTotal) * 100;
}

/**
 * Função que calcula a Média
 * @param somatorioTotal -> somatório dos Elementos
 * @param quantidadeElementos -> quantidade de Elementos somados
 * @return -> Média
 */
float Media(float somatorioTotal, float quantidadeElementos) {
    return somatorioTotal / quantidadeElementos;
}

/**
 * Função que calcula o Desvio Padrão
 * @param somatorioDesvios -> somatório dos desvios
 * @param quantidadeElementos -> quantidade de elementos
 * @return -> Desvio Padrão
 */
float DesvioPadrao(float somatorioDesvios, float quantidadeElementos) {
    return sqrtf(somatorioDesvios / quantidadeElementos);
}

/**
 * Função que Calcula a Mediana
 * Se o Total de Elementos for ímpar devolve o Elemento central (if)
 * Se o Total de Elementos for Par devolve a média dos 2 Elementos centrais (else)
 * @param elementos -> array de Elementos
 * @param totalElementos -> total de Elementos
 * @return -> Mediana
 */
float Mediana(int *elementos, int totalElementos) {
    if (totalElementos % 2 != 0) {
        return (float) elementos[(int) (totalElementos / 2)];
    } else {
        return Media((float) (elementos[(int) ((totalElementos - 1) / 2)] + elementos[(int) (totalElementos / 2)]), 2);
    }
}
