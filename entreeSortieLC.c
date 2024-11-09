#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Biblio *charger_n_entrees(char *nomfic, int n){
    Biblio *b = creer_biblio();
    FILE *f = fopen(nomfic,"r");
    if(f == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }
    int num_lu;
    char auteur_lu[255];
    char titre_lu[255];
    for (int i= 0;i<n;i++){
        if(fscanf(f,"%d %s %s\n", &num_lu, titre_lu, auteur_lu)==3){
            //printf("%d %s %s\n",num_lu,auteur_lu, titre_lu);
            inserer_en_tete(b,num_lu,titre_lu,auteur_lu);
        }
        else{
            printf("Erreur lors de la lecture des donnees");
            break;
        }
    }
    fclose(f);
    return b;
}

void enregistrer_biblio(Biblio *b, char *nomfic){
    FILE *f = fopen(nomfic,"w");
    if(f == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    if(b == NULL || b->L == NULL){
        printf("Bibliotheque vide\n");
        fclose(f);
        return;
    }
    Livre *tmp = b->L;
    while(tmp){
        //printf("%d %s %s\n", tmp->num, tmp->titre, tmp->auteur);
        fprintf(f, "%d %s %s\n", tmp->num, tmp->titre, tmp->auteur);
        tmp = tmp->suiv;
    }
    
    fclose(f);
}