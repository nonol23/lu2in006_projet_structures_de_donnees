#include "biblioH.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int fonctionClef(char* auteur){
    int clef=0;
    for (int i = 0; auteur[i] != '\0'; i++) {
        clef += (int)auteur[i];
    }
    return clef;
}
LivreH *creer_livre(int num,char* titre,char* auteur){
    LivreH *l = (LivreH*)malloc(sizeof(LivreH));
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    l->suivant = NULL;
    l->clef = fonctionClef(l->auteur);
    return l;
}
void liberer_livre(LivreH *l){
    if(l == NULL){
        return;
    }
    free(l->titre);
    free(l->auteur);
    free(l);
}
BiblioH* creerBiblio(int m) {
    BiblioH* biblio = (BiblioH*)malloc(sizeof(BiblioH));
    if (biblio == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour la bibliothèque.\n");
        return NULL;
    }
    biblio->nE = 0;
    biblio->m = m;
    biblio->T = (LivreH**)malloc(m * sizeof(LivreH*));
    if (biblio->T == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour la table de hachage.\n");
        return NULL;
    }
    for (int i = 0; i < m; i++) {
        biblio->T[i] = NULL;
    }
    return biblio;
}
void libererBiblio(BiblioH* b) {
    if(b == NULL){
        return;
    }
    for (int i = 0; i < b->m; i++) {
        LivreH* tmp = b->T[i];
        while (tmp != NULL) {
            LivreH* temp = tmp;
            tmp = tmp->suivant;
            liberer_livre(temp);
        }
    }
    free(b->T);
    free(b);
}
int fonctionHachage(int cle, int m){
    float a = (sqrt(5)-1)/2;
    int res = m * (cle*a - floor(cle*a));
    return res;
}
void inserer(BiblioH* b,int num,char* titre,char* auteur){
    int i = fonctionHachage(fonctionClef(auteur),b->m);
    //printf("%d\n",i);
    LivreH *new = creer_livre(num,titre,auteur);
    if(b->T[i] == NULL){
        b->T[i] = new;
    }
    else{
        new->suivant = b->T[i];
        b->T[i] = new;
    }
}
void afficherLivre(LivreH *l){
    if(l == NULL){
        return;
    }
    printf("Numéro: %d, Titre: %s, Auteur: %s, Clef: %d\n", l->num, l->titre, l->auteur,l->clef);
}

void afficherBiblioH(BiblioH *b){
    if(b == NULL){
        return;
    }
    for(int i=0;i<b->m;i++){
        LivreH *tmp = b->T[i];
        while(tmp){
            afficherLivre(tmp);
            tmp = tmp->suivant;
        }
    } 
}

LivreH *rechercheNumH(BiblioH *b,int n){
    for(int i=0; i<b->m; i++){
        LivreH *tmp = b->T[i];
        while(tmp){
            if(n==tmp->num){
                //printf("Le livre à été trouvé avec succès ;)\n");
                return tmp;
            }
            tmp = tmp->suivant;
        }
    }
    printf("Numéro inconnu.\n");
    return NULL;
}

LivreH *rechercheTitreH(BiblioH *b,char *titre){
    for(int i=0; i<b->m; i++){
        LivreH *tmp = b->T[i];
        while(tmp){
            if(strcmp(titre,tmp->titre)==0){
                printf("Le livre à été trouvé avec succès ;)\n");
                return tmp;
            }
            tmp = tmp->suivant;
        }
    }
    printf("Titre inconnu.\n");
    return NULL;
}

BiblioH *rechercheAuteurH(BiblioH *b,char *auteur){
    BiblioH *res = creerBiblio(b->m);
    bool inser = false;
    int i = fonctionHachage(fonctionClef(auteur),b->m);
        LivreH *tmp = b->T[i];
        while(tmp){
            if(strcmp(auteur,tmp->auteur)==0){
                inserer(res,tmp->num,tmp->titre,tmp->auteur);
                inser = true;
            }
            tmp = tmp->suivant;
        }
    if(inser == false){
        printf("Auteur inconnu.\n");
        libererBiblio(res);
        return NULL;
    }
    return res;
}

void supprimer(BiblioH *b, int num, char *titre, char *auteur){
    int i = fonctionHachage(fonctionClef(auteur),b->m);
    LivreH *tmp = b->T[i];
    LivreH *trouve = NULL;
    LivreH *prec = NULL;
        
    while (tmp) {
        if ((tmp->num == num) && (strcmp(titre, tmp->titre) == 0) && (strcmp(auteur, tmp->auteur)== 0)) {
            printf("Livre trouvé\n");
            trouve = tmp;
            if (prec == NULL) { 
                b->T[i] = tmp->suivant;
            } else {
                prec->suivant = tmp->suivant;
            }
            tmp = tmp->suivant;
            trouve->suivant = NULL;
            liberer_livre(trouve);
            printf("Le livre à été supprimé avec succès ;)");
            break; 
        }
        prec = tmp;
        tmp = tmp->suivant;
    }
    if(trouve == NULL) {
        printf("Livre non trouvé\n");
    }

}

BiblioH *fusionH(BiblioH *b1,BiblioH *b2){
    if (b1 == NULL || b1->T == NULL) {
        libererBiblio(b2); 
        return b1;
    }
    if (b2 == NULL || b2->T == NULL) {
        libererBiblio(b1);
        return b2;
    }
    LivreH *tmp1 = b1->T[0];
    int c = tmp1->num;
    c++;
    for(int i=0;i<b2->m;i++){
        LivreH *tmp2 = b2->T[i];
        while(tmp2){
            inserer(b1,c++,tmp2->titre,tmp2->auteur);
            tmp2=tmp2->suivant;
        }
    }
    libererBiblio(b2);
    printf("Ajout terminé.\n");
    return b1;
}


LivreH **rechercheH(BiblioH *b){
    BiblioH* res = creerBiblio(b->m);
    for(int i=0; i<b->m; i++){
        LivreH *liste = b->T[i];
        while(liste){
            bool ajout = false;
            int num = liste->num;
            char* titre = liste->titre;
            char* auteur = liste->auteur; 
            LivreH* liste2 = b->T[i];
            while(liste2){
                if((strcmp(titre, liste2->titre)==0) && (strcmp(auteur, liste2->auteur)==0) && (num != liste2->num)){
                    ajout = true;

                }
                liste2=liste2->suivant;
            }
            if(ajout == true){
                inserer(res, num, titre, auteur);
            }
            liste=liste->suivant;
        }
    }
    return res->T;
}