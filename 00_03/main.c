//
// Created by gianluca on 13/10/19.
//
#include <stdio.h>
#define MAX 9

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

int main()
{
    int vet[MAX] = {1,2,3,4,5,6,7,8,9};
    int p, dir;

    printf("Inserisci p e dir: ");
    scanf("%d %d", &p, &dir);

    for (int j = 0; j < MAX; j++) {
        printf("%d ", vet[j]);
    }

    ruota(vet, p, dir);

    printf("\n");
    for (int j = 0; j < MAX; j++) {
        printf("%d ", vet[j]);
    }

    return 0;
}

