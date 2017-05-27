#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

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
    testeE = procurar_listaExames(lista_E, testeData, "C5.4");

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


    return 0;
}


/*
int main()
{

    int input;
    while(input != 0) {
        printf("1 - Inserir um aluno:\n");
        printf("2 - Inserir uma disciplina:\n");
        printf("3 - Inserir um exame:\n");
        printf("4 - Increver aluno em exame:\n");
        printf("5 - Apagar exame:\n");
        printf("6 - Lista de exames:\n");
        printf("7 - Lista de alunos inscritos num dado exame:\n");
        printf("8 - Lista de exames que um dado aluno esta inscrito:\n");
        printf("9 - Salas reservadas para dado exame:\n");
        printf("0 - Sair.\n");
        scanf("%d", &input);
        switch (input) {
            case '1':
                cria_aluno();
                break;
            case '2':
               cria_disciplina();
               break;
            case '3':
                cria_exame();
                break;

        }
    }
    return 0;
} */
