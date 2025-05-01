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

void imprimirEstrutura(avl *raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    imprimirEstrutura(raiz->dir, nivel + 1);

    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("%d\n", raiz->chave);

    imprimirEstrutura(raiz->esq, nivel + 1);
}

int validarBST(avl *raiz, int min, int max) {
    if (!raiz) return 1;

    if (raiz->chave <= min || raiz->chave >= max)
        return 0;

    return validarBST(raiz->esq, min, raiz->chave) &&
           validarBST(raiz->dir, raiz->chave, max);
}


avl *substituir(avl *raiz, int chaveAntiga, int chaveNova) {
    if (!raiz) {
        printf("[!] Substituicao invalida\n");
        return raiz;
    }

    avl *noAntigo = pesquisar(raiz, chaveAntiga);
    avl *existeNovo = pesquisar(raiz, chaveNova);

    if (!noAntigo || existeNovo) {
        printf("[!] Substituicao invalida\n");
        return raiz;
    }

    int chaveOriginal = noAntigo->chave;
    noAntigo->chave = chaveNova;

    if (!validarBST(raiz, INT_MIN, INT_MAX)) {
        noAntigo->chave = chaveOriginal;
        printf("[!] Substituicao invalida\n");
        return raiz;
    }

    printf("[!] Substituicao feita!\n");
    return raiz;
}






void menu(int pos)
{
    system("cls");
    int maxOp = 6;
    printf("======================================\n");
    printf("|                 MENU               |\n");
    printf("======================================\n");
    char op[][30] = {
        "Inserir",
        "Remover",
        "Imprimir - Pre Ordem",
        "Imprimir - Estrutura",
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
