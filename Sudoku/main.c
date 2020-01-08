//
// Created by gianluca on 06/01/20.
//
#include <stdio.h>
#include <stdlib.h>

#define dim 9

int disposizioni(int pos, int **tab);
int check(int **tab, int k, int i, int j);
int** carica()
{
    int **schema;
    schema = malloc(dim* sizeof(int*));
    for (int i = 0; i < dim; i++) {
        schema[i]=malloc(dim* sizeof(int));
    }

    FILE *fp = fopen("sudoku.txt", "r");
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            fscanf(fp, "%1d", &schema[i][j]);
        }
    }
    fclose(fp);
    return schema;
}
void stampa(int **schema)
{
    for (int i = 0; i < dim; i++) {
        if(i%3==0 && i!=0) printf("------|-------|------\n");
        for (int j = 0; j < dim; j++) {
            if(j%3==0 && j!=0)printf("| ");
            printf("%d ", schema[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int **tab;

    tab = carica();
    stampa(tab);

    printf("Soluzione: \n");
     disposizioni(0, tab);

    return 0;
}

int disposizioni(int pos, int **tab)
{
    if(pos>=dim*dim)
    {
        stampa(tab);
        return 1;
    }

    int i = pos/dim;
    int j = pos%dim;
    if (tab[i][j]!=0)
    {
        return disposizioni(pos+1, tab);
    }

    for (int k = 1; k <= dim; k++) {
        tab[i][j]=k;
        if (check(tab, k, i, j))
        {
            if(disposizioni(pos+1, tab)) return 1;
        }
        tab[i][j]=0;
    }
    return 0;
}

int check(int **tab, int k, int i, int j)
{
    int c, r;

    for(c=0; c<dim; c++)
    {
        if(c!=j && tab[i][c]==k) return 0;
    }
    for(r=0; r<dim; r++)
    {
        if(r!=i && tab[r][j]==k) return 0;
    }
    for(r=(i/3)*3; r<3; r++)
    {
        for(c=(j/3)*3; c<3; c++)
        {
            if(r!=i || c!=j)
            {
                if(tab[r][c]==k) return 0;
            }
        }
    }
    return 1;
}

