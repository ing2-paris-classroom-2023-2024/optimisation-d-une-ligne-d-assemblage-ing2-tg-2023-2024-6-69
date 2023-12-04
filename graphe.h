//
// Created by antoi on 04/12/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_GRAPHE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_GRAPHE_H

#include <stdbool.h>

#define MAX_OPERATIONS 36

//graphe pour optimisation
typedef struct {
    // contraintes
    bool contrainteTemps;
    bool contrainteExclusion;
    bool contraintePrecedence;

    // parametres operations
    bool matriceAdjacence[MAX_OPERATIONS][MAX_OPERATIONS];
    int degreEntrant[MAX_OPERATIONS];
    bool existe[MAX_OPERATIONS];
    float tempsOperation[MAX_OPERATIONS];

    // Matrice d'exclusion
    bool matriceExclusion[MAX_OPERATIONS][MAX_OPERATIONS];

    // opérations du graphe
    int V;

    //assemblage
    float tempsCycle;
} Graphe;

Graphe* creerGraphe(int V);

void ajouterArete(Graphe* graphe, int source, int destination);


#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_GRAPHE_H
