// Atividade por: Isaias Ramos Batista
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFAS 100
#define TAM_DESCRICAO 200

typedef struct {
    int id;
    char descricao[TAM_DESCRICAO];
    int concluida;
} Tarefa;

Tarefa tarefas[MAX_TAREFAS];
int quantidade = 0;
int proximoId = 1;

void limparBuffer() {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF);
}

void lerTexto(char *texto, int tamanho) {
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

int buscarIndicePorId(int id) {
    for (int i = 0; i < quantidade; i++) {
        if (tarefas[i].id == id) {
            return i;
        }
    }

    return -1;
}

void adicionarTarefa() {
    if (quantidade >= MAX_TAREFAS) {
        printf("\nA lista está cheia.\n");
        return;
    }

    tarefas[quantidade].id = proximoId++;
    tarefas[quantidade].concluida = 0;

    printf("\nDigite a descrição da tarefa: ");
    lerTexto(tarefas[quantidade].descricao, TAM_DESCRICAO);

    quantidade++;

    printf("Tarefa adicionada com sucesso!\n");
}

void listarTarefas() {
    if (quantidade == 0) {
        printf("\nNenhuma tarefa cadastrada.\n");
        return;
    }

    printf("\n===== LISTA DE TAREFAS =====\n");

    for (int i = 0; i < quantidade; i++) {
        printf("ID: %d\n", tarefas[i].id);
        printf("Descrição: %s\n", tarefas[i].descricao);
        printf("Status: %s\n", tarefas[i].concluida ? "Concluída" : "Pendente");
        printf("----------------------------\n");
    }
}

void buscarTarefa() {
    int id;

    printf("\nDigite o ID da tarefa: ");
    scanf("%d", &id);
    limparBuffer();

    int indice = buscarIndicePorId(id);

    if (indice == -1) {
        printf("Tarefa não encontrada.\n");
        return;
    }

    printf("\nTarefa encontrada:\n");
    printf("ID: %d\n", tarefas[indice].id);
    printf("Descrição: %s\n", tarefas[indice].descricao);
    printf("Status: %s\n",
           tarefas[indice].concluida ? "Concluída" : "Pendente");
}

void alterarTarefa() {
    int id;

    printf("\nDigite o ID da tarefa que deseja alterar: ");
    scanf("%d", &id);
    limparBuffer();

    int indice = buscarIndicePorId(id);

    if (indice == -1) {
        printf("Tarefa não encontrada.\n");
        return;
    }

    printf("Digite a nova descrição: ");
    lerTexto(tarefas[indice].descricao, TAM_DESCRICAO);

    printf("Tarefa alterada com sucesso!\n");
}

void removerTarefa() {
    int id;

    printf("\nDigite o ID da tarefa que deseja remover: ");
    scanf("%d", &id);
    limparBuffer();

    int indice = buscarIndicePorId(id);

    if (indice == -1) {
        printf("Tarefa não encontrada.\n");
        return;
    }

    for (int i = indice; i < quantidade - 1; i++) {
        tarefas[i] = tarefas[i + 1];
    }

    quantidade--;

    printf("Tarefa removida com sucesso!\n");
}

void marcarComoConcluida() {
    int id;

    printf("\nDigite o ID da tarefa: ");
    scanf("%d", &id);
    limparBuffer();

    int indice = buscarIndicePorId(id);

    if (indice == -1) {
        printf("Tarefa não encontrada.\n");
        return;
    }

    tarefas[indice].concluida = 1;

    printf("Tarefa marcada como concluída!\n");
}

void exibirQuantidade() {
    printf("\nQuantidade total de tarefas: %d\n", quantidade);
}

void exibirMenu() {

}

int main(void) {
    int opcaoSelecionada;

    printf("<--- Atividade por: Isaias Ramos Batista --->\n\n");

    do {
        printf("\n<---- MENU ---->\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Listar tarefas\n");
        printf("3. Buscar tarefa\n");
        printf("4. Alterar tarefa\n");
        printf("5. Remover tarefa\n");
        printf("6. Marcar tarefa como concluída\n");
        printf("7. Informar quantidade de tarefas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoSelecionada);

        switch (opcaoSelecionada) {
            case 1:
                adicionarTarefa();
                break;

            case 2:
                listarTarefas();
                break;

            case 3:
                buscarTarefa();
                break;

            case 4:
                alterarTarefa();
                break;

            case 5:
                removerTarefa();
                break;

            case 6:
                marcarComoConcluida();
                break;

            case 7:
                exibirQuantidade();
                break;

            case 0:
                printf("\nPrograma encerrado.\n");
                break;

            default:
                printf("\nOpção inválida.\n");
        }

    } while (opcaoSelecionada != 0);

    return 0;
}