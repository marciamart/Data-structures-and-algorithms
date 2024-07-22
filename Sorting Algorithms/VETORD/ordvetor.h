#include <stdio.h>
#include <stdlib.h>

#ifndef ORDVETOR_H
#define ORDVETOR_H

typedef int COMP(void* x, void* y);

//Vetor ordenado estatico. 
typedef struct vet{
	int N;//tamanho do vetor
	int P;//numero de elementos no vetor
	void** elems;//o vetor de elementos
	COMP* comparador;//a funcao de comparacao
}VETORORD;


// Cria um vetor ordernado vazio de tamanho n e com funcao de comparacao compara
// return um ponteiro para uma estrutura VETORORD
VETORORD* VETORD_create(int n, COMP* compara);

// adiciona novo elemento no vetor ordenando-o em ordem crescente
// parametros: vetor->o vetor que tera elemento incluido | newelem-> o elemento a ser adicionado
void VETORD_add(VETORORD* vetor, void* newelem);

// Remove o menor elemento do vetor, de acordo com a funcao compara.
// parametro vetor: o vetor a ter seu elemento removido
// return um ponteiro para o elemento que foi removido do vetor.
void* VETORD_remove(VETORORD* vetor);

#endif