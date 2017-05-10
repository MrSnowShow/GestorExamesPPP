#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

#define MAX 256

/* Funcoes de print */

void print_aluno(Aluno *a)
{
    printf("ID:\t\t%d\n", a->id);
    printf("Matricula:\t%d\n", a->matricula);
    printf("Curso:\t\t%s\n", a->curso);
    printf("Regime:\t\t%s\n", a->regime);
}

void print_disciplina(Disciplina d)
{
    printf("Nome:\t\t%s\n", d.nome);
    printf("Docente:\t%s\n", d.docente);
}

void print_data(Data d)
{
    printf("Data:\t\t%d/%d/%d\n", d.dia, d.mes, d.ano);
}

void print_hora(Hora h)
{
    printf("Hora:\t\t%dh%d\n", h.horas, h.minutos);
}


void print_exame(Exame *e)
{
    print_disciplina(e->disciplina);
    print_data(e->data);
    print_hora(e->duracao);
    printf("Epoca:\t\t%s\n", e->epoca);
    printf("Sala:\t\t%d\n", e->sala);
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

Disciplina cria_disciplina()
{
    Disciplina d;
    d.nome = malloc(MAX*sizeof(char));
    d.docente = malloc(MAX*sizeof(char));

    printf("Nome: ");
    gets(d.nome);
    fflush(stdin);
    printf("Docente: ");
    gets(d.docente);
    fflush(stdin);
    return d;
}

Aluno* cria_aluno()
{
    Aluno *a;
    a = malloc(sizeof(Aluno));
    a->curso = malloc(MAX*sizeof(char));
    a->regime = malloc(MAX*sizeof(char));
    a->exames_inscritos = malloc(sizeof(Lista_exames));
    a->exames_inscritos->info = NULL;
    a->exames_inscritos->next = NULL;

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
    e->alunos_inscritos = malloc(sizeof(Lista_alunos));
    e->alunos_inscritos->info = NULL;
    e->alunos_inscritos->next = NULL;

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
