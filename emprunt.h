#ifndef EMPRUNT_H
#define EMPRUNT_H

#include "student.h"
#include "books.h"

// Structure pour représenter un emprunt
struct Emprunt {
    int student_number;
    int book_code;
};
struct Student;
struct Book;

void createEmprunt(struct Emprunt* emprunts, int student_number, int book_code, int* numEmprunts);
void deleteEmprunt(struct Emprunt* emprunts, int book_code, int* numEmprunts);
void updateEmprunt(struct Emprunt* emprunts, int book_code, int new_student_number, int* numEmprunts);
void displayEmprunts(struct Emprunt* emprunts, int numEmprunts, struct Student* students, int numStudents, struct Book* library, int numBooks);
void saveEmpruntsToFile(struct Emprunt* emprunts, int* numEmprunts);
void loadEmpruntsFromFile(struct Emprunt* emprunts, int* numEmprunts);

#endif // EMPRUNT_H
