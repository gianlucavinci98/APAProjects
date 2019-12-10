//
// Created by gianluca on 23/11/19.
//
#include <stdio.h>

int gcd(int a, int b)
{
    int tmp;
    if(a<b)
    {
        tmp=a;
        a=b;
        b=tmp;
    }
    if(a==b) return a;

    if (a%2==0 || b==0)
    {
        if (b%2==0) return 2*gcd(a/2, b/2);
        else return gcd(a/2, b);
    }
    else
    {
        if (b%2==0) return gcd(a, b/2);
        else return gcd((a-b)/2, b);
    }
}

int main()
{
    int a=32;
    int b=16;

    printf("%d\n", gcd(a,b));

    return 0;
}


