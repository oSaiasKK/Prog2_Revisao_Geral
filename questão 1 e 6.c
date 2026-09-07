// Atividade por: Isaias Ramos Batista
#include <stdio.h>

#define MAX 100

int maiorValor(int numeros[], int quantidade) {
    int maior = numeros[0];

    for (int i = 1; i < quantidade; i++) {
        if (numeros[i] > maior) {
            maior = numeros[i];
        }
    }

    return maior;
}

int menorValor(int numeros[], int quantidade) {
    int menor = numeros[0];

    for (int i = 1; i < quantidade; i++) {
        if (numeros[i] < menor) {
            menor = numeros[i];
        }
    }

    return menor;
}

double calcularMedia(int numeros[], int quantidade) {
    int soma = 0;

    for (int i = 0; i < quantidade; i++) {
        soma += numeros[i];
    }

    return (double)soma / quantidade;
}

int quantidadePares(int numeros[], int quantidade) {
    int pares = 0;

    for (int i = 0; i < quantidade; i++) {
        if (numeros[i] % 2 == 0) {
            pares++;
        }
    }

    return pares;
}

int quantidadeImpares(int numeros[], int quantidade) {
    int impares = 0;

    for (int i = 0; i < quantidade; i++) {
        if (numeros[i] % 2 != 0) {
            impares++;
        }
    }

    return impares;
}

int somarRecursivo(int numeros[], int quantidade) {
    if (quantidade == 0) {
        return 0;
    }

    return numeros[quantidade - 1]
           + somarRecursivo(numeros, quantidade - 1);
}

int main(void) {
    int numeros[MAX];
    int quantidade;
    int opcaoSelecionada;

    printf("<--- Atividade por: Isaias Ramos Batista --->\n\n");

    printf("Digite a quantidade de numeros: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0 || quantidade > MAX) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("Digite o %d.o numero: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    do {
        printf("\n<---- MENU ---->\n");
        printf("1. Maior valor\n");
        printf("2. Menor valor\n");
        printf("3. Calcular media dos valores\n");
        printf("4. Quantidade de numeros pares\n");
        printf("5. Quantidade de numeros impares\n");
        printf("6. Soma dos valores\n");
        printf("0. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoSelecionada);

        switch (opcaoSelecionada) {
            case 1:
                printf("\nMaior valor: %d\n",
                       maiorValor(numeros, quantidade));
                break;

            case 2:
                printf("\nMenor valor: %d\n",
                       menorValor(numeros, quantidade));
                break;

            case 3:
                printf("\nMedia dos valores: %.2f\n",
                       calcularMedia(numeros, quantidade));
                break;

            case 4:
                printf("\nQuantidade de numeros pares: %d\n",
                       quantidadePares(numeros, quantidade));
                break;

            case 5:
                printf("\nQuantidade de numeros impares: %d\n",
                       quantidadeImpares(numeros, quantidade));
                break;

            case 6:
                printf("\nSoma dos valores: %d\n",
                       somarRecursivo(numeros, quantidade));
                break;

            case 0:
                printf("\nPrograma encerrado...\n");
                break;

            default:
                printf("\nA opcao selecionada nao existe. "
                       "Tente novamente.\n");
        }

    } while (opcaoSelecionada != 0);

    return 0;
}