#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quickGenerator(void);
/* Gerador de entrada e saída para o Quick Select */

int ordenTopoGenerator(void);
/* Gerador de entrada e saída para a ordenação topológica */

/*----------------------------------------------------------------------------*/

int main(void) {
    int cont, cont2, troca,
        *vetor=NULL, tam=0;

    FILE *input, *output;

    srand(time(NULL));

    if((input = fopen("input.txt", "w+")) == NULL) {
        printf("failed: open file\n");
        return 0;
    }

    if((output = fopen("output.txt", "w+")) == NULL) {
        printf("failed: open file\n");
        return 0;
    }

    for(cont=0; cont<100 ; cont+=1) {
        fprintf(input, "%d\n", rand());
    }
    rewind(input);

    while(fscanf(input, "%d", &cont2) != EOF) {
        if(vetor != NULL) {
            tam += 1;
            if((vetor = realloc(vetor, sizeof(int)*tam)) == NULL) {
                puts("failed: realloc");
                return 0;                
            }
            vetor[tam-1] = cont2;
        }
        else {
            tam += 1;
            if((vetor = malloc(sizeof(int))) == NULL) {
                puts("failed: malloc");
                return 0;
            }
            vetor[tam-1] = cont2;
        }
    }

    for(cont=0 ; cont<tam ; cont+=1){
        for(cont2=0 ; cont2<tam-1-cont ; cont2+=1) {
            if(vetor[cont2] > vetor[cont2+1]) {
                troca = vetor[cont2];
                vetor[cont2] = vetor[cont2+1];
                vetor[cont2+1] = troca;
            }
        }
    }

    for(cont=0 ; cont<tam ; cont+=1) fprintf(output, "%d\n", vetor[cont]);

    fclose(input);
    fclose(output);
    free(vetor);

    return 1;
}