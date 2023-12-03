#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_EXCLUSIONS_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_EXCLUSIONS_H


#include <stdio.h>
#include <stdlib.h>


// Structure d'un arc
struct Arc {
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int poids;  // poids de l'arc
    struct Arc* suivant;
};

typedef struct Arc Arc;

// Structure d'un sommet
struct Sommet {
    int valeur;
    struct Arc* liste_adjacence;
};

typedef struct Sommet Sommet;

// Structure du graphe
struct Graphe {
    int ordre;
    Sommet* sommets;
};

typedef struct Graphe Graphe;

Graphe* lire_graphe(char* nomFichier);
int* colorer_graphe(Graphe *graphe);

// Fonction pour afficher les stations et les opérations assignées
void afficher_stations(Graphe *graphe, int *couleur);
void exclusions();

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_EXCLUSIONS_H
