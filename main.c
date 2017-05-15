#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

int main()
{
    Node_aluno *listaA;
    Aluno *a1, *a2, *a3;
    listaA = init_listaA();
    a1 = cria_aluno();
    a2 = cria_aluno();
    a3 = cria_aluno();

    inserir_listaA(listaA, a1);
    inserir_listaA(listaA, a2);
    inserir_listaA(listaA, a3);
    print_listaA(listaA);
    return 0;
}
