#ifndef STUDENT_MENU_H
#define STUDENT_MENU_H

#include "../emprunt/emprunt.h"
#include "student.h"

struct Book;

struct Emprunt;

struct Student ;

void studentMenu(struct Student *students, int *numStudents,struct Book * library, int numBooks,struct Emprunt *emprunts, int *numEmprunts  );
#endif // STUDENT_MENU_H