#include <stdio.h>
#include <string.h>
#include "emprunt.h"
#include "student.h"
#include "books.h"

// Fonction pour afficher tous les emprunts
void displayEmprunts(struct Emprunt* emprunts, int numEmprunts, struct Student* students, int numStudents, struct Book* library, int numBooks) {
    printf("Liste des emprunts :\n");
    for (int i = 0; i < numEmprunts; ++i) {
        int student_number = emprunts[i].student_number;
        int book_code = emprunts[i].book_code;
        // Recherche de l'étudiant correspondant
        char student_name[50];
        int student_found = 0;
        for (int j = 0; j < numStudents; ++j) {
            if (students[j].number == student_number) {
                strcpy(student_name, students[j].name);
                student_found = 1;
                break;
            }
        }
        // Recherche du livre correspondant
        char book_name[50];
        char book_author[50];
        int book_found = 0;
        for (int k = 0; k < numBooks; ++k) {
            if (library[k].code == book_code) {
                strcpy(book_name, library[k].name);
                strcpy(book_author, library[k].author);
                book_found = 1;
                break;
            }
        }
        // Affichage de l'emprunt
        if (student_found && book_found) {
            printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
            printf("|   Étudiant : %s,   | Livre : %s      | (Auteur : %s)\n", student_name, book_name, book_author);
            printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        }
    }
}

void saveEmpruntsToFile(struct Emprunt *emprunts, int *numEmprunts)
{
    FILE *file = fopen("emprunts.txt", "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier emprunts.txt");
        return;
    }

    for (int i = 0; i < *numEmprunts; ++i) { // Notez l'utilisation de *numEmprunts
        fprintf(file, "%d %d\n", emprunts[i].student_number, emprunts[i].book_code);
    }

    fclose(file);
}



// Fonction pour créer un nouvel emprunt
void createEmprunt(struct Emprunt* emprunts, int student_number, int book_code, int* numEmprunts) {
    emprunts[*numEmprunts].student_number = student_number;
    emprunts[*numEmprunts].book_code = book_code;
    (*numEmprunts)++;
}

// Fonction pour supprimer un emprunt
void deleteEmprunt(struct Emprunt* emprunts, int book_code, int* numEmprunts) {
    int i;
    for (i = 0; i < *numEmprunts; ++i) {
        if (emprunts[i].book_code == book_code) {
            // Supprimer l'emprunt en décalant les éléments suivants
            for (int j = i; j < *numEmprunts - 1; ++j) {
                emprunts[j] = emprunts[j + 1];
            }
            (*numEmprunts)--;
            break;
        }
    }
}

// Fonction pour mettre à jour un emprunt
void updateEmprunt(struct Emprunt* emprunts, int book_code, int new_student_number, int* numEmprunts) {
    int i;
    for (i = 0; i < *numEmprunts; ++i) {
        if (emprunts[i].book_code == book_code) {
            // Mettre à jour le numéro de l'étudiant associé à l'emprunt
            emprunts[i].student_number = new_student_number;
            break;
        }
    }
}

// Fonction pour charger les emprunts à partir d'un fichier
void loadEmpruntsFromFile(struct Emprunt* emprunts, int* numEmprunts) {
    FILE *file = fopen("emprunts.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier emprunts.txt");
        return;
    }

    *numEmprunts = 0;
    while (fscanf(file, "%d %d", &emprunts[*numEmprunts].student_number, &emprunts[*numEmprunts].book_code) == 2) {
        (*numEmprunts)++;
    }

    fclose(file);
}



