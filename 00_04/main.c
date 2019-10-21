//
// Created by gianluca on 17/10/19.
//
#include <stdio.h>

#define DIM 20

int min(int n1, int n2) {
    if(n1<n2) return n1;
    else n2;
}

int stampaSommaMat(int m[][DIM], int rigSt, int rigEnd,int colSt, int colEnd)
{
    int somma = 0;
    for (int i = rigSt; i <= rigEnd; i++) {
        for (int j = colSt; j <= colEnd; j++) {
            printf("%d ", m[i][j]);
            somma+=m[i][j];
        }
        printf("\n");
    }

    return somma;
}

void subMats(int m[][DIM], int nr, int nc, int n)
{
    int maxSomma = 0;
    int somma = 0;
    for (int i = 0; i <=nr-n; i++) {
        for (int j = 0; j <=nc-n; j++) {
            somma = stampaSommaMat(m,i,i+n-1,j,j+n-1);
            printf("\n");
            if(maxSomma<somma)
            {
                maxSomma = somma;
            }
        }
    }

    printf("Somma massima: %d\n", maxSomma);
}

int main()
{
    int mat[DIM][DIM];
    FILE *fp;

    printf("Inserisci nome file: ");
    char nomeFile[DIM];
    scanf("%s", nomeFile);

    fp=fopen(nomeFile, "r");

    int nc, nr;
    fscanf(fp,"%d %d", &nr, &nc);
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }

    stampaSommaMat(mat,0,nr-1,0,nc);

    int scelta = 0;
    printf("Formato soottomatrice: ");
    scanf("%d", &scelta);
    while (scelta<=min(nr, nc) && scelta>=1)
    {
        subMats(mat, nr, nc,scelta);
        printf("\n");

        printf("Formato soottomatrice: ");
        scanf("%d", &scelta);
    }

    return 0;
}




