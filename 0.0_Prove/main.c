#include <stdio.h>

int main()
{
    FILE *fp = fopen("provaStampa1.txt", "w");
    fprintf(fp, "Ciao\n");
    fprintf(fp,"cacac\n");
    fprintf(fp, "dlsp\n");

    return 0;
}

