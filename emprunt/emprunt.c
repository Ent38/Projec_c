#include <stdio.h>
#include <string.h>
#include <time.h> // Ajout de la bibliothèque pour la gestion du temps
#include "emprunt.h"
#include "../student/student.h"
#include "../books/books.h"

// Fonction pour afficher tous les emprunts
void displayEmprunts(struct Emprunt* emprunts, int numEmprunts, struct Student* students, int numStudents, struct Book* library, int numBooks) {
    printf("Liste des emprunts :\n");
    for (int i = 0; i < numEmprunts; ++i) {
        int student_number = emprunts[i].student_number;
        int book_code = emprunts[i].book_code;
        
        // Recherche de l'étudiant correspondant
        char student_name[50];
        int student_found = 0;
        for (int j = 0; j < numStudents; ++j) {
            if (students[j].number == student_number) {
                strcpy(student_name, students[j].name);
                student_found = 1;
                break;
            }
        }
        
        // Recherche du livre correspondant
        char book_name[50];
        char book_author[50];
        int book_found = 0;
        for (int k = 0; k < numBooks; ++k) {
            if (library[k].code == book_code) {
                strcpy(book_name, library[k].name);
                strcpy(book_author, library[k].author);
                book_found = 1;
                break;
            }
        }

        // Affichage de l'emprunt avec la date d'emprunt et la date de retour
        if (student_found && book_found) {
            printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
            printf("|   Étudiant : %s,   | Livre : %s      | (Auteur : %s) | Date d'emprunt : %s | Date de retour : %s\n", student_name, book_name, book_author,
                emprunts[i].emprunt_date_str, emprunts[i].return_date_str);
            printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        }
    }
}

// Fonction pour créer un nouvel emprunt
void createEmprunt(struct Emprunt* emprunts, int student_number, int book_code, int* numEmprunts) {
    // Demander la date d'emprunt à l'utilisateur
    printf("Entrez la date d'emprunt (JJ/MM/AAAA) : ");
    char emprunt_date_str[20];
    scanf("%s", emprunt_date_str);

    // Demander la date de retour à l'utilisateur
    printf("Entrez la date de retour (JJ/MM/AAAA) : ");
    char return_date_str[20];
    scanf("%s", return_date_str);

    emprunts[*numEmprunts].student_number = student_number;
    emprunts[*numEmprunts].book_code = book_code;
    strcpy(emprunts[*numEmprunts].emprunt_date_str, emprunt_date_str); // Stockez la date d'emprunt en tant que chaîne de caractères
    strcpy(emprunts[*numEmprunts].return_date_str, return_date_str);   // Stockez la date de retour en tant que chaîne de caractères

    (*numEmprunts)++;
}


// Fonction pour sauvegarder les emprunts dans un fichier
void saveEmpruntsToFile(struct Emprunt *emprunts, int *numEmprunts)
{
    FILE *file = fopen("emprunt/emprunts.txt", "w");
    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier emprunts.txt");
        return;
    }

    for (int i = 0; i < *numEmprunts; ++i)
    { 
        fprintf(file, "%d %d %s %s\n", emprunts[i].student_number, emprunts[i].book_code, emprunts[i].emprunt_date_str, emprunts[i].return_date_str);
    }

    fclose(file);
}

// Fonction pour charger les emprunts à partir d'un fichier
void loadEmpruntsFromFile(struct Emprunt* emprunts, int* numEmprunts) {
    FILE *file = fopen("emprunt/emprunts.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier emprunts.txt");
        return;
    }
    *numEmprunts = 0;
    while (fscanf(file, "%d %d %s %s", &emprunts[*numEmprunts].student_number, &emprunts[*numEmprunts].book_code,
            emprunts[*numEmprunts].emprunt_date_str, emprunts[*numEmprunts].return_date_str) == 4) {
        (*numEmprunts)++;
    }
    fclose(file);
}

// Fonction pour rechercher un emprunt par code de livre
struct Emprunt *searchEmpruntByBookCode(struct Emprunt emprunts[], int numEmprunts, int book_code) {
    for (int i = 0; i < numEmprunts; i++) {
        if (emprunts[i].book_code == book_code) {
            return &emprunts[i]; // Retourne un pointeur vers l'emprunt trouvé
        }
    }
    return NULL; // Si aucun emprunt avec le code de livre donné n'est trouvé, retourne NULL
}


// Fonction pour supprimer un emprunt
void deleteEmprunt(struct Emprunt* emprunts, int book_code, int* numEmprunts) {
    int i;
    for (i = 0; i < *numEmprunts; ++i) { 
        if (emprunts[i].book_code == book_code) {
            // Supprimer l'emprunt en décalant les éléments suivants
            for (int j = i; j < *numEmprunts - 1; ++j) {
                emprunts[j] = emprunts[j + 1];
            }
            (*numEmprunts)--;
            break;
        }
    }
}

// Fonction pour mettre à jour un emprunt
void updateEmprunt(struct Emprunt* emprunts, int book_code, int new_student_number, int* numEmprunts) {
    for (int i = 0; i < *numEmprunts; ++i) {
        if (emprunts[i].book_code == book_code) {
            // Mettre à jour les informations de l'emprunt
            emprunts[i].student_number = new_student_number;

            break;
        }
    }
}
