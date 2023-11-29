#include <stdio.h>
#include <stdlib.h>

// Structure pour stocker les données d'une opération
typedef struct {
    int numero;
    float tempsExecution;
} Operation;

// Fonction pour lire le temps de cycle à partir d'un fichier
void lireTempsCycle(char *nomFichier, float *tempsCycle) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier temps_cycle.txt");
        exit(EXIT_FAILURE);
    }

    // Lire le temps de cycle
    fscanf(fichier, "%f", tempsCycle);

    fclose(fichier);
}

// Fonction pour lire les opérations à partir d'un fichier
void lireOperations(char *nomFichier, Operation *operations, int *nbOperations) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier operations.txt");
        exit(EXIT_FAILURE);
    }

    // Lire le nombre total d'opérations
    fscanf(fichier, "%d", nbOperations);

    // Lire les opérations
    for (int i = 0; i < *nbOperations; i++) {
        fscanf(fichier, "%d %f", &operations[i].numero, &operations[i].tempsExecution);
    }

    fclose(fichier);
}

// Fonction pour vérifier la contrainte de temps de cycle
int verifierContrainteTempsCycle(float *tempsExecution, int *affectations, int nbStations, int nbOperations, float tempsCycle) {
    for (int k = 1; k <= nbStations; k++) {
        float tempsTotal = 0.0;
        for (int j = 1; j <= nbOperations; j++) {
            if (affectations[j] == k) {
                tempsTotal += tempsExecution[j];
            }
        }
        if (tempsTotal > tempsCycle) {
            return 0; // La contrainte de temps de cycle est violée
        }
    }
    return 1; // La contrainte de temps de cycle est respectée
}

int main() {
    // Déclarer la variable pour stocker la durée du temps de cycle
    float tempsCycle;

    // Lire la durée du temps de cycle à partir du fichier
    lireTempsCycle("temps_cycle.txt", &tempsCycle);

    // Déclarer une structure pour stocker les opérations
    int nbOperations;
    Operation operations[35];

    // Lire les opérations à partir du fichier
    lireOperations("operations.txt", operations, &nbOperations);

    // Exemple d'affectations à chaque station
    int nbStations = 3; // À ajuster en fonction de votre modèle
    int affectations[36] = {0, 1, 1, 2, 2, 3, 1, 3, 1, 2, 3, 1, 2, 2, 3, 3, 3, 1, 1, 1, 2, 2, 1, 3, 1, 2, 3, 2, 3, 3, 3, 1, 1, 2, 3, 3};

    // Vérifier la contrainte de temps de cycle
    if (verifierContrainteTempsCycle(operations, affectations, nbStations, nbOperations, tempsCycle)) {
        printf("La contrainte de temps de cycle est respectee.\n");
    } else {
        printf("La contrainte de temps de cycle est violée.\n");
    }

    return 0;
}
