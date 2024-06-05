#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define MAX 100

/*
    Les Fonctions Qui Realiser Ce Project
    - Afficher le Menu
    - Ajouter Un Livres --> Linked List + Pile
    - Afficher Les Livres
    - Suprimmer Un Livres
    - Recherche D'un Livres
    - Modifier les details d'un livre
*/

typedef struct Livre {
    char nom_livre[MAX];
    char author_livre[MAX];
    float prix;
    struct Livre *precedent;
    struct Livre *suivant;
} Livre;

// Affichage De Menu
void afficherMenu() {
    printf("\n-------------------------------------------\n");
    printf("\n\t\t\t\t\t\tMenu :\n\n");
    printf("\t\t\t\t\t\t1. ➕ Ajouter un livre\n");
    printf("\t\t\t\t\t\t2. 📚 Afficher les livres\n");
    printf("\t\t\t\t\t\t3. ❌ Supprimer un livre\n");
    printf("\t\t\t\t\t\t4. 🔍 Rechercher un livre\n");
    printf("\t\t\t\t\t\t5. ✏️  Modifier les details d'un livre\n");
    printf("\t\t\t\t\t\t6. 🚪 Quitter\n");
    printf("\n-------------------------------------------\n");
}

// Supprimer Les Espaces
void supprimer_espaces(char *chaine) {
    int i, j;
    int longueur = strlen(chaine);
    for (i = 0; i < longueur; i++) {
        if (chaine[i] == ' ') {
            chaine[i] = '_';
        }
    }
}

// Ajouter des livres
void ajouter_des_livres(Livre **debut, Livre **sommet) {
    Livre *nouveau_livre = (Livre *) malloc(sizeof(Livre));
    if (nouveau_livre == NULL) {
        printf("\nErreur d'allocation\n");
    } else {
        nouveau_livre->precedent = nouveau_livre->suivant = NULL;
        printf("Entrez le nom du livre : "); 
        getchar();  // Pour consommer le '\n' residuel
        scanf("%[^\n]", nouveau_livre->nom_livre);
        supprimer_espaces(nouveau_livre->nom_livre);
        getchar();  // Pour consommer le '\n' apres la saisie
        printf("Entrez l'auteur du livre : ");
        scanf("%[^\n]", nouveau_livre->author_livre);
        supprimer_espaces(nouveau_livre->author_livre);
        getchar();  // Pour consommer le '\n' apres la saisie
        printf("Entrez le prix du livre : ");
        scanf("%f", &nouveau_livre->prix);
        if (*debut == NULL) {
            *debut = nouveau_livre;
            *sommet = nouveau_livre;
        } else {
            nouveau_livre->precedent = *sommet;
            (*sommet)->suivant = nouveau_livre;
            *sommet = nouveau_livre;
        }
        // Ouvrir Fichier
        FILE *p_file = fopen("livre.txt", "a");
        if (p_file == NULL) printf("\nFichier Pas Ouvrit\n");
        else {
            fprintf(p_file, "%s %s %f\n", nouveau_livre->nom_livre, nouveau_livre->author_livre, nouveau_livre->prix);
        }
        fclose(p_file);
    }
}

// Affichage des livres
void afficher_livres(Livre *debut) {
    if (debut == NULL) printf("\nAucun Livre Exist\n");
    else {
        Livre *temp = debut;
        while (temp != NULL) {
            printf("%s %s %.2f\n", temp->nom_livre, temp->author_livre, temp->prix);
            temp = temp->suivant;
        }
        printf("\n");
    }
}


// Recherche Par Nom de livre
void recherche_livre_nom(Livre *debut) {
    char recherche[MAX];
    printf("Entrez le nom du livre a rechercher : "); getchar();
    scanf("%[^\n]", recherche);
    supprimer_espaces(recherche);
    Livre *temp = debut;
    int trouve = 0;
    while (temp != NULL) {
        if (strcmp(temp->nom_livre, recherche) == 0) {
            printf("Livre trouve : '%s' '%s' %.2f\n", temp->nom_livre, temp->author_livre, temp->prix);
            trouve = 1;
        }
        temp = temp->suivant;
    }

    if (!trouve) {
        printf("Le livre recherche n'a pas ete trouve.\n");
    }
}

// Recherche Par Nom de Author
void recherche_livre_author(Livre *debut) {
    char recherche[MAX];
    printf("Entrez le nom de l'auteur a rechercher : ");
    getchar();  // Pour consommer le '\n' residuel
    scanf("%[^\n]", recherche);
    supprimer_espaces(recherche);
    Livre *temp = debut;
    int trouve = 0;
    while (temp != NULL) {
        if (strcmp(temp->author_livre, recherche) == 0) {
            printf("Livre trouve : '%s' '%s' %.2f\n", temp->nom_livre, temp->author_livre, temp->prix);
            trouve = 1;
        }
        temp = temp->suivant;
    }
    if (!trouve) {
        printf("Le livre recherche n'a pas ete trouve.\n");
    }
}



