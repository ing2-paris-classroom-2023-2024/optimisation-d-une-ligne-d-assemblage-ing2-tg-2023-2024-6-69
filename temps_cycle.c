#include "temps_cycle.h"
#include "graphe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATIONS 100

//lire durée totale cycle
float lireDureeCycle(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur ouverture fichier temps de cycle");
        exit(EXIT_FAILURE);
    }
    float dureeCycle;
    fscanf(fichier, "%f", &dureeCycle);
    fclose(fichier);
    return dureeCycle;
}

// vérifier la contrainte d'exclusion
bool estExclu(Graphe* graphe, int sommetCourant, int *operationsStation, int nombreOperations) {
    for (int i = 0; i < nombreOperations; i++) {
        if (graphe->matriceExclusion[sommetCourant][operationsStation[i]]) {
            return true;
        }
    }
    return false;
}

//bfs sur le graphe
void bfs(Graphe* graphe) {
    int file[MAX_OPERATIONS], front = 0, arriere = -1;
    int stationCourante = 1;
    int operationsParStation[MAX_STATIONS][MAX_OPERATIONS] = {0};
    int nombreOperationsParStation[MAX_STATIONS] = {0};
    float tempsParStation[MAX_STATIONS] = {0.0};
    bool visite[MAX_OPERATIONS] = {false};

    // init file d'attente
    for (int i = 1; i < graphe->V; i++) {
        if (graphe->existe[i] && (!graphe->contraintePrecedence || graphe->degreEntrant[i] == 0)) {
            file[++arriere] = i;
            visite[i] = true;
        }
    }

    while (front <= arriere) {
        int sommetCourant = file[front++];
        bool ajoutStation = false;

        // parcours stations existantes
        for (int i = 1; i <= stationCourante && !ajoutStation; i++) {
            bool peutEtreAjoute = true;

            // verif contraintes
            if ((graphe->contrainteTemps && (tempsParStation[i] + graphe->tempsOperation[sommetCourant] > graphe->tempsCycle)) ||
                (graphe->contrainteExclusion && estExclu(graphe, sommetCourant, operationsParStation[i], nombreOperationsParStation[i]))) {
                peutEtreAjoute = false;
            }

            if (peutEtreAjoute) {
                operationsParStation[i][nombreOperationsParStation[i]++] = sommetCourant;
                tempsParStation[i] += graphe->tempsOperation[sommetCourant];
                ajoutStation = true;
            }
        }

        // i l'opération pas ajoutée, nouvelle station
        if (!ajoutStation) {
            stationCourante++;
            operationsParStation[stationCourante][0] = sommetCourant;
            nombreOperationsParStation[stationCourante] = 1;
            tempsParStation[stationCourante] = graphe->tempsOperation[sommetCourant];
        }

        // Ajouter opérations à la file d'attente
        for (int l = 1; l < graphe->V; l++) {
            if (graphe->matriceAdjacence[sommetCourant][l] && !visite[l] && graphe->existe[l]) {
                file[++arriere] = l;
                visite[l] = true;
            }
        }
    }

    // Affichage stations avec opérations
    for (int k = 1; k <= stationCourante; k++) {
        printf("Station %d : ", k);
        for (int j = 0; j < nombreOperationsParStation[k]; j++) {
            printf("%d; ", operationsParStation[k][j]);
        }
        printf("en %.2f seconde(s)\n", tempsParStation[k]);
    }
}

//lire temps exécution opérations
void lireTempsOperations(Graphe* graphe, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        perror("Erreur ouverture fichier operation");
        exit(EXIT_FAILURE);
    }

    int operation;
    float temps;

    // paires opération-temps depuis fichier et les intègre dans le graphe
    while (fscanf(fichier, "%d %f", &operation, &temps) == 2) {
        // Vérifie si l'opération est dans la plage valide
        if (operation >= 1 && operation < MAX_OPERATIONS) {
            graphe->tempsOperation[operation] = temps;
        }
    }
    fclose(fichier);
}
