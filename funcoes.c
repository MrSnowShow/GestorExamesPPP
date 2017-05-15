#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

#define MAX 256

/* Funcoes de print */

void print_data(Data d)
{
    printf("Data:\t\t%d/%d/%d\n", d.dia, d.mes, d.ano);
}

void print_hora(Hora h)
{
    printf("Hora:\t\t%dh%d\n", h.horas, h.minutos);
}

void print_disciplina(Disciplina *d)
{
    printf("Nome:\t\t%s\n", d->nome);
    printf("Docente:\t%s\n", d->docente);
}

void print_aluno(Aluno *a)
{
    printf("ID:\t\t%d\n", a->id);
    printf("Matricula:\t%d\n", a->matricula);
    printf("Curso:\t\t%s\n", a->curso);
    printf("Regime:\t\t%s\n", a->regime);
    print_listaE(a->exames_inscritos);
}

void print_exame(Exame *e)
{
    print_disciplina(e->disciplina);
    print_data(e->data);
    print_hora(e->duracao);
    printf("Epoca:\t\t%s\n", e->epoca);
    printf("Sala:\t\t%d\n", e->sala);
    print_listaA(e->alunos_inscritos);
}

void print_listaD(Node_disciplina *listaD)
{
    printf("\nLista de disciplinas\n");
    while (listaD != NULL) {
        print_disciplina(listaD->info);
        printf("\n");
        listaD = listaD->next;
    }
}

void print_listaA(Node_aluno *listaA)
{
    if (listaA->info == NULL) {
        printf("Nao ha alunos!\n");
        return;
    }
    printf("\nLista de alunos\n");
    while (listaA != NULL) {
        print_aluno(listaA->info);
        printf("\n");
        listaA = listaA->next;
    }
}

void print_listaE(Node_exame *listaE)
{
    if (listaE->info == NULL) {
        printf("Nao ha exames!\n");
        return;
    }
    printf("\nLista de exames\n");
    while (listaE != NULL) {
        print_exame(listaE->info);
        printf("\n");
        listaE = listaE->next;
    }
}

/* Funcoes de criar */

Data cria_data()
{
    Data d;
    printf("Dia: ");
    scanf("%d", &d.dia);
    printf("Mes: ");
    scanf("%d", &d.mes);
    printf("Ano: ");
    scanf("%d", &d.ano);
    return d;
}

Hora cria_hora()
{
    Hora h;
    printf("Horas: ");
    scanf("%d", &h.horas);
    printf("Minutos: ");
    scanf("%d", &h.minutos);
    return h;
}

Disciplina* cria_disciplina()
{
    Disciplina *d;
    d = malloc(sizeof(Node_disciplina));
    d->nome = malloc(MAX*sizeof(char));
    d->docente = malloc(MAX*sizeof(char));

    printf("Nome: ");
    gets(d->nome);
    fflush(stdin);
    printf("Docente: ");
    gets(d->docente);
    fflush(stdin);
    return d;
}

Aluno* cria_aluno()
{
    Aluno *a;
    a = malloc(sizeof(Aluno));
    a->curso = malloc(MAX*sizeof(char));
    a->regime = malloc(MAX*sizeof(char));
    a->exames_inscritos = init_listaE();

    printf("ID: ");
    scanf("%d", &a->id);
    printf("Matricula: ");
    scanf("%d", &a->matricula);
    fflush(stdin);
    printf("Curso: ");
    gets(a->curso);
    fflush(stdin);
    printf("Regime: ");
    gets(a->regime);
    fflush(stdin);
    return a;
}

Exame* cria_exame()
{
    Exame *e;
    e = malloc(sizeof(Exame));
    e->epoca = malloc(MAX*sizeof(char));
    e->alunos_inscritos = init_listaA();

    printf("Disciplina\n");
    e->disciplina = cria_disciplina();
    printf("Data\n");
    e->data = cria_data();
    printf("Duracao\n");
    e->duracao = cria_hora();
    fflush(stdin);
    printf("Epoca: ");
    gets(e->epoca);
    fflush(stdin);
    printf("Sala: ");
    scanf("%d", &e->sala);
    return e;
}

/* Funcoes para inicializar as listas ligadas (criar o primeiro node e deixar a NULL) */

Node_disciplina* init_listaD()
{
    Node_disciplina *primeiro_node;
    primeiro_node = malloc(sizeof(Node_disciplina));
    primeiro_node->info = NULL;
    primeiro_node->next = NULL;
    return primeiro_node;
}

Node_aluno* init_listaA()
{
    Node_aluno *primeiro_node;
    primeiro_node = malloc(sizeof(Node_aluno));
    primeiro_node->info = NULL;
    primeiro_node->next = NULL;
    return primeiro_node;
}

Node_exame* init_listaE()
{
    Node_exame *primeiro_node;
    primeiro_node = malloc(sizeof(Node_exame));
    primeiro_node->info = NULL;
    primeiro_node->next = NULL;
    return primeiro_node;
}

/* Funcoes para inserir um node na lista ligada */

void inserir_listaD(Node_disciplina *listaD, Disciplina *novaD)
{
    Node_disciplina *novo_node;

    if (listaD->info == NULL) {
        listaD->info = novaD;
    } else {
        while (listaD->next != NULL)
            listaD = listaD->next;

        /* quando chega ate ao fim */
        novo_node = malloc(sizeof(Node_disciplina));
        novo_node->info = novaD;
        novo_node->next = NULL;
        listaD->next = novo_node;
    }
}

void inserir_listaA(Node_aluno *listaA, Aluno *novoA)
{
    Node_aluno *novo_node;

    if (listaA->info == NULL) {
        listaA->info = novoA;
    } else {
        while (listaA->next != NULL)
            listaA = listaA->next;
        /* a mesma coisa */
        novo_node = malloc(sizeof(Node_aluno));
        novo_node->info = novoA;
        novo_node->next = NULL;
        listaA->next = novo_node;
    }
}
