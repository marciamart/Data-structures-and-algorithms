#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int chave;
	char cor;
	struct no *pai, *esq, *dir;
}No;

No *externo = NULL;

void moverPai(No **v, No **u, No **ptraiz) {
	if((*u)->pai  == externo){
		ptraiz = v;
	} else {
		if u == (*u)->pai->esq{
			(*u)->pai->esq = v;
		} else {
			(*u)->pai->dir = v;
		}
		
		(*v)->pai = (*u)->pai;
	}
}

int main() {
	No *ptraiz = externo;
	
	No *u = (No*)malloc(sizeof(No));
	No *v = (No*)malloc(sizeof(No));
	
	v->chave = 20;
	v->pai = v->esq = v->dir = NULL;
	
	u->chave = 10;
	u->pai = u->esq = u->dir = NULL;
	
	moverPai(&v, &u, &ptraiz);
	
	return 0;
}