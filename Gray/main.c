//
// Created by gianluca on 20/11/19.
//
#include <stdio.h>
#define MAXBIT 8
#define MAXCODE 256

int pow2(int e) {
    return 1 << e;
}

void resetCodici(int cod[][MAXBIT], int nbit)
{
    int ncode=pow2(nbit);
    for (int i = 0; i < ncode; i++) {
        for (int j = 0; j < nbit; j++) {
            cod[i][j]=0;
        }
    }
}
void stampaCodici(int cod[][MAXBIT], int nbit)
{
    int ncode = pow2(nbit);

    for (int i = 0; i < ncode; i++) {
        for (int j = 0; j < nbit; j++) {
            printf("%d ", cod[i][j]);
        }
        printf("\n");
    }
}

void gray1(int cod[][MAXBIT], int pos, int nbit)
{
    int nb = nbit-pos;
    int ncode = pow2(nb);

    if (pos==nbit-1)
    {
        cod[0][pos]=0;
        cod[1][pos]=1;
        return;
    }

    gray1(cod, pos+1, nbit);

    for (int i = 0; i < ncode / 2; i++) {
        cod[i][pos]=0;
        cod[i+(ncode/2)][pos]=1;
        for (int j = 0; j < nbit - 1; j++) {
            cod[ncode-i-1][pos+j+1]=cod[i][pos+j+1];
        }
    }
}

int main()
{
    int codici[MAXCODE][MAXBIT];

    int nbit=3;

    resetCodici(codici, nbit);

    gray1(codici, 0, nbit);

    stampaCodici(codici, nbit);

    return 0;
}

