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
    lista_E = ler_exames("exames.txt");

    while(input != 0) {
        printf("\n");
        printf("1 - Criar aluno:\n");
        printf("2 - Alterar aluno:\n");
        printf("3 - Apagar aluno:\n");
        printf("4 - Criar uma disciplina:\n");
        printf("5 - Alterar uma disciplina:\n");
        printf("6 - Apagar uma disciplina:\n");
        printf("7 - Criar um exame:\n");
        printf("8 - Apagar exames realizados:\n");
        printf("9 - Listar exames:\n");
        printf("10 - Increver aluno num exame:\n");
        printf("11 - Desinscrever aluno dum exame:\n");
        printf("12 - Lista de alunos inscritos num dado exame:\n");
        printf("13 - Lista de exames que um dado aluno esta inscrito:\n");
        printf("14 - Salas reservadas para dado exame:\n");
        printf("0 - Sair.\n");
        scanf("%d", &input);
        switch (input) {
            case 1:
                user_aluno = NULL;
                while (user_aluno == NULL) {
                    user_aluno = cria_aluno(lista_A);
                }
                inserir_listaAlunos(lista_A, user_aluno);
                break;
            case 2:
                break;
            case 3:
                printf("ID do aluno a apagar: ");
                scanf("%d", &user_id);
                remover_listaAlunos(lista_A, user_id);
                break;
            case 4:
                user_disciplina = NULL;
                while (user_disciplina == NULL) {
                    user_disciplina = cria_disciplina(lista_D);
                }
                inserir_listaDisciplinas(lista_D, user_disciplina);
                break;
            case 5:
                break;
            case 6:
                printf("Nome da disciplina a apagar: ");
                gets(user_string);
                fflush(stdin);
                remover_listaDisciplinas(lista_D, user_string);
                break;
            case 7:
                user_exame = NULL;
                while (user_exame == NULL) {
                    user_exame = cria_exame(lista_D, lista_E);
                }
                inserir_listaExames(lista_E, user_exame);
                break;
            case 8:
                break;
            case 9:
                print_listaExames(lista_E);
                break;
            case 10:
                printf("ID do aluno a inscrever: ");
                scanf("%d", &user_id);
                printf("Data do exame a realizar\n");
                user_data = cria_data();

                user_aluno = procurar_listaAlunos(lista_A, user_id);
                if (user_aluno == NULL)
                    printf("\nAluno nao encontrado!\n");

                user_exame = procurar_listaExames(lista_E, user_data);
                if (user_exame == NULL)
                    printf("\nExame nao encontrado!\n");

                if (user_aluno != NULL && user_exame != NULL) {
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
                }
                break;
            case 11:
                printf("ID do aluno a desinscrever: ");
                scanf("%d", &user_id);
                printf("Data do exame a desinscrever\n");
                user_data = cria_data();

                user_aluno = procurar_listaAlunos(lista_A, user_id);
                if (user_aluno == NULL)
                    printf("\nAluno nao encontrado!\n");

                user_exame = procurar_listaExames(lista_E, user_data);
                if (user_exame == NULL)
                    printf("\nExame nao encontrado!\n");

                if (user_aluno != NULL && user_exame != NULL)
                    desinscrever(user_aluno, user_exame);
                break;
            case 12:
                printf("Data do exame\n");
                user_data = cria_data();
                user_exame = procurar_listaExames(lista_E, user_data);
                if (user_exame == NULL)
                    printf("\nExame nao encontrado!\n");
                else
                    print_listaAlunos(user_exame->alunos_inscritos);

                break;
            case 13:
                printf("ID do aluno: ");
                scanf("%d", &user_id);
                user_aluno = procurar_listaAlunos(lista_A, user_id);
                if (user_aluno == NULL)
                    printf("\nAluno nao encontrado!\n");
                else
                    print_listaExames(user_aluno->exames_inscritos);

                break;
            case 14:
                break;


        }
    }
    return 0;
}

/*
int main()
{
    Node_disciplina *lista_D;
    Node_aluno *lista_A;
    Node_exame *lista_E;

    Aluno *testeA;
    Exame *testeE;
    Data testeData;

    lista_D = ler_disciplinas("disciplinas.txt");
    lista_A = ler_alunos("alunos.txt");
    lista_E = ler_exames("exames.txt");

    testeData = cria_data();

    testeA = procurar_listaAlunos(lista_A, 128);
    testeE = procurar_listaExames(lista_E, testeData);

    printf("************ANTES*************\n");
    print_aluno(testeA);
    print_exame(testeE);

    if (pode_inscrever(testeA, testeE))
        inscrever(testeA, testeE);
    else
        printf("Nao pode!\n");

    printf("************DEPOIS*************\n");
    print_listaAlunos(testeE->alunos_inscritos);
    print_listaExames(testeA->exames_inscritos);

    printf("*********AGORA VAMOS DESINSCREVER*******\n");
    desinscrever(testeA, testeE);
    print_listaAlunos(testeE->alunos_inscritos);
    print_listaExames(testeA->exames_inscritos);


    return 0;
}*/

/*

int main()
{
    Node_disciplina *lista_D;
    Node_aluno *lista_A;
    Node_exame *lista_E;

    Aluno *testeA;
    Disciplina *testeD;

    lista_D = ler_disciplinas("disciplinas.txt");
    lista_A = ler_alunos("alunos.txt");
    lista_E = ler_exames("exames.txt");

    testeD = procurar_listaDisciplinas(lista_D, "AED");
    print_disciplina(testeD);
    alterar_disciplina(lista_D, testeD);
    print_disciplina(testeD);
    return 0;
}*/
