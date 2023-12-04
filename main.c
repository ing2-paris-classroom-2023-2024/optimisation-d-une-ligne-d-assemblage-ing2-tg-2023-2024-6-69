#include "graphe.h"
#include "precedences.h"
#include "temps_cycle.h"
#include "exclusions.h"
#include <stdio.h>

int main() {
    Graphe* graphe = creerGraphe(MAX_OPERATIONS);

    // menu
    printf("Choisissez les contraintes à appliquer :\n");
    printf("1: Exclusion seulement\n");
    printf("2: Temps de cycle et précédence\n");
    printf("3: Toutes les contraintes\n");
    int choix;
    scanf("%d", &choix);

    // applique contrainte
    graphe->contrainteExclusion = (choix == 1 || choix == 3);
    graphe->contrainteTemps = (choix == 2 || choix == 3);
    graphe->contraintePrecedence = (choix == 2 || choix == 3);

    //lecture fichiers
    lireRelationsPrecedence(graphe, "C:/Users/nicol/OneDrive/Bureau/precedences.txt");
    lireTempsOperations(graphe, "C:/Users/nicol/OneDrive/Bureau/operations.txt");
    lirePairesExclusion(graphe, "C:/Users/nicol/OneDrive/Bureau/exclusions.txt");

    // durée cycle
    graphe->tempsCycle = lireDureeCycle("C:/Users/nicol/OneDrive/Bureau/temps_cycle.txt");

    //sommets visités
    bool visite[MAX_OPERATIONS] = {false};
    bfs(graphe);

    return 0;
}
