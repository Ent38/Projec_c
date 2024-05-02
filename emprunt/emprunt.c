#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "emprunt.h"
#include "../student/student.h"
#include "../books/books.h"
#define MAX_DATE_LENGTH 20

#define EMPRUNTS_FILE "emprunt/emprunts.txt"

void displayEmprunts(struct Emprunt* emprunts, int numEmprunts) {
    printf("Liste des emprunts :\n");
    for (int i = 0; i < numEmprunts; ++i) {

        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        printf("|   Étudiant : %s   | Livre : %s      | Date d'emprunt : %s | Date de retour : %s\n", emprunts[i].student_name, emprunts[i].book_name, emprunts[i].emprunt_date_str, emprunts[i].return_date_str);
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
    }
}


struct Emprunt* createEmprunt(struct Emprunt** emprunts, int* numEmprunts, char student_name[], char book_name[], char return_date_str[], char emprunt_date_str[]) {
    struct Emprunt* new_emprunt = (struct Emprunt*)malloc(sizeof(struct Emprunt));
    if (new_emprunt == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire pour le nouvel emprunt.\n");
        return NULL;
    }

    strcpy(new_emprunt->student_name, student_name);
    strcpy(new_emprunt->book_name, book_name);
    strcpy(new_emprunt->return_date_str, return_date_str);
    strcpy(new_emprunt->emprunt_date_str, emprunt_date_str);

    *numEmprunts += 1;
    *emprunts = realloc(*emprunts, (*numEmprunts) * sizeof(struct Emprunt*));
    if (*emprunts == NULL) {
        printf("Erreur: Impossible de réallouer de la mémoire pour la liste d'emprunts.\n");
        free(new_emprunt); 
        return NULL;
    }
    (*emprunts)[(*numEmprunts) - 1] = *new_emprunt;

    saveEmpruntsToFile(*emprunts, *numEmprunts);

    return new_emprunt;
}

void saveEmpruntsToFile(struct Emprunt* emprunts, int numEmprunts) {
    FILE* file = fopen(EMPRUNTS_FILE, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s pour sauvegarde des emprunts.\n", EMPRUNTS_FILE);
        return;
    }
    for (int i = 0; i < numEmprunts; ++i) {
        fprintf(file, "%s %s %s %s \n", emprunts[i].student_name, emprunts[i].book_name, emprunts[i].emprunt_date_str, emprunts[i].return_date_str);
    }
    fclose(file);
}

void loadEmpruntsFromFile(struct Emprunt** emprunts, int* numEmprunts) {
    FILE* file = fopen(EMPRUNTS_FILE, "r");
    if (file == NULL) {
        printf("Fichier d'emprunts introuvable. Créez-le en ajoutant des emprunts.\n");
        return;
    }

    *numEmprunts = 0;
    *emprunts = NULL;

    while (1) {
        *emprunts = realloc(*emprunts, (*numEmprunts + 1) * sizeof(struct Emprunt));
        if (*emprunts == NULL) {
            printf("Erreur lors de la réallocation de mémoire.\n");
            fclose(file);
            return;
        }

        if (fscanf(file, "%s %s %s %s \n", (*emprunts)[*numEmprunts].student_name, (*emprunts)[*numEmprunts].book_name,(*emprunts)[*numEmprunts].emprunt_date_str, (*emprunts)[*numEmprunts].return_date_str) == 4) {

            (*numEmprunts)++;
        } else {
            break;
        }
    }
    
    fclose(file);
}

void deleteEmprunt(struct Emprunt** emprunts, char book_name[], int* numEmprunts) {
    int indexToDelete = -1;
    for (int i = 0; i < *numEmprunts; ++i) {
        if (strcmp((*emprunts)[i].book_name, book_name) == 0) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete != -1) {
        for (int i = indexToDelete; i < *numEmprunts - 1; ++i) {
            (*emprunts)[i] = (*emprunts)[i + 1];
        }
        (*numEmprunts)--;
        
        if (*numEmprunts > 0) {
            *emprunts = realloc(*emprunts, *numEmprunts * sizeof(struct Emprunt));
            if (*emprunts == NULL) {
                printf("Erreur lors de la réallocation de mémoire.\n");
                return;
            }
        } else {
            free(*emprunts);
            *emprunts = NULL;
        }
    } else {
        printf("Erreur: Impossible de trouver l'emprunt avec le nom du livre %s\n", book_name);
        return;
    }

    saveEmpruntsToFile(*emprunts, *numEmprunts);
    loadEmpruntsFromFile(emprunts,numEmprunts);
}

void editEmprunt(struct Emprunt* emprunts, int numEmprunts, char book_name[], char emprunt_date_str[], char return_date_str[]) {
    // Recherche de l'emprunt par le nom du livre
    int indexToEdit = -1;
    for (int i = 0; i < numEmprunts; ++i) {
        if (strcmp(emprunts[i].book_name, book_name) == 0) {
            indexToEdit = i;
            break;
        }
    }

    if (indexToEdit != -1) {
        strcpy(emprunts[indexToEdit].emprunt_date_str, emprunt_date_str);
        strcpy(emprunts[indexToEdit].return_date_str, return_date_str);

        saveEmpruntsToFile(emprunts, numEmprunts);

        printf("Emprunt modifié avec succès.\n");
    } else {
        printf("Erreur: Impossible de trouver l'emprunt avec le nom du livre %s\n", book_name);
    }
}

int countEmpruntsByBookName(struct Emprunt* emprunts, int numEmprunts, char book_name[]) {
    int count = 0;
    for (int i = 0; i < numEmprunts; ++i) {
        if (strcmp(emprunts[i].book_name, book_name) == 0) {
            count++;
        }
    }
    return count;
}

struct Emprunt** searchEmpruntsByBookName(struct Emprunt* emprunts, int numEmprunts, char book_name[]) {
    int count = countEmpruntsByBookName(emprunts, numEmprunts, book_name);
    if (count == 0) {
        return NULL; // Aucun emprunt correspondant trouvé
    }
    
    struct Emprunt** result = (struct Emprunt**)malloc(count * sizeof(struct Emprunt*));
    if (result == NULL) {
        printf("Erreur lors de l'allocation de mémoire.\n");
        return NULL;
    }
    
    int index = 0;
    for (int i = 0; i < numEmprunts; ++i) {
        if (strstr(emprunts[i].book_name, book_name) != NULL) {
            if (index >= count) {
                break; 
            }
            result[index] = (struct Emprunt*)malloc(sizeof(struct Emprunt));
            if (result[index] == NULL) {
                printf("Erreur lors de l'allocation de mémoire pour l'emprunt correspondant.\n");
                for (int j = 0; j < index; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strcpy(result[index]->student_name, emprunts[i].student_name);
            strcpy(result[index]->book_name, emprunts[i].book_name);
            strcpy(result[index]->emprunt_date_str, emprunts[i].emprunt_date_str);
            strcpy(result[index]->return_date_str, emprunts[i].return_date_str);
            index++;
        }
    }
    
    return result;
}


