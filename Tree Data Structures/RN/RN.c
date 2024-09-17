#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no{
	int chave;
	char cor;
	struct no *pai, *esq, *dir;
}No;

No externo = {0,'N', NULL, NULL, NULL};

void moverPai(No *v, No *u, No **ptraiz);
void InserirRN(No *z, No **ptraiz);
void RotaRN(No *z, No **ptraiz);
void RotacaoE(No *x, No **ptraiz);
void RotacaoD(No* y, No **ptraiz);
No *antecessor(No *x);
void RemoverRN(No *z, No **ptraiz);
void RotaRemoverRN(No *x, No **ptraiz);
int QtdNos(No *pt);
No *criarNO(int chave);
void esvaziarInrdem(No *raiz);
void chavesInserir(int chavesInseridas[]);
int ERN(No *aux);
int alturaNegra(No *ptraiz);

int main() {
    srand(time(NULL));
    No *ptraiz[1000];

    for(int i = 0; i < 1000; i++){
        ptraiz[i] = NULL;
    }

    int chavesInseridas[10000];

    for (int i = 0; i < 1000; i++) { 
        int rn = 0;
		chavesInserir(chavesInseridas);

        printf("RN %i:\n", i+1);
        for(int j = 0; j < 10000; j++){
			if(ptraiz[i] == NULL){
                ptraiz[i] = criarNO(chavesInseridas[j]);
            }else{
                InserirRN(criarNO(chavesInseridas[j]), &ptraiz[i]);
            }
        }

        printf("Total de nos inserido: %i\n", QtdNos(ptraiz[i]));
        
        rn = ERN(ptraiz[i]);
        if (rn == 1){printf("E RN :D\n");}
        else{printf("Nao e RN :(\n");}

        for (int j = 0; j < 1000; j++) {
            No *delet = ptraiz[i];
            RemoverRN(delet, &ptraiz[i]);
        }
        printf("Total de nos apos remocao: %i\n", QtdNos(ptraiz[i]));
		
		rn = 0;
        rn = ERN(ptraiz[i]);
        if (rn == 1){printf("Ainda e RN :D\n");}
        else{printf("Nao e mais RN :(\n");}
        
        printf("Teste concluido da RN %i com sucesso!\n", i+1);

        esvaziarInrdem(ptraiz[i]);
    }
	return 0;
}

