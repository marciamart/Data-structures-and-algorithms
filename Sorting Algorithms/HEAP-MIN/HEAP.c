#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

//HEAP MINIMA

static int filho_esq(int index) {//localiza o filho da esqueda
    return (2*index) + 1;    
}

static int filho_dir(int index) {//localiza filho da direita
    return (2*index) + 2;
}

static void heap_descida(void **elems, int P, COMP *comparador)//desce a heap para haver a ordenação
{
    int pai_pos = 0;
    int filhoe_pos = filho_esq(pai_pos);
    int filhod_pos = filho_dir(pai_pos);
    int menor = pai_pos; 
    
    while (pai_pos < P - 1)//enquanto a posição do pai for menor do que o numero de elementos do vetor 
    {   
        //descobrindo o menor elemento
        if (filhoe_pos < P && comparador(elems[filhoe_pos], elems[pai_pos]) == -1)
        {
            menor = filhoe_pos;        
        }

        if (filhod_pos < P && comparador(elems[filhod_pos], elems[menor]) == -1)
        {
            menor = filhod_pos;

        }
        
        if (menor == pai_pos)
        {
            break;    
        }
        
        // troca dos valores entre o pai e o meno elemento encontrado
        void *aux = elems[pai_pos];
        elems[pai_pos] = elems[menor];
        elems[menor] = aux;

        // Atualização de índices.
        pai_pos = menor;
        filhoe_pos = filho_esq(pai_pos);
        filhod_pos = filho_dir(pai_pos);
    }
}

HEAP* HEAP_create(int n, COMP* compara)
{
    HEAP* heap = malloc(sizeof(HEAP));   //cria a heap
    heap->comparador = compara;
    heap->N = n;                                 //seta os valores da heap 
    heap->P = 0;
    heap->elems = malloc(n * sizeof(void *));
   
    for(int i = 0; i < n; i++)
    {
        heap->elems[i] = NULL;   //seta cada elems da heap para null
    }
 
    return heap;
}

void HEAP_add(HEAP* vetor, void* newelem)
{  
    if(vetor->P < vetor->N) //verifica se pode ser adicionado
    {
        if(vetor->P == 0)// heap vazia
        {
            vetor->elems[0] = newelem;       // Adição do novo elemento no começo da HEAP.
            vetor->P++;
        }
        else
        {
            vetor->elems[vetor->P] = newelem;  //add no final 
            vetor->P++;
             
            for(int i = vetor->P-1; i>0; i--)
            {//encontra o lugar onde deve ser encaixado o elemento
                if(vetor->comparador(vetor->elems[i], vetor->elems[i/2]) == -1)  
                {
                    void* aux = vetor->elems[i];
                    vetor->elems[i] = vetor->elems[i/2];      //troca de posições 
                    vetor->elems[i/2] = aux;
                }
            }
        }
    }
}

void* HEAP_remove(HEAP* vetor)
{ 
    
    if(vetor->P < 1) //verifica se a heap esta vazia
    {
        return NULL;
    }
    if(vetor->P == 1) //heap com apenas um elemento
    {
        vetor->P--;
        return vetor->elems[vetor->P];
    }
	else 
    {
        void* aux = vetor->elems[0];  // ponteiro auxiliar para remoção
        
        // troca do último elemento com o primeiro.
        vetor->elems[0] = vetor->elems [vetor->P-1]; 
        vetor->elems[vetor->P - 1] = aux;
        
        // Decrementa o vetor.
        vetor->P--;
        //operação de descida que ira buscar o menor elemento e substituir 
        heap_descida(vetor->elems, vetor->P, vetor->comparador);
        
        // Retorna o elemento removido.
        return aux;
    }
    
}
