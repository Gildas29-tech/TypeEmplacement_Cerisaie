#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FICHIER_TYPE "TypeEmplacement.txt"
#define FICHIER_TEMP "Temp.txt"

typedef struct {
    int id;
    char nom[40];
    float prix;
} TypeEmplacement;

// ---------------------------------------------------------
//         FONCTION : AJOUTER UN TYPE D'EMPLACEMENT
// ---------------------------------------------------------
void ajouterType() {
    TypeEmplacement t;

    printf("\n--- AJOUT D'UN TYPE D'EMPLACEMENT ---\n");
    printf("Identifiant : ");
    scanf("%d", &t.id);

    printf("Nom du type : ");
    scanf("%s", t.nom);

    printf("Prix par jour : ");
    scanf("%f", &t.prix);

    FILE *f = fopen(FICHIER_TYPE, "a");
    if (!f) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(f, "%d|%s|%.2f\n", t.id, t.nom, t.prix);
    fclose(f);

    printf(">> Type ajouté avec succès.\n");
}

void listerTypes() {
    FILE *f = fopen(FICHIER_TYPE, "r");
    char ligne[200];

    printf("\n================ LISTE DES TYPES D'EMPLACEMENT ================\n\n");

    if (!f) {
        printf("Aucun fichier trouvé.\n");
        return;
    }

    // En-tête du tableau
    printf("%-12s %-25s %-10s\n", "Identifiant", "Nom", "Prix");
    printf("---------------------------------------------------------------\n");

    int id;
    char nom[40];
    float prix;

    while (fgets(ligne, 200, f)) {
        sscanf(ligne, "%d|%[^|]|%f", &id, nom, &prix);
        printf("%-12d %-25s %-10.2f\n", id, nom, prix);
    }

    printf("---------------------------------------------------------------\n");

    fclose(f);
}

// ---------------------------------------------------------
//           FONCTION : RECHERCHER PAR ID
// ---------------------------------------------------------
void chercherType() {
    int idRecherche;
    char ligne[200];
    int id;
    char nom[40];
    float prix;

    printf("\nIdentifiant à rechercher : ");
    scanf("%d", &idRecherche);

    FILE *f = fopen(FICHIER_TYPE, "r");
    if (!f) {
        printf("Fichier introuvable.\n");
        return;
    }

    int trouve = 0;

    while (fgets(ligne, 200, f)) {
        sscanf(ligne, "%d|%[^|]|%f", &id, nom, &prix);

        if (id == idRecherche) {
            trouve = 1;
            printf("\n-- Type trouvé --\n");
            printf("ID : %d\nNom : %s\nPrix : %.2f\n", id, nom, prix);
            break;
        }
    }

    if (!trouve) {
        printf("Aucun type avec cet ID.\n");
    }

    fclose(f);
}

// ---------------------------------------------------------
//              FONCTION : MODIFIER UN TYPE
// ---------------------------------------------------------
void modifierType() {
    int idRecherche;
    printf("\nID du type à modifier : ");
    scanf("%d", &idRecherche);

    FILE *f = fopen(FICHIER_TYPE, "r");
    FILE *ft = fopen(FICHIER_TEMP, "w");

    if (!f || !ft) {
        printf("Erreur de fichiers.\n");
        return;
    }

    char ligne[200];
    int id;
    char nom[40];
    float prix;
    int modifie = 0;

    while (fgets(ligne, 200, f)) {
        sscanf(ligne, "%d|%[^|]|%f", &id, nom, &prix);

        if (id == idRecherche) {
            modifie = 1;
            printf("\nNouveau nom : ");
            scanf("%s", nom);
            printf("Nouveau prix : ");
            scanf("%f", &prix);
        }

        fprintf(ft, "%d|%s|%.2f\n", id, nom, prix);
    }

    fclose(f);
    fclose(ft);

    remove(FICHIER_TYPE);
    rename(FICHIER_TEMP, FICHIER_TYPE);

    if (modifie)
        printf(">> Modification effectuée.\n");
    else
        printf("ID introuvable.\n");
}

// ---------------------------------------------------------
//              FONCTION : SUPPRIMER UN TYPE
// ---------------------------------------------------------
void supprimerType() {
    int idRecherche;
    printf("\nID du type à supprimer : ");
    scanf("%d", &idRecherche);

    FILE *f = fopen(FICHIER_TYPE, "r");
    FILE *ft = fopen(FICHIER_TEMP, "w");

    if (!f || !ft) {
        printf("Erreur de fichiers.\n");
        return;
    }

    char ligne[200];
    int id;
    char nom[40];
    float prix;
    int supprime = 0;

    while (fgets(ligne, 200, f)) {
        sscanf(ligne, "%d|%[^|]|%f", &id, nom, &prix);

        if (id == idRecherche) {
            supprime = 1;
            continue; // NE PAS écrire cette ligne → suppression physique
        }

        fprintf(ft, "%d|%s|%.2f\n", id, nom, prix);
    }

    fclose(f);
    fclose(ft);

    remove(FICHIER_TYPE);
    rename(FICHIER_TEMP, FICHIER_TYPE);

    if (supprime)
        printf(">> Suppression effectuée.\n");
    else
        printf("ID introuvable.\n");
}

// ---------------------------------------------------------
//                       MENU PRINCIPAL
// ---------------------------------------------------------
int main() {
    int choix;

    do {
        printf("\n===== MENU TYPE EMPLACEMENT =====\n");
        printf("1. Ajouter un type\n");
        printf("2. Lister les types\n");
        printf("3. Rechercher un type par ID\n");
        printf("4. Modifier un type\n");
        printf("5. Supprimer un type\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterType(); break;
            case 2: listerTypes(); break;
            case 3: chercherType(); break;
            case 4: modifierType(); break;
            case 5: supprimerType(); break;
        }
    } while (choix != 0);

    return 0;
}
