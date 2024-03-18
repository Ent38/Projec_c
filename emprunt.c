#include <stdio.h>
#include <string.h>
#include "emprunt.h"

// Fonction pour créer un nouvel emprunt
void createEmprunt(struct Emprunt* emprunts, int student_number, int book_code, int* numEmprunts) {
    emprunts[*numEmprunts].student_number = student_number;
    emprunts[*numEmprunts].book_code = book_code;
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
void updateEmprunt(struct Emprunt* emprunts, int book_code, int new_student_number, int* numEmprunts) {
    int i;
    for (i = 0; i < *numEmprunts; ++i) {
        if (emprunts[i].book_code == book_code) {
            // Mettre à jour le numéro de l'étudiant associé à l'emprunt
            emprunts[i].student_number = new_student_number;
            break;
        }
    }
}
