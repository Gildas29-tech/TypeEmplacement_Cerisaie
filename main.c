#include <stdio.h>
#include "TypeEmplacement.h"

int main() {
    int choix;

    do {
        printf("\n===== MENU TYPE EMPLACEMENT =====\n");
        printf("1. Ajouter un type\n");
        printf("2. Lister les types\n");
        printf("3. Rechercher un type\n");
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

