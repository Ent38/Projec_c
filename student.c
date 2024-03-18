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

// Fonction pour afficher la liste des étudiants avec indication du livre emprunté
void displayStudentList(struct Student* students, int numStudents, struct Emprunt* emprunts, int numEmprunts, struct Book* library, int numBooks) {
    printf("Liste des étudiants :\n");
    for (int i = 0; i < numStudents; ++i) {
        printf("Nom : %s, Numéro : %d, Email : %s, Code postal : %d\n", students[i].name, students[i].number, students[i].email, students[i].codep);
        int emprunt_found = 0;
        for (int j = 0; j < numEmprunts; ++j) {
            if (emprunts[j].student_number == students[i].number) {
                emprunt_found = 1;
                // Recherche du livre emprunté
                for (int k = 0; k < numBooks; ++k) {
                    if (library[k].code == emprunts[j].book_code) {
                        printf("  - Livre emprunté : %s\n", library[k].name);
                        break;
                    }
                }
            }
        }
        if (!emprunt_found) {
            printf("  - Aucun livre emprunté\n");
        }
        else{
            printf("ici il faut le mon du livre");
        }
    }
}

