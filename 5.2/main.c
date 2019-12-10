//
// Created by gianluca on 25/11/19.
//
#include <stdlib.h>
#include <stdio.h>

int **malloc2dR(int *nr, int *nc, FILE *fp) {
    int i, j, **m;
    fscanf(fp, "%d %d", nr, nc);
    m = (int**) calloc((size_t) *nr, sizeof(int*));
    for (i=0; i<*nr; i++) {
        m[i] = (int*) calloc((size_t) *nc, sizeof(int));
        for (j=0; j<*nc; j++)
            fscanf(fp, "%d", &m[i][j]);
    }
    return m;
}

void split(int **m, int nr, int nc, int **b, int **n, int *nb, int *nn) {
    int i, j, contaB = 0, contaN = 0, sq = nr * nc;
    *nb = sq / 2;
    *nn = sq / 2 + sq % 2;
    *b = (int*) calloc((size_t) *nb, sizeof(int));
    *n = (int*) calloc((size_t) *nn, sizeof(int));
    for(i=0;i<nr;i++) {
        for(j=0;j<nc;j++) {
            if ((i+j)%2) {
                (*b)[contaB++] = m[i][j];
            } else
                (*n)[contaN++] = m[i][j];
        }
    }
}

void stampa(int *vett, int n) {
    int i;
    for(i=0;i<n;i++)
        printf("%d ", vett[i]);
    printf("\n");
}

int main(int argc, char **argv) {
    int **mat, *w, *b, nr, nc, nw, nb;
    FILE *fp = fopen("mat.txt", "r");
    mat = malloc2dR(&nr, &nc, fp);
    fclose(fp);

    split(mat, nr, nc, &w, &b, &nw, &nb);
    printf("Bianche\n");
    stampa(w, nw);
    printf("Nere\n");
    stampa(b, nb);

    free(w);
    free(b);

    return 0;
}

