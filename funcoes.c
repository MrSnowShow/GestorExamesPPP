#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "funcoes.h"


/* Funcoes auxiliares */

void remove_barraN(char *minha_string)
{
    minha_string[strlen(minha_string)-1] = '\0';
}

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
    print_listaExames(a->exames_inscritos);
}

void print_exame(Exame *e)
{
    print_disciplina(e->disciplina);
    print_data(e->data);
    print_hora(e->duracao);
    printf("Epoca:\t\t%s\n", e->epoca);
    printf("Sala:\t\t%d\n", e->sala);
    print_listaAlunos(e->alunos_inscritos);
}

void print_listaDisciplinas(Node_disciplina *listaD)
{
    printf("\nLista de disciplinas\n");
    listaD = listaD->next;
    while (listaD != NULL) {
        print_disciplina(listaD->info);
        printf("\n");
        listaD = listaD->next;
    }
}

void print_listaAlunos(Node_aluno *listaA)
{
    if (listaA->next == NULL) {
        printf("Nao ha alunos!\n");
        return;
    }
    listaA = listaA->next;
    printf("\nLista de alunos\n");
    while (listaA != NULL) {
        print_aluno(listaA->info);
        printf("\n");
        listaA = listaA->next;
    }
}

void print_listaExames(Node_exame *listaE)
{
    if (listaE->next == NULL) {
        printf("Nao ha exames!\n");
        return;
    }
    listaE = listaE->next;
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
    d = init_disciplina();

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
    a = init_aluno();

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
    e = init_exame();

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
    gets(e->sala);
    fflush(stdin);
    return e;
}

/* Funcoes para inicializar (fazer mallocs) as estruturas */

Disciplina* init_disciplina()
{
    Disciplina *d;
    d = malloc(sizeof(Node_disciplina));
    d->nome = malloc(MAX*sizeof(char));
    d->docente = malloc(MAX*sizeof(char));
    return d;
}
Aluno* init_aluno()
{
    Aluno *a;
    a = malloc(sizeof(Aluno));
    a->exames_inscritos = init_nodeExame();

    return a;
}
Exame* init_exame()
{
    Exame *e;
    e = malloc(sizeof(Exame));
    e->alunos_inscritos = init_nodeAluno();

    return e;
}

/* Funcoes para inicializar as listas ligadas (criar o primeiro node e deixar os campos a NULL) */

Node_disciplina* init_nodeDisciplina()
{
    Node_disciplina *primeiro_node;
    primeiro_node = malloc(sizeof(Node_disciplina));
    primeiro_node->info = NULL;
    primeiro_node->next = NULL;
    return primeiro_node;
}

Node_aluno* init_nodeAluno()
{
    Node_aluno *primeiro_node;
    primeiro_node = malloc(sizeof(Node_aluno));
    primeiro_node->info = NULL;
    primeiro_node->next = NULL;
    return primeiro_node;
}

Node_exame* init_nodeExame()
{
    Node_exame *primeiro_node;
    primeiro_node = malloc(sizeof(Node_exame));
    primeiro_node->info = NULL;
    primeiro_node->next = NULL;
    return primeiro_node;
}

/* Funcoes para inserir um node na lista ligada */

void inserir_listaDisciplinas(Node_disciplina *listaD, Disciplina *novaDisciplina)
{
    Node_disciplina *novo_node;

    while (listaD->next != NULL)
        listaD = listaD->next;

    /* quando chega ate ao fim */
    novo_node = init_nodeDisciplina();
    novo_node->info = novaDisciplina;
    listaD->next = novo_node;
}

void inserir_listaAlunos(Node_aluno *listaA, Aluno *novoAluno)
{
    Node_aluno *novo_node;

    while (listaA->next != NULL)
        listaA = listaA->next;

    novo_node = init_nodeAluno();
    novo_node->info = novoAluno;
    listaA->next = novo_node;
}

void inserir_listaExames(Node_exame *listaE, Exame *novoExame)
{
    Node_exame *novo_node;

    while (listaE->next != NULL)
        listaE = listaE->next;

    novo_node = init_nodeExame();
    novo_node->info = novoExame;
    listaE->next = novo_node;
}

/* Funcoes para remover da lista ligada */

void remover_listaDisciplinas(Node_disciplina *listaD, char *nome)
{
    Node_disciplina *anterior;
    anterior = listaD;
    listaD = listaD->next;

    while (strcmp(nome, listaD->info->nome) != 0) {
        anterior = anterior->next;
        listaD = listaD->next;
    }

    anterior->next = listaD->next;
    free(listaD);

}

/* funcoes para ler ficheiros */

Node_disciplina* ler_disciplinas()
{
    FILE *txt;
    Disciplina *d;
    Node_disciplina *listaD;
    char linha[MAX];

    listaD = init_nodeDisciplina();

    txt = fopen("disciplinas.txt", "r");

    fgets(linha, MAX, txt);
    remove_barraN(linha);
    while (strcmp(linha, "")) {
        if (strcmp(linha, "-") == 0) {
            d = init_disciplina();

            fgets(linha, MAX, txt);
            remove_barraN(linha);

            strcpy(d->nome, linha);

            fgets(linha, MAX, txt);
            remove_barraN(linha);

            strcpy(d->docente, linha);

            inserir_listaDisciplinas(listaD, d);
        }
        fgets(linha, MAX, txt);
        remove_barraN(linha);
    }
    fclose(txt);
    return listaD;
}

