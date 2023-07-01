#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no {
    struct no *zero, *um;
    char *info;
} no;

/*
typedef struct numBin {
    char 
} numBin;
*/

/*----------------------------------------------------------------------------*/

/* Recebe os inputs das CIDRs e faz o tratamento das strings */
void lerInput(void);

/*
    Converte o número em base decimal passado como argumento para
    binário, e o concatena na string também passada como argumento.
*/
void ipToBin(int numDec, char *string);

/*  */
void makeDigitalT(void);

/*----------------------------------------------------------------------------*/

int main(void) {
    char *numero = calloc(sizeof(char), 1);
    int cont;

    ipToBin(94, numero);
    ipToBin(2, numero);

    puts(numero);

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

    char *numBin = calloc(1, 1), troca,
        *concat = malloc(0);
    
    puts(string);
    for(cont=0 ; ddendo>0 ; cont+=1) {
        resto = ddendo % 2;
        ddendo /= 2;

        numBin = realloc(numBin, sizeof(char)*(cont+1));
        numBin[cont] = 48+resto;
    }
    numBin = realloc(numBin, sizeof(char)*(cont+1));
    numBin[cont] = '\0';
    tamBin = cont-1;

    for(cont=0 ; cont<(tamBin+1)/2 ; cont+=1) {
        troca = numBin[cont];
        numBin[cont] = numBin[tamBin-cont];
        numBin[tamBin-cont] = troca;
    }

    strcat(string, numBin);
}
/*----------------------------------------------------------------------------*/
