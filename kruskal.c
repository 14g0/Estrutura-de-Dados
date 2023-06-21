#include <stdio.h>
#include <stdlib.h>


/*

- Cata todas as arestas 

*/

typedef struct Aresta {
    int peso, v1, v2;
} aresta;



/*----------------------------------------------------------------------------*/

/* Lê as entradas das arestas e seus respectivos pesos */
void getArestas(aresta *arestas);


void UnionFind(void);


/*----------------------------------------------------------------------------*/

int main(void) {
    aresta *arestas = malloc(sizeof(aresta));

    getArestas(arestas);

    return 0;
}

/*----------------------------------------------------------------------------*/

void getArestas(aresta *arestas) {
    int cont;

    scanf("%*d %d", &cont);

    printf("%d\n", cont);

}