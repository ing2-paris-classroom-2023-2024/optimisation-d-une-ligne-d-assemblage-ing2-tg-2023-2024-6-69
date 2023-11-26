//
// Created by Kamil Benjelloun on 26/11/2023.
//


#include <stdio.h>
#include <stdlib.h>

int main() {
    //tableau

    int tab[5] = {1, 2, 3, 4, 5};
    int *p = tab;
    int *q = tab + 2;
    int *r = tab + 4;
    printf("%d\n", *p);

    printf("%d\n", *q);
    printf("%d\n", *r);
    printf("%d\n", *p + 1);
    printf("%d\n", *q + 1);

}
