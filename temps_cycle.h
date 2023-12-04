//
// Created by antoi on 04/12/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_TEMPS_CYCLE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_TEMPS_CYCLE_H

#include "graph.h"
float lireDureeCycle(const char* nomFichier);
//algorithme de parcours en largeur
void bfs(Graphe* graphe);
//lecture des temps d'opérations
void lireTempsOperations(Graphe* graphe, const char* nomFichier);


#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_TEMPS_CYCLE_H
