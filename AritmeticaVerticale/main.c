//
// Created by gianluca on 28/12/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 8+1
#define n 10

int lett_dist=0;

typedef struct
{
    char let;
    int val;
} alpha;

int trovaIndice(char c, alpha *let) {
    for (int i = 0; i < lett_dist; i++) {
        if (let[i].let == c) return i;
    }
    return -1;
}

int word2int(alpha *let, char* str)
{
    int val = 0;
    int len = strlen(str);
    if (let[trovaIndice(str[0], let)].val==0) return -1;
    for (int i = 0; i < len; i++) {
        val = val*10 + let[trovaIndice(str[i], let)].val;
    }
    return val;
}
alpha* initLettere()
{
    alpha *let = malloc(n* sizeof(alpha));
    for (int i = 0; i < n; i++) {
        let[i].val=-1;
        let[i].let='\0';
    }
    return let;
}
void setupLettere(alpha *let, char* str1, char* str2, char* str3)
{
    for (int i = 0; i < strlen(str1); i++) {
        if(trovaIndice(str1[i], let) == -1) let[lett_dist++].let=str1[i];
    }
    for (int i = 0; i < strlen(str2); i++) {
        if(trovaIndice(str2[i], let) == -1) let[lett_dist++].let=str2[i];
    }
    for (int i = 0; i < strlen(str3); i++) {
        if(trovaIndice(str3[i], let) == -1) let[lett_dist++].let=str3[i];
    }
}
int check(alpha *let, char* str1, char* str2, char* str3)
{
    int n1=0, n2=0, n3=0;
    n1 = word2int(let, str1);
    n2 = word2int(let, str2);
    n3 = word2int(let, str3);
    if(n1==-1 || n2==-1 || n3==-1) return 0;
    if((n1+n2)==n3)
    {
        printf("%s\n%d\n%s\n%d\n%s\n%d\n",str1,n1,str2,n2,str3,n3);
        return 1;
    }
    return 0;
}
int disposizioni(int pos, int *mark, alpha *let, char* str1, char* str2, char* str3)
{
    if(pos>=lett_dist)
    {
        if(check(let, str1, str2, str3))
        {
            for (int i = 0; i < lett_dist; i++) {
                printf("%c", let[i].let);
            }
            printf("\n");
            for (int i = 0; i < lett_dist; i++) {
                printf("%d", let[i].val);
            }
            printf("\n");
            return 1;
        }
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (mark[i]==0)
        {
            mark[i]=1;
            let[pos].val=i;
            if(disposizioni(pos+1, mark, let, str1, str2, str3)) return 1;
            mark[i]=0;
            let[pos].val=-1;
        }
    }
    return 0;
}

int main()
{
    char str1[LEN] = {"send"}, str2[LEN] = {"more"}, str3[LEN+1] = {"money"};
    int mark[n]={0};
    alpha * lettere = initLettere();

    setupLettere(lettere, str1, str2, str3);

    disposizioni(0, mark, lettere, str1, str2, str3);

    free(lettere);
    return 0;
}

