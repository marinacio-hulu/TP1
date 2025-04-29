#include "avl.h"

typedef struct arv {
    int chave;
    struct arv *esq;
    struct arv *dir;
    int altura;
} avl;

int altura(avl *raiz) {
    return (raiz == NULL) ? 0 : raiz->altura;
}

int maior(int esq, int dir) {
    return (esq > dir) ? esq : dir;
}

int verificarBalanceamento(avl *raiz) {
    if (raiz == NULL) {
        return 0;
    }

    return altura(raiz->esq) - altura(raiz->dir);
}

avl *rotDir(avl *raiz) {
    avl *x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;

    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
    x->altura = maior(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

avl *rotEsq(avl *raiz) {
    avl *x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;

    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
    x->altura = maior(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

avl *criarNo(int chave) {
    avl *raiz = malloc(sizeof(avl));

    if (!raiz) {
        printf("[!] Erro de alocacao de memoria\n");
        exit(1);
    }

    raiz->chave = chave;
    raiz->esq = raiz->dir = NULL;
    raiz->altura = 1;

    return raiz;
}

avl *inserir(avl *raiz, int chave) {
    if (!raiz) {
        return criarNo(chave);
    }

    if (chave < raiz->chave) {
        raiz->esq = inserir(raiz->esq, chave);

    } else if (chave > raiz->chave) {
        raiz->dir = inserir(raiz->dir, chave);

    } else {
        printf("[!] Esta chave já existe: %d\n", chave);
        return raiz;
    }

    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));
    int fb = verificarBalanceamento(raiz);

    if (fb > 1 && chave < raiz->esq->chave) {
        return rotDir(raiz);
    }

    if (fb < -1 && chave > raiz->dir->chave) {
        return rotEsq(raiz);
    }

    if (fb > 1 && chave > raiz->esq->chave) {
        raiz->esq = rotEsq(raiz->esq);
        return rotDir(raiz);
    }

    if (fb < -1 && chave < raiz->dir->chave) {
        raiz->dir = rotDir(raiz->dir);
        return rotEsq(raiz);
    }

    return raiz;
}

avl *menorChave(avl *raiz) {
    avl *menor = raiz;

    while (menor && menor->esq != NULL) {
        menor = menor->esq;
    }

    return menor;
}

avl *remover(avl *raiz, int chave) {
    if (!raiz) {
        return NULL;
    }

    if (chave < raiz->chave) {
        raiz->esq = remover(raiz->esq, chave);

    } else if (chave > raiz->chave) {
        raiz->dir = remover(raiz->dir, chave);

    } else {
        if (!raiz->esq || !raiz->dir) {

            avl *aux = raiz->esq ? raiz->esq : raiz->dir;

            if (!aux) {
                aux = raiz;
                raiz = NULL;

            } else {
                *raiz = *aux;
            }

            free(aux);

        } else {

            avl *aux = menorChave(raiz->dir);
            raiz->chave = aux->chave;
            raiz->dir = remover(raiz->dir, aux->chave);
        }
    }

    if (!raiz) {
        return NULL;
    }

    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir));

    int fb = verificarBalanceamento(raiz);

    if (fb > 1 && verificarBalanceamento(raiz->esq) >= 0)
        return rotDir(raiz);

    if (fb > 1 && verificarBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotEsq(raiz->esq);
        return rotDir(raiz);
    }

    if (fb < -1 && verificarBalanceamento(raiz->dir) <= 0)
        return rotEsq(raiz);

    if (fb < -1 && verificarBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotDir(raiz->dir);
        return rotEsq(raiz);
    }

    return raiz;
}

avl *pesquisar(avl *raiz, int chave) {
    if (!raiz || raiz->chave == chave) {
        return raiz;

    }

    if (chave < raiz->chave) {
        return pesquisar(raiz->esq, chave);
    } else {
        return pesquisar(raiz->dir, chave);
    }
}

void imprimirEmOrdem(avl *raiz) {
    if (raiz) {
        imprimirEmOrdem(raiz->esq);
        printf("%d ", raiz->chave);
        imprimirEmOrdem(raiz->dir);
    }
}

void menu(int pos)
{
    system("cls");
    int maxOp = 5;
    printf("======================================\n");
    printf("|                 MENU               |\n");
    printf("======================================\n");
    char op[][20] = {
        "Inserir",
        "Remover",
        "Mostrar - Pre Ordem",
        "Pesquisar",
        "Substituir"
    };
    
    for (int i = 0; i < maxOp; i++)
    {
        if(pos == i+1)
        {
            printf(" --> \t%s\n", op[i]);
            printf("--------------------------------------\n");
        } else {
            printf(" %s\n", op[i]);
            printf("--------------------------------------\n");

        }
    }
    
}