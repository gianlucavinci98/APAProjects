//
// Created by gianluca on 24/11/19.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR 20
#define NMENU 9

typedef enum {VUOTA, DATA, CODICE, PARTENZA, ARRIVO} key;

typedef struct {int g,m,a;} date;
typedef struct {int h,m,s;} time;
typedef struct
{
    char *cod, *part, *dest;
    char *dataStr, *oraPStr, *oraAStr;
    time oraA, oraP;
    date data;
    int ritardo;
} voce;
typedef struct
{
    voce **ordC, **ordD, **ordP, **ordA;
} vetOrd; //struct wrapper che contiene tutti i vettori ordinamento

int confrontaData(date d1, time o1, date d2, time o2) {
    int data1 = d1.a * 10000 + d1.m * 100 + d1.g;
    int data2 = d2.a * 10000 + d2.m * 100 + d2.g;
    if (data1 < data2) return -1;
    else if (data1 > data2) return 1;
    else {
        int ora1 = o1.h * 3600 + o1.m * 60 + o1.s;
        int ora2 = o2.h * 3600 + o2.m * 60 + o2.s;
        if (ora1 < ora2) return -1;
        else if (ora1 > ora2) return 1;
        else return 0;
    }
}
int itemLT(voce v1, voce v2, key k) {
    switch (k) {
        case DATA:
            return (confrontaData(v1.data, v1.oraA, v2.data, v2.oraA) < 0) ? 1 : 0;
        case CODICE:
            return (strcmp(v1.cod, v2.cod) < 0) ? 1 : 0;
        case PARTENZA:
            return (strcmp(v1.part, v2.part) < 0) ? 1 : 0;
        case ARRIVO:
            return (strcmp(v1.dest, v2.dest) < 0) ? 1 : 0;
        default:
            break;
    }
}
void insertionSort(voce *vet[], int nvoci, key k) {
    for (int i = 1; i < nvoci; i++) {
        int j = i - 1;
        voce *x = vet[i];
        while (j >= 0 && itemLT(*x, *vet[j], k)) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = x;
    }
}
int leggiLog(voce **log, vetOrd *vet, char *file)
{
    char codT[STR], partT[STR], destT[STR], dataT[STR], oraPT[STR], oraAT[STR];
    FILE *fp;
    fp = fopen(file, "r");
    int nvoci;
    fscanf(fp,"%d", &nvoci);
    voce *logT = malloc(nvoci* sizeof(voce));
    for (int i = 0; i < nvoci; i++) {
        fscanf(fp, "%s %s %s %s %s %s %d", codT,partT,destT,dataT,oraPT, oraAT, &logT[i].ritardo);
        logT[i].cod=strdup(codT);
        logT[i].part=strdup(partT);
        logT[i].dest=strdup(destT);
        logT[i].dataStr=strdup(dataT);
        logT[i].oraPStr=strdup(oraPT);
        logT[i].oraAStr=strdup(oraAT);
        sscanf(logT[i].dataStr,"%d/%d/%d", &logT[i].data.a, &logT[i].data.m, &logT[i].data.g);
        sscanf(logT[i].oraPStr, "%d:%d:%d",&logT[i].oraP.h, &logT[i].oraP.m, &logT[i].oraP.s);
        sscanf(logT[i].oraAStr, "%d:%d:%d",&logT[i].oraA.h, &logT[i].oraA.m, &logT[i].oraA.s);
    }

    vet->ordP=malloc(nvoci* sizeof(voce*));
    vet->ordA=malloc(nvoci* sizeof(voce*));
    vet->ordD=malloc(nvoci* sizeof(voce*));
    vet->ordC=malloc(nvoci* sizeof(voce*));

    for (int i = 0; i < nvoci; i++) {
        vet->ordP[i]=&logT[i];
        (*vet).ordA[i]=&logT[i];
        (*vet).ordD[i]=&logT[i];
        (*vet).ordC[i]=&logT[i];
    }

    insertionSort(vet->ordP, nvoci, PARTENZA);
    insertionSort((*vet).ordA, nvoci, ARRIVO);
    insertionSort((*vet).ordD, nvoci, DATA);
    insertionSort((*vet).ordC, nvoci, CODICE);

    *log=logT;
    return nvoci;
}
void stampaVoce(voce v, FILE *fp)
{
    fprintf(fp,"%s %s-%s %s ", v.cod,v.part,v.dest,v.dataStr);
    fprintf(fp,"%s-%s rit: %d minut%c\n",v.oraPStr,v.oraAStr,v.ritardo,(v.ritardo==1)?'o':'i');
}
void stampaLog(voce *vet[], int nvoci, FILE *fp)
{
    for (int i = 0; i < nvoci; i++) {
        stampaVoce(*(vet[i]), fp);
    }
}
void stampaMenu(char **menu)
{
    for (int i = 0; i < NMENU; i++) {
        printf("%d -> %s\n",i,menu[i]);
    }
    printf("Scelta: ");
}
void ricercaBin(voce **vet, int nvoci, char* string)
{
    int trovato = 0;
    int l=0, r=nvoci-1, m;
    int i=0, j=0;
    while(l<=r && !trovato)
    {
        m = (l+r)/2;
        if(strncmp(vet[m]->part,string, strlen(string))==0)
        {
            trovato = 1;
            i=m;
            j=m-1;
        }
        else
        {
            if(strncmp(vet[m]->part,string, strlen(string))>0) r = m-1;
            else l = m+1;
        }
    }
    if(trovato)
    {
        while(strncmp(vet[i]->part,string, strlen(string))==0 && i<nvoci)
        {
            stampaVoce(*vet[i], stdout);
            i++;
        }
        while(j>=0 && strncmp(vet[j]->part,string, strlen(string))==0)
        {
            stampaVoce(*vet[j], stdout);
            j--;
        }
    }
    else printf("Valore non trovato\n");
}
void libera(voce *log, vetOrd vet, int nvoci)
{
    for (int i = 0; i < nvoci; i++) {
        free(log[i].oraAStr);
        free(log[i].oraPStr);
        free(log[i].dataStr);
        free(log[i].dest);
        free(log[i].part);
        free(log[i].cod);
    }
    free(log);
    free(vet.ordP);
    free(vet.ordC);
    free(vet.ordD);
    free(vet.ordA);
}

