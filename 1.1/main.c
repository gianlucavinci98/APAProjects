//
// Created by gianluca on 21/10/19.
//
#include <stdio.h>
#define DIM 20

void calcolaGiornata(int mat[][DIM], int squadre, int giornata, int punti[])
{
    for (int i = 0; i < squadre; i++) {
        punti[i]+=mat[i][giornata];
    }
}

int trovaCapolista(int punti[], int squadre)
{
    int capo = 0;
    int max = 0;
    for (int i = 0; i < squadre; i++) {
        if(punti[i]>max)
        {
            max=punti[i];
            capo = i;
        }
    }
    return capo;
}

int main()
{
    int nteam,ngior;
    int mat[DIM][DIM];
    int punti[DIM] = {0};

    FILE *fp;
    fp = fopen("camp.txt","r");
    fscanf(fp,"%d %d", &nteam, &ngior);
    for (int i = 0; i < nteam; i++) {
        for (int j = 0; j < ngior; j++) {
            fscanf(fp, "%d",&mat[i][j]);
        }
    }
    fclose(fp);

    for (int i = 0; i < nteam; i++) {
        for (int j = 0; j < ngior; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (int j = 0; j < ngior; j++) {
        calcolaGiornata(mat, nteam, j, punti);
        printf("Capolista giornata %d: %d\n", j+1,  trovaCapolista(punti, nteam));
    }

    return 0;
}
