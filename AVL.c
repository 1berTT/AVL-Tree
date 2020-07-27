#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct no{
	int chave;
	int bal;
	struct no* esq;
	struct no* dir;
};
typedef struct no NO;

struct arvore{
    struct no* raiz;
};
typedef struct arvore AVL;

NO* criaNO(int x){
    NO* novo = malloc(sizeof(NO));
    novo->chave = x;
    novo->bal = 0;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

void moverPai(AVL** avl, NO** pt1, NO** pt, NO** pt2){
    if( (*pt1) == NULL ){
        (*avl)->raiz = (*pt2);
    }else{
        if( (*pt) == (*pt1)->esq ){
            (*pt1)->esq = (*pt2);
        }else{
            (*pt1)->dir = (*pt2);
        }
    }
}


void sucessor(NO** pt, NO** s, NO** paiS){
    (*paiS) = (*pt);
    (*s) = (*pt)->dir;
    if( (*s) != NULL ){
        while( (*s)->esq != NULL ){
            (*paiS) = (*s);
            (*s) = (*s)->esq;
        }
    }
}


void caso1Remover(AVL** avl, NO** pt1, NO** pt, int** h){
    NO* ptu = (*pt)->esq;
    if(ptu->bal <= 0){
        moverPai( &(*avl), &(*pt), &ptu, &ptu->dir->chave );
        moverPai( &(*avl), &(*pt1), &(*pt), &ptu );
        ptu->dir = (*pt);
        if(ptu->bal == -1){
            ptu->bal = 0;
            (*pt)->bal = 0;
            printf("Entrei no if... \n");
        }else{
            ptu->bal = 1;
            (*pt)->bal = -1;
            int* x = 0;
            (*h) = x;
        }
    }else{
            NO* ptv = ptu->dir;

            moverPai( &(*avl), &ptu, &ptv, &ptv->esq );
            moverPai( &(*avl), &(*pt), &ptu, &ptv->dir );
            moverPai( &(*avl), &(*pt1), &(*pt), &ptv );
            ptv->esq = ptu;
            ptv->dir = (*pt);
            if(ptv->bal == 0){
                ptu->bal = 0;
                (*pt)->bal = 0;
            }else if(ptv->bal == -1){
                ptu->bal = 0;
                (*pt)->bal = 1;
            }else if(ptv->bal == 1){
                ptu->bal = -1;
                (*pt)->bal = 0;
            }
            ptv->bal = 0;
            int* aux = 1;
            (*h) = aux;
    }
}


void caso1(NO** pt, int** h){
    //printf("O valor da entrada do h eh: %i \n", (*h));
    NO* ptu = (*pt)->esq;
    //printf("O valor da entrada do bal do ptu eh: %i \n", ptu->bal);
    //printf("O valor da entrada do ptu eh: %i \n", ptu->chave);
    if(ptu->bal == -1){
        printf("Rotacão simples a direita no NO de valor: %i \n", (*pt)->chave);
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt)->bal = 0;
        (*pt) = ptu;
    }else{
        printf("Rotacao dupla a direita no No de valor: %i \n", (*pt)->chave);
        NO* ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);
        if(ptv->bal == -1){
            (*pt)->bal = 1;
        }else{
            (*pt)->bal = 0;
        }

        if(ptv->bal == 1){
            ptu->bal = -1;
        }else{
            ptu->bal = 0;
        }

        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    int* haha = 0;
    (*h) = haha;
}

void caso2(NO** pt, int** h){
    NO* ptu = (*pt)->dir;
    if(ptu->bal == 1){
        printf("Rotacao simples a esquerda no NO de valor: %i \n", (*pt)->chave);
        (*pt)->dir = ptu->esq;
        ptu->esq = (*pt);
        (*pt)->bal = 0;
        (*pt) = ptu;
    }else{
        printf("Rotacao dupla a esquerda no NO de valor: %i \n", (*pt)->chave);
        NO* ptv = ptu->esq;
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);

        if(ptv->bal == 1){
            (*pt)->bal = -1;
        }else{
            (*pt)->bal = 0;
        }

        if(ptv->bal == -1){
            ptu->bal = 1;
        }else{
            ptu->bal = 0;
        }

        (*pt) = ptv;
    }
    (*pt)->bal = 0;
    int* haha = 0;
    (*h) = haha;
}


