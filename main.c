#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

int main()
{
    Node_disciplina *lista_disciplinas;
    Node_exame *lista_exams;

    lista_disciplinas = ler_disciplinas("disciplinas.txt");
    lista_exams = ler_exames("exames.txt");

    print_listaDisciplinas(lista_disciplinas);
    print_listaExames(lista_exams);

    return 0;
}
