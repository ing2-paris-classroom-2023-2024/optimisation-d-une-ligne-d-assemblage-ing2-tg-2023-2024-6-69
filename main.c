#include "graphe.h"
#include "precedences.h"
#include "temps_cycle.h"
#include "exclusions.h"
#include <stdio.h>

int main() {
    Graphe* graphe = creerGraphe(MAX_OPERATIONS);

    // menu
    printf("Choisissez votre option :\n1: Exclusion \n2: Precedence et Temps de Cycle\n3: Les 3 en meme temps\n");
    int choix;
    scanf("%d", &choix);

    // applique contrainte
    graphe->contrainteExclusion = (choix == 1 || choix == 3);
    graphe->contrainteTemps = (choix == 2 || choix == 3);
    graphe->contraintePrecedence = (choix == 2 || choix == 3);

    //lecture fichiers
    lireRelationsPrecedence(graphe, "precedences.txt");
    lireTempsOperations(graphe, "operations.txt");
    lirePairesExclusion(graphe, "exclusions.txt");

    // durée cycle
    graphe->tempsCycle = lireDureeCycle("temps_cycle.txt");

    //sommets visités
    bool visite[MAX_OPERATIONS] = {false};
    bfs(graphe);

    return 0;
}
