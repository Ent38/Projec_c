Le projet de gestion de bibliothèque est un programme en langage C conçu pour aider à gérer les activités courantes d'une bibliothèque, telles que la gestion des étudiants, des livres et des emprunts. Voici une analyse détaillée de chaque fonctionnalité et de son fonctionnement :

## 1. Gestion des étudiants :

### Fonctionnalités :
- **Créer un étudiant** : Permet d'ajouter un nouvel étudiant à la bibliothèque en spécifiant son numéro, son nom, son email et son code permanent.
- **Modifier un étudiant** : Permet de mettre à jour les informations d'un étudiant existant, telles que son nom, son email et son code permanent.
- **Supprimer un étudiant** : Permet de retirer un étudiant de la base de données de la bibliothèque.
- **Afficher la liste des étudiants** : Affiche tous les étudiants enregistrés dans la bibliothèque, avec leurs informations associées.
- **Rechercher un étudiant par son numéro** : Permet de trouver un étudiant en saisissant son numéro.

### Fonctionnement :
- L'utilisateur choisit une option dans le menu des étudiants.
- En fonction de l'option sélectionnée, le programme effectue les opérations correspondantes en interagissant avec la structure de données des étudiants.
- Les données des étudiants sont stockées dans un fichier `students.txt` pour une utilisation future.

## 2. Gestion des livres :

### Fonctionnalités :
- **Créer un livre** : Permet d'ajouter un nouveau livre à la bibliothèque en spécifiant son code, son titre, sa catégorie et son auteur.
- **Modifier un livre** : Permet de mettre à jour les informations d'un livre existant, telles que son titre, sa catégorie et son auteur.
- **Supprimer un livre** : Permet de retirer un livre de la base de données de la bibliothèque.
- **Afficher la liste des livres** : Affiche tous les livres disponibles dans la bibliothèque, avec leurs détails.
- **Rechercher un livre par son code** : Permet de trouver un livre en saisissant son code.

### Fonctionnement :
- L'utilisateur choisit une option dans le menu des livres.
- Le programme exécute les opérations correspondantes en fonction de l'option sélectionnée, en interagissant avec la structure de données des livres.
- Les données des livres sont stockées dans un fichier `books.txt` pour une utilisation future.

## 3. Gestion des emprunts :

### Fonctionnalités :
- **Créer un emprunt** : Permet d'effectuer un nouvel emprunt en associant un étudiant à un livre, avec les dates d'emprunt et de retour.
- **Modifier un emprunt** : Permet de mettre à jour les informations d'un emprunt existant, telles que l'étudiant associé et les dates.
- **Supprimer un emprunt** : Permet de retourner un livre et de supprimer l'emprunt correspondant de la base de données.
- **Afficher la liste des emprunts** : Affiche tous les emprunts en cours, avec les détails de l'étudiant, du livre et les dates.
- **Rechercher un emprunt par le code du livre** : Permet de trouver un emprunt en saisissant le code du livre associé.

### Fonctionnement :
- L'utilisateur choisit une option dans le menu des emprunts.
- Le programme effectue les opérations correspondantes en interagissant avec la structure de données des emprunts.
- Les données des emprunts sont stockées dans un fichier `loans.txt` pour une utilisation future.

## Fonctionnement global :
- Au démarrage du programme, les données sont chargées à partir des fichiers de sauvegarde dans la mémoire du programme.
- L'utilisateur peut interagir avec les différents menus pour effectuer les opérations souhaitées.
- Toutes les opérations effectuées par l'utilisateur sont reflétées dans les fichiers de sauvegarde pour une utilisation future.

Ce programme offre une solution complète pour la gestion efficace des opérations courantes dans une bibliothèque, en automatisant les processus liés aux étudiants, aux livres et aux emprunts.