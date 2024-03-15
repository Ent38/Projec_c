// Structure pour représenter un étudiant
struct Student {
    char name[50];
    int number;
    char email[50];
    int codep;
};

// Fonction pour créer un nouvel étudiant
struct Student createStudent(char name[], int number, char email[], int codep) {
    struct Student new_student;
    strcpy(new_student.name, name);
    new_student.number = number;
    strcpy(new_student.email, email);
    new_student.codep = codep;
    return new_student;
}

// Fonction pour afficher la liste des étudiants avec indication de l'emprunt ou non d'un livre
void displayStudentList(struct Student* students, int numStudents, struct Emprunt* emprunts, int numEmprunts) {
    printf("Liste des étudiants :\n");
    for (int i = 0; i < numStudents; ++i) {
        printf("Nom : %s, Numéro : %d, Email : %s, Code postal : %d\n", students[i].name, students[i].number, students[i].email, students[i].codep);
        int emprunt_found = 0;
        for (int j = 0; j < numEmprunts; ++j) {
            if (emprunts[j].student_number == students[i].number) {
                emprunt_found = 1;
                break;
            }
        }
        if (emprunt_found) {
            printf("  - Un livre est emprunté\n");
        } else {
            printf("  - Aucun livre emprunté\n");
        }
    }
}

