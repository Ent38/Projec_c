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
                        int new_student_number;
                        printf("Entrez le nouveau numéro de l'étudiant pour cet emprunt : ");
                        scanf("%d", &new_student_number);

                        // Obtenir la date et l'heure actuelles pour la mise à jour de l'emprunt
                        time_t current_time;
                        time(&current_time);

                        // Mettre à jour l'emprunt avec les nouvelles informations et la date actuelle
                        updateEmprunt(emprunts, book_code, new_student_number, current_time, emprunts[i].return_date, numEmprunts);
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
                for (int i = 0; i < *numEmprunts; i++) {
                    if (emprunts[i].book_code == book_code) {
                        printf("Emprunt trouvé :\n");
                        printf("Nom de l'étudiant : %s\n", students[emprunts[i].student_number].name);
                        printf("Nom du livre : %s\n", library[emprunts[i].book_code].name);
                        printf("Date d'emprunt : %s", ctime(&emprunts[i].emprunt_date));
                        printf("Date de retour : %s", ctime(&emprunts[i].return_date));
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
