// Atividade por: Isaias Ramos Batista
#include <stdio.h>
#include <math.h>

double soma(double a, double b);
double subtracao(double a, double b);
double multiplicacao(double a, double b);
double divisao(double a, double b);
double potencia(double a, double b);
double restoDivisao(double a, double b);

unsigned long long fatorial(int n);

int main(void) {
    int opcaoSelecionada;
    int numeroFatorial;
    double num1, num2, resultado;

    printf("<--- Atividade por: Isaias Ramos Batista --->\n\n");

    do {
        printf("\n<---- MENU ---->\n");
        printf("1. Soma\n");
        printf("2. Subtracao\n");
        printf("3. Multiplicacao\n");
        printf("4. Divisao\n");
        printf("5. Potencia\n");
        printf("6. Resto da divisao\n");
        printf("7. Fatorial\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcaoSelecionada) != 1) {
            printf("\nEntrada invalida!\n");

            while (getchar() != '\n');

            continue;
        }

        if (opcaoSelecionada == 0) {
            printf("\nPrograma encerrado.\n");
            break;
        }

        if (opcaoSelecionada == 7) {
            printf("Digite um numero inteiro nao negativo: ");

            if (scanf("%d", &numeroFatorial) != 1) {
                printf("\nEntrada invalida!\n");

                while (getchar() != '\n');

                continue;
            }

            if (numeroFatorial < 0) {
                printf("\nErro: o fatorial nao existe para numeros negativos.\n");
            } else if (numeroFatorial > 20) {
                printf("\nErro: o resultado ultrapassa o limite do tipo utilizado.\n");
            } else {
                printf("\n%d! = %llu\n",
                       numeroFatorial,
                       fatorial(numeroFatorial));
            }

            continue;
        }

        if (opcaoSelecionada < 1 || opcaoSelecionada > 6) {
            printf("\nA opcao selecionada nao existe. Tente novamente.\n");
            continue;
        }

        printf("Digite o primeiro numero: ");

        if (scanf("%lf", &num1) != 1) {
            printf("\nEntrada invalida!\n");

            while (getchar() != '\n');

            continue;
        }

        printf("Digite o segundo numero: ");

        if (scanf("%lf", &num2) != 1) {
            printf("\nEntrada invalida!\n");

            while (getchar() != '\n');

            continue;
        }

        switch (opcaoSelecionada) {
            case 1:
                resultado = soma(num1, num2);
                printf("\nResultado: %.2lf\n", resultado);
                break;

            case 2:
                resultado = subtracao(num1, num2);
                printf("\nResultado: %.2lf\n", resultado);
                break;

            case 3:
                resultado = multiplicacao(num1, num2);
                printf("\nResultado: %.2lf\n", resultado);
                break;

            case 4:
                if (num2 == 0) {
                    printf("\nErro: nao e possivel dividir por zero.\n");
                } else {
                    resultado = divisao(num1, num2);
                    printf("\nResultado: %.2lf\n", resultado);
                }
                break;

            case 5:
                resultado = potencia(num1, num2);
                printf("\nResultado: %.2lf\n", resultado);
                break;

            case 6:
                if (num2 == 0) {
                    printf("\nErro: nao e possivel calcular resto com divisor zero.\n");
                } else {
                    resultado = restoDivisao(num1, num2);
                    printf("\nResultado: %.2lf\n", resultado);
                }
                break;
        }

    } while (opcaoSelecionada != 0);

    return 0;
}

double soma(double a, double b) {
    return a + b;
}

double subtracao(double a, double b) {
    return a - b;
}

double multiplicacao(double a, double b) {
    return a * b;
}

double divisao(double a, double b) {
    return a / b;
}

double potencia(double a, double b) {
    return pow(a, b);
}

double restoDivisao(double a, double b) {
    return fmod(a, b);
}

unsigned long long fatorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    return n * fatorial(n - 1);
}

/*  
1. Qual é o caso-base da função?
O caso-base ocorre quando n é 0 ou 1:
if (n == 0 || n == 1) {
    return 1;
}

Isso acontece porque:
0! = 1
1! = 1

A partir desses valores, a função consegue encerrar as chamadas recursivas.


2. O que aconteceria se o caso-base não existisse?
A função continuaria chamando a si mesma indefinidamente:


3. Versão não recursiva do mesmo algoritmo
Uma versão utilizando um laço for seria:

int fatorialIterativo(int n) {
    int resultado = 1;

    for (int i = 1; i <= n; i++) {
        resultado = resultado * i;
    }

    return resultado;
}
*/