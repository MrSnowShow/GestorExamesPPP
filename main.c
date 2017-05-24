#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

int main()
{
    Node_disciplina *lista_Disciplinas;

    lista_Disciplinas = ler_disciplinas();
    printf("ANTES\n");
    print_listaDisciplinas(lista_Disciplinas);

    printf("DEPOIS\n");
    remover_listaDisciplinas(lista_Disciplinas, "Fisica");
    remover_listaDisciplinas(lista_Disciplinas, "Beber pinga");
    print_listaDisciplinas(lista_Disciplinas);

    return 0;
}
