#include <stdio.h>
#include <stdlib.h>

void InsetionSort(int A[], int n){
    for(int i = 1; i < n; i++){
        int chave = A[i];
        int j = i - 1;
        while (A[j] > chave && j >= 0){
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = chave;
    }
}

int main(void){
    int n = 10;
    int array[] = {5, 54, 86, 10, 7, 15, 28, 35, 1000, 1};

    InsetionSort(array, n);

    for(int i = 0; i < n; i++){
        printf("%i, ", array[i]);
    }

    return 0;
}