void add(int x, NO** pt, int** h){
    if((*pt) == NULL){
        //printf("Entrei aq...");
        NO* novo = NULL;
        novo = criaNO(x);
        (*pt) = novo;
        int* aux = 1;
        (*h) = aux;
        //printf("sai daq... \n");
    }else if( (*pt)->chave == x ){
        //printf("A chave ja existe... \n");
    }else{
        if( (*pt)->chave > x ){
          //  printf("Sou menor... \n");
            add(x, &(*pt)->esq, &(*h));
            if( (*h) == 1 ){
                if( (*pt)->bal == 1 ){
                    (*pt)->bal = 0;
                    int* aux1 = 0;
                    (*h) = aux1;
                }else if( (*pt)->bal == 0 ){
                    (*pt)->bal = -1;
                }else if( (*pt)->bal == -1 ){
                    caso1(&(*pt), &(*h));
                }
            }
        }else{
            //printf("Sou maior... \n");
            add(x, &(*pt)->dir, &(*h));
            //printf("Valor do h: %i \n", (*h));
            if((*h) == 1){
              //  printf("Valor do bal: %i \n", (*pt)->bal);
                if( (*pt)->bal == -1 ){
                (*pt)->bal = 0;
                int* aux2 = 0;
                (*h) = aux2;
                }else if( (*pt)->bal == 0 ){
                    (*pt)->bal = 1;
                }else if( (*pt)->bal == 1 ){
                    caso2(&(*pt), &(*h));
                }
            }
        }
    }
}

void remover(AVL** avl, int x, NO** pt1, NO** pt, int** h){
    if( (*pt) == NULL ){
        printf("Eu nao existo... \n");
    }else{
        if(x < (*pt)->chave){
            remover(&(*avl), x, &(*pt), &(*pt)->esq, &(*h));
            if( (*h) == 1 ){
                if( (*pt)->bal == -1 ){
                    (*pt)->bal = 0;
                    int* msn = 1;
                    (*h) = msn;
                }else if( (*pt)->bal == 0 ){
                    (*pt)->bal = 1;
                    int* messi = 0;
                    (*h) = messi;
                }else if( (*pt)->bal == 1 ){
                    caso2(&(*pt), &(*h));
                }
            }
        }else{
            if(x > (*pt)->chave){
                remover(&(*avl), x, &(*pt), &(*pt)->dir, &(*h));
                if( (*h) == 1 ){
                    if( (*pt)->bal == 1 ){
                        (*pt)->bal = 0;
                    }else if( (*pt)->bal == 0 ){
                        (*pt)->bal = -1;
                        int* cassio = 0;
                        (*h) = cassio;
                    }else if( (*pt)->bal == -1 ){
                        caso1Remover(&(*avl), &(*pt1), &(*pt), &(*h) );
                    }
                }
            }else{
                if( (*pt)->esq == NULL ){
                    moverPai( &(*avl), &(*pt1), &(*pt), &(*pt)->dir );
                    int* fagner = 1;
                    (*h) = fagner;
                }else{
                    if( (*pt)->dir == NULL ){
                        moverPai( &(*avl), &(*pt1), &(*pt), &(*pt)->esq );
                        int* boselli = 1;
                        (*h) = boselli;
                    }else{
                        printf("Aparece no trocar talquei... \n");
                        NO* s;
                        NO* paiS;
                        sucessor( &(*pt), &s, &paiS );
                        //printf("Valor do pt1: %i \n", (*pt1)->chave);
                        printf("Valor do pt: %i \n", (*pt)->chave);
                        printf("Valor do pai do sucessor: %i \n", paiS->chave);
                        printf("Valor do sucessor: %i \n", s->chave);

                        //trocar( &(*pt1), &(*pt), &paiS, &s );
                        //TROCANDO O PAI DE PT COM O PAI DO SUCESSOR

                        //NO* auxPai = (*pt1);
                        //(*pt1) = paiS;
                        //paiS = auxPai;

                        //TROCANDO OS ESQ E DIR DO PT COM O SUCESSOR
                        NO* pt_aux = (*pt);

                        if( (*pt1) == NULL ){
                            printf("Sou raiz \n");
                            (*avl)->raiz = s;
                        }else{
                            if(pt_aux == (*pt1)->esq){
                                (*pt1)->esq = s;
                            }else{
                                (*pt1)->dir = s;
                            }
                        }

                        if(s == paiS->esq){
                            paiS->esq = pt_aux;
                        }else{
                            paiS->dir = pt_aux;
                        }

                        NO* aux1PT = pt_aux->esq;
                        NO* aux2PT = pt_aux->dir;

                        pt_aux->esq = s->esq;
                        pt_aux->dir = s->dir;
                        s->esq = aux1PT;
                        s->dir = aux2PT;

                        remover( &(*avl), x, &s, &s->dir, &(*h) );
                        if( (*h) == 1 ){
                            if( s->bal == 1 ){
                                s->bal = 0;
                            }else if( s->bal == 0 ){
                                s->bal = -1;
                                int* buffon = 0;
                                (*h) = buffon;
                            }else if( s->bal == -1 ){
                                //caso1(&s, &(*h));
                                caso1Remover(&(*avl), &(*pt1), &s, &(*h) );
                            }
                        }
                    }
                }
            }
        }
    }
}

