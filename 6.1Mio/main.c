//
// Created by gianluca on 18/12/19.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int u, v;
} arco;

arco* leggiFile(int *n, int *e)
{
    FILE *fp = fopen("grafo.txt","r");
    arco *ar;
    fscanf(fp,"%d %d",n, e);
    ar = malloc(*e* sizeof(arco));
    for (int i = 0; i < *e; i++) {
        fscanf(fp, "%d %d", &ar[i].u, &ar[i].v);
    }
    return ar;
}
int check(int *sol, int e, arco *a)
{
    int ok = 1;
    for (int i = 0; i<e && ok; i++) {
        if (sol[a[i].u]!=1 && sol[a[i].v]!=1) ok=0;
    }
    return ok;
}
int powerset(int pos, int *sol, int k,int count, int e , arco *a)
{
    if(pos>=k)
    {
        if(check(sol, e, a))
        {
            printf("{ ");
            for (int i = 0; i < k; i++) {
                if(sol[i]!=0) printf("%d ", i);
            }
            printf("}\n");
            return count+1;
        }
        return count;
    }

    sol[pos]=0;
    count = powerset(pos+1, sol, k, count, e, a);
    sol[pos]=1;
    count = powerset(pos+1, sol, k, count, e, a);
    return count;
}

int main()
{
    arco *a;
    int n, e;

    a = leggiFile(&n, &e);
    int *sol = malloc(n*sizeof(int));

    int count = powerset(0, sol, n, 0, e, a);
    printf("Totale soluzioni: %d\n", count);

    return 0;
}

