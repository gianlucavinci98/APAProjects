//
// Created by gianluca on 24/11/19.
//
#include <stdio.h>
#include <string.h>

#define STR 20
#define MAX 100
#define NMENU 8

typedef enum {VUOTA, DATA, CODICE, PARTENZA, ARRIVO} key;

typedef struct {int g,m,a;} date;
typedef struct {int h,m,s;} time;
typedef struct
{
    char cod[STR], part[STR], dest[STR];
    char dataStr[STR], oraPStr[STR], oraAStr[STR];
    time oraA, oraP;
    date data;
    int ritardo;
} voce;

int leggiLog(voce log[])
{
    FILE *fp;
    fp = fopen("log.txt", "r");
    int nvoci;
    fscanf(fp,"%d", &nvoci);
    for (int i = 0; i < nvoci; i++) {
        fscanf(fp, "%s %s %s %s %s %s %d", log[i].cod, log[i].part, log[i].dest,log[i].dataStr, log[i].oraPStr, log[i].oraAStr, &log[i].ritardo);
        sscanf(log[i].dataStr,"%d/%d/%d", &log[i].data.a, &log[i].data.m, &log[i].data.g);
        sscanf(log[i].oraPStr, "%d:%d:%d",&log[i].oraP.h, &log[i].oraP.m, &log[i].oraP.s);
        sscanf(log[i].oraAStr, "%d:%d:%d",&log[i].oraA.h, &log[i].oraA.m, &log[i].oraA.s);
    }
    return nvoci;
}
void stampaVoce(voce v, FILE *fp)
{
    fprintf(fp,"%s %s-%s %s ", v.cod,v.part,v.dest,v.dataStr);
    fprintf(fp,"%s-%s rit: %d minut%c\n",v.oraPStr,v.oraAStr,v.ritardo,(v.ritardo==1)?'o':'i');
}
void stampaLog(voce log[], int nvoci, FILE *fp)
{
    for (int i = 0; i < nvoci; i++) {
        stampaVoce(log[i], fp);
    }
}
void stampaMenu(char **menu)
{
    for (int i = 0; i < NMENU; i++) {
        printf("%d -> %s\n",i,menu[i]);
    }
    printf("Scelta: ");
}
int confrontaData(date d1, time o1, date d2, time o2)
{
    int data1 = d1.a*10000+d1.m*100+d1.g;
    int data2 = d2.a*10000+d2.m*100+d2.g;
    if (data1<data2) return -1;
    else if(data1>data2) return 1;
    else
    {
        int ora1 = o1.h*3600+o1.m*60+o1.s;
        int ora2 = o2.h*3600+o2.m*60+o2.s;
        if (ora1<ora2) return -1;
        else if(ora1>ora2) return 1;
        else return 0;
    }
}
int itemLT(voce v1, voce v2, key k)
{
    switch (k)
    {
        case DATA:
            return (confrontaData(v1.data, v1.oraA, v2.data, v2.oraA)<0) ? 1 : 0;
        case CODICE:
            return (strcmp(v1.cod, v2.cod)<0) ? 1 : 0;
        case PARTENZA:
            return (strcmp(v1.part, v2.part)<0) ? 1 : 0;
        case ARRIVO:
            return (strcmp(v1.dest, v2.dest)<0) ? 1 : 0;
        default:
            break;
    }
}
key insertionSort(voce *log, int nvoci, key k)
{
    for (int i = 1; i < nvoci; i++) {
        int j = i-1;
        voce x = log[i];
        while (j>=0 && itemLT(x, log[j], k))
        {
            log[j+1] = log[j];
            j--;
        }
        log[j+1]=x;
    }
    return k;
}
void ricercaLin(voce *log, int nvoci, char* string)
{
    int trovato = 0;
    for (int i = 0; i < nvoci; i++) {
        if (strstr(log[i].part, string) != NULL)
        {
            stampaVoce(log[i], stdout);
            trovato = 1;
        }
    }
    if(!trovato) printf("Nessun valore trovato\n");
}
void ricercaBin(voce *log, int nvoci, char* string)
{
    int trovato = 0;
    int l=0, r=nvoci-1, m;
    int i, j;
    while(l<=r && !trovato)
    {
        m = (l+r)/2;
        if(strncmp(log[m].part,string, strlen(string))==0)
        {
            trovato = 1;
            i=m;
            j=m-1;
        }
        else
        {
            if(strncmp(log[m].part,string, strlen(string))>0) r = m-1;
            else l = m+1;
        }
    }
    if(trovato)
    {
        while(strncmp(log[i].part,string, strlen(string))==0)
        {
            stampaVoce(log[i], stdout);
            i++;
        }
        while(strncmp(log[j].part,string, strlen(string))==0)
        {
            stampaVoce(log[j], stdout);
            j--;
        }
    }
    else printf("Valore non trovato\n");
}

int main()
{
    voce log[MAX];
    int nvoci, scelta;
    key k = VUOTA;
    char file[STR];
    char *menu[] = {
            "Stampa a video",
            "Stampa su file",
            "Ordina per data",
            "Ordina per cod",
            "Ordina per stazione di partenza",
            "Ordina per stazione di arrivo",
            "Ricerca per stazione di partenza",
            "Esci"
    };

    nvoci = leggiLog(log);

    do
    {
        stampaMenu(menu);
        //printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta)
        {
            case 0:
                stampaLog(log, nvoci, stdout);
                break;
            case 1:
                printf("Inserisci nome file: ");
                scanf("%s",file);
                FILE *fp = fopen(file, "w");
                stampaLog(log, nvoci, fp);
                fclose(fp);
                break;
            case 2:
                k=insertionSort(log,nvoci, DATA);
                stampaLog(log, nvoci, stdout);
                break;
            case 3:
                k=insertionSort(log,nvoci, CODICE);
                stampaLog(log, nvoci, stdout);
                break;
            case 4:
                k=insertionSort(log,nvoci, PARTENZA);
                stampaLog(log, nvoci, stdout);
                break;
            case 5:
                k=insertionSort(log,nvoci, ARRIVO);
                stampaLog(log, nvoci, stdout);
                break;
            case 6:
                printf("Inserisci stazione: ");
                char staz[STR];
                scanf("%s", staz);
                if(k==PARTENZA) ricercaBin(log, nvoci, staz);
                else ricercaLin(log, nvoci, staz);
                break;
            case 7:
                break;
            default:
                printf("Comando non valido\n");
                break;
        }
    }while (scelta!=7);

    return 0;
}

