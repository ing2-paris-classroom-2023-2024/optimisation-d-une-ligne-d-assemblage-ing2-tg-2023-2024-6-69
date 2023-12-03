#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int main(){
    int choix;
    printf("Selectionnez une option :\n1- Exclusion\n2- Precedence et Temps de Cycle\n3- Exclusion et Precedence\n4- Exclusion et Temps de Cycle\n5- Les 3 a la fois\n");
    scanf("%d", &choix);
    switch (choix) {
        case 1:
            printf("1. Exclusion\n");
            //exclusions();
            break;
        case 2:
            printf("2. Precedence et Temps de Cycle\n");
            //precedences();
            break;
        case 3:
            printf("3. Exclusion et Precedence\n");
            break;
        case 4:
            printf("4. Exclusion et Temps de Cycle\n");
            break;
        case 5:
            printf("5. Les 3 a la fois\n");
            break;
    }
}
