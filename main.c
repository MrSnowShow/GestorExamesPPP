#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

int main()
{
    Node_disciplina *lista_disciplinas;
    Node_aluno *lista_alunos;
    Node_exame *lista_exams;

    lista_disciplinas = ler_disciplinas("disciplinas.txt");
    lista_alunos = ler_alunos("alunos.txt");
    lista_exams = ler_exames("exames.txt");



    return 0;
}
