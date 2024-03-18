// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include "emprunt.h"

// Structure pour représenter un étudiant
struct Student {
    char name[50];
    int number;
    char email[50];
    int codep;
};

// Fonction pour créer un nouvel étudiant
struct Student createStudent(char name[], int number, char email[], int codep);

// Fonction pour afficher la liste des étudiants avec indication de l'emprunt ou non d'un livre
void displayStudentList(struct Student* students, int numStudents, struct Emprunt* emprunts, int numEmprunts);

#endif // STUDENT_H
