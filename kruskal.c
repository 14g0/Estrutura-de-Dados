#include <stdio.h>
#include <stdlib.h>


typedef struct Aresta {
    int peso, v1, v2;
} Aresta;

Aresta *arestas;
int qtdVert, qtdArestas;
int *subconjuntos, *tamanhos;

/*----------------------------------------------------------------------------*/

/* Lê as entradas das arestas e seus respectivos tamanhos. */
void mallocGrafo(void);

/* Ordena o vetor de arestas pelo seu peso, tendo o último sempre como pivot. */
void quickSort(int inicio, int fim);

/* Une os subconjuntos de vértices do grafo. */
void Union(int raiz1, int raiz2);

/* Procura o vértice raiz de um subconjunto. */
int Find(int valor);

/*----------------------------------------------------------------------------*/

int main(void) {
    int cont, resultado=0;

    mallocGrafo();

    for(cont=0 ; cont<qtdArestas ; cont+=1) {
        if(Find(arestas[cont].v1) != Find(arestas[cont].v2)) {
            Union(arestas[cont].v1, arestas[cont].v2);
            resultado += arestas[cont].peso;
        }
    }

    printf("%d\n", resultado);

    return 0;
}

/*----------------------------------------------------------------------------*/

void mallocGrafo(void) {
    int cont;

    scanf("%d %d", &qtdVert, &qtdArestas);

    if((arestas = malloc(qtdArestas*sizeof(Aresta))) == NULL) {
        puts("\033[mfailed: malloc Arestas L37\033[m");
    }

    if((subconjuntos = malloc((qtdVert+1)*sizeof(int))) == NULL) {
        puts("\033[mfailed: calloc Arestas L52\033[m");
    }

    if((tamanhos = calloc((qtdVert+1), sizeof(int))) == NULL) {
        puts("\033[mfailed: calloc Arestas L52\033[m");
    }

    for(cont=0 ; cont<qtdVert+1 ; cont+=1) {
        subconjuntos[cont] = cont;
    }

    for(cont=0 ; cont<qtdArestas ; cont+=1) {
        scanf("%d %d %d", &arestas[cont].v1, &arestas[cont].v2, &arestas[cont].peso);
    }

    quickSort(1, qtdArestas);

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
    int r1 = Find(raiz1),
        r2 = Find(raiz2);

    if(tamanhos[r1] > tamanhos[r2]) {
        subconjuntos[raiz2] = raiz1;
        tamanhos[r1] += 1;
    }
    else if(tamanhos[r2] > tamanhos[r1]) {
        subconjuntos[raiz1] = raiz2;
        tamanhos[r2] += 1;
    }
    else {
        subconjuntos[raiz2] = raiz1;
        tamanhos[raiz1] += 1;
    }
}

/*----------------------------------------------------------------------------*/

int Find(int chave) {
    int procurado = chave;
    while(subconjuntos[procurado] != procurado) {
        procurado = subconjuntos[procurado];
    }
    return procurado;
}