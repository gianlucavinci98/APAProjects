//
// Created by gianluca on 12/12/19.
//
#include <stdio.h>
#include <malloc.h>

int check(int *s, int n)
{
    int i,j;
    int cs=0, cd=0;
    for(i=0, j=n-1; i<n/2; i++, j--)
    {
        if(s[i]==1)cs++;
        if(s[j]==1)cd++;
    }
    return cs==cd;
}

int binari(int pos, int *sol, int k, int count)
{
    if(pos>=k)
    {
        if (check(sol, k))
        {
            for (int i = 0; i < k; i++) {
                printf("%d ", sol[i]);
            }
            printf("\n");
            return count + 1;
        }
        return count;
    }
    sol[pos]=0;
    count = binari(pos+1, sol, k,count);
    sol[pos]=1;
    count = binari(pos+1, sol, k, count);
    return count;
}

int main()
{
    int n = 4;
    int *sol = calloc((size_t) n, sizeof(int));

    int c = binari(0, sol, n, 0);
    printf("Soluzioni valide: %d\n",c);
    free(sol);

    return 0;
}

