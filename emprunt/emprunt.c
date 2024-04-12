#include <stdio.h>
#include <string.h>
#include "emprunt.h"
#include "../student/student.h"
#include "../books/books.h"
#include <time.h>


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
        
        // Affichage de l'emprunt avec la date de l'emprunt et la date de retour
        if (student_found && book_found) {
            struct tm* emprunt_tm = localtime(&emprunts[i].emprunt_date);
            struct tm* return_tm = localtime(&emprunts[i].return_date);
            char emprunt_date_str[50];
            char return_date_str[50];
            strftime(emprunt_date_str, sizeof(emprunt_date_str), "%c", emprunt_tm); // Convertir la date de l'emprunt en format lisible
            strftime(return_date_str, sizeof(return_date_str), "%c", return_tm); // Convertir la date de retour en format lisible
            
            printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
            printf("|   Étudiant : %s,   | Livre : %s      | (Auteur : %s) | Date d'emprunt : %s | Date de retour : %s\n", student_name, book_name, book_author, emprunt_date_str, return_date_str);
            printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        }
    }
}

// Fonction pour créer un nouvel emprunt



void createEmprunt(struct Emprunt* emprunts, int student_number, int book_code, int* numEmprunts) {
    time_t current_time = time(NULL); // Obtenir la date et l'heure actuelles
    emprunts[*numEmprunts].student_number = student_number;
    emprunts[*numEmprunts].book_code = book_code;
    emprunts[*numEmprunts].emprunt_date = current_time;
    emprunts[*numEmprunts].return_date = current_time + 10 * 24 * 60 * 60;
    
    (*numEmprunts)++;
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
void updateEmprunt(struct Emprunt* emprunts, int book_code, int new_student_number, time_t new_emprunt_date, time_t new_return_date, int* numEmprunts) {
    for (int i = 0; i < *numEmprunts; ++i) {
        if (emprunts[i].book_code == book_code) {
            // Mettre à jour les informations de l'emprunt
            emprunts[i].student_number = new_student_number;
            emprunts[i].emprunt_date = new_emprunt_date;
            emprunts[i].return_date = new_return_date;

            // Mettre à jour les chaînes de caractères pour les dates
            struct tm* emprunt_tm = localtime(&new_emprunt_date);
            struct tm* return_tm = localtime(&new_return_date);
            strftime(emprunts[i].emprunt_date_str, sizeof(emprunts[i].emprunt_date_str), "%c", emprunt_tm); // Convertir la date de l'emprunt en format lisible
            strftime(emprunts[i].return_date_str, sizeof(emprunts[i].return_date_str), "%c", return_tm); // Convertir la date de retour en format lisible

            break;
        }
    }
}

// Fonction pour charger les emprunts à partir d'un fichier
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
        struct tm* emprunt_tm = localtime(&emprunts[i].emprunt_date);
        struct tm* return_tm = localtime(&emprunts[i].return_date);
        char emprunt_date_str[50];
        char return_date_str[50];
        strftime(emprunt_date_str, sizeof(emprunt_date_str), "%c", emprunt_tm); // Convertir la date de l'emprunt en format lisible
        strftime(return_date_str, sizeof(return_date_str), "%c", return_tm); // Convertir la date de retour en format lisible

        fprintf(file, "%d %d %s %s\n", emprunts[i].student_number, emprunts[i].book_code, emprunt_date_str, return_date_str);
    }

    fclose(file);
}

void loadEmpruntsFromFile(struct Emprunt* emprunts, int* numEmprunts) {
    FILE *file = fopen("emprunt/emprunts.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier emprunts.txt");
        return;
    }

    *numEmprunts = 0;
    while (fscanf(file, "%d %d %s %s", &emprunts[*numEmprunts].student_number, &emprunts[*numEmprunts].book_code, emprunts[*numEmprunts].emprunt_date_str, emprunts[*numEmprunts].return_date_str) == 4) {
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