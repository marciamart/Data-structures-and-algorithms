#include <stdio.h>
#include <stdlib.h>

void descer(int T[], int i, int n){
    int j = 2*i;
    if (j <= n){
        if (j < n){
            if (T[j] > T[j-1]){
                j = j + 1;
            }
        }
        if (T[i-1] < T[j-1]){
            int aux = T[i-1];
            T[i-1] = T[j-1];
            T[j-1] = aux;
            descer(T, j, n);
        }
    }
}

void construir(int T[], int n){
    for (int i = n/2; i >= 1; i--){
        descer(T, i, n);
    }
}

void HeapSort(int T[],int n){
    construir(T,n);
    for (int i = n-1; i > 1; i--)
    {
        int aux = T[i];
        T[i] = T[0];
        T[0] = aux;
        descer(T, 1, i - 1);
    }
}