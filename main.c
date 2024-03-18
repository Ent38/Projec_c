#include <stdio.h>
#include "student.h"
#include "books.h"
#include "emprunt.h"

// Fonction pour afficher le menu
void displayMenu() {
    printf("\nMenu :\n");
    printf("1. Créer un étudiant\n");
    printf("2. Modifier un étudiant\n");
    printf("3. Supprimer un étudiant\n");
    printf("4. Créer un livre\n");
    printf("5. Modifier un livre\n");
    printf("6. Supprimer un livre\n");
    printf("7. Créer un emprunt\n");
    printf("8. Supprimer un emprunt\n");
    printf("9. Afficher la liste des étudiants et des emprunts\n");
    printf("10. Afficher la liste des livres\n");
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

    int choice;
    do {
        // Afficher le menu
        displayMenu();
        
        // Demander à l'utilisateur de choisir une option
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Créer un étudiant
                char name[50], email[50];
                int number, codep;
                printf("Entrez le nom de l'étudiant : ");
                scanf(" %[^\n]", name);
                printf("Entrez le numéro de l'étudiant : ");
                scanf("%d", &number);
                printf("Entrez l'email de l'étudiant : ");
                scanf(" %[^\n]", email);
                printf("Entrez le code postal de l'étudiant : ");
                scanf("%d", &codep);
                students[numStudents++] = createStudent(name, number, email, codep);
                printf("Étudiant créé avec succès.\n");
                break;
            }
            case 2: {
                // Modifier un étudiant
                int number;
                printf("Entrez le numéro de l'étudiant à modifier : ");
                scanf("%d", &number);
                // Code pour modifier l'étudiant
                break;
            }
            case 3: {
                // Supprimer un étudiant
                int number;
                printf("Entrez le numéro de l'étudiant à supprimer : ");
                scanf("%d", &number);
                // Code pour supprimer l'étudiant
                break;
            }
            case 4: {
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
                library[numBooks++] = createBook(name, category, code, author);
                printf("Livre créé avec succès.\n");
                break;
            }
            case 5: {
                // Modifier un livre
                int code;
                printf("Entrez le code du livre à modifier : ");
                scanf("%d", &code);
                // Code pour modifier le livre
                break;
            }
            case 6: {
                // Supprimer un livre
                int code;
                printf("Entrez le code du livre à supprimer : ");
                scanf("%d", &code);
                // Code pour supprimer le livre
                break;
            }
            case 7: {
                // Créer un emprunt
                int student_number, book_code;
                printf("Entrez le numéro de l'étudiant : ");
                scanf("%d", &student_number);
                printf("Entrez le code du livre : ");
                scanf("%d", &book_code);
                createEmprunt(emprunts, student_number, book_code, &numEmprunts);
                printf("Emprunt créé avec succès.\n");
                break;
            }
            case 8: {
                // Supprimer un emprunt
                int book_code;
                printf("Entrez le code du livre à rendre : ");
                scanf("%d", &book_code);
                deleteEmprunt(emprunts, book_code, &numEmprunts);
                printf("Emprunt supprimé avec succès.\n");
                break;
            }
            case 9:
                // Afficher la liste des étudiants et des emprunts
                displayStudentList(students, numStudents, emprunts, numEmprunts);
                break;
            case 10:
                // Afficher la liste des livres
                displayBookList(library, numBooks, emprunts, numEmprunts);
                break;
            case 0:
                // Quitter le programme
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez choisir une option valide.\n");
        }
    } while (choice != 0);

    return 0;
}
