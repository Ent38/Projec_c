#ifndef BOOKS_H
#define BOOKS_H

// Structure pour représenter un livre
struct Book {
    char name[50];
    char category[50];
    int code;
    char author[50];
    int rented; // 1 si emprunté, 0 sinon
};

// Fonction pour créer un nouveau livre
struct Book createBook(char name[], char category[], int code, char author[]);

// Fonction pour supprimer un livre
void deleteBook(struct Book* library, int code, int* numBooks);

// Fonction pour modifier les détails d'un livre
void editBook(struct Book* library, int code, char name[], char category[], char author[], int* numBooks);

// Fonction pour afficher la liste des livres avec indication de l'emprunt ou non
void displayBookList(struct Book* library, int numBooks, struct Emprunt* emprunts, int numEmprunts);

#endif // BOOKS_H
