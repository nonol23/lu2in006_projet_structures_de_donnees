#include "entreeSortieH.h"
#include "biblioH.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


BiblioH *charger_n_entreesH(char *nomfic, int n){
    BiblioH *b = creerBiblio(20);
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
            inserer(b,num_lu,titre_lu,auteur_lu);
        }
        else{
            printf("Erreur lors de la lecture des donnees");
            break;
        }
    }
    fclose(f);
    return b;
}

void enregistrer_BiblioH(BiblioH *b, char *nomfic){
    FILE *f = fopen(nomfic,"w");
    if(f == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    if(b == NULL || b->T == NULL){
        printf("BiblioHtheque vide\n");
        fclose(f);
        return;
    }

    for(int i=0; i<b->m; i++){
        LivreH *tmp = b->T[i];
        while(tmp){
            fprintf(f, "%d %s %s %d\n", tmp->num, tmp->titre, tmp->auteur,tmp->clef);
            tmp = tmp->suivant;
        }
    }
    
    fclose(f);
}