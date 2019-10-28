//
// Created by gianluca on 22/10/19.
//
#include <stdio.h>
#define MAX 10

void ruota(int v[], int p, int dir, int dim)
{
    int tmp[dim];

    if (p>dim) p = p%dim;
    if (dir == -1) p = dim-p;

    int c = 0;
    for(int i=dim-1; i>=0; i--)
    {
        if (i >= dim-p)
        {
            tmp[c] = v[i];
            c++;
        }
        else v[i+p]=v[i];
    }
    p--;
    c=0;
    for(int i=p; i>=0; i--)
    {
        v[i]=tmp[c];
        c++;
    }
}
void stampaMat(int mat[][MAX], int nr, int nc)
{
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
void stampaVet(int vet[], int d)
{
    for (int i = 0; i < d; i++) {
        printf("%d ", vet[i]);
    }
}
void linearizza(int mat[][MAX], int vet[], int ind, int dim)
{
    for (int i = 0; i < dim; i++) {
        vet[i]=mat[i][ind];
    }
}
void normalizza(int vet[], int mat[][MAX], int ind, int dim)
{
    for (int i = 0; i < dim; i++) {
        mat[i][ind]=vet[i];
    }
}

int main()
{
    FILE *fp;
    int mat[MAX][MAX];
    int nr, nc;
    int sel, ind, pos, dir;

    fp = fopen("file.txt", "r");
    fscanf(fp, "%d %d", &nr, &nc);
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
    fclose(fp);

    stampaMat(mat, nr, nc);

    printf("selettore: ");
    scanf("%d", &sel);
    while(sel!=-1)
    {
        printf("indice | direzione | posizioni: ");
        scanf("%d %d %d", &ind, &dir, &pos);
        if (sel==0)
        {
            ruota(mat[ind], pos, dir, nc);
        }
        else
        {
            int tmp[MAX];
            linearizza(mat, tmp, ind, nr);
            ruota(tmp, pos, dir, nr);
            normalizza(tmp, mat, ind, nr);
        }

        stampaMat(mat, nr, nc);

        printf("selettore: ");
        scanf("%d", &sel);
    }

    return 0;
}

