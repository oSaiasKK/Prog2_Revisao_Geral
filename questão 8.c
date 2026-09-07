// Atividade por: Isaias Ramos Batista
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_URL 200

typedef struct {
    char paginas[100][TAM_URL];
    int topo;
} Pilha;

void inicializar(Pilha *pilha) {
    pilha->topo = -1;
}

int estaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

int estaCheia(Pilha *pilha) {
    return pilha->topo == 99;
}

void visitarPagina(Pilha *pilha, char url[]) {
    if (estaCheia(pilha)) {
        printf("O histórico está cheio.\n");
        return;
    }

    pilha->topo++;
    strcpy(pilha->paginas[pilha->topo], url);

    printf("Página visitada: %s\n", url);
}

void paginaAtual(Pilha *pilha) {
    if (estaVazia(pilha)) {
        printf("Nenhuma página foi visitada.\n");
    } else {
        printf("Página atual: %s\n", pilha->paginas[pilha->topo]);
    }
}

void voltarPagina(Pilha *pilha) {
    if (estaVazia(pilha)) {
        printf("Não há páginas anteriores.\n");
        return;
    }

    printf("Saindo da página: %s\n", pilha->paginas[pilha->topo]);
    pilha->topo--;

    if (!estaVazia(pilha)) {
        printf("Página atual: %s\n", pilha->paginas[pilha->topo]);
    } else {
        printf("Não há mais páginas no histórico.\n");
    }
}

void exibirHistorico(Pilha *pilha) {
    int i;

    if (estaVazia(pilha)) {
        printf("Histórico vazio.\n");
        return;
    }

    printf("\nHistórico de páginas:\n");

    for (i = pilha->topo; i >= 0; i--) {
        if (i == pilha->topo) {
            printf("%s <- página atual\n", pilha->paginas[i]);
        } else {
            printf("%s\n", pilha->paginas[i]);
        }
    }
}

int main(void) {
    Pilha historico;
    int opcaoSelecionada;
    char url[TAM_URL];

    inicializar(&historico);

    printf("<--- Atividade por: Isaias Ramos Batista --->\n\n");

    do {
        printf("\n<---- HISTÓRICO DE NAVEGAÇÃO ---->\n");
        printf("1. Visitar nova página\n");
        printf("2. Visualizar página atual\n");
        printf("3. Voltar para página anterior\n");
        printf("4. Exibir histórico\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoSelecionada);
        getchar();

        switch (opcaoSelecionada) {
            case 1:
                printf("Digite a URL da página: ");
                fgets(url, TAM_URL, stdin);

                url[strcspn(url, "\n")] = '\0';

                visitarPagina(&historico, url);
                break;

            case 2:
                paginaAtual(&historico);
                break;

            case 3:
                voltarPagina(&historico);
                break;

            case 4:
                exibirHistorico(&historico);
                break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcaoSelecionada != 0);

    return 0;
}

/*
Uma pilha é adequada porque segue o princípio LIFO: a última página visitada é a primeira a ser removida.
Assim, ao visitar uma página ela é empilhada e ao voltar é desempilhada, retornando à página anterior.
*/