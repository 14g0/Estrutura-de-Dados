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

/* 
    Acessa os ponteiros da árvore digital de acordo com os bits em
    "numBin", e atribui a informação passada em "info" de acordo com
    a sub-máscara de rede. Se o bit da casa do número binário não
    foi alocado, a função o aloca e acrescenta na lista encadeada.
*/
void makeDigitalTree(int subMasc, char *numBin, char *info);

/* Lê os IPs requisitados para output, e imprime conforme a leitura. */
void printOutput(void);

/*----------------------------------------------------------------------------*/

int main(void) {
    cabeca = calloc(1, sizeof(no));

    lerInput();
    puts("----------------------------------");
    printOutput();

    return 0;
}

/*----------------------------------------------------------------------------*/

void lerInput(void) {
    int cont, n1, n2, n3, n4, subMasc, qtd;
    char *binario = calloc(sizeof(char), 33),
         *info = calloc(sizeof(char), 61);

    scanf("%d", &qtd);

    for(cont=0 ; cont<qtd ; cont+=1) {
        scanf("%d.%d.%d.%d/%d ", &n1, &n2, &n3, &n4, &subMasc);
        fgets(info, 61, stdin);

        ipToBin(n1, binario);
        ipToBin(n2, binario);
        ipToBin(n3, binario);
        ipToBin(n4, binario);
        makeDigitalTree(subMasc, binario, info);
    }
}

/*----------------------------------------------------------------------------*/

void ipToBin(int numDec, char *string) {
    int cont, tamStr=0, resto,
        ddendo = numDec;

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

void makeDigitalTree(int subMasc, char *numBin, char *info) {
    int cont, cont2;
    no *novo, *ultimo = cabeca;

    for(cont=0 ; cont<32 ; cont+=1) {
        if(numBin[cont] == '0') {
            if(ultimo->zero) ultimo = ultimo->zero;
            else {
                if((novo = calloc(1, sizeof(no))) == NULL) {
                    puts("\033[1;31mfailed: calloc L110\033[m");
                    exit(-1);
                }
                else {
                    ultimo->zero = novo;
                    ultimo = novo;
                }
            }
        }
        else if(numBin[cont] == '1') {
            if(ultimo->um) ultimo = ultimo->um;
            else {
                if((novo = calloc(1, sizeof(no))) == NULL) {
                    puts("\033[1;31mfailed: calloc L123\033[m");
                    exit(-1);
                }
                else {
                    ultimo->um = novo;
                    ultimo = novo;
                }
            }
        }

        if(cont == subMasc-1) {
            for(cont2=0 ; info[cont2] != '\0' ; cont2+=1);

            if((ultimo->info = malloc(sizeof(char)*(cont2+1))) == NULL) {
                puts("\033[1;31mfailed: malloc L136\033[m");
                exit(-1);
            }
            else {
                for(cont2=0 ; info[cont2] != '\0' ; cont2+=1) {
                    ultimo->info[cont2] = info[cont2];
                }
                info[cont2] = '\0';
            }
        }
    }
}

/*----------------------------------------------------------------------------*/

void printOutput(void) {
    int cont, n1, n2, n3, n4;
    char *binario = calloc(sizeof(char), 33), *info;
    no *ultimo = cabeca;

    while(scanf("%d.%d.%d.%d\n", &n1, &n2, &n3, &n4)) {
        ipToBin(n1, binario);
        ipToBin(n2, binario);
        ipToBin(n3, binario);
        ipToBin(n4, binario);

        for(cont=0 ; ultimo ; cont+=1) {
            if(binario[cont] == '0') {
                ultimo = ultimo->zero;

                info = ultimo->info;
                puts("0");
            }
            else if(binario[cont] == '1') {
                ultimo = ultimo->um;

                info = ultimo->info;
                puts("1");
            }
        }

        printf("%s", info);
    }

    free(binario);
}