#include <stdio.h>

int main() {
    int vet[10] =  {3,6,8,1,2,4,7,9,5,0};

    for (int k = 0; k < 10 ; k++) {
        printf("%d ",vet[k]);
    }
    printf("\n");

    for (int i = 1; i < 10; i++) {
        int tmp = vet[i];
        int j = i-1;
        while (tmp<vet[j] && j>=0)
        {
            vet[j+1]=vet[j];
            j--;
        }
        vet[j+1]=tmp;

    }

    for (int k = 0; k < 10 ; k++) {
        printf("%d ",vet[k]);
    }
    printf("\n");

    return 0;
}
