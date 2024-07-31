#include <stdio.h>
#include <stdlib.h>

void subir(int T[], int i){
    int j = i/2;
    if (j >= 1){
        if (T[i] > T[j])
        {
            int aux = T[i];
            T[i] = T[j];
            T[j] = aux;
            subir(T, j);
        }
    }
}

void descer(int T[], int i){

}

void construir(int T[]){

}

int main(void){
    int n = 10;
    int array[] = {5, 54, 86, 10, 7, 15, 28, 35, 1000, 1};

    construir(array);

    for(int i = 0; i < n; i++){
        printf("%i, ", array[i]);
    }

    return 0;
}