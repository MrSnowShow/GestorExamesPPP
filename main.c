#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

int main()
{
    Node_disciplina *lista_D;
    Node_aluno *lista_A;
    Node_exame *lista_E;

    Exame *teste;

    lista_D = ler_disciplinas("disciplinas.txt");
    lista_A = ler_alunos("alunos.txt");
    lista_E = ler_exames("exames.txt");

    printf("\tANTES\n");
    print_listaExames(lista_E);
    teste = NULL;
    while (teste == NULL) {
        printf("Cria um novo exame");
        teste = cria_exame(lista_D, lista_E);
    }
    inserir_listaExames(lista_E, teste);
    printf("\tDEPOIS\n");
    print_listaExames(lista_E);

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
