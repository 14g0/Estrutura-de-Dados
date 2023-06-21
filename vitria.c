#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int v1, v2, peso;
} Aresta;

int compare(const void* a, const void* b) {
    return ((Aresta*)a)->peso - ((Aresta*)b)->peso;
}

int find(int v, int* parent) {
    if (parent[v] == -1)
        return v;
    return find(parent[v], parent);
}

void unionFind(int x, int y, int* parent) {
    int xset = find(x, parent);
    int yset = find(y, parent);
    parent[xset] = yset;
}

int kruskal(int n_vertices, Aresta arestas[], int n_arestas) {
    qsort(arestas, n_arestas, sizeof(Aresta), compare);

    int* parent = (int*)malloc(n_vertices * sizeof(int));
    for (int i = 0; i < n_vertices; i++) {
        parent[i] = -1;
    }

    int resultado = 0;
    int arestasSelecionadas = 0;

    for (int i = 0; i < n_arestas; i++) {
        int v1 = find(arestas[i].v1, parent);
        int v2 = find(arestas[i].v2, parent);

        if (v1 != v2) {
            resultado += arestas[i].peso;
            unionFind(v1, v2, parent);
            arestasSelecionadas++;

            if (arestasSelecionadas == n_vertices - 1) {
                break;  // Todas as arestas necessárias foram selecionadas
            }
        }
    }

    free(parent);

    return resultado;
}

int main() {
    int n_vertices, n_arestas;
    scanf("%d %d", &n_vertices, &n_arestas);

    Aresta* arestas = (Aresta*)malloc(n_arestas * sizeof(Aresta));

    for (int i = 0; i < n_arestas; i++) {
        scanf("%d %d %d", &arestas[i].v1, &arestas[i].v2, &arestas[i].peso);
    }

    int resultado = kruskal(n_vertices, arestas, n_arestas);

    printf("%d\n", resultado);

    free(arestas);

    return 0;
}

{


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
    int cont, resultado=0, cont2;

    mallocGrafo();

    for(cont=0 ; cont<qtdArestas ; cont+=1) {
        if(Find(arestas[cont].v1) != Find(arestas[cont].v2)) {
            printf("juntei: %d | %d\n", arestas[cont].v1, arestas[cont].v2);
            Union(arestas[cont].v1, arestas[cont].v2);
            for(cont2=0 ; cont2<qtdVert+1 ; cont2+=1) {
                printf("%d |", subconjuntos[cont2]);
            }
            puts("");
            printf("\033[32mSOMEI %d\033[m\n", arestas[cont].peso);
            resultado += arestas[cont].peso;
            puts("\n");
        }
    }

    
    puts("\n--------------------------");
    puts("\n");
    for(cont=0 ; cont<qtdVert ; cont+=1) {
        printf("%d, ", tamanhos[cont]);
    }


    printf("\n%d\n", resultado);

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

    
    for(cont=0 ; cont<qtdArestas ; cont+=1) {
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

}