#ifndef BOOKS_H
#define BOOKS_H

#include "emprunt.h"  // Assurez-vous d'inclure le fichier d'en-tête emprunt.h
struct Student;

struct Book {
    char name[50];
    char category[50];
    int code;
    char author[50];
    int rented; // 1 si emprunté, 0 sinon
};


struct Book createBook(char name[], char category[], int code, char author[]);
void deleteBook(struct Book* library, int code, int* numBooks);
void editBook(struct Book* library, int code, char name[], char category[], char author[], int* numBooks);
void displayBookList(struct Book* library, int numBooks, struct Emprunt* emprunts, int numEmprunts, struct Student* students, int numStudents);

#endif // BOOKS_H
