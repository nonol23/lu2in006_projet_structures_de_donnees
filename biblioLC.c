#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Livre *creer_livre(int num,char *titre,char *auteur){
    Livre *l = (Livre*)malloc(sizeof(Livre));
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    return l;
}

void liberer_livre(Livre *l){
    free(l->titre);
    free(l->auteur);
    free(l);
}

Biblio *creer_biblio(){
    Biblio *b = (Biblio *)malloc(sizeof(Biblio));
    return b;
}

void liberer_biblio(Biblio *b){
    Livre *tmp = NULL;
    while(b->L){
        tmp = b->L;
        b->L = b->L->suiv;
        liberer_livre(tmp);
    }
    free(b);
}

void inserer_en_tete(Biblio *b, int num, char *titre, char *auteur){
    Livre *new = creer_livre(num,titre,auteur);
    new->suiv = b->L;
    b->L=new;
}

void afficherLivre(Livre *l){
    if(l == NULL){
        return;
    }
    printf("Numéro: %d, Titre: %s, Auteur: %s\n", l->num, l->titre, l->auteur);
}

void afficherBilio(Biblio *b){
    if(b == NULL){
        return;
    }
    Livre *tmp = b->L;
    while(tmp){
        afficherLivre(tmp);
        tmp = tmp->suiv;
    }
}

Livre *rechercheNum(Biblio *b,int n){
    Livre *tmp = b->L;
    while(tmp){
        if(n==tmp->num){
            //printf("Le livre à été trouvé avec succès ;)\n");
            return tmp;
        }
        tmp = tmp->suiv;
    }
    printf("Numéro inconnu.\n");
    return NULL;
}

Livre *rechercheTitre(Biblio *b,char *titre){
    Livre *tmp = b->L;
    while(tmp){
        if(strcmp(titre,tmp->titre) == 0){
            printf("Le livre à été trouvé avec succès ;)\n");
            return tmp;
        }
        tmp = tmp->suiv;
    }
    printf("Titre inconnu.\n");
    return NULL;
}
Biblio *rechercheAuteur(Biblio *b,char *auteur){
    Biblio *res = creer_biblio();
    Livre *tmp = b->L;
    while(tmp){
        if(strcmp(auteur,tmp->auteur) == 0){
            inserer_en_tete(res,tmp->num,tmp->titre,tmp->auteur);
        }
        tmp = tmp->suiv;
    }
    if(res->L == NULL){
        printf("Auteur inconnu.\n");
        liberer_biblio(res);
        return NULL;
    }
    else{
       printf("Le livre à été trouvé avec succès ;)\n");
        return res; 
    }
    
}

void supprimerLivre(Biblio *b, int num, char *titre, char *auteur) {
    Livre *tmp = b->L;
    Livre *trouve = NULL;
    Livre *prec = NULL;
    
    while (tmp) {
        if ((tmp->num == num) && (strcmp(titre, tmp->titre) == 0) && (strcmp(auteur, tmp->auteur) == 0)) {
            printf("Livre trouvé\n");
            trouve = tmp;
            if (prec == NULL) { 
                b->L = tmp->suiv;
            } else {
                prec->suiv = tmp->suiv;
            }
            tmp = tmp->suiv;
            trouve->suiv = NULL;
            liberer_livre(trouve);
            printf("Le livre à été supprimé avec succès ;)");
            break; 
        }
        prec = tmp;
        tmp = tmp->suiv;
    }
    
    if (trouve == NULL) {
        printf("Livre non trouvé\n");
    }
}

Biblio *fusion(Biblio *b1,Biblio *b2){
    if (b1 == NULL || b1->L == NULL) {
        liberer_biblio(b2); 
        return b1;
    }
    if (b2 == NULL || b2->L == NULL) {
        liberer_biblio(b1);
        return b2;
    }
    Livre *tmp1 = b1->L;
    Livre *tmp2 = b2->L;
    int c = tmp1->num;
    c++;
    while(tmp2){
        inserer_en_tete(b1,c++,tmp2->titre,tmp2->auteur);
        tmp2=tmp2->suiv;
    }
    liberer_biblio(b2);
    printf("Ajout terminé.\n");
    return b1;
}

Livre *recherche(Biblio *b){
    Livre *liste = b->L;
    Biblio* res = creer_biblio();
    while(liste){
        bool ajout = false;
        int num = liste->num;
        char* titre = liste->titre;
        char* auteur = liste->auteur; 
        Livre* liste2 = b->L;
        while(liste2){
            if((strcmp(titre, liste2->titre)==0) && (strcmp(auteur, liste2->auteur)==0) && (num != liste2->num)){
                ajout = true;

            }
            liste2=liste2->suiv;
        }
        if(ajout == true){
            inserer_en_tete(res, num, titre, auteur);
        }
        liste=liste->suiv;
    }
    return res->L;
}