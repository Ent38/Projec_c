// emprunt.h
#ifndef EMPRUNT_H
#define EMPRUNT_H

// Structure pour représenter un emprunt
struct Emprunt {
    int student_number;
    int book_code;
};

// Fonction pour créer un nouvel emprunt
void createEmprunt(struct Emprunt* emprunts, int student_number, int book_code, int* numEmprunts);

// Fonction pour supprimer un emprunt
void deleteEmprunt(struct Emprunt* emprunts, int book_code, int* numEmprunts);

// Fonction pour mettre à jour un emprunt
void updateEmprunt(struct Emprunt* emprunts, int book_code, int new_student_number, int* numEmprunts);

#endif // EMPRUNT_H
