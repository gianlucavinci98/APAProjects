//
// Created by gianluca on 24/11/19.
//
#include <stdio.h>
#define MAXD 7

int maj(int *v, int n);

int main()
{
    int vet[MAXD] = {3, 3, 9, 4, 3, 5, 3};

    int ris = maj(vet, MAXD);
    printf("%d\n", ris);

    return 0;
}

int maj(int *v, int n)
{
    if(n==1) return *v; //Il vettore unitario ha il suo unico elemento come maggioritario

    //Calcolo maggioritario di sinistra
    int ms = maj(v, n/2); // v contiente l'indirizzo prima cella vettore originale (prima cella vettore sx)
    int md = maj(v+(n/2), n/2); //v+(n/2) contiene l'ndirizzo della riga successiva a quella di mezzo (prima cella vettore dx)

    if (ms==-1 && md==-1) return -1; //se entrambi i vettori non hanno l'elemento è inutile cercare
    if (ms == md) return ms; //se i valori sono uguali ovviamente l'elemento sarà un maj

    int cs = 0, cd=0;
    // conta contemporanea di maj sx e dx all'interno del vettore originale
    for (int i = 0; i < n; i++) {
        if (v[i]==ms) cs++;
        if (v[i]==md) cd++;
    }
    if (cs>n/2) return ms; // !!In caso di parità torna sempre il vincitore di sinistra
    if (cd>n/2) return md;
    else return -1;
}

