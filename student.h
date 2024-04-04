#ifndef STUDENTS_H
#define STUDENTS_H

#include "emprunt.h"

struct Book;

struct Emprunt;

// Structure pour représenter un étudiant
struct Student {
    char name[50];
    int number;
    char email[50];
    int codep;
};

struct Student createStudent(char name[], int number, char email[], int codep);
void displayStudentList(struct Student* students, int numStudents, struct Emprunt* emprunts, int numEmprunts, struct Book* library, int numBooks);
void saveStudentsToFile(struct Student* students, int numStudents);
void loadStudentsFromFile(struct Student* students, int* numStudents);
void editStudent(struct Student* students, int numStudents, int number, char name[], char email[], int codep);
void deleteStudent(struct Student* students, int codep, int* numStudents);

#endif // STUDENTS_H
