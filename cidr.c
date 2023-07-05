#include <stdio.h>
#include <stdlib.h>


typedef struct no {
    struct no *zero, *um;
    char *info;
} no;

no *cabeca;

/*----------------------------------------------------------------------------*/

/* Recebe os inputs das CIDRs e faz o tratamento das strings. */
void lerInput(void);

/*
    Converte o número em base decimal passado como argumento para
    binário, e o concatena na string também passada como argumento.
*/
void ipToBin(int numDec, char *string);

/* Organiza  */
void makeDigitalTree(int subMask, char *string);

/*----------------------------------------------------------------------------*/

int main(void) {
    int cont, n1, n2, n3, n4, subMask, qtd, qtdPointer;
    char *numero = calloc(sizeof(char), 33),
         *info = calloc(31, sizeof(char));

    scanf("%d", &qtd);

    for(cont=0 ; cont<qtd ; cont+=1) {
        scanf("%d.%d.%d.%d/%d ", &n1, &n2, &n3, &n4, &subMask);
    }

    return 0;
}

/*----------------------------------------------------------------------------*/

void lerInput(void) {
    int cont, qtd;

    scanf("%d", &qtd);
}

/*----------------------------------------------------------------------------*/

void ipToBin(int numDec, char *string) {
    int cont, tamStr=0, tamBin=0,
        resto, ddendo = numDec;

    char *numBin = calloc(9, sizeof(char)), troca;
    for(cont=0 ; cont<8 ; cont+=1) numBin[cont] = '0';

    /* Adiciona os números na string */
    for(cont=0 ; ddendo>0 ; cont+=1) {
        resto = ddendo % 2;
        ddendo /= 2;

        numBin[cont] = 48+resto;
    }

    /* Inverte a string */
    for(cont=0 ; cont<4 ; cont+=1) {
        troca = numBin[cont];
        numBin[cont] = numBin[7-cont];
        numBin[7-cont] = troca;
    }

    while(string[tamStr] != '\0') tamStr += 1;
    
    for(cont=0 ; cont<9 ; cont+=1) string[tamStr+cont] = numBin[cont];

    free(numBin);
}

/*----------------------------------------------------------------------------*/