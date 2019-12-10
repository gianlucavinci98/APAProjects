//
// Created by gianluca on 25/11/19.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX 256

typedef struct{
    int nBrani;
    char **titolo;
} amico;

amico *leggiFile(char *file, int *na) {
    int i, j;
    char titTmp[MAX];
    amico *a;
    FILE *in = fopen(file, "r");

    fscanf(in, "%d", na);
    a = calloc((size_t) *na, sizeof(amico));
    for (i=0; i<*na; i++)
    {
        fscanf(in, "%d", &a[i].nBrani);
        a[i].titolo = calloc((size_t) a[i].nBrani, sizeof(char*));
        for (j=0; j<a[i].nBrani; j++)
        {
            fscanf(in, "%s", titTmp);
            a[i].titolo[j] = strdup(titTmp);
        }
    }
    return a;
}

void molt(int pos, amico *a, int *sol, int na, int *cnt) {
    int i;

    if (pos == na)
    {
        printf("Playlist #%d\n", ++(*cnt));
        for (i=0; i<pos; i++)
        {
            printf(" * %s\n", a[i].titolo[sol[i]]);
        }
        printf("\n");
        return;
    }

    for(i=0;i<a[pos].nBrani; i++) {
        sol[pos] = i;
        molt(pos + 1, a, sol, na, cnt);
    }
}

void playlist(amico *a, int na) {
    int *sol, cnt = 0;
    sol = calloc((size_t) na, sizeof(int));
    molt(0, a, sol, na, &cnt);
    free(sol);
}

void libera (amico *a, int na) {
    int i;
    for (i=0; i<na; i++)
        free(a[i].titolo);
    free(a);
}
int main() {
    int na = -1;
    amico *a = leggiFile("brani.txt", &na);
    playlist(a, na);
    libera(a, na);
    return 0;
}

