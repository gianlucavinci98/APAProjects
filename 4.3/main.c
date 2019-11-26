//
// Created by gianluca on 25/11/19.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 80
char *cercaReg(char* src, char* reg);
int comapareMeta(char c, char* reg, int *salto)
{
    int ris, n;

    switch (reg[0])
    {
        case '.':
            ris = 1;
            n=1;
            break;
        case '\\':
            ris = (reg[1]=='a') ? islower(c) : isupper(c);
            n=2;
            break;
        case '[':
            ris = 0;
            for(n=1; reg[n]!=']'; n++) {
                if (reg[n] == '^') {
                    ris = 1;
                }
                else if (reg[n]==c)
                    ris = !ris;
            }
            n++;
            break;
        default:
            ris = c==reg[0];
            n=1;
            break;
    }

    *salto=n;
    return ris;
}
int compare(char *str, char* reg)
{
    int i, iReg, salto;
    for(i=iReg=0; reg[iReg]!='\0'; i++)
    {
        if (!comapareMeta(str[i], &reg[iReg], &salto)) return 0;
        iReg= iReg+salto;
    }
    return 1;
}

int main()
{
    char testo[MAX] = "pappa toto";
    char reg[MAX] = "foto";

    char *ris = cercaReg(testo, reg);
    printf("%.*s", (int) strlen(testo), ris);

    return 0;
}

char* cercaReg(char* src, char* reg)
{
    int lenSrc;

    lenSrc = strlen(src);
    for (int i = 0; i < lenSrc; i++) { //si potrebbe ridurre sottraendo alla lunghezza della sorgente quella del regEXP
        if(compare(&src[i], reg)) return &src[i];
    }
    return  NULL;
}