// Recherche Par Prix
void recherche_livre_prix(Livre *debut) {
    float recherche;
    printf("Entrez le prix a rechercher : ");
    scanf("%f", &recherche);
    Livre *temp = debut;
    int trouve = 0;
    while (temp != NULL) {
        if (temp->prix == recherche) {
            printf("Livre trouve : '%s' '%s' %.2f\n", temp->nom_livre, temp->author_livre, temp->prix);
            trouve = 1;
        }
        temp = temp->suivant;
    }

    if (!trouve) {
        printf("Le livre recherche n'a pas ete trouve.\n");
    }
}

// Recherche d'un livre
void recherche_livre(Livre *debut) {
    int choix;
    printf("1. Nom de livre\n");
    printf("2. Nom de Author\n");
    printf("3. Prix\n");
    printf("Enterz Votre Choix : ");
    scanf("%d", &choix);
    switch(choix) {
        case 1: {
            recherche_livre_nom(debut); break;
        } case 2: {
            recherche_livre_author(debut); break;
        }
        case 3: {
            recherche_livre_prix(debut); break;
        } 
        default: printf("\nErreur\n");
    }
}

// modifier le prix du livre
void modifier_prix_livre(Livre *debut) {
    float recherche_prix;
    printf("Entrez le prix du livre a modifier : ");
    scanf("%f", &recherche_prix);

    Livre *temp = debut;
    while (temp != NULL) {
        if (temp->prix == recherche_prix) {
            printf("Entrez le nouveau prix du livre : ");
            scanf("%f", &temp->prix);
            printf("Le prix du livre a ete modifie avec succès.\n");
            return;
        }
        temp = temp->suivant;
    }
    printf("Le livre recherche n'a pas ete trouve.\n");
}

// Modifier le nom du livre
void modifier_nom_livre(Livre *debut) {
    char recherche[MAX];
    printf("Entrez le nom du livre a modifier : ");
    getchar();  // Pour consommer le '\n' residuel
    scanf("%[^\n]", recherche);
    supprimer_espaces(recherche);

    Livre *temp = debut;
    while (temp != NULL) {
        if (strcmp(temp->nom_livre, recherche) == 0) {
            printf("Entrez le nouveau nom du livre : ");
            getchar();  // Pour consommer le '\n' residuel
            scanf("%[^\n]", temp->nom_livre);
            supprimer_espaces(temp->nom_livre);
            printf("Le nom du livre a ete modifie avec succès.\n");
            return;
        }
        temp = temp->suivant;
    }
    printf("Le livre recherche n'a pas ete trouve.\n");
}

// Modifier le nom de l'auteur
void modifier_nom_auteur(Livre *debut) {
    char recherche[MAX];
    printf("Entrez le nom de l'auteur a modifier : ");
    getchar();  // Pour consommer le '\n' residuel
    scanf("%[^\n]", recherche);
    supprimer_espaces(recherche);

    Livre *temp = debut;
    while (temp != NULL) {
        if (strcmp(temp->author_livre, recherche) == 0) {
            printf("Entrez le nouveau nom de l'auteur : ");
            getchar();  // Pour consommer le '\n' residuel
            scanf("%[^\n]", temp->author_livre);
            supprimer_espaces(temp->author_livre);
            printf("Le nom de l'auteur a ete modifie avec succès.\n");
            return;
        }
        temp = temp->suivant;
    }
    printf("L'auteur recherche n'a pas ete trouve.\n");
}

// Modifier les informations d'un livre
void modifier_details(Livre *debut) {
    int choix;
    printf("1. Nom de livre\n");
    printf("2. Nom de l'auteur\n");
    printf("3. Prix\n");
    printf("Entrez votre choix pour modifier le livre : ");
    scanf("%d", &choix);
    switch (choix) {
        case 1: {
            modifier_nom_livre(debut);
            break;
        }
        case 2: {
            modifier_nom_auteur(debut);
            break;
        }
        case 3: {
            modifier_prix_livre(debut);
            break;
        }
        default: {
            printf("\nErreur\n");
            break;
        }
    }
}


// Supprimer un livre par nom
void supprimer_livre_par_nom(Livre **debut, Livre **sommet) {
    char recherche[MAX];
    printf("Entrez le nom du livre a supprimer : ");
    getchar();
    scanf("%[^\n]", recherche);
    supprimer_espaces(recherche);
    Livre *temp = *debut;
    while (temp != NULL) {
        if (strcmp(temp->nom_livre, recherche) == 0) {
            if (temp->precedent != NULL)
                temp->precedent->suivant = temp->suivant;
            else
                *debut = temp->suivant;

            if (temp->suivant != NULL)
                temp->suivant->precedent = temp->precedent;
            else
                *sommet = temp->precedent;
            free(temp);
            printf("Le livre a ete supprime.\n");
            return;
        }
        temp = temp->suivant;
    }
    printf("Le livre recherche n'a pas ete trouve.\n");
}

