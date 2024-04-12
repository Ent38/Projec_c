#include "books.h"
#include <stdio.h>
#include <string.h>

// Fonction pour créer un nouveau livre
struct Book createBook(char name[], char category[], int code, char author[]) {
    struct Book new_book;
    strcpy(new_book.name, name);
    strcpy(new_book.category, category);
    new_book.code = code;
    strcpy(new_book.author, author);
    new_book.rented = 0; // Nouveau livre, donc non emprunté
    return new_book;
}

// Fonction pour sauvegarder les livres dans un fichier
void saveBooksToFile(struct Book* library, int numBooks) {
    FILE* file = fopen("books/books.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarde des livres.\n");
        return;
    }
    for (int i = 0; i < numBooks; ++i) {
        fprintf(file, "%s,%s,%d,%s,%d\n", library[i].name, library[i].category, library[i].code, library[i].author, library[i].rented);
    }
    fclose(file);
}

// Fonction pour charger les livres à partir d'un fichier
void loadBooksFromFile(struct Book* library, int* numBooks) {
    FILE* file = fopen("books/books.txt", "r");
    if (file == NULL) {
        printf("Fichier de livres introuvable. Créez-le en ajoutant des livres.\n");
        return;
    }
    *numBooks = 0;
    while (fscanf(file, "%[^,],%[^,],%d,%[^,],%d\n", library[*numBooks].name, library[*numBooks].category, &library[*numBooks].code, library[*numBooks].author, &library[*numBooks].rented) == 5) {
        (*numBooks)++;
    }
    fclose(file);
}

// Fonction pour supprimer un livre
void deleteBook(struct Book* library, int code, int* numBooks) {
    int i;
    for (i = 0; i < *numBooks; ++i) {
        if (library[i].code == code) {
            // Supprimer le livre en décalant les éléments suivants
            for (int j = i; j < *numBooks - 1; ++j) {
                library[j] = library[j + 1];
            }
            (*numBooks)--;
            break;
        }
    }
    saveBooksToFile(library, *numBooks); // Sauvegarder les modifications dans le fichier
}

// Fonction pour modifier les détails d'un livre
void editBook(struct Book* library, int code, char name[], char category[], char author[], int* numBooks) {
    int i;
    for (i = 0; i < *numBooks; ++i) {
        if (library[i].code == code) {
            // Modifier les détails du livre
            strcpy(library[i].name, name);
            strcpy(library[i].category, category);
            strcpy(library[i].author, author);
            break;
        }
    }
    saveBooksToFile(library, *numBooks); // Sauvegarder les modifications dans le fichier
}

// Fonction pour afficher la liste des livres avec indication de l'emprunt ou non
void displayBookList(struct Book* library, int numBooks, struct Emprunt* emprunts, int numEmprunts, struct Student* students, int numStudents) {
    printf("Liste des livres :\n");
    for (int i = 0; i < numBooks; ++i) {
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        printf("|   Nom : %s,    | Catégorie : %s,    | Code : %d,   |  Auteur : %s\n", library[i].name, library[i].category, library[i].code, library[i].author);
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        int emprunt_found = 0;
        for (int j = 0; j < numEmprunts; ++j) {
            if (emprunts[j].book_code == library[i].code) {
                emprunt_found = 1;
                // Afficher les détails de l'étudiant associé à cet emprunt
                for (int k = 0; k < numStudents; ++k) {
                    if (emprunts[j].student_number == students[k].number) {
                        printf("  - Ce livre est emprunté par l'étudiant : %s\n", students[k].name);
                        break;
                    }
                }
                break;
            }
        }
        if (!emprunt_found) {
            printf("  - Ce livre est disponible\n");
        }
    }
}

// Fonction pour rechercher un livre par code
struct Book *searchBookByCode(struct Book library[], int numBooks, int code) {
    for (int i = 0; i < numBooks; i++) {
        if (library[i].code == code) {
            return &library[i]; // Retourne un pointeur vers le livre trouvé
        }
    }
    return NULL; // Si aucun livre avec le code donné n'est trouvé, retourne NULL
}