void preOrdem(NO* raiz){
    printf("%i - %i \n", raiz->chave, raiz->bal);
    if(raiz->esq != NULL){
        preOrdem(raiz->esq);
    }

    if(raiz->dir != NULL){
        preOrdem(raiz->dir);
    }
}

void imprimeAvl(NO * no, int espacos){

    if(no != NULL){
        if(no->dir != NULL){
            imprimeAvl(no->dir, espacos + 5);
        }

        imprimeNo(no, espacos);
        puts("");

        if(no->esq != NULL){
            imprimeAvl(no->esq, espacos + 5);
        }
    }
}

void imprimeNo(NO * no, int espacos){

    while (espacos != 0){
        printf(" ");
        espacos--;
    }

    printf("(%d", no->chave);
    printf(", %d)", no->bal);
}




void main(){
    AVL* avl = malloc(sizeof(AVL));
    avl->raiz = NULL;
    int* h;
    int chave;

    int chaves[] = {8, 5, 7, 4, 12, 14, 9, 3, 6, 11, 13};
    for(int i = 0;i < 11;i++){
        add(chaves[i], &avl->raiz, &h);
    }
    //add(8, &avl->raiz, &h);
    //add(9, &avl->raiz, &h);
    //add(10, &avl->raiz, &h);
    //add(11, &avl->raiz, &h);
    //add(12, &avl->raiz, &h);
    //add(13, &avl->raiz, &h);
    //add(14, &avl->raiz, &h);
    //add(15, &avl->raiz, &h);
    //add(13, &avl->raiz, &h);
    //add(17, &avl->raiz, &h);



    /*imprimeAvl(avl->raiz, 0);
    NO* pt1 = NULL;

    printf("\n");
    remover( &avl, 7, &pt1, &avl->raiz, &h );

    pt1 = NULL;
    printf("\n");
    imprimeAvl(avl->raiz, 0);
    remover( &avl, 6, &pt1, &avl->raiz, &h );

    pt1 = NULL;
    printf("\n");
    imprimeAvl(avl->raiz, 0);
    remover( &avl, 5, &pt1, &avl->raiz, &h );

    printf("\n");
    printf("Sai do remover... \n");

    //preOrdem(&avl->raiz);
    remover( &avl, 5, &pt1, &avl->raiz, &h );
    //remover( &avl, 13, &pt1, &avl->raiz, &h );*/
    //printf("\n");
    NO* pt1 = NULL;
    imprimeAvl(avl->raiz, 0);
    remover( &avl, 13, &pt1, &avl->raiz, &h );
    printf("\n\n");
    imprimeAvl(avl->raiz, 0);
}


