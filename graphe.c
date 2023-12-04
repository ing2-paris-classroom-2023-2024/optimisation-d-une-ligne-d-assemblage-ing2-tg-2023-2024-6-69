#include "graphe.h"
#include <stdlib.h>

// creer graphe
Graphe* creerGraphe(int V) {
    // Alloue la mémoire pour le graphe
    Graphe* graphe = (Graphe*) malloc(sizeof(Graphe));

    // Init le nombre de sommets
    graphe->V = V;

    // Initialise les tableaux
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graphe->matriceAdjacence[i][j] = false;
        }
        graphe->degreEntrant[i] = 0;
        graphe->existe[i] = false;
        graphe->tempsOperation[i] = 0;
    }

    return graphe;
}

// ajouter arete
void ajouterArete(Graphe* graphe, int src, int dest) {
    graphe->matriceAdjacence[src][dest] = true;
    graphe->degreEntrant[dest]++;
    graphe->existe[src] = graphe->existe[dest] = true;
}

