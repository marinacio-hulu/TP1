#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>

typedef struct arv avl;

int altura(avl *raiz);
int maior(int esq, int dir);
int verificarBalanceamento(avl *raiz);
avl *rotDir(avl *raiz);
avl *rotEsq(avl *raiz);
avl *criarNo(int chave);
avl *inserir(avl *raiz, int chave);
avl *menorChave(avl *raiz);
avl *remover(avl *raiz, int chave);
avl *pesquisar(avl *raiz, int chave);
void imprimirEmOrdem(avl *raiz);
void imprimirEstrutura(avl *raiz, int nivel);
int validarBST(avl *raiz, int min, int max);
avl *substituir(avl *raiz, int chaveAntiga, int chaveNova);
void menu(int pos);

