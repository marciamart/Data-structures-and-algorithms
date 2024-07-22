#include <stdio.h>
#include <stdlib.h>
#include "ordvetor.h"


VETORORD* VETORD_create(int n, COMP* compara)
{
	VETORORD *p = (VETORORD*)malloc(sizeof(VETORORD)); //criação de ponteiro para o vetor a ser criado
	if(p == NULL)
	{
		fprintf(stderr, "Não foi possível alocar memória.\n");
		exit(EXIT_FAILURE);
	}
	p -> N = n;
	p -> P = 0;
	p -> comparador = compara;                      //setando valores do novo vetor 
	p -> elems = (void**)malloc(sizeof(void*) * p->N);
	
	if(p -> elems == NULL) 
	{
		fprintf(stderr, "Não foi possível alocar memória\n");
		exit(EXIT_FAILURE);
	}

	for(unsigned i = 0; i < p->N; ++i) // fazendo cada elemento do vetor receber NULL
		p->elems[i] = NULL;
	
	return p; //retorna ponteiro da estrutura
}

void VETORD_add(VETORORD* vetor, void* newelem)
{
	if (vetor->P < vetor->N) //verifica se tem espaço no vetor 
	{
       	if (vetor->P == 0) //verifica se vetor nao tem elementos 
            vetor->elems[0] = newelem;// adiciona no inicio
        else if //veriifica se o novo elemento sera adicionando no final 
        ( 
			vetor->comparador(newelem, vetor->elems[vetor->P-1]) == 1 ||  //se ele for maior ou equivalente ao ultimo
			vetor->comparador(newelem, vetor->elems[vetor->P-1]) == 0
        ) 
            vetor->elems[vetor->P] = newelem; // adiciona  elemento no final
		else //adiciona no meio    
            for (int i = vetor->P-1; i > -1; --i) 
			{    
                if (vetor->comparador(newelem, vetor->elems[i]) == 1) //sempre que o novo elemento for maior do que o i 
				{
                    vetor->elems[i+1] = vetor->elems[i]; //coloca o novo na sua posição a frente  
                    vetor->elems[i] = newelem;
                }
				else 
					break; //quando chegar no seu local
            }

        vetor->P++;
    }	
}

void* VETORD_remove(VETORORD* vetor)//remove o menor elemento
{
	void* aux = vetor->elems[0]; //aponta pro elemento a se excluido
    for(int i = 0; i < vetor->P-1; i++)
        vetor->elems[i] = vetor->elems[i+1]; //realoca os elementos no seus lugares

    --vetor->P;

    return aux;
}
