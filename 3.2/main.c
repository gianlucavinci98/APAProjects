//
// Created by gianluca on 29/10/19.
//
#include<stdlib.h>
#include<stdio.h>

int checkBigEndian() {
    int test = 1;
    char *pchar = (char *)&test;
    return (*pchar == 0);
}

int nBitEsponente(int size) {
    switch (size) {
        case 4: return 8;   //float
        case 8: return 11;  //double
        default: return 15; //long double
    }
}

int Padding (int size, int bigEndian) {
    if (size>8 && !bigEndian) {
        int size_tmp;
        long double a = 1.0, b = -a;
        unsigned char *pa=(unsigned char *)&a, *pb=(unsigned char *)&b;
        for (size_tmp=0; size_tmp < size && pa[size_tmp] == pb[size_tmp]; size_tmp++);
        if (size_tmp < size) {
            printf("Padding di %d byte\n", size - size_tmp - 1);
            size = size_tmp + 1;
            printf("Dimensioni + padding: %d\n", size);
        }
    }
    return size;
}

int estraiBit(unsigned char *bytes, int iBit) {
    int indByte = iBit / 8;

    unsigned char mask = 0x01 << (iBit%8);
    int bit = ((bytes[indByte] & mask) == 0) ? 0 : 1;

    return bit;
}

void stampaCodifica (void *p, int size, int bigEndian) {
    int i, nExpBits, nBits;
    unsigned char *pchar = p;

    size = Padding(size, bigEndian);

    nBits = size*8;
    nExpBits = nBitEsponente(size);

    printf("bit di segno : %d\n", estraiBit(pchar,nBits-1));
    printf("esponente    : ");
    for (i=nBits-2; i>nBits-2-nExpBits; i--)
        printf("%d", estraiBit(pchar,i));
    printf("\nmantissa     : ");
    for (i=nBits-2-nExpBits; i>=0; i--)
        printf("%d", estraiBit(pchar,i));
    printf("\n");
}

int main(int argc, char *argv[]) {

    float af;
    double ad;
    long double ald;

    int bigE = checkBigEndian();
    if(bigE) printf ("BIG ENDIAN\n");
    else printf ("LITTLE ENDIAN\n");

    printf("af: %d\nad: %d\nald: %d\n", (int)sizeof(af), (int)sizeof(ad), (int)sizeof(ald));

    printf("Numero reale: ");
    scanf("%f", &af);

    ad = (double)af;
    ald = (long double)af;

    printf("\ncodifica float:\n");
    stampaCodifica((void *)&af, sizeof(af), bigE);

    printf("\ncodifica double:\n");
    stampaCodifica((void *)&ad, sizeof(ad), bigE);

    printf("\ncodifica long double:\n");
    stampaCodifica((void *)&ald, sizeof(ald), bigE);

    return 0;
}