// Supprimer un livre par auteur
void supprimer_livre_par_auteur(Livre **debut, Livre **sommet) {
    char recherche[MAX];
    printf("Entrez le nom de l'auteur du livre a supprimer : ");
    getchar();
    scanf("%[^\n]", recherche);
    getchar(); 
    supprimer_espaces(recherche);
    Livre *temp = *debut;
    while (temp != NULL) {
        if (strcmp(temp->author_livre, recherche) == 0) {
            if (temp->precedent != NULL)
                temp->precedent->suivant = temp->suivant;
            else
                *debut = temp->suivant;
            if (temp->suivant != NULL)
                temp->suivant->precedent = temp->precedent;
            else
                *sommet = temp->precedent;
            free(temp);
            printf("Le livre a ete supprime.\n");
            return;
        }
        temp = temp->suivant;
    }
    printf("Le livre recherche n'a pas ete trouve.\n");
}


// Supprimer un livre par prix
void supprimer_livre_par_prix(Livre **debut, Livre **sommet) {
    float recherche;
    printf("Entrez le prix du livre a supprimer : ");
    scanf("%f", &recherche);
    Livre *temp = *debut;
    while (temp != NULL) {
        if (temp->prix == recherche) {
            if (temp->precedent != NULL)
                temp->precedent->suivant = temp->suivant;
            else
                *debut = temp->suivant;
            if (temp->suivant != NULL)
                temp->suivant->precedent = temp->precedent;
            else
                *sommet = temp->precedent;
            free(temp);
            printf("Le livre a ete supprimer.\n");
            return;
        }
        temp = temp->suivant;
    }
    printf("Le livre recherche n'a pas ete trouve.\n");
}

// Supprimer un livre
void supprimer_livres(Livre **debut, Livre **sommet) {
    int choix;
    printf("1. Nom de livre\n");
    printf("2. Nom de l'auteur\n");
    printf("3. Prix\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choix);
    switch (choix) {
        case 1:
            supprimer_livre_par_nom(debut, sommet);
            break;
        case 2:
            supprimer_livre_par_auteur(debut, sommet);
            break;
        case 3:
            supprimer_livre_par_prix(debut, sommet);
            break;
        default:
            printf("\nErreur\n");
    }
}

// Mettre A Jour Le Contenu De Fichier
void mettre_a_jour_fichier(Livre *debut, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        perror("Erreur");
        return;
    }
    Livre *temp = debut;
    while (temp != NULL) {
        fprintf(fichier, "%s %s %f\n", temp->nom_livre, temp->author_livre, temp->prix);
        temp = temp->suivant;
    }
    fclose(fichier);
}


// ajouter en cas de fichier
void ajouter_en_cas_de_fichier(char *nom_livre, char *author_livre, float prix, Livre **debut, Livre **sommet) {
    Livre *nouveau_livre = (Livre *) malloc(sizeof(Livre));
    strcpy(nouveau_livre->nom_livre, nom_livre);
    strcpy(nouveau_livre->author_livre, author_livre);
    nouveau_livre->prix = prix;
    if (nouveau_livre == NULL) {
        printf("\nErreur d'allocation\n");
    } else {
        if (*debut == NULL) {
            *debut = nouveau_livre;
            *sommet = nouveau_livre;
        } else {
            nouveau_livre->precedent = *sommet;
            (*sommet)->suivant = nouveau_livre;
            *sommet = nouveau_livre;
        }
    }
}

// Recupere Donne a fichier
void recuperer_donner_a_fichier(Livre **debut, Livre **sommet) {
    FILE *p_file = fopen("livre.txt", "r");
    if (p_file == NULL) printf("\nFichier Pas Ouvrit\n");
    else {
        char nom_livre[MAX];
        char author_livre[MAX];
        float prix;
        while (fscanf(p_file, "%s %s %f", nom_livre, author_livre, &prix) == 3) {
            ajouter_en_cas_de_fichier(nom_livre, author_livre, prix, debut, sommet);
            char c;
            while ((c = fgetc(p_file)) != EOF && c != '\n');
        }
    }
    fclose(p_file);
}


int main() {
    int choix;
    Livre *debut = NULL;
    Livre *sommet = NULL;
    recuperer_donner_a_fichier(&debut, &sommet);
    do {
        afficherMenu();
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch(choix) {
            case 1: {
                ajouter_des_livres(&debut, &sommet); break;
            } 
            case 2: {
                afficher_livres(debut); break;
            }
            case 3: {
                supprimer_livres(&debut, &sommet); break;
            } 
            case 4: {
                recherche_livre(debut); break;
            }
            case 5: {
                modifier_details(debut); break;
            }
            default: {
                mettre_a_jour_fichier(debut, "livre.txt"); break;
            }
        }
    } while (choix < 6);
    return 0;
}





