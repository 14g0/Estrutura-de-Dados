#include <stdio.h>
#include <stdlib.h>

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


/* Cria os vetores de adjacência e inicializa os outros vetores. */
int callocFile(void);

/* Cria as adjacências de cada vértice como uma lista encadeada. */
void newVertice(vertice *array, int valor, int pos);

/* Remove um nó da lista especificada de adjacências. */
int removeVertice(vertice *array, int pos);

/* Adiciona um valor na fila. */
void addToQueue(queue *fila, int valor);

/* Remove o valor da fila. */
int removeFromQueue(queue *fila);

/* Cria a ordenação topológica do grafo. */
void ordenacaoTopologica(void);


/* Funções auxiliares que eu usei desenvolvendo o código. */
void printQueue(queue fila);
void printLinked(void);

/*----------------------------------------------------------------------------*/

int main(int argc, char **argv) {
    vertice *percorre, *troca, *primeiro;

    callocFile();
    printLinked();
    percorre = &vertices[0];

    /*Percorre se encontra no A*/
    while(percorre) {
        puts("1");
        if(percorre->valor /*A*/ > percorre->prox->valor/*B*/) {
            puts("if");
            primeiro = percorre;
            troca = percorre->prox->prox; /*Guardamos o endereço do C*/
            percorre = percorre->prox; /*Percorre agora é o B*/
            percorre->prox = primeiro;
            primeiro->prox = troca;
            percorre = primeiro;
        }
        else {
            puts("else");
            percorre = percorre->prox;
        }
    }
    puts("-----------------------------");
    printLinked();

    return 1;
}

/*----------------------------------------------------------------------------*/

int callocFile(void) {
    char carac = 1, numero[30];
    int cont, absolute = 0,
        posCarac=0, potencia = 1, barraN = 0;

    scanf("%d %d", &tam, &cont);
    getchar();

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
        while(((carac = getchar()) != ' ') && (carac != '\n')) {
            if((48 <= carac) && (carac <= 57)) {
                numero[posCarac] = carac;
                posCarac += 1;
            }
            else if(carac == EOF) break;
        }
        numero[posCarac] = '\0';

        posCarac = 0;
        while(numero[posCarac] != '\0') posCarac += 1;
        for(cont=posCarac-1 ; cont>=0 ; cont-=1) {
            absolute += (numero[cont]-48)*potencia;
            potencia *= 10;
        }

        if(absolute) {
            vetor[absolute-1] += 1;
            newVertice(vertices, absolute, barraN);
        }

        if(carac == '\n') barraN += 1;
        potencia = 1;
        posCarac = 0;
        absolute = 0;
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
    vertice *atual, *prox;

    atual = &array[pos];
    prox = atual->prox;
    removido = atual->valor;
    if(!atual->prox) atual->valor = 0;
    else {
        *atual = *prox;
        free(prox);
    }

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
    int cont, qRem, vRem, ordemPos=0;
    vertice *head;

    for(cont=0 ; cont<tam ; cont+=1) {
        if(vetor[cont] == 0) addToQueue(&fila, cont+1);
    }

    while(fila.queue != NULL) {
        qRem = removeFromQueue(&fila);
        head = &vertices[qRem-1];
        while(head->prox || head->valor) {
            vRem = removeVertice(vertices, qRem-1);
            vetor[vRem-1] -= 1;
            if(vetor[vRem-1] == 0) addToQueue(&fila, vRem);
        }
        ordem[ordemPos] = qRem;
        ordemPos += 1;
    }
    

    for(cont=0 ; cont<tam ; cont+=1) printf("%d ", ordem[cont]);
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
        printf("[%d, %x]->", printv.valor, printv.prox);
        while(printv.prox != NULL) {
            printv = *printv.prox;
            printf("[%d, %x]->", printv.valor, printv.prox);
        }
        puts("");
    }
}