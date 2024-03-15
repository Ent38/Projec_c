#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition des structures de données
struct Student {
    char name[50];
    int number;
    char email[50];
    int codep;
};

struct Book {
    char name[50];
    char category[50];
    int code;
    char author[50];
    int rented;
};

struct Emprunt {
    int student_number;
    int book_code;
};

// Prototypes des fonctions
struct Student createStudent(char name[], int number, char email[], int codep);
struct Book createBook(char name[], char category[], int code, char author[]);
struct Emprunt createEmprunt(int student_number, int book_code);
void deleteBook(struct Book* library, int code, int* numBooks);
void editBook(struct Book* library, int code, char name[], char category[], char author[], int* numBooks);
void createEmprunt(struct Emprunt* emprunts, int student_number, int book_code, int* numEmprunts);
void deleteEmprunt(struct Emprunt* emprunts, int book_code, int* numEmprunts);
void updateEmprunt(struct Emprunt* emprunts, int book_code, int new_student_number, int* numEmprunts);
void displayStudentList(struct Student* students, int numStudents, struct Emprunt* emprunts, int numEmprunts);
void displayBookList(struct Book* library, int numBooks, struct Emprunt* emprunts, int numEmprunts);

int main() {
    // Initialisation des données
    struct Student students[100];
    int numStudents = 0;

    struct Book library[100];
    int numBooks = 0;

    struct Emprunt emprunts[100];
    int numEmprunts = 0;

    // Exemples d'utilisation des fonctions
    students[numStudents++] = createStudent("John Doe", 1234, "john@example.com", 12345);
    library[numBooks++] = createBook("C Programming", "Programming", 101, "John Smith");
    library[numBooks++] = createBook("Data Structures", "Computer Science", 102, "Alice Johnson");
    createEmprunt(emprunts, 1234, 101, &numEmprunts);

    // Affichage des informations
    printf("Liste des étudiants et des emprunts :\n");
    displayStudentList(students, numStudents, emprunts, numEmprunts);

    printf("\nListe des livres :\n");
    displayBookList(library, numBooks, emprunts, numEmprunts);

    return 0;
}

