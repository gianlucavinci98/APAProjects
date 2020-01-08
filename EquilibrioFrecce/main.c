//
// Created by gianluca on 27/12/19.
//
#include <stdio.h>
#include <stdlib.h>

void stampaFrecce(int *f, int dim)
{
    char sym[2] = {'>','<'};
    for (int i = 0; i < dim; i++) {
        printf("%c", sym[f[i]]);
    }
}

void invertiSimbolo(int *sym)
{
    *sym = *sym==0 ? 1 : 0;
}
int check(int *sol, int *val, int j, int k)
{
    int cs, cd;
    int ok =1;

    int *freTMP = malloc(k* sizeof(int));
    for (int i = 0; i < k; i++) {
        freTMP[i]=val[i];
    }
    for (int i = 0; i < j; i++) {
        invertiSimbolo(&freTMP[sol[i]]);
    }

    for (int i = 0; i < k && ok;) {
        cd = 0;
        while(freTMP[i]==0 && i<k)
        {
            cd++;
            i++;
        }
        cs = 0;
        while (freTMP[i]==1 && i<k)
        {
            cs++;
            i++;
        }
        if(cs!=cd) ok = 0;
    }

    if(ok)
    {
        stampaFrecce(freTMP, k);
        printf(" -> ");
    }
    free(freTMP);
    return ok;
}
int powerset(int *val, int *sol, int k, int j, int pos, int start)
{
    if(pos==j)
    {
        if(check(sol, val, j, k))
        {
            printf("{ ");
            for (int i = 0; i < j; i++) {
                printf("%d ", sol[i]);
            }
            printf("}\n");
            return 1;
        }
        return 0;
    }
    for (int i = start; i < k; i++) {
        sol[pos]=i;
        if (powerset(val, sol, k, j, pos+1, i+1)) return 1;
    }
    return 0;
}
void powersetW(int * val, int k)
{
    int *sol=calloc((size_t) k, sizeof(int));
    int trovato=0;
    for (int j = 1; j <= k && trovato!=1; j++) {
        trovato=powerset(val, sol, k, j, 0, 0);
    }
}

int main()
{
    int frecce[6] = {0,1,0,0,0,1};
    int n = 6;

    stampaFrecce(frecce, n);
    printf("\n");

    powersetW(frecce, n);

    return 0;
}

