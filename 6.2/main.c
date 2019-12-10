//
// Created by gianluca on 26/11/19.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN 50
#define NSCELTE 8

typedef struct {
    int gg, mm, aaaa;
} date ;

typedef struct {
    char citta[LEN], via[LEN];
    int cap;
} address;

typedef struct {
    char codice[LEN];
    char nome[LEN], cognome[LEN];
    char ddn_str[LEN];
    date data;
    address indirizzo;
} Item;

typedef struct nodo_s *link;

typedef struct nodo_s {
    Item val;
    link next;
} nodo_t;

enum { falso, vero };
typedef int bool;

Item leggiItem(FILE *fp);
void stampaItem(Item it, FILE *fp);
Item ItemSetVoid(void);
int ItemCheckVoid(Item it);
int comparaData(date d1, date d2);
int stampaMenu(char *scelte[]);
void stampaAnagrafica(link head, char* file);
link carica(link head, char *file);
void freeAnagrafica(link head);
void scanData(char *strData, date *data);
link aggiungi(link head);
Item ricercaCodice(link head, char* codice);
Item elimina(link *head, char* codice);
Item eliminaTraDate(link *head, date d1, date d2);

int main(int argc, char **argv) {

    char *scelte[] = {
            "Fine",
            "Carica",
            "Aggiungi",
            "Stampa a video",
            "Stampa su file",
            "Ricerca per codice",
            "Elimina dato codice",
            "Elimina tra date"
    };

    char codiceRicerca[LEN], nomeFile[25], d_str1[LEN], d_str2[LEN];
    date d1, d2;
    link head = NULL;
    bool fineProgramma = falso;
    int selezione;
    Item it;

    do {
        selezione = stampaMenu(scelte);
        switch(selezione){

            case 0: {
                fineProgramma = vero;
            } break;

            case 1: {
                printf("Inserire nome file\n");
                scanf("%s",nomeFile);
                head = carica(head, nomeFile);
            } break;

            case 2: {
                head = aggiungi(head);
            } break;

            case 3: {
                stampaAnagrafica(head, NULL);
            } break;

            case 4: {
                printf("Inserire nome file\n");
                scanf("%s",nomeFile);
                stampaAnagrafica(head, nomeFile);
            } break;

            case 5: {
                printf("Inserire codice: ");
                scanf("%s", codiceRicerca);
                it = ricercaCodice(head, codiceRicerca);
                if(!ItemCheckVoid(it)) {
                    stampaItem(it, stdout);
                } else {
                    fprintf(stdout, "Codice non trovato\n");
                }
            } break;

            case 6: {
                printf("Inserire codice: ");
                scanf("%s", codiceRicerca);
                it = elimina(&head, codiceRicerca);
                if(!ItemCheckVoid(it)) {
                    stampaItem(it, stdout);
                } else {
                    fprintf(stdout, "Codice non trovato\n");
                }
            } break;

            case 7: {
                printf("Inserire data 1: ");
                scanf("%s", d_str1);
                printf("Inserire data 2: ");
                scanf("%s", d_str2);
                scanData(d_str1, &d1);
                scanData(d_str2, &d2);
                if (comparaData(d1, d2) > 0) {
                    date tmp;
                    tmp = d1;
                    d1 = d2;
                    d2 = tmp;
                }
                do {
                    it = eliminaTraDate(&head, d1, d2);
                    if(!ItemCheckVoid(it)) {
                        stampaItem(it, stdout);
                    } else {
                        printf("Fine operazione di cancellazione\n");
                        break;
                    }
                } while(vero);
            } break;

            default:{
                printf("Scelta non valida\n");
            } break;
        }
    } while(!fineProgramma);

    freeAnagrafica(head);
    head = NULL;
    return 0;
}

int stampaMenu(char *scelte[]){
    int i=0, selezione;
    printf("\nMENU'\n");
    for(i=0; i < NSCELTE; i++) printf("%2d > %s\n", i, scelte[i]);
    scanf("%d",&selezione);
    return selezione;
}

