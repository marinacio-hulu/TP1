#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct arv avl;

int altura(avl *raiz);
int max(int esq, int dir);
int verificarBalanceamento(avl *raiz);
avl *rotDir(avl *raiz);
avl *rotEsq(avl *raiz);
avl *criarNo(int chave);
avl *inserir(avl *raiz, int chave);
avl *menorChave(avl *raiz);
avl *remover(avl *raiz, int chave);
avl *pesquisar(avl *raiz, int chave);
void imprimirEmOrdem(avl *raiz);
void menu(int pos);

