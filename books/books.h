#ifndef BOOKS_H
#define BOOKS_H

#include "../student/student.h"  // Inclure student.h avant la déclaration de struct Book

// Déclaration avancée de la structure Emprunt
struct Emprunt;

// Déclaration complète de la structure Student
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
struct Book *searchBookByCode(struct Book library[], int numBooks, int code);

// Fonction pour sauvegarder les livres dans un fichier
void saveBooksToFile(struct Book* library, int numBooks);

// Fonction pour charger les livres à partir d'un fichier
void loadBooksFromFile(struct Book* library, int* numBooks);

#endif // BOOKS_H
