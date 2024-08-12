#include <stdio.h>
#include <stdlib.h>
#define V 1
#define F 0

struct no
{
    int chave;
    int bal;
    struct no *esq, *dir;
};

typedef struct no No;

int QtdNos(No *pt);
void Caso1R(No **pt, int *h);
void Caso2R(No **pt, int *h);
void imprimirInOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        imprimirInOrdem(raiz->esq);    
        imprimirInOrdem(raiz->dir);   
    }
}

int main(){
    No *ptraiz = NULL;
    No A, B, C;

    A.chave = 12;
    C.chave = 70;
    B.chave = 9;

    ptraiz = &A;
    A.esq = &B;
    B.dir = &C;
    A.dir = NULL;

    B.esq = NULL;
    C.dir = C.esq = NULL;

    A.bal = -2;
    B.bal = 1;
    C.bal = 0;

    int h = V;

    imprimirInOrdem(ptraiz);
    Caso1R(&ptraiz, &h);
    imprimirInOrdem(ptraiz);
    
    printf("%d", QtdNos(ptraiz)); //OK
}

void Caso1R(No **pt, int *h){//rotação a direita
    No *ptu = (*pt)->esq;
    if (ptu->bal == -1 ){
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        (*pt)->dir->bal = 0;
    }
    else{
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);
        switch (ptv->bal){
        case 1:
            (*pt)->bal = 0; ptu->bal = -1;
            break;
        case 0:
            (*pt)->bal = 0; ptu->bal = 0;
            break;
        case -1:
            (*pt)->bal = -1; ptu->bal = 0;
            break;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = F;
}

void Caso2R(No **pt, int *h){//rotação a esquerda
    No *ptu = (*pt)->dir;
    if (ptu->bal == 1 ){
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;
        (*pt)->esq->bal = 0;
    }
    else{
        No *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);
        switch (ptv->bal){
        case 1:
            (*pt)->bal = -1; ptu->bal = 0;
            break;
        case 0:
            (*pt)->bal = 0; ptu->bal = 0;
            break;
        case -1:
            (*pt)->bal = 0; ptu->bal = 1;
            break;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = F;
}

int QtdNos(No *pt){
    if (pt == NULL) {return 0;}
    return QtdNos(pt->esq) + QtdNos(pt->dir) + 1;
}