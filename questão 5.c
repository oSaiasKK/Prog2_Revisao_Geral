#include <stdio.h>


//  Calcula o n-ésimo termo de Fibonacci usando recursão.
//  Convenção:
//  F(0) = 0
//  F(1) = 1
unsigned long long fibonacci_recursivo(int n) {
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    return fibonacci_recursivo(n - 1) +
           fibonacci_recursivo(n - 2);
}

//  Calcula o n-ésimo termo de Fibonacci usando repetição.
unsigned long long fibonacci_iterativo(int n) {
    unsigned long long anterior = 0;
    unsigned long long atual = 1;
    unsigned long long proximo;

    if (n == 0) {
        return 0;
    }

    for (int i = 2; i <= n; i++) {
        proximo = anterior + atual;
        anterior = atual;
        atual = proximo;
    }

    return atual;
}

int main(void) {
    int n;

    printf("<--- Atividade por: Isaias Ramos Batista --->\n\n");

    printf("Digite o valor de n: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("O valor de n deve ser nao negativo.\n");
        return 1;
    }

    printf("Fibonacci recursivo: %llu\n",
           fibonacci_recursivo(n));

    printf("Fibonacci iterativo: %llu\n",
           fibonacci_iterativo(n));

    return 0;
}

/*
A versão recursiva é simples, mas recalcula termos várias vezes,
tendo complexidade O(2^n) e podendo causar estouro da pilha.

A versão iterativa é mais eficiente, com complexidade O(n) e uso constante de memória O(1). 
Por isso, é recomendada para valores altos de n.

Com unsigned long long, os valores são confiáveis até aproximadamente F(93).
*/