#ifndef BOOK_MENU_H
#define BOOK_MENU_H
#include "books.h"

#include "../student/student.h"  
struct Emprunt;

struct Student;

struct Book ;

void booksMenu(struct Book *library, int *numBooks,struct Student *students, int numStudents,struct Emprunt *emprunts, int numEmprunts);

#endif // BOOKS_MENU_H