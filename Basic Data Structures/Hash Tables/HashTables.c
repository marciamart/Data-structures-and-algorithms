#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//tam é o tamanho do vetor (retornar indice)
int metodo_divisao(int chave, int tam){
    return chave % tam;
}

int potdois(int n){
    int potencia = 0;
    if(n<0){
        return -1;
    }else{
        while(n % 2 == 0){
            n /= 2;
            potencia += 1;
        }
        if(n == 1){
            return potencia;
        }else{
            return -1;
        }
    }
}

int potDez(int n){
    int potencia = 0;
    if(n<0){
        return -1;
    }else{
        while(n % 10 == 0){
            n /= 10;
            potencia += 1;
        }
        if(n == 1){
            return potencia;
        }else{
            return -1;
        }
    }
}

//binario
int metodo_dobra_BIN_E(int chave, int tam){
    pot = potdois(tam)
    if (pot >= 0){
        x = contarDigitos(chave);
        char str[x];
        sprintf(str, "%d", chave);

        mod = x%pot;
        aum = 0;

        if (mod != 0){
           aum = pot - mod;
        }
        char strzero[aum] = {'0'}

        strcat(strzero, str)

        for (int i = 0; i < x + aum; i++){
            
        }
        


        
        for (int i = 0; i < x; i++)
        {
            
        }
        
        
        return 0;
    }else{printf("tabela não é potência de 2\n");}
    

    
}

int metodo_dobra_BIN_OU(){
    return 0;
}

int metodo_dobra_BIN_OUEXCLUSIVO(){
    return 0;
}

//decimal
int metodo_dobra_DEC(int chave, int tam){
    if (/* condition */)
    {
        x = contarDigitos(chave);
        digitos = x-1

        char str[x];
        sprintf(str, "%d", chave);

        for (int i = 0; i < ; i++)
        {
            /* code */
        }
        

        return 0;
    }
    
    
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

int metodo_analise_digitos_EXP2(int chave,int numDigEscolhidos, int V[],int tamv){
    int maiornum = 0; //quant. de digitos a ser considerado

    for (int i = 0; i < tamv; i++){
        if (V[i]> maiornum){maiornum = V[i];}   
    }
    int digmax = contarDigitos(maiornum);
    
    float desvios[digmax];//cada index um digito com o seu desvio

    for (int digito = 0; digito < digmax; digito++) {
        float qtdchaves[10] = {0}; 
        for (int todos = 0; todos < tamv; todos++) {
            char str[digmax + 1];
            snprintf(str, sizeof(str), "%0*d", digmax, V[todos]);
            int d = str[digito] - '0';
            qtdchaves[d]++;
        }

        float media = tamv / 10.0;
        float resultado = 0;
        for (int qtdc = 0; qtdc < 10; qtdc++) {
            float x = qtdchaves[qtdc] - media;
            resultado += x * x;
        }
        desvios[digito] = resultado;
    }

    char str[digmax + 1];
    snprintf(str, sizeof(str), "%0*d", digmax, chave);

    int digitos[numDigEscolhidos]; 
    for (int i = 0; i < numDigEscolhidos; i++) {
        digitos[i] = -1;
    }

    for (int i = 0; i < digmax; i++) {
        for (int j = 0; j < numDigEscolhidos; j++) {
            if (digitos[j] == -1 || desvios[i] < desvios[digitos[j]]) {
                for (int k = numDigEscolhidos - 1; k > j; k--) {
                    digitos[k] = digitos[k - 1];
                }
                digitos[j] = i;
                break;
            }
        }
    }

    char stresul[numDigEscolhidos + 1];
    for (int i = 0; i < numDigEscolhidos; i++) {
        stresul[i] = str[digitos[i]];
    }
    stresul[numDigEscolhidos] = '\0';
    int resultado = atoi(stresul);

    return resultado;
}

int metodo_analise_digitos_MOD(int chave,int numDigEscolhidos, int V[],int tamv){
    int maiornum = 0; //quant. de digitos a ser considerado

    for (int i = 0; i < tamv; i++){
        if (V[i]> maiornum){maiornum = V[i];}   
    }
    int digmax = contarDigitos(maiornum);
    
    float desvios[digmax];//cada index um digito com o seu desvio

    for (int digito = 0; digito < digmax; digito++) {
        float qtdchaves[10] = {0}; 
        for (int todos = 0; todos < tamv; todos++) {
            char str[digmax + 1];
            snprintf(str, sizeof(str), "%0*d", digmax, V[todos]);
            int d = str[digito] - '0';
            qtdchaves[d]++;
        }

        float media = tamv / 10.0;
        float resultado = 0;
        for (int qtdc = 0; qtdc < 10; qtdc++) {
            float x = qtdchaves[qtdc] - media;
            resultado += abs(x) ;
        }
        desvios[digito] = resultado;
    }

    char str[digmax + 1];
    snprintf(str, sizeof(str), "%0*d", digmax, chave);

    int digitos[numDigEscolhidos]; 
    for (int i = 0; i < numDigEscolhidos; i++) {
        digitos[i] = -1;
    }

    for (int i = 0; i < digmax; i++) {
        for (int j = 0; j < numDigEscolhidos; j++) {
            if (digitos[j] == -1 || desvios[i] < desvios[digitos[j]]) {
                for (int k = numDigEscolhidos - 1; k > j; k--) {
                    digitos[k] = digitos[k - 1];
                }
                digitos[j] = i;
                break;
            }
        }
    }

    char stresul[numDigEscolhidos + 1];
    for (int i = 0; i < numDigEscolhidos; i++) {
        stresul[i] = str[digitos[i]];
    }
    stresul[numDigEscolhidos] = '\0';
    int resultado = atoi(stresul);

    return resultado;
}

int main() {
    printf("existo\n");
    int vetor[] = {44,46, 49, 68, 71, 97};
    int local = metodo_analise_digitos_MOD(44, 1, vetor, 6);
    printf("%i", local);

    return 0;
}