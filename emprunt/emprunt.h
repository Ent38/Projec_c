#ifndef EMPRUNT_H
#define EMPRUNT_H

#include "../student/student.h"
#include "../books/books.h"

struct Student;
struct Book;

struct Emprunt {
     char student_name[50]; 
    char book_name[50];
    char return_date_str[50]; 
    char emprunt_date_str[50]; 
};

struct Emprunt* createEmprunt(struct Emprunt** emprunts, int* numEmprunts, char student_name[], char book_name[], char return_date_str[], char emprunt_date_str[]);
void deleteEmprunt(struct Emprunt** emprunts, char book_name[], int* numEmprunts);
void editEmprunt(struct Emprunt* emprunts, int numEmprunts, char book_name[], char emprunt_date_str[], char return_date_str[]);
void displayEmprunts(struct Emprunt* emprunts, int numEmprunts) ;
void saveEmpruntsToFile(struct Emprunt* emprunts, int numEmprunts);
struct Emprunt** searchEmpruntsByBookName(struct Emprunt* emprunts, int numEmprunts, char book_name[]) ;
int countEmpruntsByBookName(struct Emprunt* emprunts, int numEmprunts, char book_name[]);
void loadEmpruntsFromFile(struct Emprunt** emprunts, int* numEmprunts);
#endif // EMPRUNT_H
