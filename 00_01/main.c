//
// Created by gianluca on 12/10/19.
//

#include <stdio.h>
#define maxn 30

void stampaVet(int v[], int inizio, int fine)
{
    for (int i = inizio; i < fine; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main() {

    int vet[maxn] = {0,0,3,4,5,6,0,0,1,3,4,0,1,0,9,4,2,3,0};
    int c=0;
    int cmax=0;
    //int v[maxn];

    for (int i = 0; i < 19; i++) {
        if(vet[i]!=0)
        {
            c = c+1;
        }
        else
        {
            if (cmax<c) cmax=c;
            c=0;
        }
    }
    printf("%d\n", cmax);
    /*c=0;
    for (int i = 0; i < maxn; i++)
    {
        if (vet[i]!=0)
        {
            v[c]=vet[i];
            c++;
        }
        else {
            if (c == cmax) {
                for (int j = 0; j < cmax; j++) {
                    printf("%d ", v[j]);
                }
                printf("\n");
            }
            c = 0;
        }
    }*/

    // versione senza vettore ausiliario
    int st=0, end=0;
    for (int i = 0; i < 19; i++) {
        if (vet[i]!=0)
        {
            if (vet[i-1]==0) {
                st = i;
            }
        }
        else
        {
            if (vet[i-1]!=0 && i!=0)
            {
                end = i;
                if((end-st)==cmax)
                {
                    stampaVet(vet, st, end);
                }
            }
        }
    }
    return 0;
}
