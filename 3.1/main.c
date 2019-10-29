//
// Created by gianluca on 28/10/19.
//
#include <stdio.h>
#define MAX 50

typedef struct
{
    int r,c,h,l; //riga, colonna, altezza, lunghezza
} Ris; //contiene informazioni sui rettangoli

void readMat(int m[][MAX], int *nr, int *nc)
{
    FILE *fp;
    fp = fopen("mappa.txt", "r");
    fscanf(fp, "%d %d", nr, nc);
    for (int i = 0; i < *nr; i++) {
        for (int j = 0; j < *nc; j++) {
            fscanf(fp, "%d", &m[i][j]);
        }
    }
    fclose(fp);
}
void printMat(int m[][MAX], int nr, int nc)
{
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int verificaRegione(int m[][MAX], int nr, int nc, int r, int c, int *h, int *l)
{
    int tmp = c;

    if (m[r][c]==1)
    {
        while(m[r][c]==1 && c<nc)
        {
            *l=*l+1;
            c++;
        }
        c=tmp;
        while (m[r][c]==1 && r<nr)
        {
            *h=*h+1;
            r++;
        }
        return 1;
    }
    else return 0;
}

int main()
{
    int mat[MAX][MAX];
    int nr, nc;
    Ris maxh = {0,0,0,0};
    Ris maxl = {0,0,0,0};
    Ris maxa = {0,0,0,0};

    readMat(mat, &nr, &nc);
    printMat(mat, nr, nc);

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            int h=0, l=0;
            if (verificaRegione(mat, nr, nc, i, j, &h, &l))
            {
                if(h>maxh.h)
                {
                    maxh.h=h;
                    maxh.l=l;
                    maxh.r=i;
                    maxh.c=j;
                }
                if(l>maxl.l)
                {
                    maxl.h=h;
                    maxl.l=l;
                    maxl.r=i;
                    maxl.c=j;
                }
                int a = h*l;
                if(a>(maxa.l*maxa.h))
                {
                    maxa.l=l;
                    maxa.h=h;
                    maxa.r=i;
                    maxa.c=j;
                }
                j = j+l-1; //salta alla fine della lunghezza del rettangolo trovato per risprmiare qualche ciclo
            }
        }
    }

    printf("Massima lunghezza-> i=%d j=%d l=%d h=%d a=%d\n", maxl.r, maxl.c, maxl.l, maxl.h, maxl.h*maxl.l);
    printf("Massima altezza-> i=%d j=%d l=%d h=%d a=%d\n", maxh.r, maxh.c, maxh.l, maxh.h, maxh.h*maxh.l);
    printf("Massima area-> i=%d j=%d l=%d h=%d a=%d\n", maxa.r, maxa.c, maxa.l, maxa.h, maxa.h*maxa.l);

    return 0;
}
