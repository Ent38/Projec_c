#include "student.h"
#include "../emprunt/emprunt.h"
#include "../books/books.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100
#define STUDENTS_FILE "student/students.txt"

struct Student* createStudent(struct Student** students, int* numStudents ,char name[], int number, char email[], int codep) {
    // Allouer de la mémoire pour le nouveau étudiant
    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
    if (new_student == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire pour le nouvel étudiant.\n");
        return NULL;
    }

    // Copier les informations de l'étudiant
    strcpy(new_student->name, name);
    new_student->number = number;
    strcpy(new_student->email, email);
    new_student->codep = codep;

    (*numStudents) += 1; 
    *students = realloc(*students, (*numStudents) * sizeof(struct Student)); 
    if (*students == NULL) {
        printf("Erreur: Impossible de réallouer de la mémoire pour la liste d'étudiants.\n");
        free(new_student); // Libérer la mémoire allouée pour le nouvel étudiant
        return NULL;
    }
    (*students)[(*numStudents) - 1] = *new_student; 

    saveStudentsToFile(*students, *numStudents);
    loadStudentsFromFile(students, numStudents);

    return new_student;
}


void saveStudentsToFile(struct Student* students, int numStudents) {
    FILE* file = fopen(STUDENTS_FILE, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s pour sauvegarde des étudiants.\n", STUDENTS_FILE);
        return;
    }
    for (int i = 0; i < numStudents; ++i) {
        fprintf(file, "%s,%d,%s,%d\n", students[i].name, students[i].number, students[i].email, students[i].codep);
    }
    fclose(file);
}

void loadStudentsFromFile(struct Student** students, int* numStudents) {
    FILE* file = fopen(STUDENTS_FILE, "r");
    if (file == NULL) {
        printf("Fichier d'étudiants introuvable. Créez-le en ajoutant des étudiants.\n");
        return;
    }
    *numStudents = 0;
    *students = NULL;
    while (1) {
        *students = realloc(*students, (*numStudents + 1) * sizeof(struct Student));
        if (*students == NULL) {
            printf("Erreur lors de la réallocation de mémoire.\n");
            fclose(file);
            return;
        }
        if (fscanf(file, " %[^,],%d, %[^,],%d", (*students)[*numStudents].name, &(*students)[*numStudents].number, (*students)[*numStudents].email, &(*students)[*numStudents].codep) == 4) {
            (*numStudents)++;
        } else {
            break;
        }
    }
    fclose(file);
}

void deleteStudent(struct Student** students, int number, int* numStudents) {
    // Recherche de l'étudiant par son numéro
    struct Student* studentToDelete = searchStudentByNumber(*students, *numStudents, number);
    if (studentToDelete == NULL) {
        printf("Étudiant non trouvé avec le numéro %d\n", number);
        return;
    }

    int indexToDelete = -1;
    for (int i = 0; i < *numStudents; ++i) {
        if ((*students)[i].number == number) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete != -1) {
        for (int i = indexToDelete; i < *numStudents - 1; ++i) {
            (*students)[i] = (*students)[i + 1];
        }
        (*numStudents)--;
    } else {
        printf("Erreur: Impossible de trouver l'étudiant avec le numéro %d\n", number);
        return;
    }

    // Réallocation de mémoire
    *students = realloc(*students, *numStudents * sizeof(struct Student));
    if (*students == NULL && *numStudents > 0) {
        printf("Erreur lors de la réallocation de mémoire.\n");
        return;
    }

    saveStudentsToFile(*students, *numStudents);
    loadStudentsFromFile(students, numStudents);
}

void editStudent(struct Student* students, int numStudents, int number, char name[], char email[], int codep) {
    struct Student* studentToEdit = searchStudentByNumber(students, numStudents, number);

    if (studentToEdit != NULL) {
        strcpy(studentToEdit->name, name);
        strcpy(studentToEdit->email, email);
        studentToEdit->codep = codep;

        saveStudentsToFile(students, numStudents);
        
        loadStudentsFromFile(&students, &numStudents);

        printf("Étudiant modifié avec succès.\n");
    } else {
        printf("Étudiant non trouvé avec le numéro %d\n", number);
    }
}

void displayStudentList(struct Student* students, int numStudents, struct Emprunt* emprunts, int numEmprunts, struct Book* library, int numBooks) {
    printf("Liste des étudiants :\n");
    for (int i = 0; i < numStudents; ++i) {
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        printf("| Nom : %s,   | Numéro : %d,    | Email : %s,     |  Code permanent : %d\n", students[i].name, students[i].number, students[i].email, students[i].codep);
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        int emprunt_found = 0;
        for (int j = 0; j < numEmprunts; j++) {
            if (emprunts[j].student_name == students[i].name) {
                emprunt_found = 1;
                int k = 0;
                while (k < numBooks) {
                    if (library[k].name == emprunts[j].book_name) {
                        printf("|  - Livre emprunté : %s\n", library[k].name);
                        break;
                    }
                    k++;
                }
            }
        }
        if (!emprunt_found) {
            printf("|  - Aucun livre emprunté\n");
        }
    }
}

struct Student *searchStudentByNumber(struct Student students[], int numStudents, int number) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].number == number) {
            return &students[i];
        }
    }
    return NULL;
}
