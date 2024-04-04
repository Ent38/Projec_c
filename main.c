#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("8. Modifier un emprunt\n");
    printf("9. Supprimer un emprunt\n");
    printf("10. Afficher la liste des étudiants \n");
    printf("11. Afficher la liste des livres\n");
    printf("12. Afficher la liste des emprunts\n");
    printf("0. Quitter\n");
}

// Fonction pour valider un numéro d'étudiant
int validateStudentNumber() {
    int number;
    char input[50];
    char *endptr;
    do {
        printf("Entrez le numéro de l'étudiant : ");
        scanf(" %[^\n]", input);
        number = strtol(input, &endptr, 10); // Convertir la chaîne en nombre
        if (*endptr != '\0' || number <= 0) { // Vérifier si la conversion a réussi et si le nombre est positif
            printf("Numéro invalide. Veuillez entrer un nombre positif.\n");
        }
    } while (*endptr != '\0' || number <= 0);
    return number;
}

// Fonction pour valider un nom ou un titre
void validateName(char *name) {
    do {
        printf("Entrez le nom : ");
        scanf(" %[^\n]", name);
        if (strspn(name, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != strlen(name)) {
            printf("Nom invalide. Veuillez entrer uniquement des lettres alphabétiques.\n");
        }
    } while (strspn(name, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != strlen(name));
}

// Fonction pour valider un email
void validateEmail(char *email) {
    do {
        printf("Entrez l'email : ");
        scanf(" %[^\n]", email);
        char *atSign = strchr(email, '@');
        char *dot = strchr(email, '.');
        if (atSign == NULL || dot == NULL || atSign >= dot) {
            printf("Email invalide. Veuillez entrer un email valide.\n");
        }
    } while (strchr(email, '@') == NULL || strchr(email, '.') == NULL || strchr(email, '@') >= strchr(email, '.'));
}

// Fonction pour valider un code de livre
int validateBookCode() {
    int code;
    char input[50];
    char *endptr;
    do {
        printf("Entrez le code du livre : ");
        scanf(" %[^\n]", input);
        
        code = strtol(input, &endptr, 10); // Convertir la chaîne en nombre
        if (*endptr != '\0' || code <= 0) { // Vérifier si la conversion a réussi et si le nombre est positif
            printf("Code invalide. Veuillez entrer un nombre positif.\n");
        }
    } while (*endptr != '\0' || code <= 0);
    return code;
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
                number = validateStudentNumber();
                validateName(name);
                validateEmail(email);
                printf("Entrez le code permanant de l'étudiant : ");
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
                for (int i = 0; i < numStudents; i++) {
                    if (students[i].number == number) {
                        // Demander les nouvelles informations
                        char name[50], email[50];
                        int codep;
                        printf("Entrez le nouveau nom de l'étudiant : ");
                        scanf(" %[^\n]", name);
                        printf("Entrez le nouvel email de l'étudiant : ");
                        scanf(" %[^\n]", email);
                        printf("Entrez le nouveau code permanant de l'étudiant : ");
                        scanf("%d", &codep);
                        // Mettre à jour les informations de l'étudiant
                        editStudent(students, numStudents, number, name, email, codep);
                        printf("Étudiant modifié avec succès.\n");
                        break;
                    }
                }
                break;
            }

            case 3: {
                // Supprimer un étudiant
                int number;
                printf("Entrez le numéro de l'étudiant à supprimer : ");
                scanf("%d", &number);
                // Code pour supprimer l'étudiant
                deleteStudent(students, number, &numStudents);
                printf("Etudiant supprimé avec succès.\n");
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
                for (int i = 0; i < numBooks; i++) {
                    if (library[i].code == code) {
                        // Demander les nouvelles informations
                        char name[50], category[50], author[50];
                        printf("Entrez le nouveau nom du livre : ");
                        scanf(" %[^\n]", name);
                        printf("Entrez la nouvelle catégorie du livre : ");
                        scanf(" %[^\n]", category);
                        printf("Entrez le nouvel auteur du livre : ");
                        scanf(" %[^\n]", author);
                        // Mettre à jour les informations du livre
                        editBook(library, code, name, category, author, &numBooks);
                        printf("Livre modifié avec succès.\n");
                        break;
                    }
                }
                break;
            }

            case 6: {
                // Supprimer un livre
                int code;
                printf("Entrez le code du livre à supprimer : ");
                scanf("%d", &code);
                deleteBook(library, code, &numBooks);
                printf("Livre supprimé avec succès.\n");
                break;
            }
            case 7: {
                // Créer un emprunt
                int student_number, book_code;
                printf("Entrez le numéro de l'étudiant : ");
                scanf("%d", &student_number);
                printf("Entrez le code du livre : ");
                scanf("%d", &book_code);
                
                // Vérifier si le livre est déjà emprunté
                int isBookRented = 0;
                for (int i = 0; i < numEmprunts; i++) {
                    if (emprunts[i].book_code == book_code) {
                        isBookRented = 1;
                        break;
                    }
                }
                
                if (isBookRented) {
                    printf("Ce livre est déjà emprunté et ne peut pas être emprunté de nouveau.\n");
                } else {
                    createEmprunt(emprunts, student_number, book_code, &numEmprunts);
                    printf("Emprunt créé avec succès.\n");
                }
                break;
            }

            case 8: {
                // Modifier un emprunt
                int book_code;
                printf("Entrez le code du livre de l'emprunt à modifier : ");
                scanf("%d", &book_code);
                for (int i = 0; i < numEmprunts; i++) {
                    if (emprunts[i].book_code == book_code) {
                        // Demander les nouvelles informations
                        int new_student_number;
                        printf("Entrez le nouveau numéro de l'étudiant pour cet emprunt : ");
                        scanf("%d", &new_student_number);
                        // Mettre à jour les informations de l'emprunt
                        updateEmprunt(emprunts, book_code, new_student_number, &numEmprunts);
                        printf("Emprunt modifié avec succès.\n");
                        break;
                    }
                }
                break;
            }

            case 9: {
                // Supprimer un emprunt
                int book_code;
                printf("Entrez le code du livre à rendre : ");
                scanf("%d", &book_code);
                deleteEmprunt(emprunts, book_code, &numEmprunts);
                printf("Emprunt supprimé avec succès.\n");
                break;
            }
            case 10:
                // Afficher la liste des étudiants 
                displayStudentList(students, numStudents, emprunts, numEmprunts, library, numBooks );
                break;
            case 11:
                // Afficher la liste des livres
                displayBookList(library, numBooks, emprunts, numEmprunts,students, numStudents );
                break;
            // Afficher la liste des emprunts
            case 12:
                displayEmprunts(emprunts, numEmprunts, students, numStudents, library, numBooks);
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
