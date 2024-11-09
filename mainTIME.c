#include "biblioH.h"
#include "entreeSortieH.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define NB 50000

int main(int argc,char **argv){
    char *nom_fichier = argv[1];
    BiblioH *B;
    FILE *f = fopen("tempsH.txt","w");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    LivreH *l;
    BiblioH *b;
    fprintf(f, "Table de hachage.\n");
    for(int i=1000; i<NB; i+=1000){
        B = charger_n_entreesH(nom_fichier, i);
        clock_t temps_initial;
        clock_t temps_final;
        double temps_cpu1;
        double temps_cpu2;
        double temps_cpu3;
        double temps_cpu4;
        double temps_cpu5;
        double temps_cpu6;
        
        //recherche numero
        temps_initial = clock();
        l = rechercheNumH(B, 0);
        temps_final = clock();
        temps_cpu1 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        //fprintf(f, "Temps recherche %d numéros : %f\n", n,temps_cpu);
        liberer_livre(l);

        //recherche numero absent
        temps_initial = clock();
        l = rechercheNumH(B, 50001);
        temps_final = clock();
        temps_cpu2 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        liberer_livre(l);

        //recherche titre
        temps_initial = clock();
        l = rechercheTitreH(B, "DZUUE");
        temps_final = clock();
        temps_cpu3 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        //fprintf(f, "Temps recherche titre : %f\n",temps_cpu);
        liberer_livre(l);

        //recherche titre absent
        temps_initial = clock();
        l = rechercheTitreH(B, "DZUUE234");
        temps_final = clock();
        temps_cpu4 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        liberer_livre(l);

        //recherche auteur
        temps_initial = clock();
        b = rechercheAuteurH(B, "qnt");
        temps_final = clock();
        temps_cpu5 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        //fprintf(f, "Temps recherche auteur : %f\n",temps_cpu);
        libererBiblio(b);

        //recherche auteur absent
        temps_initial = clock();
        b = rechercheAuteurH(B, "qnt34");
        temps_final = clock();
        temps_cpu6 = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
        libererBiblio(b);

        fprintf(f,"%d %f %f %f %f %f %f\n",i,temps_cpu1,temps_cpu2,temps_cpu3,temps_cpu4,temps_cpu5,temps_cpu6);

        libererBiblio(B);
    }
    fclose(f);
    return 0;
}