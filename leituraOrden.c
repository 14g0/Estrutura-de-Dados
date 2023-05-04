#include <stdio.h>

int main(void) {
    char carac = 1, numero[30];
    int indice = 0, *vetor, posCarac=0;

    while(carac != EOF) {
        while(((carac = getchar()) != ' ') && (carac != '\n')) {
            if((48 <= carac) && (carac <= 57)) {
                numero[posCarac] = carac;
                posCarac += 1;
            }
            else if(carac == EOF) break;
        }
        numero[posCarac] = '\0';
        printf("%s\n", numero);
    }

    return 0;
}