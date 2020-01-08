//
// Created by gianluca on 13/12/19.
//
#include <stdio.h>
#include <stdlib.h>

int** allocaMat(int *nr, int *nc)
{
    FILE *fp=fopen("mat.txt", "r");
    fscanf(fp,"%d %d", nr, nc);
    int** mat = malloc(*nr * sizeof(int*));
    for (int i = 0; i < *nr; i++) {
        mat[i]=malloc(*nc* sizeof(int));
        for (int j = 0; j < *nc; j++) {
            fscanf(fp,"%d", &mat[i][j]);
        }
    }
    return mat;
}
void allocaMatP(int *nr, int *nc, int ***mat)
{
    FILE *fp=fopen("mat.txt", "r");
    fscanf(fp, "%d %d", nr, nc);
    int **m=malloc(*nr* sizeof(int*));
    for (int i = 0; i < *nr; i++) {
        m[i]=malloc(*nc* sizeof(int));
        for (int j = 0; j < *nc; j++) {
            fscanf(fp, "%d", &m[i][j]);
        }
    }
    *mat=m;
}
void separa(int **m, int nr, int nc, int **vb, int **vn, int *nb,int *nn)
{
    int contaN=0, contaB=0;
    *nb = (nr*nc)/2;
    *nn = (nr*nc)/2 + (nr*nc)%2;
    *vb = malloc(*nb * sizeof(int));
    *vn = malloc(*nn * sizeof(int));
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if((i+j)%2==0) (*vn)[contaN++]=m[i][j];
            else (*vb)[contaB++]=m[i][j];
        }
    }
}
void stampaVet(int *v, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}
void libera(int **m, int nr)
{
    for (int i = 0; i < nr; i++) {
        free(m[i]);
    }
    free(m);
}

int main()
{
    int nr, nc;
    int **m;
    int *vb, *vn, nn, nb;

    allocaMatP(&nr, &nc, &m);
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    separa(m,nr, nc, &vb, &vn, &nb, &nn);
    stampaVet(vn,nn);
    stampaVet(vb, nb);
    libera(m, nr);
    free(vb);
    free(vn);


    return 0;
}

