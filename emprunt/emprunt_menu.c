#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emprunt.h" // Inclure le fichier d'en-tête pour accéder aux fonctions de gestion des emprunts

void displayEmpruntMenu() {
    printf("\nMenu Emprunt :\n");
    printf("1. Créer un emprunt\n");
    printf("2. Modifier un emprunt\n");
    printf("3. Supprimer un emprunt\n");
    printf("4. Afficher la liste des emprunts\n");
    printf("5. Rechercher un emprunt par le nom du livre\n");
    printf("0. Revenir au menu principal\n"); 
}

void empruntMenu(struct Emprunt *emprunts, int *numEmprunts) {

    int choice;
    do {
        displayEmpruntMenu();
        printf("Choisissez une option : ");
        scanf("%d", &choice); 
        switch (choice) {
            case 1: {
                // Créer un emprunt
                char student_name[50], book_name[50];
                printf("Entrez le nom de l'étudiant : ");
                scanf("%s", student_name);
                printf("Entrez le nom du livre : ");
                scanf("%s", book_name);
                // Demander la date d'emprunt à l'utilisateur
                printf("Entrez la date d'emprunt (JJ/MM/AAAA) : ");
                char emprunt_date_str[20];
                scanf("%s", emprunt_date_str);

                // Demander la date de retour à l'utilisateur
                printf("Entrez la date de retour (JJ/MM/AAAA) : ");
                char return_date_str[20];
                scanf("%s", return_date_str);

                // Créer l'emprunt avec les dates
                createEmprunt(&emprunts, numEmprunts, student_name, book_name, return_date_str, emprunt_date_str);
                printf("Emprunt créé avec succès.\n");
                break;
            }
            case 2: { 
                // Modifier un emprunt
                char book_name[50];
                printf("Entrez le nom du livre de l'emprunt à modifier : ");
                scanf("%s", book_name);
                for (int i = 0; i < *numEmprunts; i++) {
                    if (strcmp(emprunts[i].book_name, book_name) == 0) {
                        printf("Entrez la nouvelle date d'emprunt (JJ/MM/AAAA) : ");
                        scanf("%s", emprunts[i].emprunt_date_str);

                        printf("Entrez la nouvelle date de retour (JJ/MM/AAAA) : ");
                        scanf("%s", emprunts[i].return_date_str);

                        printf("Emprunt modifié avec succès.\n");
                        break;
                    }
                }
                break;
            }
            case 3: {
                // Supprimer un emprunt
                char book_name[50];
                printf("Entrez le nom du livre à rendre : ");
                scanf("%s", book_name);
                deleteEmprunt(&emprunts, book_name, numEmprunts);
                printf("Emprunt supprimé avec succès.\n");
                break;
            }
            case 4: {
                // Afficher la liste des emprunts
                displayEmprunts(emprunts, *numEmprunts);
                break;
            }  
           case 5: {
                // Rechercher un emprunt par le nom du livre
                char book_name[50];
                printf("Entrez le nom du livre : ");
                scanf("%s", book_name);
                struct Emprunt** found_emprunts = searchEmpruntsByBookName(emprunts, *numEmprunts, book_name);
                if (found_emprunts != NULL) {
                    printf("Emprunts trouvés pour le livre '%s':\n", book_name);
                    int count = countEmpruntsByBookName(emprunts, *numEmprunts, book_name);
                    for (int i = 0; i < count; ++i) {
                        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
                        printf("| Nom de l'étudiant : %s   | Nom du livre : %s  | Date d'emprunt : %s  | Date de retour : %s  |\n", found_emprunts[i]->student_name, found_emprunts[i]->book_name, found_emprunts[i]->emprunt_date_str, found_emprunts[i]->return_date_str);
                        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
                    }
                    // N'oubliez pas de libérer la mémoire allouée pour le tableau de pointeurs
                    free(found_emprunts);
                } else {
                    printf("Aucun emprunt trouvé pour le livre '%s'.\n", book_name);
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
