//
// Created by gianluca on 22/10/19.
//
#include <stdio.h>
#include <string.h>

#define MAXWORD 50
#define MAXDIZ 30

typedef struct {
    char word[MAXWORD];
    char token[MAXWORD];
} Entry;

int caricaDizionario(Entry diz[])
{
    FILE *in;
    in = fopen("dizionario.txt", "r");
    int entries;
    fscanf(in, "%d", &entries);
    for (int i = 0; i < entries; i++) {
        fscanf(in, "%s %s", diz[i].token, diz[i].word);
    }
    fclose(in);
    return entries;
}
int conforntaParola(char str[], int pos, Entry diz[], int nd)
{
    int trovato = 0;
    int j=0, c, ok;

    while (trovato==0 && j<nd)
    {
        c=0;
        ok=1;
        while (ok==1 && c<strlen(diz[j].word))
        {
            if (str[pos+c] != diz[j].word[c])
            {
                ok=0;
            }
            c++;
        }
        if(ok==1) trovato=1;
        j++;
    }

    if (trovato==0) return -1;
    else return j-1;
}
void processaRiga(char *str, Entry *diz, int nd)
{
    int i=0;
    int match = -1;

    FILE *fp;
    fp = fopen("compresso.txt", "a");

    while (i<strlen(str))
    {
        match = conforntaParola(str, i, diz, nd);
        if (match==-1){
            fprintf(fp, "%c", str[i]);
            printf("%c", str[i]);
        }
        else
        {
            fprintf(fp, "%s", diz[match].token);
            printf("%s", diz[match].token);
            i = (int) (i + strlen(diz[match].word) - 1);
        }
        i++;
    }
    fclose(fp);
}

int main()
{
    Entry diz[MAXDIZ];
    int nd = caricaDizionario(diz);
    char riga[80];

    FILE *in;
    in = fopen("sorgente.txt", "r");

    while (fgets(riga, 80, in)!=NULL)
    {
        processaRiga(riga, diz, nd);

    }

    fclose(in);
    return 0;
}

