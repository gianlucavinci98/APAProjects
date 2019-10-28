//
// L'algoritmo semplifica il lavoro dando il compito alla scansione da file di scandire e salvare solo
// ed esclusivamente le parole, in questo modo poi basta conforntare ogni sequenza con ogni parola salvata
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM 20 //max number of seqs
#define SEQLEN 5 //max sequence lenght
#define WLEN 25 //max word lenght
#define MAXW 150 // ipotetico max number of word

int leggiSequenze(char m[][SEQLEN])
{
    int dim;

    FILE *fp;
    fp = fopen("sequenze.txt", "r");
    fscanf(fp, "%d", &dim);
    for (int i = 0; i < dim; i++) {
        fscanf(fp, "%s", m[i]);
    }
    fclose(fp);
    return dim;
}
int leggiTesto(char m[][WLEN])
{
    FILE *fp;
    fp = fopen("text.txt", "r");
    int i=0;
    while (fscanf(fp,"%29[a-zA-Z]%*[^a-zA-Z]", m[i])==1) //si utilizza regular expression per prendere solo parole
    {
        i++;
    }
    fclose(fp);
    return i;
}
void verificaSequenza(char seq[SEQLEN], int nword, char words[][WLEN])
{
    printf("%s:\n", seq);

    int trovate = 0;
    for (int i = 0; i < nword && trovate<10; i++) { //per ogni parola
        int c = 0; //indice di lettera per le parole
        int k = 0; //indice di lettera per le sequenze
        int trovato = 0;
        while(c<strlen(words[i]) && trovato!=1) //finchè non termina la parola o è stato trovato il match
        {
            if(tolower(seq[k])==tolower(words[i][c])) k++; //se le lettere corrispondo si può verificare la lettera successiva della sequenza
            else k=0; //altrimenti si azzera la ricerca
            c++; //la parola invece va avanti sempre comunque
            if (k==strlen(seq)) trovato = 1; //se k è uguale alla lunghezza della squenza vuol dire che l'intera sequenza matcha
        }
        if (trovato)
        {
            trovate++;
            printf("%s->%d\n", words[i], i+1);
        }
    }

    printf("---------\n");
}

int main()
{
    char seq[DIM][SEQLEN];
    char words[MAXW][WLEN];

    int nseq = leggiSequenze(seq);
    int nword = leggiTesto(words);

    for (int i = 0; i < nseq; i++) { //per ogni sequenza
        verificaSequenza(seq[i], nword, words);
    }

    return 0;
}

