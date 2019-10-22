//
// Created by gianluca on 22/10/19.
//
#include <stdio.h>
#define MAX 10

void ruota(int v[], int p, int dir)
{
    int tmp[MAX];

    if (p>MAX) p = MAX%p;
    if (dir == -1) p = MAX-p;

    int c = 0;
    for(int i=MAX-1; i>=0; i--)
    {
        if (i >= MAX-p)
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

    printf("selettore | indice | direzione | posizioni: ");
    scanf("%d %d %d %d", &sel, &ind, &dir, &pos);
    while(sel!=-1)
    {
        printf("selettore | indice | direzione | posizioni: ");
        scanf("%d %d %d %d", &sel, &ind, &dir, &pos);
    }

    return 0;
}

