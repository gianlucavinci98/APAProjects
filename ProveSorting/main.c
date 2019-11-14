#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 100000
#define k 500
void stampa(int v[], int dim)
{
    for (int i = 0; i < dim; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}
void riempi(int vet[])
{
    for (int i = 0; i < DIM; i++) {
        vet[i]=rand()%(k-1)+1;
    }
}
void count(int vet[])
{
    int c[k], b[DIM];

    for (int i = 0; i < k; i++) {
        c[i]=0;
    }

    for (int i = 0; i < DIM; i++) {
        c[vet[i]]++;
    }
    //stampa(c,k);
    for (int i = 1; i < k; i++) {
        c[i]=c[i]+c[i-1];
    }
    //stampa(c, k);

    for (int i = DIM-1; i >= 0; i--) {
        b[c[vet[i]]-1]=vet[i];
        c[vet[i]]--;
    }
    stampa(b, DIM);
}
void copia(int a[], int b[])
{
    for (int i = 0;   i < DIM  ; i++) {
        b[i]=a[i];
    }
}
void selection(int vet[])
{
    int min, tmp;
    for (int i = 0; i < DIM-1; i++) {
        min=i;
        for (int j = i + 1; j < DIM; j++) {
            if (vet[j]<vet[min]) min=j;
        }
        if(min!=i)
        {
            tmp=vet[i];
            vet[i]=vet[min];
            vet[min]=tmp;
        }
    }
}


int main()
{
    int vet[DIM], a[DIM];
    clock_t start,end;
    double tempo;

    riempi(a);
    copia(a, vet);
    stampa(vet, DIM);

    start=clock();
    count(vet);
    end=clock();
    tempo = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Tempo: %f ms\n", tempo*1000);

    copia(a,vet);
    stampa(vet, DIM);
    start=clock();
    selection(vet);
    end=clock(),
            stampa(vet, DIM);
    tempo=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Tempo: %f ms\n", tempo*1000);


    return 0;
}
