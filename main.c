#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "funcoes.h"

#define MAX 256

int main()
{
    Node_disciplina *lista_D;
    Node_aluno *lista_A;
    Node_exame *lista_E;

    Disciplina *user_disciplina;
    Aluno *user_aluno;
    Exame *user_exame;

    Data user_data;
    int user_id;
    char user_string[MAX];

    int input;

    lista_D = ler_disciplinas("disciplinas.txt");
    lista_A = ler_alunos("alunos.txt");
    lista_E = ler_exames("exames.txt", lista_D);

    while(input != 0) {
        printf("\n");
        printf("1 - Criar aluno\n");
        printf("2 - Alterar aluno\n");
        printf("3 - Apagar aluno\n\n");
        printf("4 - Criar uma disciplina\n");
        printf("5 - Alterar uma disciplina\n");
        printf("6 - Apagar uma disciplina\n\n");
        printf("7 - Criar um exame\n");
        printf("8 - Apagar exames realizados\n");
        printf("9 - Listar exames\n\n");
        printf("10 - Increver aluno num exame\n");
        printf("11 - Desinscrever aluno dum exame\n\n");
        printf("12 - Lista de alunos inscritos num dado exame\n");
        printf("13 - Lista de exames que um dado aluno esta inscrito\n");
        printf("14 - Salas reservadas para dado exame\n\n");
        printf("0 - Sair\n");
        scanf("%d", &input);
        fflush(stdin);
        switch (input) {
            case 1:
                user_aluno = NULL;
                while (user_aluno == NULL) {
                    user_aluno = cria_aluno(lista_A);
                }
                inserir_listaAlunos(lista_A, user_aluno);
                print_listaAlunos(lista_A);
                break;
            case 2:
                print_listaAlunos(lista_A);
                printf("ID do aluno a alterar: ");
                scanf("%d", &user_id);

                user_aluno = procurar_listaAlunos(lista_A, user_id);
                if (user_aluno == NULL) {
                    printf("\nAluno nao encontrado!\n");
                    break;
                } else {
                    alterar_aluno(lista_A, user_aluno);
                }
                print_listaAlunos(lista_A);
                break;
            case 3:
                print_listaAlunos(lista_A);
                printf("ID do aluno a apagar: ");
                scanf("%d", &user_id);
                remover_listaAlunos(lista_A, user_id);
                print_listaAlunos(lista_A);
                break;
            case 4:
                user_disciplina = NULL;
                while (user_disciplina == NULL) {
                    user_disciplina = cria_disciplina(lista_D);
                }
                inserir_listaDisciplinas(lista_D, user_disciplina);
                print_listaDisciplinas(lista_D);
                break;
            case 5:
                print_listaDisciplinas(lista_D);
                printf("Nome da disciplina a alterar: ");
                gets(user_string);
                fflush(stdin);
                user_disciplina = procurar_listaDisciplinas(lista_D, user_string);
                if (user_disciplina == NULL) {
                    printf("Disciplina nao existe!\n");
                    break;
                } else {
                    alterar_disciplina(lista_D, user_disciplina);
                }
                print_listaDisciplinas(lista_D);
                break;
            case 6:
                print_listaDisciplinas(lista_D);
                printf("Nome da disciplina a apagar: ");
                gets(user_string);
                fflush(stdin);
                remover_listaDisciplinas(lista_D, user_string);
                print_listaDisciplinas(lista_D);
                break;
            case 7:
                user_exame = NULL;
                while (user_exame == NULL) {
                    user_exame = cria_exame(lista_D, lista_E);
                }
                inserir_listaExames(lista_E, user_exame);
                print_listaExames(lista_E);
                break;
            case 8:
                print_listaExames(lista_E);
                printf("Data dos exames a apagar (inclusive)\n");
                user_data = cria_data();
                apagar_exames(lista_E, user_data);
                print_listaExames(lista_E);
                break;
            case 9:
                print_listaExames(lista_E);
                break;
            case 10:
                print_listaAlunos(lista_A);
                printf("ID do aluno a inscrever: ");
                scanf("%d", &user_id);

                user_aluno = procurar_listaAlunos(lista_A, user_id);
                if (user_aluno == NULL) {
                    printf("\nAluno nao encontrado!\n");
                    break;
                }

                print_listaExames(lista_E);
                printf("Data do exame a realizar\n");
                user_data = cria_data();

                user_exame = procurar_listaExames(user_aluno->exames_inscritos, user_data);
                if (user_exame != NULL) {
                    printf("Ja esta inscrito!\n");
                    break;
                }

                user_exame = procurar_listaExames(lista_E, user_data);
                if (user_exame == NULL) {
                    printf("\nExame nao encontrado!\n");
                    break;
                }
                if (exame_cheio(user_exame)) {
                    printf("\nExame cheio!\n");
                    break;
                }
                if (!pode_inscrever(user_aluno, user_exame)) {
                    printf("\nNao pode inscrever neste exame!\n");
                    break;
                }
                inscrever(user_aluno, user_exame);
                printf("\nInscrito!\n");
                print_listaExames(user_aluno->exames_inscritos);
                break;
            case 11:
                print_listaAlunos(lista_A);
                printf("ID do aluno a desinscrever: ");
                scanf("%d", &user_id);

                user_aluno = procurar_listaAlunos(lista_A, user_id);
                if (user_aluno == NULL) {
                    printf("\nAluno nao encontrado!\n");
                    break;
                }
                printf("Exames inscritos:\n");
                print_listaExames(user_aluno->exames_inscritos);
                printf("Data do exame a desinscrever\n");
                user_data = cria_data();

                user_exame = procurar_listaExames(lista_E, user_data);
                if (user_exame == NULL) {
                    printf("\nExame nao encontrado!\n");
                    break;
                }
                desinscrever(user_aluno, user_exame);
                print_listaExames(user_aluno->exames_inscritos);
                break;
            case 12:
                print_listaExames(lista_E);
                printf("Data do exame\n");
                user_data = cria_data();
                user_exame = procurar_listaExames(lista_E, user_data);
                if (user_exame == NULL)
                    printf("\nExame nao encontrado!\n");
                else
                    print_listaAlunos(user_exame->alunos_inscritos);

                break;
            case 13:
                print_listaAlunos(lista_A);
                printf("ID do aluno: ");
                scanf("%d", &user_id);
                user_aluno = procurar_listaAlunos(lista_A, user_id);
                if (user_aluno == NULL)
                    printf("\nAluno nao encontrado!\n");
                else
                    print_listaExames(user_aluno->exames_inscritos);

                break;
            case 14:
                print_listaExames(lista_E);
                printf("Data do exame\n");
                user_data = cria_data();

                user_exame = procurar_listaExames(lista_E, user_data);
                if (user_exame == NULL) {
                    printf("\nExame nao encontrado!\n");
                    break;
                }
                printf("\nSala %s esta a %d/30\n", user_exame->sala, user_exame->inscritos);

                break;
        }
    }
    return 0;
}
