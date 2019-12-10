//
// Created by gianluca on 25/11/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR      30
#define NSCELTE 9

typedef enum {DATA, CODICE, PARTENZA, ARRIVO} key;

typedef struct {
    int a;
    int m;
    int g;
} date;
typedef struct {
    int h;
    int m;
    int s;
} time;

typedef struct {
    char *cod;
    char *part;
    char *dest;
    char *data_str;
    char *orap_str;
    char *orad_str;
    int ritardo;
    date data;
    time p, d;
} voce;

typedef struct {
    int n_voci;
    voce *log;
    voce **logC, **logD, **logP, **logA;
} tabella_t;

tabella_t *leggiTabella(char *file);
void liberaTabella(tabella_t *tab);
int comparaData(date d1, date d2);
void stampa(tabella_t *tab, key k, char* file);
void stampaMenu(char *scelte[], int *selezione);
void stampaEntry(voce riga, FILE *fp);
void ordinaStabile(voce **v, int n_voci, key k);
void ricercaBin(tabella_t *tab, char* partenza, int nCharConfronto);

int main(int argc, char** argv) {

    char *scelte[] = {
            "Uscita",
            "Leggi file",
            "Stampa a video",
            "Stampa su file",
            "Ordina per data",
            "Ordina per codice",
            "Ordina per stazione di partenza",
            "Ordina per stazione di arrivo",
            "Ricerca per stazione di partenza"
    };

    tabella_t *tab;
    char staz[STR];
    int scelta, lun;
    char nomeFile[STR];

    tab = leggiTabella("log.txt");

    do {
        stampaMenu(scelte, &scelta);
        switch(scelta) {
            case 0:
                break;
            case 1:
                printf("Inserire nome file\n");
                scanf("%s",nomeFile);
                liberaTabella(tab);
                tab = leggiTabella(nomeFile);
                break;
            case 2:
                stampa(tab, CODICE, NULL);
                break;
            case 3:
                printf("Inserire nome file\n");
                scanf("%s",nomeFile);
                stampa(tab, CODICE, nomeFile);
                break;
            case 4:
                printf("Elenco ordinato per data\n");
                stampa(tab, DATA, NULL);
                break;
            case 5:
                printf("Elenco ordinato per cod\n");
                stampa(tab, CODICE, NULL);
                break;
            case 6:
                printf("Elenco ordinato per partenza\n");
                stampa(tab, PARTENZA, NULL);
                break;
            case 7:
                printf("Elenco ordinato per arrivo\n");
                stampa(tab, ARRIVO, NULL);
                break;
            case 8:
                printf("Inserire stazione di partenza: ");
                scanf("%s%n", staz, &lun);
                ricercaBin(tab, staz, lun - 1);
                break;
            default:
                printf("Scelta non valida\n");
                break;
        }
    } while(scelta!=0);

    liberaTabella(tab);
    return 0;
}

