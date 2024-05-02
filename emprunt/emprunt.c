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

        // Affichage de l'emprunt avec la date d'emprunt et la date de retour
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
        printf("|   Étudiant : %s   | Livre : %s      | Date d'emprunt : %s | Date de retour : %s\n", emprunts[i].student_name, emprunts[i].book_name, emprunts[i].emprunt_date_str, emprunts[i].return_date_str);
        printf("|--------------------------------------------------------------------------------------------------------------------------|\n");
    }
}


struct Emprunt* createEmprunt(struct Emprunt** emprunts, int* numEmprunts, char student_name[], char book_name[], char return_date_str[], char emprunt_date_str[]) {
    // Allouer de la mémoire pour le nouvel emprunt
    struct Emprunt* new_emprunt = (struct Emprunt*)malloc(sizeof(struct Emprunt));
    if (new_emprunt == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire pour le nouvel emprunt.\n");
        return NULL;
    }

    // Copier les informations de l'emprunt
    strcpy(new_emprunt->student_name, student_name);
    strcpy(new_emprunt->book_name, book_name);
    strcpy(new_emprunt->return_date_str, return_date_str);
    strcpy(new_emprunt->emprunt_date_str, emprunt_date_str);

    // Ajouter le nouvel emprunt à la liste
    *numEmprunts += 1;
    *emprunts = realloc(*emprunts, (*numEmprunts) * sizeof(struct Emprunt*));
    if (*emprunts == NULL) {
        printf("Erreur: Impossible de réallouer de la mémoire pour la liste d'emprunts.\n");
        free(new_emprunt); // Libérer la mémoire allouée pour le nouvel emprunt
        return NULL;
    }
    (*emprunts)[(*numEmprunts) - 1] = *new_emprunt;

    // Sauvegarder la liste mise à jour dans le fichier
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
        // Allouer de la mémoire pour un nouvel emprunt
        *emprunts = realloc(*emprunts, (*numEmprunts + 1) * sizeof(struct Emprunt));
        if (*emprunts == NULL) {
            printf("Erreur lors de la réallocation de mémoire.\n");
            fclose(file);
            return;
        }

        // Lire les informations de l'emprunt depuis le fichier
        if (fscanf(file, "%s %s %s %s \n", (*emprunts)[*numEmprunts].student_name, (*emprunts)[*numEmprunts].book_name,(*emprunts)[*numEmprunts].emprunt_date_str, (*emprunts)[*numEmprunts].return_date_str) == 4) {

            (*numEmprunts)++;
        } else {
            // Si la lecture échoue, sortir de la boucle
            break;
        }
    }
    
    fclose(file);
}

void deleteEmprunt(struct Emprunt** emprunts, char book_name[], int* numEmprunts) {
    // Recherche de l'emprunt par le nom du livre
    int indexToDelete = -1;
    for (int i = 0; i < *numEmprunts; ++i) {
        if (strcmp((*emprunts)[i].book_name, book_name) == 0) {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete != -1) {
        // Décalage des emprunts restants
        for (int i = indexToDelete; i < *numEmprunts - 1; ++i) {
            (*emprunts)[i] = (*emprunts)[i + 1];
        }
        // Diminution du nombre total d'emprunts
        (*numEmprunts)--;
        
        // Réallocation de mémoire si nécessaire
        if (*numEmprunts > 0) {
            *emprunts = realloc(*emprunts, *numEmprunts * sizeof(struct Emprunt));
            if (*emprunts == NULL) {
                printf("Erreur lors de la réallocation de mémoire.\n");
                return;
            }
        } else {
            // Si le nombre d'emprunts est devenu nul, libérer la mémoire et mettre le pointeur à NULL
            free(*emprunts);
            *emprunts = NULL;
        }
    } else {
        printf("Erreur: Impossible de trouver l'emprunt avec le nom du livre %s\n", book_name);
        return;
    }

    // Écriture de la liste mise à jour dans le fichier
    saveEmpruntsToFile(*emprunts, *numEmprunts);
    // Recharger la liste des emprunts depuis le fichier
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
        // Modification des données de l'emprunt
        strcpy(emprunts[indexToEdit].emprunt_date_str, emprunt_date_str);
        strcpy(emprunts[indexToEdit].return_date_str, return_date_str);

        // Écriture de la liste mise à jour dans le fichier
        saveEmpruntsToFile(emprunts, numEmprunts);

        // Afficher un message de confirmation
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
            // Vérifier si l'index dépasse le nombre d'emprunts trouvés
            if (index >= count) {
                break; // Arrêter la boucle si on a déjà trouvé tous les emprunts nécessaires
            }
            // Allouer de la mémoire pour stocker une copie de l'emprunt correspondant
            result[index] = (struct Emprunt*)malloc(sizeof(struct Emprunt));
            if (result[index] == NULL) {
                printf("Erreur lors de l'allocation de mémoire pour l'emprunt correspondant.\n");
                // Libérer la mémoire allouée pour les emprunts précédents
                for (int j = 0; j < index; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            // Copier l'emprunt correspondant dans la mémoire allouée
            strcpy(result[index]->student_name, emprunts[i].student_name);
            strcpy(result[index]->book_name, emprunts[i].book_name);
            strcpy(result[index]->emprunt_date_str, emprunts[i].emprunt_date_str);
            strcpy(result[index]->return_date_str, emprunts[i].return_date_str);
            // Incrémenter l'index pour le prochain emprunt correspondant
            index++;
        }
    }
    
    return result;
}


