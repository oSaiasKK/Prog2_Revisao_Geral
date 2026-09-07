// Atividade por: Isaias Ramos Batista
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int validarNome(const char nome[]) {
    int i;

    for (i = 0; nome[i] != '\0'; i++) {
        if (!isspace((unsigned char)nome[i])) {
            return 1;
        }
    }

    return 0;
}

int validarIdade(int idade) {
    return idade >= 14 && idade <= 120;
}

int validarEmail(const char email[]) {
    const char *arroba;
    const char *ponto;

    for (int i = 0; email[i] != '\0'; i++) {
        if (isspace((unsigned char)email[i])) {
            return 0;
        }
    }

    arroba = strchr(email, '@');

    if (arroba == NULL || arroba == email) {
        return 0;
    }

    if (strchr(arroba + 1, '@') != NULL) {
        return 0;
    }

    ponto = strchr(arroba + 1, '.');

    if (ponto == NULL || ponto == arroba + 1 || *(ponto + 1) == '\0') {
        return 0;
    }

    return 1;
}

int validarSenha(const char senha[]) {
    return strlen(senha) >= 8;
}

void removerEnter(char texto[]) {
    texto[strcspn(texto, "\n")] = '\0';
}

int main(void) {
    char nome[120];
    int idade;
    char email[100];
    char senha[100];

    char idadeTexto[20];
    int opcaoSelecionada;

    printf("<--- Atividade por: Isaias Ramos Batista --->\n\n");

    do {
        printf("<---- MENU ---->\n");
        printf("1. Entrar\n");
        printf("2. Cadastrar\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");

        fgets(idadeTexto, sizeof(idadeTexto), stdin);
        opcaoSelecionada = atoi(idadeTexto);

        switch (opcaoSelecionada) {
            case 1:
                printf("\nA atividade nao pede um banco de dados, "
                       "entao o login nao foi implementado.\n\n");
                break;

            case 2:
                do {
                    printf("\nDigite seu nome: ");
                    fgets(nome, sizeof(nome), stdin);
                    removerEnter(nome);

                    if (!validarNome(nome)) {
                        printf("Nome invalido. Ele nao pode estar vazio.\n");
                    }

                } while (!validarNome(nome));

                do {
                    printf("Digite sua idade: ");
                    fgets(idadeTexto, sizeof(idadeTexto), stdin);
                    idade = atoi(idadeTexto);

                    if (!validarIdade(idade)) {
                        printf("Idade invalida. Digite uma idade entre "
                               "14 e 120 anos.\n");
                    }

                } while (!validarIdade(idade));

                do {
                    printf("Digite seu e-mail: ");
                    fgets(email, sizeof(email), stdin);
                    removerEnter(email);

                    if (!validarEmail(email)) {
                        printf("E-mail invalido. Exemplo: usuario@email.com\n");
                    }

                } while (!validarEmail(email));

                do {
                    printf("Digite uma senha: ");
                    fgets(senha, sizeof(senha), stdin);
                    removerEnter(senha);

                    if (!validarSenha(senha)) {
                        printf("A senha deve possuir pelo menos "
                               "8 caracteres.\n");
                    }

                } while (!validarSenha(senha));

                printf("\n--- Cadastro concluido ---\n");
                printf("Seu nome e: %s\n", nome);
                printf("Sua idade e: %d\n", idade);
                printf("Seu e-mail e: %s\n", email);
                printf("Sua senha e: %s\n\n", senha);

                break;

            case 3:
                printf("\nPrograma encerrado...\n");
                break;

            default:
                printf("\nA opcao selecionada nao existe. Tente novamente.\n\n");
        }

    } while (opcaoSelecionada != 3);

    return 0;
}