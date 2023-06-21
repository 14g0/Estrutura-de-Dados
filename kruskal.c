#include <stdio.h>
#include <stdlib.h>


typedef struct Aresta {
    int peso, v1, v2;
} Aresta;

Aresta *arestas;
int tamanho = 0;



/*----------------------------------------------------------------------------*/

/* Lê as entradas das arestas e seus respectivos pesos */
void getArestas(void);

/* Ordena o vetor de arestas pelo seu peso */
void quickSort(int inicio, int fim);

/**/
void UnionFind(void);


/*----------------------------------------------------------------------------*/

int main(void) {

    getArestas();

    return 0;
}

/*----------------------------------------------------------------------------*/

void getArestas(void) {
    int cont;

    scanf("%*d %d", &tamanho);

    if((arestas = malloc(tamanho*sizeof(Aresta))) == NULL) {
        printf("\033[mfailed: malloc Arestas L37");
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