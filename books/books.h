#ifndef BOOKS_H
#define BOOKS_H

#include "../emprunt/emprunt.h"
struct Emprunt;

struct Student;

// Structure pour représenter un livre
struct Book {
    char name[50];
    char category[50];
    int code;
    char author[50];
    int rented; // 1 si emprunté, 0 sinon
};

struct Book* createBook(struct Book** library, int* numBooks,char name[], char category[], int code, char author[]) ;
void deleteBook(struct Book** library, int code, int* numBooks);
void editBook(struct Book* library, int code, char name[], char category[], char author[], int numBooks);
void displayBookList(struct Book* library, int numBooks, struct Emprunt* emprunts, int numEmprunts, struct Student* students, int numStudents);
struct Book *searchBookByCode(struct Book library[], int numBooks, int code);
void saveBookToFile(struct Book* library, int numBooks) ;
void loadBooksFromFile(struct Book** library, int* numBooks);

#endif // BOOKS_H
