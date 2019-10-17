//
// Created by gianluca on 17/10/19.
//
#include <stdio.h>

#define DIM 20

int min(int n1, int n2) {
    if(n1<n2) return n1;
    else n2;
}

void stampaMat(int m[][DIM], int rigSt, int rigEnd,int colSt, int colEnd)
{
    for (int i = rigSt; i <= rigEnd; i++) {
        for (int j = colSt; j <= colEnd; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
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

    stampaMat(mat,0,nr-1,0,nc);

    int scelta = 0;
    printf("Formato soottomatrice: ");
    scanf("%d", &scelta);
    while (scelta<=min(nr, nc) && scelta>=1)
    {
        printf("Formato soottomatrice: ");
        scanf("%d", &scelta);
    }

    return 0;
}




