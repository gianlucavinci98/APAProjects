//
// Created by gianluca on 05/01/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 80

typedef struct nodo* link;
struct nodo
{
    char *str;
    link next;
};

link newNode(char *str, link next)
{
    link x = malloc(sizeof(*x));
    x->str=strdup(str);
    x->next=next;
    return x;
}
link insertOrdinato(link head, char *str)
{
    link x, p;
    if(head==NULL || strcmp(str, head->str)<0) return newNode(str, head);

    for(p=head, x=head->next; x!=NULL && strcmp(str,x->str)>0; p=x, x=x->next);
    p->next=newNode(str, x);
    return head;
}
void stampaLista(link head, FILE *fp)
{
    link x;
    for(x=head; x!=NULL; x=x->next)
    {
        fprintf(fp,"%s\n", x->str);
    }
}
link caricaLista(link head, FILE *fp)
{
    char stringa[LEN];
    while (fscanf(fp, "%s", stringa)!=EOF)
    {
        head=insertOrdinato(head, stringa);
    }
    return head;
}
void libera(link head)
{
    link x, tmp;
    for(x=head; x!=NULL;)
    {
        tmp = x;
        x=x->next;
        free(tmp->str);
        free(tmp);
    }
}

int main()
{
    link head = NULL;
    FILE *fp = fopen("stringhe.txt", "r");
    head = caricaLista(head, fp);
    fclose(fp);

    stampaLista(head, stdout);
    libera(head);


    return 0;
}

