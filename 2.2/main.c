//
// Created by gianluca on 11/11/19.
//
#include <stdio.h>
#include <string.h>

#define STR 30
#define CMDn 6
#define MAXL 1000

typedef enum {c_date, c_partenza, c_capolinea, c_ritardo, c_ritardoTot, c_fine} command;

typedef struct
{
    int aa, mm, gg;
} date;
typedef struct
{
    int ora, min, sec;
} time;
typedef struct
{
    int ritardo;
    char part[STR], dest[STR], cod[STR];
    date data;
    time oraP, oraA;
} voci;

void stampaComandi(char cmd[][STR])
{
    for (int i = 0; i < CMDn; i++) {
        printf("- %s\n", cmd[i]);
    }
}
command leggiComando(char comandi[][STR])
{
    char cmd[STR];
    printf("Comando: ");
    scanf("%s", cmd);
    for (command i = (command)0; i < CMDn; i++) {
        if (strcmp(cmd,comandi[i])==0) return i;
    }
    return (command) -1;
}
int leggiLog(voci log[])
{
    char dataSTR[STR], oraA[STR], oraP[STR];
    int nvoci;
    FILE *fp;
    fp = fopen("logTrasporti.txt", "r");
    fscanf(fp, "%d", &nvoci);
    for (int i = 0; i < nvoci; i++) {
        fscanf(fp, "%s %s %s %s %s %s %d", log[i].cod,log[i].part,log[i].dest,dataSTR,oraP,oraA,&log[i].ritardo);
        sscanf(dataSTR,"%d/%d/%d", &log[i].data.aa, &log[i].data.mm, &log[i].data.gg);
        sscanf(oraP,"%d:%d:%d", &log[i].oraP.ora, &log[i].oraP.min, &log[i].oraP.sec);
        sscanf(oraA,"%d:%d:%d", &log[i].oraA.ora, &log[i].oraA.min, &log[i].oraA.sec);
    }
    return nvoci;
}
void stampaVoce(voci v)
{
    printf("%s %s-%s %d/%d/%d ", v.cod,v.part,v.dest,v.data.aa,v.data.mm,v.data.gg);
    printf("%d:%d:%d-%d:%d:%d rit: %d minut%c\n",v.oraP.ora,v.oraP.min,v.oraP.sec,v.oraA.ora,v.oraA.min,v.oraA.sec,v.ritardo,(v.ritardo==1)?'o':'i');
}
int confrontaDate(date d1, date d2)
{
    int data1 = d1.aa*10000+d1.mm*100+d1.gg;
    int data2 = d2.aa*10000+d2.mm*100+d2.gg;

    if (data1<=data2) return 1;
    else return -1;
}

void byDate(voci log[], int nvoci, date d1, date d2)
{
    for (int i = 0; i < nvoci; i++) {
        if (confrontaDate(d1, log[i].data)==1 && confrontaDate(log[i].data, d2)==1)
        {
            stampaVoce(log[i]);
        }
    }
}

int main()
{
    command cmd;
    voci log[MAXL];
    char comandi[][STR] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};

    int nvoci = leggiLog(log);
    stampaComandi(comandi);

    do
    {
        cmd = leggiComando(comandi);
        switch (cmd)
        {
            case c_date:
                printf("Data 1: ");
                date d1, d2;
                scanf("%d/%d/%d", &d1.aa,&d1.mm,&d1.gg);
                printf("Data 2: ");
                scanf("%d/%d/%d", &d2.aa,&d2.mm,&d2.gg);
                byDate(log, nvoci, d1, d2);
                break;
            case c_partenza:
                break;
            case c_capolinea:
                break;
            case c_ritardo:
                break;
            case c_ritardoTot:
                break;
            case c_fine:
                break;
            default:
                stampaComandi(comandi);
                break;
        }
    }
    while (cmd != c_fine);

    return 0;
}

