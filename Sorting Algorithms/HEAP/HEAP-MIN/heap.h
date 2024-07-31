#include <stdio.h>
#include <stdlib.h>

#ifndef HEAP_H
#define HEAP_H


typedef int COMP(void* x, void* y);

//Uma Heap estatico. Os elementos do vetor estao colocado no vetor
//de acordo com a ordem indicada por comparador.
typedef struct heap{
	int N;//tamanho do vetor
	int P;//numero de elementos no vetor
	void** elems;//o vetor de elementos
	COMP* comparador;//a funcao de comparacao
}HEAP;


// Cria um heap vazio de tamanho n e com funcao de comparacao compara
// retorna um ponteiro para uma estrutura HEAP
HEAP* HEAP_create(int n, COMP* compara);

// Adiciona o elemento newelem ao Heap, na posicao correta e se for possivel inclui o elemento (se existir espaco no vetor elems). 
//  heap: o heap a ter o elemento inclui­do
//  newelem: o elemento a ser adicionado
void HEAP_add(HEAP* heap, void* newelem);


// Remove o menor elemento do heap, de acordo com a funcao compara
// parametro heap: o heap a ter seu elemento removido
// retorna um ponteiro para o elemento que foi removido do heap.
void* HEAP_remove(HEAP* heap);


#endif