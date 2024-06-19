#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void afficherTableau(int T[], int taille) {
    int i;
    for (i = 0; i < taille; i++) {
        printf("%d ", T[i]);
    }
    printf("\n");
}

void echanger(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void triSimple(int tab[], int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                echanger(&tab[j], &tab[j + 1]);
            }
        }
    }
}

void triSelection(int T[], int taille) {
    int i, j;
    for (i = 0; i < taille - 1; i++) {
        int min_idx = i;
        for (j = i + 1; j < taille; j++) {
            if (T[j] < T[min_idx]) {
                min_idx = j;
            }
        }
        echanger(&T[min_idx], &T[i]);
    }
}

void triBulle(int tableau[], int taille) {
    int i, j;
    for (i = 0; i < taille - 1; i++) {
        for (j = 0; j < taille - i - 1; j++) {
            if (tableau[j] > tableau[j + 1]) {
                echanger(&tableau[j], &tableau[j + 1]);
            }
        }
    }
}

int partition(int T[], int debut, int fin) {
    int pivot = T[fin];
    int i = debut - 1;

    for (int j = debut; j < fin; j++) {
        if (T[j] <= pivot) {
            i++;
            echanger(&T[i], &T[j]);
        }
    }
    echanger(&T[i + 1], &T[fin]);
    return i + 1;
}

void triRapide(int T[], int debut, int fin) {
    if (debut < fin) {
        int pivot = partition(T, debut, fin);
        triRapide(T, debut, pivot - 1);
        triRapide(T, pivot + 1, fin);
    }
}

void fusion(int T[], int debut, int milieu, int fin) {
    int taille_gauche = milieu - debut + 1;
    int taille_droite = fin - milieu;

    int gauche[taille_gauche];
    int droite[taille_droite];

    for (int i = 0; i < taille_gauche; i++) {
        gauche[i] = T[debut + i];
    }
    for (int j = 0; j < taille_droite; j++) {
        droite[j] = T[milieu + 1 + j];
    }

    int i = 0, j = 0, k = debut;

    while (i < taille_gauche && j < taille_droite) {
        if (gauche[i] <= droite[j]) {
            T[k] = gauche[i];
            i++;
        } else {
            T[k] = droite[j];
            j++;
        }
        k++;
    }

    while (i < taille_gauche) {
        T[k] = gauche[i];
        i++;
        k++;
    }

    while (j < taille_droite) {
        T[k] = droite[j];
        j++;
        k++;
    }
}

void triFusion(int T[], int debut, int fin) {
    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;

        triFusion(T, debut, milieu);
        triFusion(T, milieu + 1, fin);

        fusion(T, debut, milieu, fin);
    }
}

void triInsertioncroissant(int T[], int taille) {
    int i, j, tmp;
    for (i = 1; i < taille; i++) {
        tmp = T[i];
        j = i - 1;
        while (j >= 0 && T[j] > tmp) {
            T[j + 1] = T[j];
            j = j - 1;
        }
        T[j + 1] = tmp;
    }
}

void afficherMenu() {
    printf("Choisissez l'algorithme de tri :\n");
    printf("1. Tri Simple\n");
    printf("2. Tri par Selection\n");
    printf("3. Tri a Bulle\n");
    printf("4. Tri Rapide\n");
    printf("5. Tri Fusion\n");
    printf("6. Tri Insertion Croissant\n");
    printf("Entrez votre choix : ");
}

int main() {
    int T[2000];
    srand(time(NULL));
    int i;
    for (i = 0; i < 2000; i++) {
        T[i] = rand() % 10000;
    }
    int choix;

    printf("\n\nTableau avant le tri :\n\n ");
    afficherTableau(T, 2000);

    clock_t debut, fin;
    double temps_ecoule;

    do { afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                debut = clock();
                triSimple(T, 2000);
                fin = clock();
                temps_ecoule = (double) (fin - debut) / CLOCKS_PER_SEC;
                printf("\n\nTableau apres le tri avec Tri Simple :\n\n ");
                afficherTableau(T, 2000);
                printf("Temps d'execution : %f secondes\n", temps_ecoule);
                break;
            case 2:
                debut = clock();
                triSelection(T, 2000);
                fin = clock();
                temps_ecoule = (double) (fin - debut) / CLOCKS_PER_SEC;
                printf("\n\nTableau apres le tri avec Tri par Selection :\n\n ");
                afficherTableau(T, 2000);
                printf("Temps d'execution : %f secondes\n", temps_ecoule);
                break;
            case 3:
                debut = clock();
                triBulle(T, 2000);
                fin = clock();
                temps_ecoule = (double) (fin - debut) / CLOCKS_PER_SEC;
                printf("\n\nTableau apres le tri avec Tri a Bulle :\n\n ");
                afficherTableau(T, 2000);
                printf("Temps d'execution : %f secondes\n", temps_ecoule);
                break;
            case 4:
                debut = clock();
                triRapide(T, 0, 1999);
                fin = clock();
                temps_ecoule = (double) (fin - debut) / CLOCKS_PER_SEC;
                printf("\n\nTableau apres le tri avec Tri Rapide :\n\n ");
                afficherTableau(T, 2000);
                printf("Temps d'execution : %f secondes\n", temps_ecoule);
                break;
            case 5:
                debut = clock();
                triFusion(T, 0, 1999);
                fin = clock();
                temps_ecoule = (double) (fin - debut) / CLOCKS_PER_SEC;
                printf("\n\nTableau apres le tri avec Tri Fusion :\n\n ");
                afficherTableau(T, 2000);
                printf("Temps d'execution : %f secondes\n", temps_ecoule);
                break;
            case 6:
                debut = clock();
                triInsertioncroissant(T, 2000);
                fin = clock();
                temps_ecoule = (double) (fin - debut) / CLOCKS_PER_SEC;
                printf("\n\nTableau apres le tri avec Tri Insertion Croissant :\n\n ");
                afficherTableau(T, 2000);
                printf("Temps d'executio
                
                
                
                n : %f secondes\n", temps_ecoule);
            case 7:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    }while (choix != 7);

    return 0;
}