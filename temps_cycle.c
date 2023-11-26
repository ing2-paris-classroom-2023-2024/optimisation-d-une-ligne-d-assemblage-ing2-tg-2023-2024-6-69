//
// Created by antoi on 26/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void calcul(){
    int i = 0;
    int j = 0;
    for (int k = 0; k < 10; ++k) {
        printf("k = %d\n", k);
        clock_t t1 = clock();
        for (int l = 0; l < 1000000; ++l) {
            i++;
            j++;
        }
        clock_t t2 = clock();
        printf("Temps = %ld\n", t2 - t1);
        if (t2 - t1 > 0){
            printf("Temps = %ld\n", t2 - t1);
        }
    }
}
int temps_cycle(){
    int temps = 0;
    int i = 0;
    int j = 0;
    for (int k = 0; k < 10; ++k) {
        printf("k = %d\n", k);
        clock_t t1 = clock();
    }
    clock_t t2 = clock();
    printf("Temps = %ld\n", temps);
    printf("Temps = %ld\n");

    printf("hello");
    printf("hello");
    return 0;

}




int main(){
    temps_cycle();
    return 0;
}