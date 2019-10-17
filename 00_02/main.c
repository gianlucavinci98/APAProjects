#include <stdio.h>
#include <string.h>

int isVoc(char l)
{
    int res = 0;

    switch (l)
    {
        case 'a':
            res++;
            break;
        case 'A':
            res++;
            break;
        case 'e':
            res++;
            break;
        case 'E':
            res++;
            break;
        case 'i':
            res++;
            break;
        case 'I':
            res++;
            break;
        case 'o':
            res++;
            break;
        case 'O':
            res++;
            break;
        case 'u':
            res++;
            break;
        case 'U':
            res++;
            break;
        default:
            res =0;
            break;
    }
    return res;
}

int conta(char word[], int n)
{
    int len;
    int nvoc;
    int cont = 0;

    len = strlen(word);

    for (int i = 0; i < (len - n+1); i++) {
        nvoc = 0;
        for (int c = i; c < i+n; c++) {
            if (isVoc(word[c])) nvoc++;
        }
        if (nvoc==2) cont++;
    }

    return cont;
}

int main()
{
    char nomeFile[100];
    char parola[20];
    int nword;
    int subs;

    printf("Inserisci nome file: ");
    scanf("%s", nomeFile);
    printf("Inserisci grandezza subs: ");
    scanf("%d",&subs);

    FILE *fp;
    fp = fopen(nomeFile, "r");

    fscanf(fp,"%d", &nword);

    while (fscanf(fp,"%s", parola)!=EOF)
    {
        printf("%s ", parola);
        printf("%d\n", conta(parola, subs));
    }

    fclose(fp);

    return 0;
}
