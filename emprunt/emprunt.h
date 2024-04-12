#ifndef EMPRUNT_H
#define EMPRUNT_H
#include <time.h>
#include "../student/student.h"
#include "../books/books.h"

// Structure pour représenter un emprunt

struct Emprunt {
    int student_number;
    int book_code;
    time_t emprunt_date; 
    time_t return_date; 
    char emprunt_date_str[50]; 
    char return_date_str[50];
};

struct Student;
struct Book;

void createEmprunt(struct Emprunt* emprunts, int student_number, int book_code, int* numEmprunts);
void deleteEmprunt(struct Emprunt* emprunts, int book_code, int* numEmprunts);
void updateEmprunt(struct Emprunt* emprunts, int book_code, int new_student_number, time_t new_emprunt_date, time_t new_return_date, int* numEmprunts);
void displayEmprunts(struct Emprunt* emprunts, int numEmprunts, struct Student* students, int numStudents, struct Book* library, int numBooks);
void saveEmpruntsToFile(struct Emprunt* emprunts, int* numEmprunts);
struct Emprunt *searchEmpruntByBookCode(struct Emprunt emprunts[], int numEmprunts, int book_code);
void loadEmpruntsFromFile(struct Emprunt* emprunts, int* numEmprunts);

#endif // EMPRUNT_H
