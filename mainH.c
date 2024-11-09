#include "biblioH.h"
#include "entreeSortieH.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>




void menu() {
    printf("--------------------------------------------------------\n");
    printf("                       __MENU__\n");
    printf("\n");
    printf("0 - Sortie du programme.\n");
    printf("\n");
    printf("1 - Affichage.\n");
    printf("\n");
    printf("2 - Inserer ouvrage.\n");
    printf("\n");
    printf("3 - Supprimer ouvrage.\n");
    printf("\n");
    printf("4 - Rechercher par numéro.\n");
    printf("\n");
    printf("5 - Rechercher par titre.\n");
    printf("\n");
    printf("6 - Rechercher par auteur.\n");
    printf("\n");
    printf("7 - Ajouter une bibliotheque.\n");
    printf("\n");
    printf("8 - Liste des ouvrages en plusieurs exemplaires.\n");
    printf("--------------------------------------------------------\n");
        
    printf("Tapez un chiffre:");
    printf("\n");
}



int main(int argc, char **argv){

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <nom_fichier> <nombre_lignes>\n", argv[0]);
        return 1;
    }

    char *nom_fichier = argv[1];
    int n = atoi(argv[2]);
    BiblioH *B = charger_n_entreesH(nom_fichier, n);
    int rep;
    char titre[255];
    char auteur[255];
    char txt[255];

    do {
        menu();
        int num2, num3, num4, nb;
        scanf(" %d", &rep);
        switch (rep) {
            case 1:
                printf("Affichage :\n");
                printf("\n");
                afficherBiblioH(B);
                 
                break;
            case 2:
                printf("Veuillez écrire le numéro, le titre et l'auteur de l'ouvrage dans le format suivant: num titre auteur\n");
                if (scanf(" %d %s %s", &num2, titre, auteur) == 3) {
                    inserer(B, num2, titre, auteur);
                    printf("Le livre a été ajouté avec succès ;)\n");
                } else {
                    printf("Erreur de format.\n");
                }
                break;
            case 3:
                printf("Veuillez écrire le numéro, le titre et l'auteur de l'ouvrage dans le format suivant: num titre auteur\n");
                if (scanf(" %d %s %s", &num3, titre, auteur) == 3) {
                    supprimer(B, num3, titre, auteur);
                } else {
                    printf("Erreur de format.\n");
                }
                break;
            case 4:
                printf("Veuillez entrer un numéro: \n");
                if (scanf(" %d", &num4) == 1) {
                    afficherLivre(rechercheNumH(B, num4));
                } else {
                    printf("Erreur de format.\n");
                }
                break;
            case 5:
                printf("Veuillez entrer un titre: \n");
                if (scanf(" %s", titre) == 1) {
                    afficherLivre(rechercheTitreH(B, titre));
                } else {
                    printf("Erreur de format.\n");
                }
                break;
            case 6:
                printf("Veuillez entrer un auteur: \n");
                if (scanf(" %s", auteur) == 1) {
                    BiblioH *r6 = rechercheAuteurH(B, auteur);
                    afficherBiblioH(r6); 
                } else {
                    printf("Erreur de format.\n");
                }
                break;
            case 7:
                printf("Veuillez entrer le nom d'un fichier texte contenant une bibliothèque ainsi que le nombre de ligne a charger : \n");
                if (scanf(" %s %d", txt,&nb) == 2) {
                    BiblioH *r6 = charger_n_entreesH(txt,nb);
                    B = fusionH(B,r6);
                } else {
                    printf("Erreur de format.\n");
                }
                break;
            case 8:
                printf("Voici la liste des ouvrages présent plusieur fois: \n");
                LivreH **rec = rechercheH(B);
                for(int i=0;i<B->m;i++){
                    LivreH *tmp = rec[i];
                    while(tmp){
                        afficherLivre(tmp);
                        tmp=tmp->suivant;
                    } 
                }
                break;
        }
    } while (rep != 0);

    libererBiblio(B);
    return 0;
}