#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_PRECEDENCES_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_PRECEDENCES_H

typedef struct Noeud {
    int sommet;
    struct Noeud* suivant;
} Noeud;

typedef struct {
    Noeud** tableau;
    int* degreEntrant;
    struct Affectation {
        int operation;
        int station;
    } affectations;
    int sommets;
    int nombreAffectations;
} Graphep;

Graphep creerGraphe(int sommets);
void ajouterArc(Graphep* graphep, int src, int dest);
void imprimerGraphep(Graphep* graphep);
void libererGraphep(Graphep* graphep);
Graphep* construireGrapheDepuisFichier(const char* nomFichier);
double recupererDureeOperation(int numeroOperation);

void ajouterOperation(Graphep* graphe, int station, int sommet);
void retirerOperation(Graphep* graphe, int station, int sommet);
int trouverStationDisponible(Graphep* graphe, int operation, int tempsCycle);
void verifierContrainteTempsCycle(Graphep* graphe, const char* fichierTempsCycle);

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_6_69_PRECEDENCES_H
