//
// Created by gianluca on 26/11/19.
//
#include<stdlib.h>
#include<stdio.h>


typedef struct {
    int u;
    int v;
} arco;

int powerset(int pos, int *sol, int N, int E, arco *a, int count);

arco *leggiFile(char *nomeFile, int *N, int *E) {
    int i;
    arco *a;
    FILE *in = fopen(nomeFile, "r");

    fscanf(in, "%d %d", N, E);
    a = (arco *)calloc((size_t) *E, sizeof(arco));
    for (i=0; i<*E; i++)
        fscanf(in, "%d %d", &a[i].u, &a[i].v);
    return a;
}

int controllo(int *sol, int E, arco *a) {
    int i, ok=1;

    for (i=0; i<E; i++)
        if ((sol[a[i].u]==0) && (sol[a[i].v]==0))
            ok = 0;
    return ok;
}

int main() {
    int cnt, N = -1, E = -1, *sol;
    arco *a = leggiFile("grafo.txt", &N, &E);

    sol = calloc((size_t) N, sizeof(int));

    printf("Vertex cover\n");
    cnt = powerset(0, sol, N, E, a, 0);
    printf ("numero di soluzioni: %d \n", cnt);

    free(sol);
    free(a);

    return 0;
}

int powerset(int pos, int *sol, int N, int E, arco *a, int count) {
    int i;
    if (pos >= N) {
        if (controllo(sol, E, a) == 1) {
            printf("{ ");
            for (i=0; i<N; i++)
                if (sol[i]==1)
                    printf("%d ", i);
            printf("}\n");
            return count+1;
        }
        return count;
    }

    sol[pos] = 0;
    count = powerset(pos + 1, sol, N, E, a, count);
    sol[pos] = 1;
    count = powerset(pos + 1, sol, N, E, a, count);
    return count;
}

