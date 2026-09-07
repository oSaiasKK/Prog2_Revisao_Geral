// Atividade por: Isaias Ramos Batista
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Pessoa {
    int senha;
    char nome[100];
    char horarioEntrada[20];
    struct Pessoa *proximo;
} Pessoa;

typedef struct {
    Pessoa *inicio;
    Pessoa *fim;
    int quantidade;
    int proximaSenha;
} Fila;

void inicializarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->quantidade = 0;
    fila->proximaSenha = 1;
}

void obterHorarioAtual(char horario[]) {
    time_t agora = time(NULL);
    struct tm *tempoAtual = localtime(&agora);

    strftime(horario, 20, "%d/%m/%Y %H:%M:%S", tempoAtual);
}

void adicionarPessoa(Fila *fila) {
    Pessoa *novaPessoa = malloc(sizeof(Pessoa));

    if (novaPessoa == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    printf("Digite o nome da pessoa: ");
    fgets(novaPessoa->nome, sizeof(novaPessoa->nome), stdin);

    novaPessoa->nome[strcspn(novaPessoa->nome, "\n")] = '\0';

    novaPessoa->senha = fila->proximaSenha++;
    obterHorarioAtual(novaPessoa->horarioEntrada);
    novaPessoa->proximo = NULL;

    if (fila->inicio == NULL) {
        fila->inicio = novaPessoa;
        fila->fim = novaPessoa;
    } else {
        fila->fim->proximo = novaPessoa;
        fila->fim = novaPessoa;
    }

    fila->quantidade++;

    printf("\nPessoa adicionada com sucesso!\n");
    printf("Senha: %d\n", novaPessoa->senha);
    printf("Nome: %s\n", novaPessoa->nome);
    printf("Horário de entrada: %s\n", novaPessoa->horarioEntrada);
}

void chamarProximaPessoa(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("\nA fila está vazia.\n");
        return;
    }

    Pessoa *pessoaAtendida = fila->inicio;

    printf("\nPróxima pessoa chamada:\n");
    printf("Senha: %d\n", pessoaAtendida->senha);
    printf("Nome: %s\n", pessoaAtendida->nome);
    printf("Horário de entrada: %s\n", pessoaAtendida->horarioEntrada);

    fila->inicio = fila->inicio->proximo;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    fila->quantidade--;

    free(pessoaAtendida);
}

void consultarProximaPessoa(const Fila *fila) {
    if (fila->inicio == NULL) {
        printf("\nA fila está vazia.\n");
        return;
    }

    printf("\nPróxima pessoa da fila:\n");
    printf("Senha: %d\n", fila->inicio->senha);
    printf("Nome: %s\n", fila->inicio->nome);
    printf("Horário de entrada: %s\n", fila->inicio->horarioEntrada);
}

void mostrarFila(const Fila *fila) {
    if (fila->inicio == NULL) {
        printf("\nA fila está vazia.\n");
        return;
    }

    Pessoa *atual = fila->inicio;
    int posicao = 1;

    printf("\n--- Pessoas na fila ---\n");

    while (atual != NULL) {
        printf("\nPosição: %d\n", posicao);
        printf("Senha: %d\n", atual->senha);
        printf("Nome: %s\n", atual->nome);
        printf("Horário de entrada: %s\n", atual->horarioEntrada);

        atual = atual->proximo;
        posicao++;
    }
}

void mostrarQuantidade(const Fila *fila) {
    printf("\nQuantidade de pessoas aguardando: %d\n", fila->quantidade);
}

void liberarFila(Fila *fila) {
    Pessoa *atual = fila->inicio;

    while (atual != NULL) {
        Pessoa *proxima = atual->proximo;
        free(atual);
        atual = proxima;
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->quantidade = 0;
}

int main(void) {
    Fila fila;
    int opcaoSelecionada;

    inicializarFila(&fila);

    printf("<--- Atividade por: Isaias Ramos Batista --->\n\n");


    do {
        printf("\n<---- SISTEMA DE ATENDIMENTO ---->\n");
        printf("1. Adicionar pessoa à fila\n");
        printf("2. Chamar próxima pessoa\n");
        printf("3. Consultar próxima pessoa\n");
        printf("4. Mostrar toda a fila\n");
        printf("5. Informar quantidade de pessoas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcaoSelecionada);
        gechar();

        switch (opcaoSelecionada) {
            case 1:
                adicionarPessoa(&fila);
                break;

            case 2:
                chamarProximaPessoa(&fila);
                break;

            case 3:
                consultarProximaPessoa(&fila);
                break;

            case 4:
                mostrarFila(&fila);
                break;

            case 5:
                mostrarQuantidade(&fila);
                break;

            case 0:
                liberarFila(&fila);
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpção inválida.\n");
        }

    } while (opcaoSelecionada != 0);

    return 0;
}