int main()
{
    voce *log;
    vetOrd vet;
    int nvoci, scelta;
    char file[STR];
    char *menu[] = {
            "Stampa a video",
            "Stampa su file",
            "Ordina per data",
            "Ordina per cod",
            "Ordina per stazione di partenza",
            "Ordina per stazione di arrivo",
            "Ricerca per stazione di partenza",
            "Leggi file",
            "Esci"
    };

    nvoci = leggiLog(&log, &vet, "log.txt");

    do
    {
        stampaMenu(menu);
        scanf("%d", &scelta);
        switch (scelta)
        {
            case 0:
                stampaLog(vet.ordC, nvoci, stdout);
                break;
            case 1:
                printf("Inserisci nome file: ");
                scanf("%s",file);
                FILE *fp = fopen(file, "w");
                stampaLog(vet.ordC, nvoci, fp);
                fclose(fp);
                break;
            case 2:
                stampaLog(vet.ordD, nvoci, stdout);
                break;
            case 3:
                stampaLog(vet.ordC, nvoci, stdout);
                break;
            case 4:
                stampaLog(vet.ordP, nvoci, stdout);
                break;
            case 5:
                stampaLog(vet.ordA, nvoci, stdout);
                break;
            case 6:
                printf("Inserisci stazione: ");
                char staz[STR];
                scanf("%s", staz);
                ricercaBin(vet.ordP, nvoci, staz);
                break;
            case 7:
                printf("Inserisci nome file: ");
                scanf("%s",file);
                leggiLog(&log, &vet, file);
                break;
            case 8:
                break;
            default:
                printf("Comando non valido\n");
                break;
        }
    }while (scelta!=8);

    libera(log, vet, nvoci);

    return 0;
}

