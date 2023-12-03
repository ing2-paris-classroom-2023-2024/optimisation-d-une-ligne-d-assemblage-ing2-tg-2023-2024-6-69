//
// Created by Kamil Benjelloun on 26/11/2023.
//


#include "precedences.h"
#include <stdio.h>
#include <stdlib.h>



Graphep* creerGraphe(int sommets) {
    Graphep* graphe = (Graphep*)malloc(sizeof(Graphep));
    graphe->sommets = sommets;
    graphe->tableau = (Noeud**)malloc(sommets * sizeof(Noeud*));
    graphe->degreEntrant = (int*)malloc(sommets * sizeof(int));

    for (int i = 0; i < sommets; ++i) {
        graphe->tableau[i] = NULL;
        graphe->degreEntrant[i] = 0;
    }

    return graphe;
}

void ajouterArc(Graphep* graphe, int src, int dest) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    nouveauNoeud->sommet = dest;
    nouveauNoeud->suivant = graphe->tableau[src];
    graphe->tableau[src] = nouveauNoeud;
    graphe->degreEntrant[dest]++;
}

void imprimerGraphep(Graphep* graphep) {
    for (int i = 0; i < graphep->sommets; ++i) {
        if (graphep->tableau[i] != NULL) {
            printf("Sommet %d : ", i);
            Noeud* courant = graphep->tableau[i];
            while (courant) {
                printf("%d ", courant->sommet);
                courant = courant->suivant;
            }
            printf("\n");
        }
    }
    printf("----------------\n");
}

void libererGraphep(Graphep* graphe) {
    for (int i = 0; i < graphe->sommets; ++i) {
        Noeud* courant = graphe->tableau[i];
        while (courant) {
            Noeud* suivant = courant->suivant;
            free(courant);
            courant = suivant;
        }
    }

    free(graphe->tableau);
    free(graphe->degreEntrant);
    free(graphe);
}

Graphep* construireGrapheDepuisFichier(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int src, dest;
    int sommets = 0;

    while (fscanf(fichier, "%d %d", &src, &dest) == 2) {
        sommets = (src > sommets) ? src : sommets;
        sommets = (dest > sommets) ? dest : sommets;
    }

    fseek(fichier, 0, SEEK_SET);

    Graphep* graphe = creerGraphe(sommets + 1);

    while (fscanf(fichier, "%d %d", &src, &dest) == 2) {
        ajouterArc(graphe, src, dest);
    }

    fclose(fichier);
    return graphe;
}

double recupererDureeOperation(int numeroOperation) {
    FILE* fichier = fopen("operations.txt", "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier operations.txt");
        exit(EXIT_FAILURE);
    }

    int numero;
    double duree;

    while (fscanf(fichier, "%d %lf", &numero, &duree) == 2) {
        if (numero == numeroOperation) {
            fclose(fichier);
            return duree;
        }
    }

    fclose(fichier);
    // Gérer le cas où le numéro de l'opération n'est pas trouvé.
    return 0.0;
}

void verifierContrainteTempsCycle(Graphep* graphe, const char* fichierTempsCycle) {
    FILE* fichier = fopen(fichierTempsCycle, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier temps_cycle");
        exit(EXIT_FAILURE);
    }

    int tempsCycle;
    fscanf(fichier, "%d", &tempsCycle);
    fclose(fichier);

    for (int i = 0; i < graphe->sommets; ++i) {
        Noeud* courant = graphe->tableau[i];
        double dureeTotale = 0;

        while (courant) {
            int sommet = courant->sommet;
            double dureeOperation = recupererDureeOperation(sommet);
            dureeTotale += dureeOperation;

            courant = courant->suivant;
        }

        if (dureeTotale > tempsCycle) {
            printf("La durée totale des opérations par la station %d dépasse le temps de cycle spécifié.\n", i);
            // Ajoutez ici le code pour prendre des mesures en conséquence, par exemple, arrêter le programme.
        }
    }
}

void precedences() {
    Graphep* graphe = construireGrapheDepuisFichier("precedences.txt");
    imprimerGraphep(graphe);
    verifierContrainteTempsCycle(graphe, "temps_cycle.txt");
    libererGraphep(graphe);
}