void moverPai(No *u, No *v, No **ptraiz) {
	if(u->pai  == &externo){
		(*ptraiz) = v;
        if (v != &externo){
            v->pai = &externo;
        }
	} else {
		if( u == u->pai->esq){
			u->pai->esq = v;
		}else{
			u->pai->dir = v;
		}
        v->pai = u->pai;
	}
}
void InserirRN(No *z, No **ptraiz){
	No *y = &externo; 
	No *pt = (*ptraiz);

	while (pt != &externo){
		y = pt;
		if (z->chave == pt->chave){
			printf("chave existente");
			y = NULL;
			pt = &externo;
		}else{
			if(z->chave < pt->chave){
				pt = pt->esq;
			}else{pt = pt->dir;}
		}
	}
	z->pai = y;
	if (y == &externo){
		(*ptraiz) = z;
	}else{
		if (z->chave < y->chave){
			y->esq = z;
		}else{
			y->dir = z;
		}
	}
	z->esq = z->dir = &externo;
	z->cor = 'R';
	RotaRN(z, ptraiz);
}
void RotaRN(No *z, No **ptraiz){
	while (z->pai->cor == 'R'){
		if (z->pai == z->pai->pai->esq){
			No *y = z->pai->pai->dir;
			if (y->cor == 'R'){
				z->pai->cor = y->cor = 'N';
				z->pai->pai->cor = 'R';
				z = z->pai->pai;
			}else{
				if(z == z->pai->dir){
					z = z->pai;
					RotacaoE(z, ptraiz);
				}
				z->pai->cor = 'N';
				z->pai->pai->cor = 'R';
				RotacaoD(z->pai->pai, ptraiz);
			}
		}else{
			No *y = z->pai->pai->esq;
            if(y->cor == 'R'){
                z->pai->cor = y->cor = 'N';
                z->pai->pai->cor = 'R';
                z = z->pai->pai;
            }else{
                if(z == z->pai->esq){
                    z = z->pai;
                    RotacaoD(z, ptraiz);
                }
                z->pai->cor = 'N';
                z->pai->pai->cor = 'R';
                RotacaoE(z->pai->pai, ptraiz);
			}
		}
		(*ptraiz)->cor = 'N';
	}
	// printf("fou rotacionado");
}
void RotacaoE(No *x, No **ptraiz){

    No *y = x->dir;
    x->dir = y->esq;
    if(y->esq != &externo){
        y->esq->pai = x;
    }
    y->pai = x->pai;
    if(x->pai == &externo){
        (*ptraiz) = y;
    }else if(x == x->pai->esq){
        x->pai->esq = y;
    }else{
        x->pai->dir = y;
    }
    y->esq = x;
    x->pai = y;
} 
void RotacaoD(No *y, No **ptraiz) {
    No* x = y->esq;
    y->esq = x->dir;
    if (x->dir != &externo) {
        x->dir->pai = y;
    }
    x->pai = y->pai;
    if (y->pai == &externo) {
        (*ptraiz) = x;
    } else if (y == y->pai->esq) {
        y->pai->esq = x;
    } else {
        y->pai->dir = x;
    }
    x->dir = y;
    y->pai = x;
}
No *sucessor(No *x){
    No *y = x->dir;
	while (y->esq != &externo){
		y = y->esq;
	}
	return y;
}
void RemoverRN(No *z, No **ptraiz){
    No *y = z;
    char corOriginal = y->cor;
    No *x = NULL;
    if(z->esq == &externo){
        x = z->dir;
        moverPai( z, z->dir, ptraiz);
    }else{
		if(z->dir == &externo){
        x = z->esq;
        moverPai(z, z->esq, ptraiz);
		}else{
			y = sucessor(z);
			corOriginal = y->cor;
			x = y->dir;
			if(y->pai == z){
				x->pai = y;
			}else{
				moverPai(y, y->dir, ptraiz);
				y->dir = z->dir;
				y->dir->pai = y;
			}
			moverPai( z, y, ptraiz);
			y->esq = z->esq;
			y->esq->pai = y;
			y->cor = z->cor;
		}
	}
    if(corOriginal == 'N'){
        RotaRemoverRN(x, ptraiz);
    }
}
void RotaRemoverRN(No *x, No **ptraiz){
    while(x != (*ptraiz) && x->cor != 'R'){
        if(x == x->pai->esq){
            No *w = x->pai->dir;
            if(w->cor == 'R'){
                x->pai->cor = 'R';
                w->cor = 'N';
                RotacaoE(x->pai, ptraiz);
                w = x->pai->dir;
            }
            if(w->dir->cor == 'N' && w->esq->cor == 'N'){
                w->cor = 'R';
                x = x->pai;
            }else{
                if(w->dir->cor == 'N'){
                    w->esq->cor = 'N';
                    w->cor = 'R';
                    RotacaoD(w, ptraiz);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->dir->cor = 'N';
                RotacaoE(x->pai, ptraiz);
                x = (*ptraiz);
            }
        }else{
            No *w = x->pai->esq;
            if(w->cor == 'R'){
                w->cor = 'N';
                x->pai->cor = 'R';
                RotacaoD(x->pai, ptraiz);
                w = x->pai->esq;
            }
            if(w->esq->cor == 'N' && w->dir->cor == 'N'){
                w->cor = 'R';
                x = x->pai;
            }else{
                if(w->esq->cor == 'N'){
                    w->dir->cor = 'N';
                    w->cor = 'R';
                    RotacaoE(w, ptraiz);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = 'N';
                w->esq->cor = 'N';
                RotacaoD(x->pai, ptraiz);
                x = (*ptraiz);
            }
        }
    }
    x->cor = 'N';
}
int QtdNos(No *pt){
    if (pt == &externo) {return 0;}
    return QtdNos(pt->esq) + QtdNos(pt->dir) + 1;
}
No *criarNO(int chave){
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->cor = 'N';
    novoNo->chave = chave;
    novoNo->esq = &externo;
    novoNo->dir = &externo;
    novoNo->pai = &externo;
    return novoNo;
}
void esvaziarInrdem(No *raiz) {
    if (raiz != NULL) {
        esvaziarInrdem(raiz->esq);
        esvaziarInrdem(raiz->dir); 
        free(raiz);
    }
}
void chavesInserir(int chavesInseridas[]){
    int tabelaPresenca[100001] = {0};  
    int count = 0;

    while (count < 10000) {
        int chave = rand() % 100001;  
		// printf("%i", chave);
        if (!tabelaPresenca[chave]) {  
            chavesInseridas[count] = chave;  
            tabelaPresenca[chave] = 1;  
            count++;  
        }
    }
}
int ERN(No *aux){
    if(aux == NULL || aux == &externo){
        return 1;
    }
    if((aux->cor == 'R' && (aux->esq->cor == 'R' || aux->dir->cor == 'R')) || (aux->cor != 'R' && aux->cor != 'N')){
        return 0;
    }

    int altNesq = alturaNegra(aux->esq);
    int altNdir = alturaNegra(aux->dir);
    if(altNesq == 0 || altNdir == 0 || altNdir != altNesq){
        return 0;
    }

    int subArvEsq = ERN(aux->esq);
    int subArvDir = ERN(aux->dir);
    if(subArvDir == 0 || subArvEsq == 0){
        return 0;
    }
    return 1;
}
int alturaNegra(No *ptraiz){
    if(ptraiz == NULL || ptraiz == &externo){
        return 1;
    }else{
        int altEsq = alturaNegra(ptraiz->esq);
        int altDir = alturaNegra(ptraiz->dir);
        if(altEsq != altDir){
            return 0;
        }else{
            return (ptraiz->cor == 'N') ? altEsq + 1 : altEsq;
        }
    }
}