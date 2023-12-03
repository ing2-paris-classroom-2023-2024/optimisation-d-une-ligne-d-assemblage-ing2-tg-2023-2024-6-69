#include <string.h>
#include "exclusions.h"


Graphe* lire_graphe(char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("fichier introuvable\n");
        exit(EXIT_FAILURE);
    }

    Graphe* graphe = (Graphe*)malloc(sizeof(Graphe));
    if (!graphe) {
        printf("Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    graphe->ordre = 0;
    graphe->sommets = NULL;

    int s1, s2;
    while (fscanf(fichier, "%d %d", &s1, &s2) == 2) {

        if (s1 >= graphe->ordre) {
            graphe->sommets = realloc(graphe->sommets, (s1 + 1) * sizeof(Sommet));
            for (int i = graphe->ordre; i <= s1; i++) {
                graphe->sommets[i].valeur = i;
                graphe->sommets[i].liste_adjacence = NULL;
            }
            graphe->ordre = s1 + 1;
        }

        if (s2 >= graphe->ordre) {
            graphe->sommets = realloc(graphe->sommets, (s2 + 1) * sizeof(Sommet));
            for (int i = graphe->ordre; i <= s2; i++) {
                graphe->sommets[i].valeur = i;
                graphe->sommets[i].liste_adjacence = NULL;
            }
            graphe->ordre = s2 + 1;
        }


        Arc* nouvel_arc = malloc(sizeof(Arc));
        nouvel_arc->sommet = s2;
        nouvel_arc->poids = 1;
        nouvel_arc->suivant = graphe->sommets[s1].liste_adjacence;
        graphe->sommets[s1].liste_adjacence = nouvel_arc;

        Arc* nouvel_arc_inverse = malloc(sizeof(Arc));
        nouvel_arc_inverse->sommet = s1;
        nouvel_arc_inverse->poids = 1;
        nouvel_arc_inverse->suivant = graphe->sommets[s2].liste_adjacence;
        graphe->sommets[s2].liste_adjacence = nouvel_arc_inverse;
    }

    fclose(fichier);
    return graphe;
}


int *colorer_graphe(Graphe *graphe) {
    int *couleur = (int *)malloc(graphe->ordre * sizeof(int));
    if (!couleur) {
        printf("Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }


    for (int i = 0; i < graphe->ordre; i++) {
        couleur[i] = -1;
    }

    couleur[0] = 0;
    int nombre_de_stations = 1;


    int *disponible = (int *)calloc(graphe->ordre, sizeof(int));


    for (int i = 1; i < graphe->ordre; i++) {

        Arc *arc = graphe->sommets[i].liste_adjacence;
        while (arc != NULL) {
            if (couleur[arc->sommet] != -1) {
                disponible[couleur[arc->sommet]] = 1;
            }
            arc = arc->suivant;
        }


        int cr;
        for (cr = 0; cr < graphe->ordre; cr++) {
            if (disponible[cr] == 0) {
                break;
            }
        }

        couleur[i] = cr;
        if (cr >= nombre_de_stations) {
            nombre_de_stations = cr + 1;
        }


        memset(disponible, 0, graphe->ordre * sizeof(int));
        //fonct pr reinitialiser le tableau dispo
    }



    free(disponible);

    return couleur;
}



void afficher_stations(Graphe *graphe, int *couleur) {
    for (int i = 0; i < graphe->ordre; i++) {
        if (graphe->sommets[i].liste_adjacence != NULL) {
            printf("Opération %d assignée à la station %d\n", i , couleur[i] + 1);
        }
    }
}

void liberer_graphe(Graphe *graphe) {
    for (int i = 0; i < graphe->ordre; i++) {
        Arc *arc = graphe->sommets[i].liste_adjacence;
        while (arc) {
            Arc *tmp = arc;
            arc = arc->suivant;
            free(tmp);
        }
    }
    free(graphe->sommets);
    free(graphe);
}

void exclusions() {
    Graphe* graphe = lire_graphe("exclusions.txt");
    int *couleurs = colorer_graphe(graphe);
    afficher_stations(graphe, couleurs);
    liberer_graphe(graphe);
    free(couleurs);
}