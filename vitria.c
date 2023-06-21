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