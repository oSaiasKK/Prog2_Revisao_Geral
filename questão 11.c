// Atividade por: Isaias Ramos Batista
#include <stdio.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

Produto criarProduto(int codigo, const char *nome, float preco, int quantidade) {
    Produto p;
    p.codigo = codigo;
    strncpy(p.nome, nome, sizeof(p.nome) - 1);
    p.nome[sizeof(p.nome) - 1] = '\0';
    p.preco = (preco > 0) ? preco : 0.0f;
    p.quantidade = (quantidade >= 0) ? quantidade : 0;
    return p;
}

void adicionarEstoque(Produto *p, int qtd) {
    if (qtd > 0) {
        p->quantidade += qtd;
        printf("\n[SUCESSO] +%d unidades adicionadas. Novo estoque: %d\n", qtd, p->quantidade);
    } else {
        printf("\n[ERRO] Quantidade invalida!\n");
    }
}

void retirarEstoque(Produto *p, int qtd) {
    if (qtd <= 0) {
        printf("\n[ERRO] Quantidade invalida!\n");
    } else if (qtd > p->quantidade) {
        printf("\n[ERRO] Tentativa de retirar %d unidades, mas ha apenas %d em estoque.\n", qtd, p->quantidade);
    } else {
        p->quantidade -= qtd;
        printf("\n[SUCESSO] -%d unidades retiradas. Estoque atual: %d\n", qtd, p->quantidade);
    }
}

void alterarPreco(Produto *p, float novoPreco) {
    if (novoPreco >= 0) {
        p->preco = novoPreco;
        printf("\n[SUCESSO] Preco alterado para R$ %.2f\n", p->preco);
    } else {
        printf("\n[ERRO] Preco invalido!\n");
    }
}

float calcularValorTotal(const Produto *p) {
    return p->preco * p->quantidade;
}

void exibirProduto(const Produto *p) {
    printf("\n=== PRODUTO: %s (Codigo: %d) ===\n", p->nome, p->codigo);
    printf("Preco unitario : R$ %.2f\n", p->preco);
    printf("Em estoque     : %d unidades\n", p->quantidade);
    printf("Valor total    : R$ %.2f\n", calcularValorTotal(p));
}

int main() {
    Produto p;
    int produtoCriado = 0;
    int opcao;

    do {
        printf("\n<----- MENU ----->\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Adicionar Unidades ao Estoque\n");
        printf("3. Retirar Unidades do Estoque\n");
        printf("4. Alterar Preco\n");
        printf("5. Exibir Dados do Produto\n");
        printf("0. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao >= 2 && opcao <= 5 && !produtoCriado) {
            printf("\n[AVISO] Cadastre um produto primeiro (Opcao 1)!\n");
            continue;
        }

        switch (opcao) {
            case 1: {
                int codigo, qtd;
                char nome[50];
                float preco;

                printf("\n--- CADASTRAR PRODUTO ---\n");
                printf("Codigo: ");
                scanf("%d", &codigo);
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Preco: R$ ");
                scanf("%f", &preco);
                printf("Quantidade inicial: ");
                scanf("%d", &qtd);

                p = criarProduto(codigo, nome, preco, qtd);
                produtoCriado = 1;
                printf("\nProduto cadastrado com sucesso!\n");
                break;
            }
            case 2: {
                int qtd;
                printf("\nQuantidade a adicionar: ");
                scanf("%d", &qtd);
                adicionarEstoque(&p, qtd);
                break;
            }
            case 3: {
                int qtd;
                printf("\nQuantidade a retirar: ");
                scanf("%d", &qtd);
                retirarEstoque(&p, qtd);
                break;
            }
            case 4: {
                float novoPreco;
                printf("\nNovo preco: R$ ");
                scanf("%f", &novoPreco);
                alterarPreco(&p, novoPreco);
                break;
            }
            case 5:
                exibirProduto(&p);
                break;

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}