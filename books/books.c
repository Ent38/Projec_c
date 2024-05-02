#include "books.h"
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>

struct Book* createBook(struct Book** library, int* numBooks,char name[], char category[], int code, char author[]) {
    // Allouer de la mémoire pour le nouveau livre
    struct Book* new_book = (struct Book*)malloc(sizeof(struct Book));
    if (new_book == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire pour le nouveau livre.\n");
        return NULL;
    }

    // Copier les informations du livre
    strcpy(new_book->name, name);
    strcpy(new_book->category, category);
    new_book->code = code;
    strcpy(new_book->author, author);
    new_book->rented = 0; 

    // Ajouter le nouveau livre à la liste
    (*numBooks) += 1; 
    *library = realloc(*library, (*numBooks) * sizeof(struct Book)); 
    if (*library == NULL) {
        printf("Erreur: Impossible de réallouer de la mémoire pour la liste de livres.\n");
        free(new_book); 
        return NULL;
    }
    (*library)[(*numBooks) - 1] = *new_book; 
    saveBookToFile(*library, *numBooks);
    loadBooksFromFile(library,numBooks);


    return new_book;
}

void loadBooksFromFile(struct Book** library, int* numBooks) {
    FILE* file = fopen("books/books.txt", "r");
    if (file == NULL) {
        printf("Fichier de livres introuvable. Créez-le en ajoutant des livres.\n");
        return;
    }
    *numBooks = 0;
    *library = (struct Book*)malloc(sizeof(struct Book)); // Allocation initiale
    if (*library == NULL) {
        printf("Erreur lors de l'allocation de mémoire.\n");
        fclose(file);
        return;
    }
    while (fscanf(file, "%[^,],%[^,],%d,%[^,],%d\n", (*library)[*numBooks].name, (*library)[*numBooks].category, &(*library)[*numBooks].code, (*library)[*numBooks].author, &(*library)[*numBooks].rented) == 5) {
        (*numBooks)++;
        *library = realloc(*library, (*numBooks + 1) * sizeof(struct Book)); // Réallocation
        if (*library == NULL) {
            printf("Erreur lors de la réallocation de mémoire.\n");
            fclose(file);
            free(*library); 
            return;
        }
    }
    fclose(file);
}
void deleteBook(struct Book** library, int code, int* numBooks) {
    int indexToDelete = -1;
    for (int i = 0; i < *numBooks; ++i) {
        if ((*library)[i].code == code) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete != -1) {
        for (int i = indexToDelete; i < *numBooks - 1; ++i) {
            (*library)[i] = (*library)[i + 1];
        }
        (*numBooks)--;
    } else {
        printf("Erreur: Impossible de trouver le livre avec le code %d\n", code);
        return;
    }

    *library = realloc(*library, *numBooks * sizeof(struct Book));
    if (*library == NULL && *numBooks > 0) {
        printf("Erreur lors de la réallocation de mémoire.\n");
        return;
    }

    saveBookToFile(*library,*numBooks);
    loadBooksFromFile(library,numBooks);
}

void editBook(struct Book* library, int code, char name[], char category[], char author[], int numBooks) {
    int indexToEdit = -1;
    for (int i = 0; i < numBooks; ++i) {
        if (library[i].code == code) {
            indexToEdit = i;
            break;
        }
    }

    if (indexToEdit != -1) {
        strcpy(library[indexToEdit].name, name);
        strcpy(library[indexToEdit].category, category);
        strcpy(library[indexToEdit].author, author);
    } else {
        printf("Erreur: Impossible de trouver le livre avec le code %d\n", code);
        return;
    }

    saveBookToFile(library,numBooks);
    loadBooksFromFile(&library,&numBooks);

}

void saveBookToFile(struct Book* library, int numBooks) {
    FILE* file = fopen("books/books.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarde du livre.\n");
        return;
    }
    for (int i = 0; i < numBooks; ++i) {
        fprintf(file, "%s,%s,%d,%s,%d\n", library[i].name, library[i].category, library[i].code, library[i].author, library[i].rented);
    }
    fclose(file);
}

void displayBookList(struct Book* library, int numBooks, struct Emprunt* emprunts, int numEmprunts, struct Student* students, int numStudents) {
    printf("Liste des livres :\n");
    for (int i = 0; i < numBooks; ++i) {
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        printf("|   Nom : %s,    | Catégorie : %s,    | Code : %d,   |  Auteur : %s\n", library[i].name, library[i].category, library[i].code, library[i].author);
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        
        // Vérifier si le livre est emprunté
        int emprunt_found = 0;
        for (int j = 0; j < numEmprunts; ++j) {
            if (strcmp(emprunts[j].book_name, library[i].name) == 0) { 
                emprunt_found = 1;
                for (int k = 0; k < numStudents; ++k) {
                    if (strcmp(emprunts[j].student_name, students[k].name) == 0) { 
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


struct Book *searchBookByCode(struct Book library[], int numBooks, int code) {
    for (int i = 0; i < numBooks; i++) {
        if (library[i].code == code) {
            return &library[i]; 
        }
    }
    return NULL; 
}
