#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "../books/books.h"
#include "../emprunt/emprunt.h"

void displayStudentMenu() {
    printf("\nMenu Etudiant :\n");
    printf("1. Créer un étudiant\n");
    printf("2. Modifier un étudiant\n");
    printf("3. Supprimer un étudiant\n");
    printf("4. Afficher la liste des étudiants\n");
    printf("5. Rechercher un étudiant par son numéro\n");
    printf("0. Revenir au menu principal\n");
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

void studentMenu(struct Student*students, int *numStudents ,struct Book * library, int numBooks,struct Emprunt *emprunts, int *numEmprunts ) {
    int choice;
    do {
        displayStudentMenu();
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Créer un étudiant
                char name[50], email[50];
                int codep,number;
                number = validateStudentNumber();
                validateName(name);
                validateEmail(email);
                printf("Entrez le code permanant de l'étudiant : ");
                scanf("%d", &codep);
                students[*numStudents] = *createStudent(&students,numStudents,name,number,email,codep);
                (*numStudents)++;
                printf("Étudiant créé avec succès.\n");
                break;
            }
            case 2: {
                // Modifier un étudiant
                int number;
                printf("Entrez le numéro de l'étudiant à modifier : ");
                scanf("%d", &number);
                for (int i = 0; i < *numStudents; i++) {
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
                        editStudent(students, *numStudents, number, name, email, codep);
                        printf("Étudiant modifié avec succès.\n");
                        }
                }
                break;
            }
            case 3: {
                // Supprimer un étudiant
                int number;
                printf("Entrez le numéro de l'étudiant à supprimer : ");
                scanf("%d", &number);
                deleteStudent(&students, number, numStudents);
                printf("Etudiant supprimé avec succès.\n");
                break;
            }
            case 4:
                // Afficher la liste des étudiants
                displayStudentList(students, *numStudents, emprunts, *numEmprunts ,library, numBooks);
                break;
            case 5: {
                // Rechercher un étudiant par son numéro
                // Rechercher un étudiant par son numéro
                int number;
                printf("Entrez le numéro de l'étudiant : ");
                scanf("%d", &number);
                struct Student *foundStudent = searchStudentByNumber(students, *numStudents, number);
                if (foundStudent != NULL) {
                    printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
                    printf("| Informations de l'étudiant :\n");
                    printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
                    printf("|  Nom : %s |  Numéro : %d   |  Email : %s   |   Code permanent : %d   |\n", foundStudent->name,foundStudent->number,foundStudent->email,foundStudent->codep);
                    printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
                } else {
                    printf("Aucun étudiant trouvé avec le numéro %d\n", number);
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