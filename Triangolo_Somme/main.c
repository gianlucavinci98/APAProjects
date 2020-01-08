//
// Created by gianluca on 12/12/19.
//
#include <stdio.h>
#define DIM 5

void triangoloInverso(int *v, int n)
{
    int tmp[DIM];
    if(n==1)
    {
        printf("%d\n", v[0]);
        return;
    }

    for (int i = 0; i < n-1; i++) {
        tmp[i]=v[i]+v[i+1];
    }

    triangoloInverso(tmp, n-1);

    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    return;
}

void triangolo(int *v, int n)
{
    int tmp[DIM];
    if(n==1)
    {
        printf("%d\n", v[0]);
        return;
    }

    for (int i = 0; i < n-1; i++) {
        tmp[i]=v[i]+v[i+1];
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");

    triangolo(tmp, n-1);

    return;
}

int main()
{
    int vet[DIM] = {1,2,3,4,5};

    triangoloInverso(vet, DIM);
    triangolo(vet, DIM);

    return 0;
}

