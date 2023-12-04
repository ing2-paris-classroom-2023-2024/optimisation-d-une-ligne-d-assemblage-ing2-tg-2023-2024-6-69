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

    // choix contraintes
    switch (choix) {
        case 1:
            graphe->contrainteExclusion = 1;
            graphe->contrainteTemps = 0;
            graphe->contraintePrecedence = 0;
            break;

        case 2:
            graphe->contrainteExclusion = 0;
            graphe->contrainteTemps = 1;
            graphe->contraintePrecedence = 1;
            break;

        case 3:
            graphe->contrainteExclusion = 1;
            graphe->contrainteTemps = 1;
            graphe->contraintePrecedence = 1;
            break;

        default:
            printf("Option invalide.\n");
            return 1;
    }

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
