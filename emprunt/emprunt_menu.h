#ifndef EMPRUNT_MENU_H
#define EMPRUNT_MENU_H
#include <time.h>
#define MAX_EMPRUNTS 100 // Définir le nombre maximal d'emprunts
#include "../student/student.h"
#include "../books/books.h"
#include "emprunt.h"

struct Emprunt ;

struct Student;
struct Book;

void empruntMenu(struct Emprunt *emprunts, int *numEmprunts);

#endif // EMPRUNT_MENU_H
 