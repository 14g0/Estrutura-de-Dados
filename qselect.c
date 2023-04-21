#include <stdio.h>
#include <stdlib.h>

/* Variáveis globais */
int *vetor = NULL, tam=0;

/*--------------------------------- Funções ----------------------------------*/
int commandLine(char* flag, char* position, int qtt);
/* Analisa os argumentos passados na linha de comando. */

int strCompare(char* str1, char* str2);
/* Remake da strcmp da biblioteca <string.h> */

int mallocFile(void);
/* Lê os números pela entrada e realiza a alocação dinâmica dos inteiros nele */

int quickSelect(int* array, int start, int end, int pos);
/* Descobre o elemento da posição desejada sem ordenar o vetor completamente. */

/*----------------------------------------------------------------------------*/

int main(int argc, char **argv) {
    int resultado;

    if(!mallocFile()) puts("O vetor está vazio.");

    if((resultado = commandLine(argv[1], argv[2], argc))) {
        resultado = quickSelect(vetor, 1, tam, resultado);
    }

    printf("%d\n", resultado);

    return 0;
}

/*----------------------------------------------------------------------------*/

int commandLine(char* flag, char* number, int qtt) {
    int cont, posicao=0, tamanho, potencia=1;

    if(qtt != 3) return 0;

    for(cont=0 ; flag[cont]!='\0' ; cont+=1) {
        if(((cont>1) && (flag[cont]!='\0')) || ((cont<=1) && (flag[cont]=='\0'))) return 0;
    }

    if(strCompare("-k", flag)) {
        puts("\033[31mfailed: unknown flag\033[m");
        exit(0);
    }

    for(cont=0 ; number[cont]!='\0' ; cont+=1);
    tamanho = cont;

    for(cont=tamanho-1 ; cont>=0 ; cont-=1) {
        if((number[cont] > 57) || (number[cont] < 48)) {
            printf("\033[31mfailed: flag argument NaN\033[m");
            exit(0);
        }

        posicao += (number[cont]-48)*potencia;
        potencia *= 10;
    }
    if(posicao == 0) {
        puts("\033[31mfailed: invalid position");
        puts("-position must be higher than 0\033[m");
        exit(0);
    }
    else if(posicao > tam) {
        puts("\033[31mfailed: invalid position");
        puts("-position must be lower than array maxIndex\033[m");
        exit(0);
    }

    return posicao;
}

/*----------------------------------------------------------------------------*/

int strCompare(char* str1, char* str2) {
    int cont=0;

    while((str1[cont] == str2[cont]) && ((str1[cont]!='\0') || (str2[cont]!='\0'))) cont+=1;

    if(str1[cont] > str2[cont]) return 1;
    else if(str2[cont] > str1[cont]) return -1;
    else return 0;
}

/*----------------------------------------------------------------------------*/

int mallocFile(void) {
    int input;

    while(scanf("%d", &input) != EOF) {
        if(vetor != NULL) {
            tam += 1;
            if((vetor = realloc(vetor, sizeof(int)*tam)) == NULL) {
                puts("\033[31mfailed: realloc\033[m");
                exit(0);
            }
            vetor[tam-1] = input;
        }
        else {
            tam += 1;
            if((vetor = malloc(sizeof(int))) == NULL) {
                puts("\033[31mfailed: malloc\033[m");
                exit(0);
            }
            vetor[tam-1] = input;
        }
    }

    return tam;
}

/*----------------------------------------------------------------------------*/

int quickSelect(int* array, int start, int end, int pos) {
    int cont, troca, maior = start-2;

    for(cont=start-1 ; cont<end-1 ; cont+=1) {
        if(array[cont] <= array[end-1]) {
            maior += 1;
            troca = array[cont];
            array[cont] = array[maior];
            array[maior] = troca;
        }
    }

    maior += 1;
    troca = array[end-1];
    array[end-1] = array[maior];
    array[maior] = troca;

    if((pos-1) > maior) quickSelect(vetor, maior+1, tam, pos);
    else if((pos-1) < maior) quickSelect(vetor, 1, maior, pos);

    return array[pos-1];
}