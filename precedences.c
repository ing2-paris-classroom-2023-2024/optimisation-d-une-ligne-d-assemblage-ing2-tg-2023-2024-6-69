#include "precedences.h"
#include <stdio.h>
#include <stdlib.h>

//lire relations précédence et les intégrer dans le graphe
void lireRelationsPrecedence(Graphe* graphe, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur ouverture fichier précédence");
        exit(EXIT_FAILURE);
    }
    int source, destination;

    // paires source-destination, les ajoute au graphe
    while (fscanf(fichier, "%d %d", &source, &destination) == 2) {
        // sommet plage valide
        if (source >= 1 && source < MAX_OPERATIONS && destination >= 1 && destination < MAX_OPERATIONS) {
            ajouterArete(graphe, source, destination);
        }
    }
    fclose(fichier);
}
