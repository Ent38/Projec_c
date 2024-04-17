#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student/student.h"
#include "books/books.h"
#include "emprunt/emprunt.h"
#include "student/student_menu.h"
#include "books/book_menu.h"
#include "emprunt/emprunt_menu.h"

// Fonction pour afficher le menu principal
void displayMainMenu() {
    printf("\nMenu Principal :\n");
    printf("1. Gérer les étudiants\n");
    printf("2. Gérer les livres\n");
    printf("3. Gérer les emprunts\n");
    printf("0. Quitter\n");
}

int main() {
    // Initialisation des données
    struct Student students[100];
    int numStudents = 0;

    struct Book library[100];
    int numBooks = 0;

    struct Emprunt emprunts[100];
    int numEmprunts = 0;

    // Charger les données depuis les fichiers
    loadStudentsFromFile(students, &numStudents);
    loadBooksFromFile(library, &numBooks);
    loadEmpruntsFromFile(emprunts, &numEmprunts);

    int choice;
    do {
        // Afficher le menu principal
        displayMainMenu();
        
        // Demander à l'utilisateur de choisir une option
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Accéder au menu pour gérer les étudiants
                studentMenu(students, &numStudents, library, numBooks, emprunts, &numEmprunts);
                break;
            case 2:
                // Accéder au menu pour gérer les livres
                booksMenu(library, &numBooks,students, numStudents,emprunts, numEmprunts);
                break;
            case 3:
                // Accéder au menu pour gérer les emprunts
                empruntMenu(emprunts, &numEmprunts,students, numStudents,library, numBooks);
                break;
            case 0:
                // Quitter le programme
                printf("Au revoir !\n");
                // Sauvegarder les données dans les fichiers
                saveStudentsToFile(students, numStudents);
                saveBooksToFile(library, numBooks);
                saveEmpruntsToFile(emprunts, &numEmprunts);
                break;
            default:
                printf("Choix invalide. Veuillez choisir une option valide.\n");
        }
    } while (choice != 0);

    return 0;
}
