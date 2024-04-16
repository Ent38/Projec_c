#include <stdio.h>
#include <stdlib.h>
#include "emprunt.h"

void displayEmpruntMenu() {
    printf("\nMenu Emprunt :\n");
    printf("1. Créer un emprunt\n");
    printf("2. Modifier un emprunt\n");
    printf("3. Supprimer un emprunt\n");
    printf("4. Afficher la liste des emprunts\n");
    printf("5. Rechercher un emprunt par le code du livre\n");
    printf("0. Revenir au menu principal\n");
}

void empruntMenu(struct Emprunt *emprunts, int *numEmprunts, struct Student *students, int numStudents, struct Book *library, int numBooks) {
    int choice;
    do {
        displayEmpruntMenu();
        printf("Choisissez une option : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                // Créer un emprunt
                int student_number, book_code;
                printf("Entrez le numéro de l'étudiant : ");
                scanf("%d", &student_number);
                printf("Entrez le code du livre : ");
                scanf("%d", &book_code);

                // Créer l'emprunt avec les dates
                createEmprunt(emprunts, student_number, book_code, numEmprunts);
                printf("Emprunt créé avec succès.\n");
                break;
            }
            case 2: {
                // Modifier un emprunt
                int book_code;
                printf("Entrez le code du livre de l'emprunt à modifier : ");
                scanf("%d", &book_code);
                for (int i = 0; i < *numEmprunts; i++) {
                    if (emprunts[i].book_code == book_code) {
                        printf("Entrez la nouvelle date d'emprunt (JJ/MM/AAAA) : ");
                        scanf("%s", emprunts[i].emprunt_date_str);

                        printf("Entrez la nouvelle date de retour (JJ/MM/AAAA) : ");
                        scanf("%s",  emprunts[i].return_date_str);

                        printf("Emprunt modifié avec succès.\n");
                        break;
                    }
                }
                break;
            }
            case 3: {
                // Supprimer un emprunt
                int book_code;
                printf("Entrez le code du livre à rendre : ");
                scanf("%d", &book_code);
                deleteEmprunt(emprunts, book_code, numEmprunts);
                printf("Emprunt supprimé avec succès.\n");
                break;
            }
            case 4: {
                // Afficher la liste des emprunts
                displayEmprunts(emprunts, *numEmprunts, students, numStudents, library, numBooks);
                break;
            }  
            case 5: {
                // Rechercher un emprunt par le code du livre
                int book_code, found = 0;
                printf("Entrez le code du livre : ");
                scanf("%d", &book_code);
                for (int i = 0; i < *numEmprunts; ++i) {
                    if (emprunts[i].book_code == book_code) {
                        printf("Emprunt trouvé : \n");
                        printf("Nom de l'étudiant : %s   | Nom du livre : %s  | Date d'emprunt : %s  | Date de retour : %s  | \n", students[emprunts[i-1].student_number].name, library[emprunts[i-1].book_code].name, emprunts[i].emprunt_date_str, emprunts[i].return_date_str);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Emprunt non trouvé.\n");
                }

                break;
            }
            case 0:
                // Revenir au menu principal
                break;
            default:
                printf("Choix invalide. Veuillez choisir une option valide.\n");
        }
    } while (choice != 0);
}
