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
void Caso1Rinserir(No **pt, int *h);
void Caso2Rinserir(No **pt, int *h);
void inserirAVL(int x, No **pt, int *h);
void Caso1Rremover(No **pt, int *h);
void Caso2Rremover(No **pt, int *h);
void Balancear(No **pt, char R, int *h);
void trocar(No **pt, No **paiS);
void removerAVL(int x, No **pt, int *h);

void posrdem(No *raiz) {
    if (raiz != NULL) {
        posrdem(raiz->esq);
        posrdem(raiz->dir); 
        printf("%d ", raiz->chave);  
    }
}
void inrdem(No *raiz) {
    if (raiz != NULL) {
        inrdem(raiz->esq);
        printf("%d ", raiz->chave);
        inrdem(raiz->dir); 
          
    }
}
void prerdem(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        prerdem(raiz->esq);
        prerdem(raiz->dir);
    }
}

int main(){
    No *ptraiz = NULL;
    int h = V;

    inserirAVL(10,&ptraiz, &h);
    inserirAVL(58,&ptraiz, &h);
    inserirAVL(19,&ptraiz, &h);
    inserirAVL(36,&ptraiz, &h);
    inserirAVL(37,&ptraiz, &h);
    inserirAVL(49,&ptraiz, &h);
    inserirAVL(10,&ptraiz, &h);
    inserirAVL(79,&ptraiz, &h);
    removerAVL(19,&ptraiz, &h);
    removerAVL(37,&ptraiz, &h);
    removerAVL(36,&ptraiz, &h);
    
    posrdem(ptraiz);
    printf("\n");
    prerdem(ptraiz);
    printf("\n");
    inrdem(ptraiz);

    printf("\n%d", QtdNos(ptraiz)); //OK
}

void Caso1Rinserir(No **pt, int *h){//rotação a direita
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
        case 1: (*pt)->bal = 0; ptu->bal = -1; break;
        case 0: (*pt)->bal = 0; ptu->bal = 0; break;
        case -1: (*pt)->bal = 1; ptu->bal = 0; break;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = F;
}

void Caso2Rinserir(No **pt, int *h){//rotação a esquerda
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
        case 1: (*pt)->bal = -1; ptu->bal = 0; break;
        case 0: (*pt)->bal = 0; ptu->bal = 0; break;
        case -1: (*pt)->bal = 0; ptu->bal = 1; break;
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = F;
}

void inserirAVL(int x, No **pt, int *h){
    if ((*pt) == NULL){
        No *novo = (No*)malloc(sizeof(No));
        novo->chave = x;
        novo->bal = 0;
        novo->dir = novo->esq = NULL;

        *h = V;
        (*pt) = novo;
    }else{
        if (x == (*pt)->chave){printf("elemento %i ja existe\n", x); return;}
        else if(x < (*pt)->chave){
            inserirAVL(x, &(*pt)->esq, h);
            if (h == V){
                switch ((*pt)->bal){
                case 1:
                    (*pt)->bal = 0; *h = F; break;
                case 0:
                    (*pt)->bal = -1; break;
                case -1:
                    Caso1Rinserir(pt,h); break;
                }
            }
        }else{
            inserirAVL(x, &(*pt)->dir, h);
            if (h == V){
                switch ((*pt)->bal){
                case -1:
                    (*pt)->bal = 0; *h = F; break;
                case 0:
                    (*pt)->bal = 1; break;
                case 1:
                    Caso2Rinserir(pt,h); break;
                }
            }  
        }
    } 
}

void Caso1Rremover(No **pt, int *h){
    No *ptu = (*pt)->esq;
    if (ptu->bal <= 0){
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        if (ptu->bal == -1){ptu->bal = (*pt)->dir->bal = 0; *h = V;}
        else{ptu->bal = 1; (*pt)->dir->bal = -1; *h = F;}
    }else{
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);
        (*pt) = ptv;
        switch (ptv->bal){
        case -1: ptu->bal = 0; (*pt)->esq->bal = 1; break;
        case 0: ptu->bal = 0; (*pt)->esq->bal = 0; break;
        case 1: ptu->bal = -1; (*pt)->esq->bal = 0; break;
        }
        (*pt)->bal = 0; *h = V;
    }
}

void Caso2Rremover(No **pt, int *h){
    No *ptu = (*pt)->dir;
    if (ptu->bal >= 0){
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt) = ptu;
        if (ptu->bal == 1){ptu->bal = (*pt)->esq->bal = 0; *h = V;}
        else{ptu->bal = -1; (*pt)->esq->bal = 1; *h = F;}
    }else{
        No *ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);
        (*pt) = ptv;
        switch (ptv->bal){
        case -1: ptu->bal = 1; (*pt)->esq->bal = 0; break;
        case 0: ptu->bal = 0; (*pt)->esq->bal = 0; break;
        case 1: ptu->bal = 0; (*pt)->esq->bal = -1; break;
        }
        (*pt)->bal = 0; *h = V;
    }
}

void Balancear(No **pt, char R, int *h){
    if (h == V){
        if (R == 'D'){
            switch ((*pt)->bal){
            case 1: (*pt)->bal = 0; break;
            case 0: (*pt)->bal = -1; *h = F; break;
            case -1: Caso1Rremover(pt, h); break;
            }
        }else{
            switch ((*pt)->bal){
            case -1: (*pt)->bal = 0; break;
            case 0: (*pt)->bal = 1; *h = F; break;
            case 1: Caso2Rremover(pt, h); break;
            }
        }
    }
}

void trocar(No **pt, No **paiS){
    No *aux = (*pt);
    (*pt) = (*paiS);
    (*paiS) = (*paiS)->dir;
    (*pt)->esq = aux->esq;
    (*pt)->dir = aux->dir;
    free(aux);
}

void removerAVL(int x, No **pt, int *h){
    if ((*pt) == NULL){printf("elemento %i nao existe\n", x); *h = F; return;}
    else{
        if (x < (*pt)->chave){
            removerAVL(x, &(*pt)->esq, h);
            Balancear(pt, 'E', h);
        }else if (x > (*pt)->chave){
            removerAVL(x, &(*pt)->dir, h);
            Balancear(pt, 'D', h);
        }else{
            No *aux = (*pt);
            if ((*pt)->esq == NULL){
                (*pt) = (*pt)->dir; *h = V;
                free(aux);
            }else if ((*pt)->dir == NULL){
                (*pt) = (*pt)->esq; *h = V;
                free(aux);
            }else{
                No *s = (*pt)->dir;
                if (s->esq == NULL){
                    s->esq = (*pt)->esq;
                    s->bal = (*pt)->bal;
                    (*pt) = s;
                    *h = V;
                    free(aux);
                }else{
                    No *paiS;
                    while (s->esq != NULL){
                        paiS = s;
                        s = s->esq;
                    }
                    trocar(pt, &(paiS)->esq);
                    removerAVL(x, &(*pt)->dir, h);
                }
                Balancear(pt, 'D', h);
            } 
        }
    }
}

int QtdNos(No *pt){
    if (pt == NULL) {return 0;}
    return QtdNos(pt->esq) + QtdNos(pt->dir) + 1;
}