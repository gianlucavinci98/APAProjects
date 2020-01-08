//
// Created by gianluca on 07/01/20.
//
#include <stdio.h>
#include <stdlib.h>

#define NPIETRE 4

int carica(int **numG, FILE *fp)
{
    int *numGemme = malloc(NPIETRE* sizeof(int));
    int tot = 0;
    for (int i = 0; i < NPIETRE; i++) {
        fscanf(fp,"%d",&numGemme[i]);
        tot = tot+numGemme[i];
    }

    *numG=numGemme;
    return tot;
}
char interpreta(int ind)
{
    switch(ind)
    {
        case 0:
            return 'z';
        case 1:
            return 'r';
        case 2:
            return 't';
        case 3:
            return 's';
        default:
            return '\0';
    }
}
void stampaCollana(int *gemme, int dim)
{
    for (int i = 0; i < dim; i++) {
        char c = interpreta(gemme[i]);
        printf("%c ", c);
    }
}
int check(int *sol, int ind, int scelta)
{
    if(ind==0) return 1;
    switch (sol[ind-1])
    {
        case 0:
            if(scelta==0 || scelta==1) return 1;
            return 0;
        case 1:
            if(scelta==3 || scelta==2) return 1;
            return 0;
        case 2:
            if(scelta==0 || scelta==1) return 1;
            return 0;
        case 3:
            if(scelta==3 || scelta==2) return 1;
            return 0;
        default:
            return 0;
    }
}
int dispRip(int pos, int *sol, int k, int *gemme)
{
    if(pos>=k)
    {
        stampaCollana(sol, k);
        return 1;
    }
    for (int i = 0; i < NPIETRE; i++) {
        if (gemme[i]>0)
        {
            gemme[i]--;
            sol[pos]=i;
            if(check(sol, pos, i))
            {
                if(dispRip(pos+1, sol, k, gemme)) return 1;
            }
            gemme[i]++;
        }
    }
    return 0;
}
int dispRipW(int *numGemme, int maxlun)
{
    int trovato = 0;
    int k;
    for (k = maxlun; k >=1 && trovato==0; k--) {
        int *sol = malloc(k* sizeof(int));
        if(dispRip(0, sol, k, numGemme)) trovato=1;
    }

    return k+1;
}
void stampaPietre(int *gemme, int maxlun)
{
    printf("Z=%d R=%d T=%d S=%d MAX=%d\n", gemme[0],gemme[1],gemme[2],gemme[3],maxlun);
}

int main()
{
    int *numGemme;
    int maxLun, ntest;

    FILE *fp = fopen("collanaHard.txt", "r");
    fscanf(fp, "%d", &ntest);

    for (int i = 0; i < ntest; i++) {
        printf("TEST#%d:\n", i+1);
        maxLun=carica(&numGemme,fp);
        stampaPietre(numGemme, maxLun);

        int sol=dispRipW(numGemme, maxLun);
        if(sol) printf(" SOL=%d\n", sol);
        else printf("Nessuna soluzione\n");
    }

    return 0;
}

