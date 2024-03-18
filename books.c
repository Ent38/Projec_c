#include <stdio.h>
#include <string.h>

// Structure pour représenter un livre
struct Book {
    char name[50];
    char category[50];
    int code;
    char author[50];
    int rented; // 1 si emprunté, 0 sinon
};

// Structure pour représenter un emprunt
struct Emprunt {
    int book_code;
    // Ajoutez ici d'autres champs si nécessaire, par exemple la date de l'emprunt
};

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
}

// Fonction pour afficher la liste des livres avec indication de l'emprunt ou non
void displayBookList(struct Book* library, int numBooks, struct Emprunt* emprunts, int numEmprunts) {
    printf("Liste des livres :\n");
    for (int i = 0; i < numBooks; ++i) {
        printf("Nom : %s, Catégorie : %s, Code : %d, Auteur : %s\n", library[i].name, library[i].category, library[i].code, library[i].author);
        int emprunt_found = 0;
        for (int j = 0; j < numEmprunts; ++j) {
            if (emprunts[j].book_code == library[i].code) {
                emprunt_found = 1;
                break;
            }
        }
        if (emprunt_found) {
            printf("  - Ce livre est emprunté\n");
        } else {
            printf("  - Ce livre est disponible\n");
        }
    }
}
