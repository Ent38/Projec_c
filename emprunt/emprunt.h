#ifndef EMPRUNT_H
#define EMPRUNT_H
#include <time.h>
#define MAX_EMPRUNTS 100 // Définir le nombre maximal d'emprunts
#include "../student/student.h"
#include "../books/books.h"

// Structure pour représenter un emprunt

struct Emprunt {
    int student_number;
    int book_code;
    char return_date_str[50]; 
    char emprunt_date_str[50]; 
};

struct Student;
struct Book;

void createEmprunt(struct Emprunt* emprunts, int student_number, int book_code, int* numEmprunts);
void deleteEmprunt(struct Emprunt* emprunts, int book_code, int* numEmprunts);
void updateEmprunt(struct Emprunt* emprunts, int book_code, int new_student_number, int* numEmprunts);
void displayEmprunts(struct Emprunt* emprunts, int numEmprunts, struct Student* students, int numStudents, struct Book* library, int numBooks);
void saveEmpruntsToFile(struct Emprunt* emprunts, int* numEmprunts);
struct Emprunt *searchEmpruntByBookCode(struct Emprunt emprunts[], int numEmprunts, int book_code);
void loadEmpruntsFromFile(struct Emprunt* emprunts, int* numEmprunts);

#endif // EMPRUNT_H
 