int comparaData(date d1, date d2) {
    if (d1.a != d2.a)
        return (d1.a-d2.a);
    else if (d1.m != d2.m)
        return (d1.m-d2.m);
    else if (d1.g != d2.g)
        return (d1.g-d2.g);
    else return 0;
}
int comparaOra(time o1, time o2) {
    if (o1.h != o2.h)
        return (o1.h-o2.h);
    else if (o1.m != o2.m)
        return (o1.m-o2.m);
    else if (o1.s != o2.s)
        return (o1.s-o2.s);
    else return 0;
}
void stampaMenu(char *scelte[], int *selezione) {
    int i=0;
    printf("\nMENU'\n");
    for(i=0; i < NSCELTE; i++) printf("%2d > %s\n", i, scelte[i]);
    scanf(" %d",selezione);
}
void liberaTabella(tabella_t *tab) {
    int i;
    if (tab == NULL)
        return;
    if (tab->logA) free(tab->logA);
    if (tab->logC) free(tab->logC);
    if (tab->logD) free(tab->logD);
    if (tab->logP) free(tab->logP);
    if (tab->log) {
        for(i=0;i<tab->n_voci;i++) {
            if (tab->log[i].cod) free(tab->log[i].cod);
            if (tab->log[i].part) free(tab->log[i].part);
            if (tab->log[i].dest) free(tab->log[i].dest);
            if (tab->log[i].data_str) free(tab->log[i].data_str);
            if (tab->log[i].orap_str) free(tab->log[i].orap_str);
            if (tab->log[i].orad_str) free(tab->log[i].orad_str);
        }
        free(tab->log);
    }
    free(tab);
}
tabella_t *leggiTabella(char *file) {
    int i;
    char tmpCodice[STR], tmpPart[STR], tmpDest[STR], tmpData[STR], tmpOraP[STR], tmpOraD[STR];
    tabella_t *tab = calloc(1, sizeof(tabella_t));
    FILE *in = fopen(file, "r");

    fscanf(in, "%d", &(tab->n_voci));
    tab->log = calloc((size_t) tab->n_voci, sizeof(voce));
    tab->logA = calloc((size_t) tab->n_voci, sizeof(voce*));
    tab->logC = calloc((size_t) tab->n_voci, sizeof(voce*));
    tab->logD = calloc((size_t) tab->n_voci, sizeof(voce*));
    tab->logP = calloc((size_t) tab->n_voci, sizeof(voce*));

    for (i=0; i<tab->n_voci; i++) {
        fscanf(in, "%s %s %s %s %s %s %d\n", tmpCodice, tmpPart, tmpDest, tmpData, tmpOraP, tmpOraD, &tab->log[i].ritardo);
        tab->log[i].cod = strdup(tmpCodice);
        tab->log[i].part = strdup(tmpPart);
        tab->log[i].dest = strdup(tmpDest);
        tab->log[i].data_str = strdup(tmpData);
        tab->log[i].orap_str = strdup(tmpOraP);
        tab->log[i].orad_str = strdup(tmpOraD);
        sscanf (tab->log[i].data_str,"%d/%d/%d", &tab->log[i].data.a,&tab->log[i].data.m,&tab->log[i].data.g);
        sscanf (tab->log[i].orap_str,"%d:%d:%d", &tab->log[i].p.h,&tab->log[i].p.m,&tab->log[i].p.s);
        sscanf (tab->log[i].orad_str,"%d:%d:%d", &tab->log[i].d.h,&tab->log[i].d.m,&tab->log[i].d.s);
    }

    for(i=0;i<tab->n_voci;i++) {
        tab->logA[i] = &tab->log[i];
        tab->logC[i] = &tab->log[i];
        tab->logD[i] = &tab->log[i];
        tab->logP[i] = &tab->log[i];
    }

    ordinaStabile(tab->logA, tab->n_voci, ARRIVO);
    ordinaStabile(tab->logC, tab->n_voci, CODICE);
    ordinaStabile(tab->logD, tab->n_voci, DATA);
    ordinaStabile(tab->logP, tab->n_voci, PARTENZA);

    return tab;
}
void stampa(tabella_t *tab, key k, char* file) {
    FILE *fp;
    int i;
    if(file == NULL)
        fp = stdout;
    else
        fp = fopen(file,"w");

    switch(k) {
        case CODICE:
            for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logC[i]), fp);
            break;
        case DATA:
            for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logD[i]), fp);
            break;
        case ARRIVO:
            for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logA[i]), fp);
            break;
        case PARTENZA:
            for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logP[i]), fp);
            break;
        default:
            for(i=0; i<tab->n_voci; i++) stampaEntry(*(tab->logC[i]), fp);
    }

    if(file!=NULL)
        fclose(fp);
}
void stampaEntry(voce v, FILE *fp) {
    fprintf(fp, "%s %s %s %s %s %s %d\n", v.cod, v.part, v.dest, v.data_str, v.orap_str, v.orad_str, v.ritardo);
}
int confrontaVoci(voce *v1, voce *v2, key k) {
    switch(k) {
        case DATA: {
            int cmp = comparaData(v1->data, v2->data);
            if (cmp == 0) return comparaOra(v1->p, v2->p);
            return cmp;
        }
        case CODICE: {
            return strcmp(v1->cod, v2->cod);
        }
        case PARTENZA: {
            return strcmp(v1->part, v2->part);
        }
        case ARRIVO: {
            return strcmp(v1->dest, v2->dest);
        }
        default: {
        } break;
    }
    return 0;
}
void ordinaStabile(voce **v, int n_voci, key k) {
    int i, j;
    int l = 0, r = n_voci-1;
    voce *x;

    for(i=l+1; i<=r; i++) {
        x = v[i];
        j = i-1;
        while(j>=l && confrontaVoci(x, v[j], k) < 0) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = x;
    }
}

void ricercaBin(tabella_t *tab, char *partenza, int nCharConfronto) {
    int iniziale = 0, finale = tab->n_voci - 1, medio, i, j, cmp;
    int trovato = 0;

    while(iniziale <= finale && !trovato) {
        medio = (iniziale + finale) / 2;
        cmp = strncmp(tab->logP[medio]->part, partenza, (size_t) nCharConfronto);
        if(cmp == 0) {
            trovato = 1;
        } else {
            if(cmp < 0)
                iniziale = medio + 1;
            else
                finale = medio - 1;
        }
    }

    if(trovato) {
        i = medio;
        j = medio -1;
        while(i < tab->n_voci && strncmp(tab->logP[i]->part, partenza, (size_t) nCharConfronto) == 0) {
            stampaEntry(*(tab->logP[i]), stdout);
            i++;
        }
        while(j>=0 && strncmp(tab->logP[j]->part, partenza, (size_t) nCharConfronto) == 0) {
            stampaEntry(*(tab->logP[j]), stdout);
            j--;
        }
    } else
        printf("Voce non trovata");
}