int comparaData(date d1, date d2) {
    if (d1.aaaa != d2.aaaa)
        return (d1.aaaa-d2.aaaa);
    else if (d1.mm != d2.mm)
        return (d1.mm-d2.mm);
    else if (d1.gg != d2.gg)
        return (d1.gg-d2.gg);
    else return 0;
}

Item ItemSetVoid(void) {
    Item it = {"","",""};
    return it;
}

int ItemCheckVoid(Item it) {
    if (strlen(it.codice)==0)
        return 1;
    return 0;
}

Item leggiItem(FILE *fp) {
    Item it;

    if (fscanf(fp, "%s %s %s %s %s %s %d",
               it.codice,it.nome,it.cognome,
               it.ddn_str,it.indirizzo.via,it.indirizzo.citta,&it.indirizzo.cap)==7) {
        scanData(it.ddn_str, &(it.data));
        return it;
    }
    return ItemSetVoid();
}

link nuovoNodo(Item val, link next) {
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

link insertOrdinato(link h, Item val) {
    link p = NULL, x = NULL;

    if(h == NULL || comparaData(h->val.data,val.data) > 0)
        return nuovoNodo(val, h);
    for (x=h->next, p=h; x!=NULL && comparaData(val.data, x->val.data) > 0; p=x, x=x->next);
    p->next = nuovoNodo(val, x);
    return h;
}

link aggiungi(link head){
    Item it;
    printf("Cod Nome Cogn Data[gg/mm/aaaa] Via Citta Cap: ");
    it = leggiItem(stdin);
    if (!ItemCheckVoid(it))
        head = insertOrdinato(head, it);
    return head;
}

link carica(link head, char *file) {
    FILE *fp;
    Item it;
    //int n;

    fp = fopen(file, "r");

    if(fp == NULL) {
        printf("Errore nell'apertura del file\n ");
        exit(-1);
    }

    //fscanf(fp, "%d", &n);

    while (!ItemCheckVoid(it = leggiItem(fp))) {
        head = insertOrdinato(head, it);
    }
    fclose(fp);
    return head;
}

void scanData(char *strData, date *data) {
    sscanf(strData, "%d/%d/%d", &(data->gg), &data->mm, &data->aaaa);
}

void stampaIndirizzo(address ind, FILE *fp) {
    fprintf(fp, "\t%s %s %05d\n", ind.via, ind.citta, ind.cap);
}

void stampaItem(Item it, FILE *fp) {
    fprintf(fp, "%s, %s %s, %s\n", it.codice, it.cognome, it.nome, it.ddn_str);
    stampaIndirizzo(it.indirizzo, fp);
}

void stampaAnagrafica(link head, char* file) {
    link x = NULL;
    FILE *fp;
    if(file == NULL)
        fp = stdout;
    else
        fp = fopen(file,"w");

    for(x = head; x != NULL; x=x->next) {
        stampaItem(x->val, fp);
    }

    if(file!=NULL)
        fclose(fp);
}

Item ricercaCodice(link head, char* codice) {
    link x;
    for(x = head; x != NULL; x=x->next) {
        if (strcmp(x->val.codice, codice) == 0) {
            return x->val;
        }
    }
    return ItemSetVoid();
}

Item elimina(link *head, char* codice){
    link x, p;
    Item it = ItemSetVoid();
    for(x = *head, p = NULL; x != NULL; p = x, x=x->next) {
        if (strcmp(x->val.codice, codice) == 0) {
            if (p == NULL) {
                *head = x->next;
            } else {
                p->next = x->next;
            }
            it = x->val;
            free(x);
            break;
        }
    }
    return it;
}

Item eliminaTraDate(link *head, date d1, date d2) {
    link x, p;
    Item it = ItemSetVoid();
    for(x = *head, p = NULL; x != NULL && comparaData(d2, x->val.data) >= 0;
        p = x, x=x->next) {
        if (comparaData(d1, x->val.data) <= 0) {
            if (p == NULL) {
                *head = x->next;
            } else {
                p->next = x->next;
            }
            it = x->val;
            free(x);
            break;
        }
    }
    return it;
}

void freeAnagrafica(link head) {
    link x, t;

    for(x = head; x != NULL; x=t) {
        t = x->next;
        free(x);
    }
}

