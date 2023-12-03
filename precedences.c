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
            printf("Station %d : ", i);
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
    // Gerer le cas où le numero de l'operation n'est pas trouve.
    return 0.0;
}

int trouverStationDisponible(Graphep* graphe, int operation, int tempsCycle) {
    for (int station = 0; station < graphe->sommets; ++station) {
        double capaciteStation = tempsCycle;
        Noeud* courant = graphe->tableau[station];

        while (courant) {
            int sommet = courant->sommet;
            double dureeOperation = recupererDureeOperation(sommet);
            capaciteStation -= dureeOperation;

            courant = courant->suivant;
        }

        if (capaciteStation >= recupererDureeOperation(operation)) {
            return station;
        }
    }

    return -1;
}

void retirerOperation(Graphep* graphe, int station, int operation) {
    Noeud* courant = graphe->tableau[station];
    Noeud* precedent = NULL;

    while (courant) {
        if (courant->sommet == operation) {
            if (precedent) {
                precedent->suivant = courant->suivant;
            } else {
                graphe->tableau[station] = courant->suivant;
            }

            free(courant);
            return;
        }

        precedent = courant;
        courant = courant->suivant;
    }
}

void ajouterOperation(Graphep* graphe, int station, int operation) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    nouveauNoeud->sommet = operation;
    nouveauNoeud->suivant = graphe->tableau[station];
    graphe->tableau[station] = nouveauNoeud;
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
            courant = graphe->tableau[i]; // Réinitialiser courant à la tête de la liste

            int sommet = courant->sommet; // Sommet à réaffecter
            int station = i;

            while (station < graphe->sommets) {
                Noeud* courantStation = graphe->tableau[station];
                double capaciteStation = tempsCycle;

                while (courantStation) {
                    int sommetActuel = courantStation->sommet;
                    double dureeOperation = recupererDureeOperation(sommetActuel);
                    capaciteStation -= dureeOperation;

                    courantStation = courantStation->suivant;
                }

                if (capaciteStation >= recupererDureeOperation(sommet)) {
                    retirerOperation(graphe, i, sommet);
                    ajouterOperation(graphe, station, sommet);

                    printf("L'operation %d a ete reaffectee a la station %d pour optimisation.\n", sommet, station);
                    break; // Sortir de la boucle si la station est trouvée
                }

                ++station; // Passer à la station suivante
            }

            if (station == graphe->sommets) {
                printf("Avertissement : Impossible de reaffecter l'operation %d a une autre station. Verifiez les contraintes.\n", sommet);
            }
        }
    }
}

void afficherStationsMisesAJour(Graphep* graphe) {
    printf("\nStations avec les opérations mises a jour :\n");
    for (int i = 0; i < graphe->sommets; ++i) {
        if (graphe->tableau[i] != NULL) {
            printf("Station %d : ", i);
            Noeud* courant = graphe->tableau[i];
            while (courant) {
                printf("%d ", courant->sommet);
                courant = courant->suivant;
            }

            printf("\n");
        }
    }
    printf("----------------\n");
}

// Modifiez votre fonction precedences
void precedences() {
    Graphep* graphe = construireGrapheDepuisFichier("precedences.txt");
    printf("Liste initiale des stations :\n");
    imprimerGraphep(graphe);

    verifierContrainteTempsCycle(graphe, "temps_cycle.txt");

    // Affichez la liste mise à jour après la vérification
    afficherStationsMisesAJour(graphe);

    libererGraphep(graphe);
}