#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../student/student.h"
#include "books.h"
#include "../emprunt/emprunt.h"

void displayBooksMenu() {
    printf("\nMenu Livres :\n");
    printf("1. Créer un livre\n");
    printf("2. Modifier un livre\n");
    printf("3. Supprimer un livre\n");
    printf("4. Afficher la liste des livres\n");
    printf("5. Rechercher un livre par son code\n");
    printf("0. Revenir au menu principal\n");
}

void booksMenu(struct Book *library, int *numBooks,struct Student *students, int numStudents,struct Emprunt *emprunts, int numEmprunts) {
    int choice;
    do {
        displayBooksMenu();
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Créer un livre
                char name[50], category[50], author[50];
                int code;
                printf("Entrez le nom du livre : ");
                scanf(" %[^\n]", name);
                printf("Entrez la catégorie du livre : ");
                scanf(" %[^\n]", category);
                printf("Entrez le code du livre : ");
                scanf("%d", &code);
                printf("Entrez l'auteur du livre : ");
                scanf(" %[^\n]", author);
                library[*numBooks] = *createBook(&library,numBooks,name,category,code,author);
                (*numBooks)++;
                printf("Livre créé avec succès.\n");
                break;
            }
            case 2: {
                // Modifier un livre
                int code;
                printf("Entrez le code du livre à modifier : ");
                scanf("%d", &code);
                for (int i = 0; i < *numBooks; i++) {
                    if (library[i].code == code) {
                        char name[50], category[50], author[50];
                        printf("Entrez le nouveau nom du livre : ");
                        scanf(" %[^\n]", name);
                        printf("Entrez la nouvelle catégorie du livre : ");
                        scanf(" %[^\n]", category);
                        printf("Entrez le nouvel auteur du livre : ");
                        scanf(" %[^\n]", author);
                        editBook(library, code, name, category, author, *numBooks);
                        printf("Livre modifié avec succès.\n");
                        break;
                    }
                }
                break;
            }
            case 3: {
                // Supprimer un livre
                int code;
                printf("Entrez le code du livre à supprimer : ");
                scanf("%d", &code);
                deleteBook(&library, code, numBooks);
                printf("Livre supprimé avec succès.\n");
                break;
            }
            case 4: {
                // Afficher la liste des livres
                displayBookList(library, *numBooks, emprunts, numEmprunts,students, numStudents );
                break;
            }
            case 5: {
                // Rechercher un livre par son code
                int code, found = 0;
                printf("Entrez le code du livre : ");
                scanf("%d", &code);
                for (int i = 0; i < *numBooks; i++) {
                    if (library[i].code == code) {
                    printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
                        printf("Livre trouvé :\n");
                        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
                        printf("| Nom : %s   |  Catégorie : %s    |    Code : %d   |     Auteur : %s    |   \n", library[i].name, library[i].category, library[i].code, library[i].author);
                        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");

                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Livre non trouvé.\n");
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
