#include "avl.h"

int main() {
    system("cls");
    printf("[!] URGENTE\n");
    printf("- Use as setas (CIMA) e (BAIXO) do teclado para navegar pelo menu.\n");
    printf("- Clique (ENTER) para selecionar a opção desejada.\n");
    printf("- Clique (ESC) para sair.\n");
    system("pause");
    system("cls");

    avl *raiz = NULL;
    int i=1, chave;
    char ch;

    menu(1);
    while (1)
    {
        ch = getch();
        switch (ch)
        {
            case 27:
                exit(0);
            break;

            case 72:
                if(i != 1)
                {
                    i--;
                    menu(i);
                }
                else {
                    i = 4;
                    menu(5);
                }
            break;

            case 80:
                if(i != 5)
                {
                    i++;
                    menu(i);
                }
                else {
                    i = 1;
                    menu(1);
                }
            break;

            case 13:
                system("cls");
                switch (i)
                {
                    case 1:
                        printf("[?] Insira uma chave: ");
                        scanf("%d", &chave);
                        raiz = inserir(raiz, chave);
                        break;
                    case 2:
                        printf("[?] Insira uma chave: ");
                        scanf("%d", &chave);
                        raiz = remover(raiz, chave);
                        
                        break;
                    case 3:
                        printf("[!] Arvore em ordem: ");
                        imprimirEmOrdem(raiz);
                        printf("\n");
                        break;
                    case 4:
                        printf("[?] Insira uma chave: ");
                        scanf("%d", &chave);
                        avl *encontrado = pesquisar(raiz, chave);
                        if (encontrado) {
                            printf("[!] Chave %d encontrada!\n", chave);
                        } else {
                            printf("[!] Chave %d não encontrada!\n", chave);
                        }
                        break;
                    case 5:
                        //substituir
                        break;
                    default:
                        break;
                }
                
                printf("\n[!] Pressione qualquer tecla para voltar ao menu...");
                getch();
                menu(i);
                break;
            break;
        
            default:
                break;
        }
    }

    return 0;
}