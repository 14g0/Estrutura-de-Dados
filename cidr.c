#include <stdio.h>
#include <stdlib.h>


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

/* Recebe os inputs das CIDRs e os aloca    */
void lerInput(void);

/*
    Converte o número em base decimal passado como argumento para binário, e o
    concatena na string também passada como argumento.
*/
void ipToBin(int numDec, char *string);

/* Converte o número pe*/
int toInt(char *numero);

/*----------------------------------------------------------------------------*/

int main(void) {
    char *numero = NULL;

    ipToBin(94, numero);



    return 0;
}

/*----------------------------------------------------------------------------*/

void lerInput(void) {
    
}

/*----------------------------------------------------------------------------*/

void ipToBin(int numDec, char *string) {
    int cont, tamanho=0,
        resto, ddendo = numDec;
    
    char carac;

    if(string == NULL) puts("abacate");
    printf("%d\n", tamanho);
    puts("--------------");

    for(cont=0 ; ddendo>=1 ; cont+=1) {
        resto = ddendo % 2;
        ddendo /= 2;
        tamanho += 1;
        printf("%d\n", resto);

        string = realloc(string, sizeof(char)*tamanho);
        carac = 48+resto;
        string[cont] = carac;
    }
    string[cont] = '\0';

    puts("-----------------------");
    printf("%s\n", string);
}

/*----------------------------------------------------------------------------*/

int toInt(char *numero) {
    int cont, numInt=0, tamanho, pot=1;

    for(cont=0 ; numero[cont]!='\0' ; cont+=1);
    tamanho = cont-1;

    for(cont=tamanho ; cont>=0 ; cont-=1) {
        numInt += (numero[cont]-48)*pot;
        pot *= 10;
    }

    return numInt;
}
