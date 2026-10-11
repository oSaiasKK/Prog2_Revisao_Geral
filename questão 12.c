// Atividade por: Isaias Ramos Batista
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    char dataNascimento[11];
} Pessoa;

void inicializarPessoa(Pessoa *p, const char *nome, const char *dataNascimento) {
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';

    strncpy(p->dataNascimento, dataNascimento, sizeof(p->dataNascimento) - 1);
    p->dataNascimento[sizeof(p->dataNascimento) - 1] = '\0';
}

void apresentarPessoa(const Pessoa *p) {
    printf("Nome: %s\n", p->nome);
    printf("Data de Nascimento: %s\n", p->dataNascimento);
}

typedef struct {
    Pessoa dadosPessoais;
    int matricula;
    char curso[50];
    float notas[3];
    int qtdNotas;
} Aluno;

void inicializarAluno(Aluno *a, const char *nome, const char *dataNascimento, 
                      int matricula, const char *curso, const float *notas, int qtdNotas) {
    inicializarPessoa(&a->dadosPessoais, nome, dataNascimento);
    a->matricula = matricula;
    
    strncpy(a->curso, curso, sizeof(a->curso) - 1);
    a->curso[sizeof(a->curso) - 1] = '\0';

    a->qtdNotas = (qtdNotas <= 3) ? qtdNotas : 3;
    for (int i = 0; i < a->qtdNotas; i++) {
        a->notas[i] = notas[i];
    }
}

float calcularMediaAluno(const Aluno *a) {
    if (a->qtdNotas == 0) return 0.0f;
    
    float soma = 0.0f;
    for (int i = 0; i < a->qtdNotas; i++) {
        soma += a->notas[i];
    }
    return soma / a->qtdNotas;
}

void apresentarAluno(const Aluno *a) {
    printf("\n--- FICHA DO ALUNO ---\n");
    apresentarPessoa(&a->dadosPessoais);
    printf("Matricula: %d\n", a->matricula);
    printf("Curso: %s\n", a->curso);
    printf("Notas: ");
    for (int i = 0; i < a->qtdNotas; i++) {
        printf("%.1f ", a->notas[i]);
    }
    printf("\nMedia Final: %.2f\n", calcularMediaAluno(a));
}


typedef struct {
    Pessoa dadosPessoais;
    int matricula;
    char disciplina[50];
} Professor;

void inicializarProfessor(Professor *prof, const char *nome, const char *dataNascimento, int matricula, const char *disciplina) {
    inicializarPessoa(&prof->dadosPessoais, nome, dataNascimento);
    prof->matricula = matricula;

    strncpy(prof->disciplina, disciplina, sizeof(prof->disciplina) - 1);
    prof->disciplina[sizeof(prof->disciplina) - 1] = '\0';
}

void apresentarProfessor(const Professor *prof) {
    printf("\n--- FICHA DO PROFESSOR ---\n");
    apresentarPessoa(&prof->dadosPessoais);
    printf("Matricula: %d\n", prof->matricula);
    printf("Disciplina: %s\n", prof->disciplina);
}

int main() {
    Aluno alunos[10];
    Professor professores[10];
    int totalAlunos = 0;
    int totalProfessores = 0;
    int opcao;

    do {
        printf("\n<---- MENU ---->\n");
        printf("1. Cadastrar Aluno\n");
        printf("2. Cadastrar Professor\n");
        printf("3. Listar Alunos\n");
        printf("4. Listar Professores\n");
        printf("0. Sair\n");
        
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (totalAlunos >= 10) {
                    printf("\n[ERRO] Limite de alunos atingido!\n");
                    break;
                }
                char nome[100], dataNasc[11], curso[50];
                int mat;
                float notas[3];

                printf("\n--- CADASTRO DE ALUNO ---\n");
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Data de Nascimento (DD/MM/AAAA): ");
                scanf(" %[^\n]", dataNasc);
                printf("Matricula: ");
                scanf("%d", &mat);
                printf("Curso: ");
                scanf(" %[^\n]", curso);
                
                printf("Digite as 3 notas:\n");
                for (int i = 0; i < 3; i++) {
                    printf("Nota %d: ", i + 1);
                    scanf("%f", &notas[i]);
                }

                inicializarAluno(&alunos[totalAlunos], nome, dataNasc, mat, curso, notas, 3);
                totalAlunos++;
                printf("\nAluno cadastrado com sucesso!\n");
                break;
            }

            case 2: {
                if (totalProfessores >= 10) {
                    printf("\n[ERRO] Limite de professores atingido!\n");
                    break;
                }
                char nome[100], dataNasc[11], disciplina[50];
                int mat;

                printf("\n--- CADASTRO DE PROFESSOR ---\n");
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Data de Nascimento (DD/MM/AAAA): ");
                scanf(" %[^\n]", dataNasc);
                printf("Matricula: ");
                scanf("%d", &mat);
                printf("Disciplina: ");
                scanf(" %[^\n]", disciplina);

                inicializarProfessor(&professores[totalProfessores], nome, dataNasc, mat, disciplina);
                totalProfessores++;
                printf("\nProfessor cadastrado com sucesso!\n");
                break;
            }

            case 3:
                if (totalAlunos == 0) {
                    printf("\nNenhum aluno cadastrado.\n");
                } else {
                    for (int i = 0; i < totalAlunos; i++) {
                        apresentarAluno(&alunos[i]);
                    }
                }
                break;

            case 4:
                if (totalProfessores == 0) {
                    printf("\nNenhum professor cadastrado.\n");
                } else {
                    for (int i = 0; i < totalProfessores; i++) {
                        apresentarProfessor(&professores[i]);
                    }
                }
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}