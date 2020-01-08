//
// Created by gianluca on 13/12/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BRANI 255

typedef struct
{
    int nBrani;
    char** brani;
} amico;

int leggiAmici(char* file, amico **a)
{
    FILE *fp = fopen(file, "r");
    int nA;
    char titTMP[MAX_BRANI];

    fscanf(fp, "%d", &nA);
    *a = malloc(nA* sizeof(amico));
    for (int i = 0; i < nA; i++) {
        fscanf(fp,"%d", &((*a)[i].nBrani));

        (*a)[i].brani=malloc((*a)[i].nBrani * sizeof(char*));

        for (int j = 0; j < (*a)[i].nBrani; j++) {
            fscanf(fp,"%s", titTMP);
            (*a)[i].brani[j]=strdup(titTMP);
        }
    }
    return nA;
}
void libera(amico *a, int na)
{
    for (int i = 0; i < na; i++) {
        for (int j = 0; j < a[i].nBrani; j++) {
            free(a[i].brani[j]);
        }
        free(a[i].brani);
    }
    free(a);
}

int playlist(int pos, amico *a, int* sol, int nA, int count)
{
    if(pos==nA)
    {
        printf("Playlist #%d\n", count);
        for (int i = 0; i < nA; i++) {
            printf("-%s\n", a[i].brani[sol[i]]);
        }
        printf("\n");
        return count+1;
    }
    for (int i = 0; i < a[pos].nBrani; i++) {
        sol[pos]=i;
        count = playlist(pos+1, a, sol, nA, count);
    }
    return count;
}

int main()
{
    amico* amici;
    int nAmici;
    int* sol;

    nAmici=leggiAmici("brani.txt", &amici);
    sol = malloc(nAmici* sizeof(int));
    playlist(0, amici, sol, nAmici, 1);
    libera(amici, nAmici);

    return 0;
}

