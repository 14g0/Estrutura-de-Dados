#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valor;
    struct nodo *prox;
} nodo;


/* Cria um novo nó para a linked */
nodo *newNodo(int valor);

/* Insere um novo nodo na lista ordenadamente*/
void insertionSort(nodo **cabeca, nodo *novoNodo);

/* Printa a linked */
void printLinked(nodo *cabeca);

/*
    Eu pensei melhor por 1min e não faz o menor sentido fazer um bubble sort
    na lista encadeada, então criei a função pra colocar ordenadamente.
    Eu tentei fazer de jeitos normais, pedi até pro gepeto, mas é tudo sinistro
    então acho melhor ficar só com o insertionSort mesmo.

    void bubbleLinked(nodo *cabeca);
*/

/*----------------------------------------------------------------------------*/

int main(void) {
    int valor;
    nodo *head = NULL;

    while(scanf("%d", &valor)) {
        insertionSort(&head, newNodo(valor));
        printLinked(head);
        puts("--------------------------");
    }

    return 0;
}

/*----------------------------------------------------------------------------*/

nodo *newNodo(int valor) {
    nodo *novaChave = malloc(sizeof(nodo));

    novaChave->valor = valor;
    novaChave->prox = NULL;

    return novaChave;
}

/*----------------------------------------------------------------------------*/

void insertionSort(nodo **cabeca, nodo *novoNodo) {
    nodo **auxiliar = cabeca, *anterior;
    
    if(!*auxiliar) {
        puts("Primeiro");
        *auxiliar = novoNodo;
    }
    else {
        while((novoNodo->valor >= (*auxiliar)->valor) && (*auxiliar)->prox) {
            (*auxiliar) = (*auxiliar)->prox;
        }
        if(!(*auxiliar)->prox) (*auxiliar)->prox = novoNodo;
        else if(auxiliar == cabeca) {
            *auxiliar = novoNodo;
            novoNodo->prox = *auxiliar;
        }
    }
}

/*----------------------------------------------------------------------------*/

void printLinked(nodo *cabeca) {
    nodo *aux = cabeca;

    while(aux) {
        printf("nodo=[%d, %x]\n", aux->valor, aux->prox);
        aux = aux->prox;
        /*
            Como o aux recebe o próximo dele mesmo, se o nodo for o último,
            o próximo dele é nulo, então o aux é nulo e while termina pq
            null é falso.
        */
    }

/*----------------------------------------------------------------------------*/

/*
void bubbleLinked(nodo *cabeca) {
    nodo *anterior = NULL, *atual;
    int trocado = 0;

    do {    
        atual = cabeca;
        trocado = 1;
        while(atual->prox != anterior) {
            if(atual->valor > atual->prox->valor) {
                if(atual->valor > atual->prox->valor) {
                    if(anterior) anterior->prox = atual->prox;
                    else cabeca = atual->prox;
                }

                atual->prox = atual->prox->prox;
                atual->prox->prox = atual;
                trocado = 1;
            }
        }
        anterior = atual;
        atual = atual->prox;
    }while(trocado);
}
*/
}