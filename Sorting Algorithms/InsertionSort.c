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