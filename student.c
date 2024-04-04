#include "student.h"
#include "emprunt.h"
#include "books.h" // Assurez-vous d'inclure le fichier d'en-tête books.h
#include <stdio.h>
#include <string.h>

// Fonction pour créer un nouvel étudiant
struct Student createStudent(char name[], int number, char email[], int codep) {
    struct Student new_student;
    strcpy(new_student.name, name);
    new_student.number = number;
    strcpy(new_student.email, email);
    new_student.codep = codep;
    return new_student;
}

// Fonction pour sauvegarder les étudiants dans un fichier
void saveStudentsToFile(struct Student* students, int numStudents) {
    FILE* file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarde des étudiants.\n");
        return;
    }
    for (int i = 0; i < numStudents; ++i) {
        fprintf(file, "%s,%d,%s,%d\n", students[i].name, students[i].number, students[i].email, students[i].codep);
    }
    fclose(file);
}

// Fonction pour charger les étudiants à partir d'un fichier
void loadStudentsFromFile(struct Student* students, int* numStudents) {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Fichier d'étudiants introuvable. Créez-le en ajoutant des étudiants.\n");
        return;
    }
    *numStudents = 0;
    while (fscanf(file, "%[^,],%d,%[^,],%d\n", students[*numStudents].name, &students[*numStudents].number, students[*numStudents].email, &students[*numStudents].codep) == 4) {
        (*numStudents)++;
    }
    fclose(file);
}

// Fonction pour afficher la liste des étudiants avec indication du livre emprunté
void displayStudentList(struct Student* students, int numStudents, struct Emprunt* emprunts, int numEmprunts, struct Book* library, int numBooks) {
    printf("Liste des étudiants :\n");
    for (int i = 0; i < numStudents; ++i) {
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        printf("| Nom : %s,   | Numéro : %d,    | Email : %s,     |  Code permanant : %d\n", students[i].name, students[i].number, students[i].email, students[i].codep);
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        int emprunt_found = 0;
        for (int j = 0; j < numEmprunts; ++j) {
            if (emprunts[j].student_number == students[i].number) {
                emprunt_found = 1;
                // Recherche du livre emprunté
                for (int k = 0; k < numBooks; ++k) {
                    if (library[k].code == emprunts[j].book_code) {
                        printf("|  - Livre emprunté : %s  |\n", library[k].name);
                        printf("|--------------------------------------------------------------------------------------------------------------------------|");

                        break;
                    }
                }
            }
        }
        if (!emprunt_found) {
            printf("  - Aucun livre emprunté\n");
        }
    }
}

// Fonction pour modifier les informations d'un étudiant
void editStudent(struct Student* students, int numStudents, int number, char name[], char email[], int codep) {
    for (int i = 0; i < numStudents; ++i) {
        if (students[i].number == number) {
            strcpy(students[i].name, name);
            strcpy(students[i].email, email);
            students[i].codep = codep;
            saveStudentsToFile(students, numStudents); // Sauvegarder les modifications dans le fichier
            return;
        }
    }
    printf("Étudiant non trouvé avec le numéro %d\n", number);
}

    // Fonction pour supprimer un eleve
void deleteStudent(struct Student* students, int codep, int* numStudents) {
    int i;
    for (i = 0; i < *numStudents; ++i) {
        if (students[i].codep == codep) {
            // Supprimer l'etudiant en décalant les éléments suivants
            for (int j = i; j < *numStudents - 1; ++j) {
                students[j] = students[j + 1];
            }
            (*numStudents)--;
            break;
        }
    }
}
