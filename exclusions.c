#include "exclusions.h"
#include <stdio.h>
#include <stdlib.h>

// lire paire d'exclusion
void lirePairesExclusion(Graphe* graphe, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur ouverture fichier exclusion");
        exit(EXIT_FAILURE);
    }
    int op1, op2;

    // opérations à lire
    while (fscanf(fichier, "%d %d", &op1, &op2) == 2) {
        // operations dans plage valide
        if (op1 >= 1 && op1 < MAX_OPERATIONS && op2 >= 1 && op2 < MAX_OPERATIONS) {
            graphe->matriceExclusion[op1][op2] = graphe->matriceExclusion[op2][op1] = true;
        }
    }
    fclose(fichier);
}
