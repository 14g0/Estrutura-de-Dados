#include <stdio.h>
#include <stdlib.h>

/* Entrada utilizada de teste, professor que forneceu.
8
2
7
2 4
6
1 3
7

3 4
*/

/*----------------------------------------------------------------------------*/

typedef struct vertice {
    int valor;
    struct vertice *prox;
} vertice;

typedef struct queue {
    int *queue,
        tam;
} queue;

int *vetor, tam = 0, *ordem;
vertice *vertices;
queue fila;

/*----------------------------------------------------------------------------*/


int callocFile(void);
/* Cria os vetores de adjacência e inicializa os outros vetores. */

void newVertice(vertice *array, int valor, int pos);
/* Cria as adjacências de cada vértice como uma lista encadeada. */

int removeVertice(vertice *array, int pos);
/* Remove um nó da lista especificada de adjacências. */

void addToQueue(queue *fila, int valor);
/* Adiciona um valor na fila. */

int removeFromQueue(queue *fila);
/* Remove o valor da fila. */

void ordenacaoTopologica(void);
/* Cria a ordenação topológica do grafo. */


/* Funções auxiliares que eu usei desenvolvendo o código. */
void printQueue(queue fila);
void printLinked(void);
/**/

/*----------------------------------------------------------------------------*/

int main(int argc, char **argv) {

    callocFile();

    return 1;
}

/*----------------------------------------------------------------------------*/

int callocFile(void) {
    int cont, index=0, pos=0, pot=1, barraN=;
    char carac = 1, numero[30];

    scanf("%d", &tam);

    if((vetor = calloc(tam, sizeof(int))) == NULL) {
        puts("\033[31mfailed: calloc array\033[m");
        exit(0);
    }

    if((ordem = calloc(tam, sizeof(int))) == NULL) {
        puts("\033[31mfailed: calloc array\033[m");
        exit(0);
    }

    if((vertices = calloc(tam, sizeof(vertice))) == NULL) {
        puts("\033[31mfailed: calloc vertex array\033[m");
        exit(0);
    }

    while(carac != EOF) {

    }

    return 1;
}

/*----------------------------------------------------------------------------*/

void newVertice(vertice *array, int valor, int pos) {
    vertice *vert = malloc(sizeof(vertice)), *atual;
    vert->valor = valor;
    vert->prox = NULL;

    atual = &array[pos];

    if((atual->valor == 0) && (atual->prox == NULL)) {
        *atual = *vert;
    }
    else {
        while(atual->prox != NULL) atual = atual->prox;
        atual->prox = vert;
    }
}

/*----------------------------------------------------------------------------*/

int removeVertice(vertice *array, int pos) {
    int removido;
    vertice *atual; /* *atual, *anterior*/

    atual = &array[pos];
    removido = atual->valor;

    if(atual->prox == NULL) atual->valor = 0;
    else *atual = *atual->prox;

    printf("%d\n", removido);
    printLinked();
    puts("\n\n");
    /*
    if((atual->valor == valor) && (atual != anterior)) {
        anterior->valor = atual->valor;
        anterior->prox = atual->prox;
        return atual->valor;
    }
    else {
        puts("else");
        atual = atual->prox;
        anterior->valor = atual->valor;
        anterior->prox = atual->prox;
        return atual->valor;
    }
    */
   return removido;
}

/*----------------------------------------------------------------------------*/

void addToQueue(queue *fila, int valor){

    if(fila->queue == NULL) {
        fila->tam += 1;
        if((fila->queue = malloc(sizeof(int)*fila->tam)) == NULL) {
            puts("\033[31mfailed: addToQueue\033[m");
            exit(0);
        }
    }
    else {
        fila->tam += 1;
        if((fila->queue = realloc(fila->queue, sizeof(int)*fila->tam)) == NULL) {
            puts("\033[31mfailed: addToQueue\033[m");
            exit(0);
        }
    }

    fila->queue[fila->tam-1] = valor;
}

/*----------------------------------------------------------------------------*/

int removeFromQueue(queue *fila) {
    int cont, valor = fila->queue[0];

    for(cont=0 ; cont<fila->tam ; cont+=1) {
        fila->queue[cont] = fila->queue[cont+1];
    }
    
    if(fila->queue != NULL) {
        fila->tam -= 1;
        if(((fila->queue = realloc(fila->queue, sizeof(int)*fila->tam)) == NULL) && (fila->tam != 0)) {
            puts("\033[31mfailed: removeFromQueue\033[m");
            exit(0);
        }
    }

    return valor;
}

/*----------------------------------------------------------------------------*/

void ordenacaoTopologica(void) {
    int cont, sup, vert, controle=0;
    queue *pfila = &fila;

    fila.tam = 0;
    fila.queue = NULL;

    for(cont=0 ; cont<tam ; cont+=1) {
        if(vetor[cont] == 0) {
            addToQueue(pfila, cont+1);
        }
    }

    removeVertice(vertices, 4);

    /*

    while(pfila->queue != NULL) {
        sup = removeFromQueue(pfila);
        printf("%d\n", controle+1);
        while((vertices[sup-1].prox != NULL) && (vertices[sup-1].valor != 0)) {
            removeVertice(vertices, sup-1);
        }
    }
    */
    printLinked();
}

/*----------------------------------------------------------------------------*/

void printQueue(queue fila) {
    int cont;

    for(cont=0 ; cont<fila.tam ; cont+=1) {
        printf("%d ", fila.queue[cont]);
    }
    puts("");
}

void printLinked(void) {
    int cont;
    vertice printv;

    for(cont=0 ; cont<tam ; cont+=1) {
        printv = vertices[cont];
        printf("[%d, %p]->", printv.valor, printv.prox);
        while(printv.prox != NULL) {
            printv = *printv.prox;
            printf("[%d, %p]->", printv.valor, printv.prox);
        }
        puts("");
    }
}