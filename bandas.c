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
    Eu pensei melhor por 1min e não faz muito sentido realizar
    um Bubble Sort na lista encadeada, é muito mais simples
    inserir ordenadamente.
    Dito isso, se alguém não conseguir fazer de nenhum, eu crio um
    Bubble Sort depois.

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
    nodo *atual;

    /*Se o novo nodo for menor que a cabeça, ele vira a cabeça*/
    if(!(*cabeca) || (*cabeca)->valor >= novoNodo->valor) {
        novoNodo->prox = *cabeca;
        *cabeca = novoNodo;
    }
    else {
        /* Começa a percorrer a cabeça */
        atual = *cabeca;
        
        /*
            Percorre até o próximo ser nulo ou o valor do pŕoximo
            ser menor que o valor do novo nodo.
        */
        while(atual->prox && (atual->prox->valor < novoNodo->valor)) {
            atual = atual->prox;
        }
        /*
            -Se o atual for o último, vc simplesmente adiciona no final
            -Se não, já tem o anterior ao novo nodo.
        */
        novoNodo->prox = atual->prox;
        atual->prox = novoNodo;
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
    nodo *anterior, *atual;
}
*/
}
