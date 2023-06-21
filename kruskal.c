#include <stdio.h>
#include <stdlib.h>


typedef struct Aresta {
    int peso, v1, v2;
} Aresta;

Aresta *arestas;
int tamanho = 0;
int* subconjuntos, pesos;

/*----------------------------------------------------------------------------*/

/* Lê as entradas das arestas e seus respectivos pesos. */
void mallocGrafo(void);

/* Ordena o vetor de arestas pelo seu peso, tendo o último sempre como pivot. */
void quickSort(int inicio, int fim);

/* Une os subconjuntos de vértices do grafo. */
void Union(int raiz1, int raiz2);

/* Procura o vértice raiz de um subconjunto. */
int Find(int valor);

/*----------------------------------------------------------------------------*/

int main(void) {

    mallocGrafo();


    return 0;
}

/*----------------------------------------------------------------------------*/

void mallocGrafo(void) {
    int cont, qtdVert;

    scanf("%d %d", &qtdVert, &tamanho);

    if((arestas = malloc(tamanho*sizeof(Aresta))) == NULL) {
        printf("\033[mfailed: malloc Arestas L37\033[m");
    }

    if((subconjuntos = malloc((qtdVert+1)*sizeof(int))) == NULL) {
        printf("\033[mfailed: calloc Arestas L52\033[m");
    }

    if((pesos = calloc(qtdVert, sizeof(int))) == NULL) {
        printf("\033[mfailed: calloc Arestas L52\033[m");
    }

    for(cont=0 ; cont<qtdVert ; cont+=1) {
        subconjuntos[cont] = cont;
    }

    for(cont=0 ; cont<tamanho ; cont+=1) {
        scanf("%d %d %d", &arestas[cont].v1, &arestas[cont].v2, &arestas[cont].peso);
    }

    quickSort(1, tamanho);

    for(cont=0 ; cont<tamanho ; cont+=1) {
        printf("V%02d= v1: %02d | v2: %02d | peso: %02d\n", (cont+1), arestas[cont].v1, arestas[cont].v2, arestas[cont].peso);
    }
}

/*----------------------------------------------------------------------------*/

void quickSort(int inicio, int fim) {
    int cont, atual=inicio-1;
    Aresta troca;

    for(cont=inicio-1 ; cont<fim-1 ; cont+=1) {
        if(arestas[cont].peso <= arestas[fim-1].peso) {
            troca = arestas[cont];
            arestas[cont] = arestas[atual];
            arestas[atual] = troca;
            atual += 1;
        }
    }

    troca = arestas[cont];
    arestas[cont] = arestas[atual];
    arestas[atual] = troca;

    if(inicio < fim) {
        quickSort(inicio, atual);
        quickSort(atual+1, fim);
    }

}

/*----------------------------------------------------------------------------*/

void Union(int raiz1, int raiz2) {

}

/*----------------------------------------------------------------------------*/

int Find(int chave) {
    int procurado = chave;
    while(subconjuntos[procurado] != procurado) {
        procurado = subconjuntos[procurado];
    }
    printf("%d\n", procurado);
    return procurado;
}