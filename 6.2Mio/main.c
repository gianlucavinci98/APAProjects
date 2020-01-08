//
// Created by gianluca on 18/12/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 50
#define NSCELTE 8

typedef struct
{
    int a,m,g;
} date;
typedef struct
{
    char cod[LEN],nome[LEN],cog[LEN],dataSTR[LEN],via[LEN],citta[LEN];
    int cap;
    date data;
} item;

typedef struct node* link;
struct node
{
    item val;
    link next;
};
void scanData(char* str, date *data)
{
    sscanf(str, "%d/%d/%d", &(data->g), &(data->m), &(data->a));
}
item itemSetVoid()
{
    item it = {"", "", ""};
    return it;
}
int itemCheckVoid(item it)
{
    if(strlen(it.cod)==0) return 1;
    return 0;
}
void stampaMenu(char** scelte)
{
    for (int i = 0; i < NSCELTE; i++) {
        printf("%d- %s\n",i+1, scelte[i]);
    }
}
int comparaData(date d1,date d2) //<0->viene prima la data di sinistra - >0 viene prima la data di destra
{
    int n1 = (d1.a*10000)+(d1.m*100)+d1.g;
    int n2 = (d2.a*10000)+(d2.m*100)+d2.g;
    return n1-n2;
}
link newNode(item val, link next)
{
    link x = malloc(sizeof(*x));
    x->val=val;
    x->next=next;
    return x;
}
link sortInsert(link head, item val)
{
    link x,p;
    if(head==NULL || comparaData(val.data,head->val.data)>0)
    {
        return newNode(val, head);
    }
    for(p=head,x=head->next; x!=NULL && comparaData(val.data, x->val.data)<=0; p=x,x=x->next);
    p->next=newNode(val, x);
    return head;
}
link add(link head)
{
    item it;
    printf("Cod Nome Cogn Data Via Citta Cap:\n");
    scanf("%s %s %s %s %s %s %d",it.cod,it.nome,it.cog,it.dataSTR,it.via,it.citta, &it.cap);
    //sscanf(it.dataSTR,"%d/%d/%d", &it.data.g, &it.data.m, &it.data.a);
    scanData(it.dataSTR, &it.data);
    return sortInsert(head, it);
}
void stampaRecord(item it, FILE *fp)
{
    fprintf(fp, "%s %s %s %s %s %s %d\n", it.cod,it.nome,it.cog,it.dataSTR,it.via,it.citta, it.cap);
}
void stampaLista(FILE* fp, link head)
{
    link x;
    for(x=head; x!=NULL; x=x->next)
    {
        stampaRecord(x->val, fp);
    }
}
link carica(link head, FILE *fp)
{
    item it;
    while(fscanf(fp, "%s %s %s %s %s %s %d",it.cod,it.nome,it.cog,it.dataSTR,it.via,it.citta, &it.cap)==7)
    {
        //sscanf(it.dataSTR,"%d/%d/%d", &it.data.g, &it.data.m, &it.data.a);
        scanData(it.dataSTR,&it.data);
        head=sortInsert(head,it);
    }
    return  head;
}
item ricerca(link head, char* cod)
{
    link x;
    for(x=head; x!=NULL; x=x->next)
    {
        if(strcmp(x->val.cod, cod)==0)
        {
            return x->val;
        }
    }
    return itemSetVoid();
}
item elimina(link *head, char* cod)
{
    link x, p;
    item it;
    if(head==NULL) return itemSetVoid();
    for(p=NULL, x=*head; x!=NULL; p=x, x=x->next)
    {
        if(strcmp(x->val.cod,cod)==0)
        {
            if(x==*head) *head=x->next;
            else p->next=x->next;
            it = x->val;
            free(x);
            return it;
        }
    }
    return itemSetVoid();
}
item eliminaTraDate(link *head, date d1, date d2)
{
    link x, p;
    item it;
    for(p=NULL, x=*head; x!=NULL; p=x, x=x->next)
    {
        if(comparaData(d1, x->val.data)>=0 && comparaData(d2, x->val.data)<=0)
        {
            it=x->val;
            if(x==*head) *head=x->next;
            else p->next=x->next;
            free(x);
            return it;
        }
    }
    return itemSetVoid();
}

int main()
{
    link head = NULL;
    char *scelte[] = {
            "Carica",
            "Aggiungi",
            "Stampa a video",
            "Stampa su file",
            "Ricerca per codice",
            "Elimina dato codice",
            "Elimina tra date",
            "Fine"
    };
    int scelta;
    item it;
    char file[LEN], data1[LEN], data2[LEN];
    date d1, d2;
    FILE *fp;

    stampaMenu(scelte);
    do
    {
        printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta)
        {
            case 1:
                printf("Inserisci nome file: ");
                scanf("%s", file);
                fp=fopen(file,"r");
                head=carica(head,fp);
                fclose(fp);
                break;
            case 2:
                head=add(head);
                break;
            case 3:
                stampaLista(stdout, head);
                break;
            case 4:
                printf("Inserisci nome file: ");
                scanf("%s", file);
                fp=fopen(file,"r");
                stampaLista(fp, head);
                fclose(fp);
                break;
            case 5:
                printf("Inserisci codice: ");
                scanf("%s",file);
                it = ricerca(head, file);
                if(itemCheckVoid(it)) printf("Elemento non trovato\n");
                else stampaRecord(it,stdout);
                break;
            case 6:
                printf("Inserisci codice: ");
                scanf("%s",file);
                it = elimina(&head, file);
                if(itemCheckVoid(it)) printf("Elemento non trovato\n");
                else stampaRecord(it,stdout);
                break;
            case 7:
                printf("Inserisci date: ");
                scanf("%s %s", data1, data2);
                scanData(data1,&d1);
                scanData(data2,&d2);
                int finito = 0;
                while(finito==0)
                {
                    it=eliminaTraDate(&head,d1, d2);
                    if(itemCheckVoid(it))
                    {
                        finito=1;
                        printf("Ricerca terminata\n");
                    }
                    else stampaRecord(it, stdout);
                }
                break;
            case 8:
                break;
            default:
                printf("Non valido\n");
                break;
        }
    }
    while (scelta!=8);

    return 0;
}

