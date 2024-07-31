#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//tam é o tamanho do vetor (retornar indice)
int metodo_divisao(int chave, int tam){
    return chave % tam;
}

//binario
int metodo_dobra_BIN_E(){
    return 0;
}

int metodo_dobra_BIN_OU(){
    return 0;
}

int metodo_dobra_BIN_OUEXCLUSIVO(){
    return 0;
}

//decimal
int metodo_dobra_DEC(){
    return 0;
}

int contarDigitos(int numero) {
    int digitos = 0;
    if (numero == 0) {
        return 1;
    }
    while (numero > 0) {
        numero /= 10;
        digitos++;
    }
    return digitos;
}

int metodo_mutiplicacao(int chave, int tam){
    int x2 = chave*chave;
    int digitos = 0;
    int tamx = contarDigitos(x2);

    while (tam > 1){//quant. de digitos que preciso pegar
       tam = tam/10;
       digitos ++;
    }
    
    char str[tamx];
    sprintf(str, "%d", x2);

    int inicio = (tamx - digitos) / 2;

    char central[digitos + 1];
    strncpy(central, &str[inicio], digitos);
    central[digitos] = '\0';

    int resultado = atoi(central);
    
    return resultado;
}

int h(int chave,int numDigEscolhidos, float Desvios[]){

    return 0;
}

int metodo_analise_digitos_EXP2(int chave,int numDigEscolhidos, int V[],int tamv){
    int digmax = 0; //quant. de digitos a ser considerado

    for (int i = 0; i < tamv; i++){
        if (V[i]> digmax){digmax = V[i]}
        
    }
    digmax = contarDigitos(digmax);

    float desvios[digmax];

    for (int i = 0; i < digmax; i++){//pra cada digito
        for (int i = 0; i < digmax; i++){//faca o desvio
            /* code */
        }
        
    }
    






    return h(chave, numDigEscolhidos, desvios);
}

int metodo_analise_digitos_MOD(int chave, int digescolhidos, int V[], int tamv){
    float desvios[10];

    return h(chave, numDigEscolhidos, desvios);
}

int main() {
    printf("existo\n");

    int local = metodo_mutiplicacao(8583, 1000);
    printf("%i", local);

    return 0;
}