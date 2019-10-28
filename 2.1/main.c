//
// Created by gianluca on 28/10/19.
//
#include <stdio.h>
#define MAX 50

typedef struct
{
    int nr, nc;
} Dim; //contiene dimensioni matrice
typedef struct
{
    int r,c,h,l; //riga, colonna, altezza, lunghezza
} Ris; //contiene informazioni sui rettangoli

Dim readMat(int m[][MAX])
{
    Dim dim;
    FILE *fp;
    fp = fopen("mappa.txt", "r");
    fscanf(fp, "%d %d", &dim.nr, &dim.nc);
    for (int i = 0; i < dim.nr; i++) {
        for (int j = 0; j < dim.nc; j++) {
            fscanf(fp, "%d", &m[i][j]);
        }
    }
    fclose(fp);
    return dim;
}
void printMat(int m[][MAX], Dim dim)
{
    for (int i = 0; i < dim.nr; i++) {
        for (int j = 0; j < dim.nc; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}
Ris verificaRegione(int m[][MAX], Dim dim, int r, int c)
{
    int tmp = c;
    Ris ris = {r, c, 1, 1};

    c++;
    while(m[r][c]==1 && c<dim.nc)
    {
        ris.l++;
        c++;
    }
    c=tmp;
    r++;
    while (m[r][c]==1 && r<dim.nr)
    {
        ris.h++;
        r++;
    }

    return ris;
}

int main()
{
    int mat[MAX][MAX];
    Dim dim;
    Ris maxh = {0,0,0,0};
    Ris maxl = {0,0,0,0};
    Ris maxa = {0,0,0,0};

    dim = readMat(mat);
    printMat(mat, dim);

    for (int i = 0; i < dim.nr; i++) {
        for (int j = 0; j < dim.nc; j++) {
            if (mat[i][j]==1) //se contiene 1 parte la scansione del rettangolo
            {
                Ris ris = verificaRegione(mat, dim, i, j);
                j = j+ris.l-1; //salta alla fine della lunghezza del rettangolo trovato per risprmiare qualche ciclo
                //Ricerca dei vari massimi
                if(ris.h>maxh.h) maxh=ris;
                if(ris.l>maxl.l) maxl=ris;
                int a = ris.h*ris.l;
                if(a>(maxa.l*maxa.h)) maxa=ris;
            }
        }
    }

    printf("Massima lunghezza-> i=%d j=%d l=%d h=%d a=%d\n", maxl.r, maxl.c, maxl.l, maxl.h, maxl.h*maxl.l);
    printf("Massima altezza-> i=%d j=%d l=%d h=%d a=%d\n", maxh.r, maxh.c, maxh.l, maxh.h, maxh.h*maxh.l);
    printf("Massima area-> i=%d j=%d l=%d h=%d a=%d\n", maxa.r, maxa.c, maxa.l, maxa.h, maxa.h*maxa.l);

    return 0;
}

