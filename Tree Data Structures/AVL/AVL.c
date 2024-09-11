#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 1
#define F 0

struct no{
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
int altura(No *pt);
void EAVL(No *pt, int *avl);


void esvaziarInrdem(No *raiz) {
    if (raiz != NULL) {
        esvaziarInrdem(raiz->esq);
        esvaziarInrdem(raiz->dir); 
        free(raiz);
    }
}

void chavesInserir(int chavesInseridas[], int chaveExistente){
    for (int i = 0; i < 10000; i++){
        do{
            chaveExistente = F;
            chavesInseridas[i] = rand() % 100001;
            for(int j = 0; j < i; j++) {
                if (chavesInseridas[j] == chavesInseridas[i]) {
                    chaveExistente = V;
                    break;
                }
            }
        }while(chaveExistente);
    }
}

void chavesRemover(int chavesInseridas[], int chavesRemover[]) {
    int countRemover = 0;


    srand(time(NULL));

    while (countRemover < 1000) {
        int chave = rand() % 100001;
        int i;
        for (i = 0; i < 10000; i++) {
            if (chavesInseridas[i] == chave) {
                break;
            }
        }
        if (i < 10000) {
            int j;
            for (j = 0; j < countRemover; j++) {
                if (chavesRemover[j] == chave) {
                    break;
                }
            }
            if (j == countRemover) {
                chavesRemover[countRemover] = chave;
                countRemover++;
            }
        }
    }
}

int main(){
    int h;
    srand(time(NULL));
    No *ptraiz[1000];

    for(int i = 0; i < 1000; i++){
        ptraiz[i] = NULL;
    }

    int chavesInseridas[10000];
    int chaveExistente;
    int chavesremover[1000];

    for (int i = 0; i < 1000; i++) { 
        int avl = F;
        printf("AVL %i:\n", i+1);

        chavesInserir(chavesInseridas, &chaveExistente);

        for(int j = 0; j < 10000; j++){
            inserirAVL(chavesInseridas[j], &ptraiz[i], &h);
        }

        printf("Total de nos inserido: %i\n", QtdNos(ptraiz[i]));
        
        EAVL(ptraiz[i], &avl);
        if (avl == V){printf("E AVL :D\n");}
        else{printf("Nao e AVL :(\n");}

        chavesRemover(chavesInseridas, chavesremover);
        for (int j = 0; j < 1000; j++) { 
            removerAVL(chavesremover[j], &ptraiz[i], &h);
        }
        printf("Total de nos apos remocao: %i\n", QtdNos(ptraiz[i]));

        EAVL(ptraiz[i], &avl);
        if (avl == V){printf("Ainda e AVL :D\n");}
        else{printf("Nao e mais AVL :(\n");}
        
        printf("Teste concluído da AVL %i com sucesso!\n", i+1);

        esvaziarInrdem(ptraiz[i]);
    }
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
        if (ptv->bal == 1){(*pt)->bal = 0; ptu->bal = -1;}
        else{if (ptv->bal == 0){(*pt)->bal = 0; ptu->bal = 0;}
        else{(*pt)->bal = 1; ptu->bal = 0;}
        }
        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    *h = F;
}

void Caso2Rinserir(No **pt, int *h){//rotação a esquerda
    No *ptu = (*pt)->dir;
    if (ptu->bal == 1){
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
        if (ptv->bal == 1){(*pt)->bal = -1; ptu->bal = 0;}
        else{if (ptv->bal == 0){(*pt)->bal = 0; ptu->bal = 0;}
        else{(*pt)->bal = 0; ptu->bal = 1;}
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
        if (x == (*pt)->chave){ return;}
        else if(x < (*pt)->chave){
            inserirAVL(x, &(*pt)->esq, h);
            if (*h == V){
                if ((*pt)->bal == 1){(*pt)->bal = 0; *h = F;}
                else{if ((*pt)->bal == 0){(*pt)->bal = -1;}
                else{Caso1Rinserir(pt, h);}}
            }
        }else{
            inserirAVL(x, &(*pt)->dir, h);
            if (*h == V){
                if ((*pt)->bal == -1){(*pt)->bal = 0; *h = F;}
                else{if ((*pt)->bal == 0){(*pt)->bal = 1;}
                else{Caso2Rinserir(pt,h);}}
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

        if(ptv->bal == -1){
            ptu->bal = 0; (*pt)->dir->bal = 1;
        }else{
            if(ptv->bal == 0){
                ptu->bal = 0; (*pt)->dir->bal = 0;
            }else{
                if(ptv->bal == 1){
                    ptu->bal = -1; (*pt)->dir->bal = 0;
                }
            }
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

        if(ptv->bal == 1){
            ptu->bal = 0; (*pt)->esq->bal = -1;
        }else{
            if(ptv->bal == 0){
                ptu->bal = 0; (*pt)->esq->bal = 0;
            }else{
                if(ptv->bal == -1){
                    ptu->bal = 1; (*pt)->esq->bal = 0;
                }
            }
        }
        (*pt)->bal = 0; *h = V;
    }
}

void Balancear(No **pt, char R, int *h){
    if (*h == V){
        if (R == 'D'){
            if((*pt)->bal == 1){
                (*pt)->bal = 0;            
            }else{
                if((*pt)->bal == 0){
                    (*pt)->bal = -1;
                    *h = F;
                }else{
                    Caso1Rremover(pt, h);
                }
            }
        }else{
            if((*pt)->bal == -1){
                (*pt)->bal = 0;
            }else{
                if((*pt)->bal == 0){
                    (*pt)->bal = 1;
                    *h = F;
                }else{
                    Caso2Rremover(pt, h);
                }
            }
        }
    }
}

void trocar(No **pt, No **s){
    No *aux;
    int balaux;

    aux = *s;
    *s = *pt;
    *pt = aux;

    aux = (*s)->esq; //troca à esquerda
    (*s)->esq = (*pt)->esq;
    (*pt)->esq = aux;

    aux = (*s)->dir; // troca à direita
    (*s)->dir = (*pt)->dir;
    (*pt)->dir = aux;

    balaux = (*s)->bal; // troca do bal
    (*s)->bal = (*pt)->bal;
    (*pt)->bal = balaux;
}

void removerAVL(int x, No **pt, int *h){
    if ((*pt) == NULL){ *h = F;}
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

int altura(No *pt){
    if (pt == NULL){return 0;}
    else{
        int alturaesq = altura(pt->esq);
        int alturadir = altura(pt->dir);

        if (alturadir > alturaesq){ return alturadir + 1;}
        else{return alturaesq + 1;}
    }
}

void EAVL(No *pt, int *avl){
    if (pt != NULL){
        int alturaesq = altura(pt->esq);
        int alturadir = altura(pt->dir);

        if (abs(alturadir - alturaesq) > 1){ *avl = F;}
        else{
        int subarvesq, subarvdir;
        EAVL(pt->esq, &subarvesq);
        EAVL(pt->dir, &subarvdir);
        if ( subarvesq == V && subarvdir == V){*avl = V;}
        else{*avl = F;}
        }
    }else{*avl = V;}
}

int QtdNos(No *pt){
    if (pt == NULL) {return 0;}
    return QtdNos(pt->esq) + QtdNos(pt->dir) + 1;
}