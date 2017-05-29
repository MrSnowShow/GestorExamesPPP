#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "funcoes.h"

#define MAX 256

/* Funcoes auxiliares */
void remove_barraN(char *minha_string)
{
    minha_string[strlen(minha_string)-1] = '\0';
}

int data_cmp(Data d1, Data d2)
{
    int d1num = d1.dia + d1.mes*100 + d1.ano*10000;
    int d2num = d2.dia + d2.mes*100 + d2.ano*10000;

    return d1num == d2num ? 0 : (d1num<d2num ? -1 : 1);
}

int hora_cmp(Hora h1, Hora h2)
{
    int h1num = h1.horas*100 + h1.minutos;
    int h2num = h2.horas*100 + h2.minutos;

    return h1num == h2num ? 0 : (h1num<h2num ? -1 : 1);
}

int exame_cheio(Exame *e)
{
    return e->inscritos >= 30 ? 1 : 0;
}

Hora fim_exame(Exame *e)
{
    int overflow_hora; /* Se acontecer algo como 50 + 20 minutos entao overflow_hora = 1 */
    Hora fim;

    fim.minutos = (e->data.hora.minutos + e->duracao.minutos) % 60;
    fim.horas = e->data.hora.horas + e->duracao.horas;

    overflow_hora = (e->data.hora.minutos + e->duracao.minutos) / 60;
    fim.horas += overflow_hora;

    return fim;
}

int exame_sobreposto(Node_exame *listaE, Exame *e)
{
    Hora inicio1, inicio2;
    Hora fim1, fim2;

    inicio1 = e->data.hora;
    fim1 = fim_exame(e);

    listaE = listaE->next;
    while (listaE != NULL) {
        if (data_cmp(listaE->info->data, e->data) == 0 && strcmp(e->sala, listaE->info->sala) == 0) {

            inicio2 = listaE->info->data.hora;
            fim2 = fim_exame(listaE->info);

            /* Se o exame comecar antes do outro acabar, ou acabar depois do outro comecar */
            if (hora_cmp(fim1, inicio2) == 1 && hora_cmp(fim2, inicio1) == 1)
                return 1;
        }
        listaE = listaE->next;
    }
    return 0;
}

int pode_inscrever(Aluno *a, Exame *e)
{
    if (strcmp(e->epoca, "Especial") == 0) {
        if (strcmp(a->regime, "Estudante") != 0 || a->matricula >= 3)
            return 1;
        else
            return 0;
    }
    else
        return 1;
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
    a->curso = malloc(MAX*sizeof(char));
    a->regime = malloc(MAX*sizeof(char));
    a->exames_inscritos = init_nodeExame();

    return a;
}
Exame* init_exame()
{
    Exame *e;
    e = malloc(sizeof(Exame));
    e->disciplina = malloc(sizeof(Disciplina));
    e->disciplina->nome = malloc(MAX*sizeof(char));
    e->disciplina->docente = malloc(MAX*sizeof(char));
    e->epoca = malloc(MAX*sizeof(char));
    e->sala = malloc(MAX*sizeof(char));
    e->inscritos = 0;
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

/* Funcoes de criar */
Hora cria_hora()
{
    Hora h;
    printf("Horas: ");
    scanf("%d", &h.horas);
    printf("Minutos: ");
    scanf("%d", &h.minutos);
    return h;
}

Data cria_data()
{
    Data d;
    printf("Dia: ");
    scanf("%d", &d.dia);
    printf("Mes: ");
    scanf("%d", &d.mes);
    printf("Ano: ");
    scanf("%d", &d.ano);
    d.hora = cria_hora();
    return d;
}

Disciplina* cria_disciplina(Node_disciplina *disciplinas_existentes)
{
    Disciplina *d, *existe;
    d = init_disciplina();

    printf("Nome: ");
    gets(d->nome);

    existe = procurar_listaDisciplinas(disciplinas_existentes, d->nome);
    fflush(stdin);
    if (existe) {
        printf("Ja existe uma disciplina com esse nome!\n");
        return NULL;
    }

    printf("Docente: ");
    gets(d->docente);
    fflush(stdin);
    return d;
}

Aluno* cria_aluno(Node_aluno *alunos_existentes)
{
    Aluno *a, *existe;
    a = init_aluno();

    printf("ID: ");
    scanf("%d", &a->id);

    existe = procurar_listaAlunos(alunos_existentes, a->id);
    fflush(stdin);
    if (existe) {
        printf("Ja existe um aluno com esse id!\n");
        return NULL;
    }

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

Exame* cria_exame(Node_disciplina *disciplinas_existentes, Node_exame *exames_existentes)
{
    Exame *e;

    char nome[MAX];
    Disciplina *existe;

    e = init_exame();

    printf("Disciplina\n");
    printf("Nome da disciplina: ");
    gets(nome);
    existe = procurar_listaDisciplinas(disciplinas_existentes, nome);

    if (existe == NULL) {
        printf("A disciplina nao existe na base de dados!\n");
        return NULL;
    }

    e->disciplina = existe;

    printf("Data\n");
    e->data = cria_data();
    printf("Duracao\n");
    e->duracao = cria_hora();
    fflush(stdin);
    printf("Sala: ");
    gets(e->sala);
    fflush(stdin);

    if (exame_sobreposto(exames_existentes, e)) {
        printf("Fica sobreposto, a sala esta ocupada!\n");
        return NULL;
    }

    printf("Epoca: ");
    gets(e->epoca);
    fflush(stdin);
    return e;
}

/* Funcoes de print */
void print_hora(Hora h)
{
    printf("Hora:\t\t%dh%d\n", h.horas, h.minutos);
}

void print_data(Data d)
{
    printf("Data:\t\t%d/%d/%d\n", d.dia, d.mes, d.ano);
    print_hora(d.hora);
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
    /*print_listaExames(a->exames_inscritos);*/
}

void print_exame(Exame *e)
{
    print_disciplina(e->disciplina);
    print_data(e->data);
    printf("Duracao:\n");
    print_hora(e->duracao);
    printf("Epoca:\t\t%s\n", e->epoca);
    printf("Sala:\t\t%s\n", e->sala);
    /*print_listaAlunos(e->alunos_inscritos);*/
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
/* Funcoes para procurar nas listas ligadas */
Disciplina* procurar_listaDisciplinas(Node_disciplina *listaD, char *nome)
{
    listaD = listaD->next;
    while (listaD != NULL) {
        if (strcmp(nome, listaD->info->nome) == 0)
            return listaD->info;
        else
            listaD = listaD->next;
    }
    return NULL; /* Se nao encontrar entao retorna NULL */
}

Aluno* procurar_listaAlunos(Node_aluno *listaA, int id)
{
    listaA = listaA->next;
    while (listaA != NULL) {
        if (listaA->info->id == id)
            return listaA->info;
        else
            listaA = listaA->next;
    }
    return NULL;
}

Exame* procurar_listaExames(Node_exame *listaE, Data data)
{
    listaE = listaE->next;
    while (listaE != NULL) {
        if (data_cmp(listaE->info->data, data) == 0
        && hora_cmp(listaE->info->data.hora, data.hora) == 0)
            return listaE->info;
        else
            listaE = listaE->next;
    }
    return NULL;
}

/* Funcoes para alterar as informacoes */
void alterar_disciplina(Node_disciplina *disciplinas_existentes, Disciplina *alterada)
{
    Disciplina *temporaria;

    strcpy(alterada->nome, "temporario");
    printf("Novas informacoes\n");
    temporaria = cria_disciplina(disciplinas_existentes);

    strcpy(alterada->nome, temporaria->nome);
    strcpy(alterada->docente, temporaria->docente);

    free(temporaria->nome);
    free(temporaria->docente);
    free(temporaria);
}
void alterar_aluno(Node_aluno *alunos_existentes, Aluno *alterado)
{
    Aluno *temporario;

    alterado->id = -129591; /* mudamos o id para o cria_aluno() nao detectar se quiser deixar id igual */
    printf("Novas infomacoes\n");
    temporario = cria_aluno(alunos_existentes);

    alterado->id = temporario->id;
    alterado->matricula = temporario->matricula;
    strcpy(alterado->curso, temporario->curso);
    strcpy(alterado->regime, temporario->regime);

    free(temporario->curso);
    free(temporario->regime);
    free(temporario);
}

/* Funcoes para inserir na lista ligada */
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

    free(listaD->info->nome);
    free(listaD->info->docente);
    free(listaD->info);
    free(listaD);
}

void remover_listaAlunos(Node_aluno *listaA, int id)
{
    Node_aluno *anterior;
    anterior = listaA;
    listaA = listaA->next;

    while (listaA->info->id != id) {
        anterior = anterior->next;
        listaA = listaA->next;
    }

    anterior->next = listaA->next;

    free(listaA->info->curso);
    free(listaA->info->regime);
    free(listaA->info->exames_inscritos);
    free(listaA->info);
    free(listaA);
}

void remover_listaExames(Node_exame *listaE, Data data)
{
    Node_exame *anterior;
    anterior = listaE;
    listaE = listaE->next;

    while (data_cmp(listaE->info->data, data) != 0 && hora_cmp(listaE->info->data.hora, data.hora) != 0) {
        anterior = anterior->next;
        listaE = listaE->next;
    }
    anterior->next = listaE->next;
    free(listaE->info->disciplina->nome);
    free(listaE->info->disciplina->docente);
    free(listaE->info->disciplina);
    free(listaE->info->epoca);
    free(listaE->info->sala);
    free(listaE->info->alunos_inscritos);
    free(listaE->info);
    free(listaE);
}

/* funcoes para ler ficheiros */
Node_disciplina* ler_disciplinas(char *ficheiro)
{
    FILE *txt;
    Disciplina *d;
    Node_disciplina *listaD;
    char linha[MAX];

    listaD = init_nodeDisciplina();

    txt = fopen(ficheiro, "r");

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

Node_aluno* ler_alunos(char *ficheiro)
{
    FILE *txt;
    Aluno *a;
    Node_aluno *listaA;
    char linha[MAX];

    listaA = init_nodeAluno();

    txt = fopen(ficheiro, "r");

    fgets(linha, MAX, txt);
    remove_barraN(linha);
    while (strcmp(linha, "")) {
        if (strcmp(linha, "-") == 0) {
            a = init_aluno();

            fgets(linha, MAX, txt);
            remove_barraN(linha);
            a->id = atoi(linha);

            fgets(linha, MAX, txt);
            remove_barraN(linha);
            a->matricula = atoi(linha);

            fgets(linha, MAX, txt);
            remove_barraN(linha);
            strcpy(a->curso, linha);

            fgets(linha, MAX, txt);
            remove_barraN(linha);
            strcpy(a->regime, linha);

            inserir_listaAlunos(listaA, a);
        }
        fgets(linha, MAX, txt);
        remove_barraN(linha);
    }
    fclose(txt);
    return listaA;
}

Node_exame* ler_exames(char *ficheiro, Node_disciplina *disciplinas_existentes)
{
    FILE *txt;
    Exame *e;
    Node_exame *listaE;
    char linha[MAX];

    listaE = init_nodeExame();

    txt = fopen(ficheiro, "r");
    fgets(linha, MAX, txt);
    remove_barraN(linha);
    while (strcmp(linha, "")) {
        if (strcmp(linha, "-") == 0) {
            e = init_exame();
            /* Disciplinas (pesquisa nas disciplinas_existentes) */
            fgets(linha, MAX, txt);
            remove_barraN(linha);

            e->disciplina = procurar_listaDisciplinas(disciplinas_existentes, linha);

            /* Data */
            fgets(linha, MAX, txt);
            remove_barraN(linha);
            e->data.dia = atoi(linha);

            fgets(linha, MAX, txt);
            remove_barraN(linha);
            e->data.mes = atoi(linha);

            fgets(linha, MAX, txt);
            remove_barraN(linha);
            e->data.ano = atoi(linha);

            fgets(linha, MAX, txt);
            remove_barraN(linha);
            e->data.hora.horas = atoi(linha);

            fgets(linha, MAX, txt);
            remove_barraN(linha);
            e->data.hora.minutos = atoi(linha);
            /* Duracao */
            fgets(linha, MAX, txt);
            remove_barraN(linha);
            e->duracao.horas = atoi(linha);

            fgets(linha, MAX, txt);
            remove_barraN(linha);
            e->duracao.minutos = atoi(linha);
            /* Epoca */
            fgets(linha, MAX, txt);
            remove_barraN(linha);
            strcpy(e->epoca, linha);
            /* Sala */
            fgets(linha, MAX, txt);
            remove_barraN(linha);
            strcpy(e->sala, linha);

            inserir_listaExames(listaE, e);
        }
        fgets(linha, MAX, txt);
        remove_barraN(linha);
    }
    fclose(txt);
    return listaE;
}

/* Funcoes de funcionalidade */
void inscrever(Aluno *a, Exame *e)
{
    inserir_listaExames(a->exames_inscritos, e);
    inserir_listaAlunos(e->alunos_inscritos, a);
    e->inscritos += 1;
}

void desinscrever(Aluno *a, Exame *e)
{
    remover_listaAlunos(e->alunos_inscritos, a->id);
    remover_listaExames(a->exames_inscritos, e->data);
    e->inscritos -= 1;
}

void apagar_exames(Node_exame *listaE, Data data)
{
    Node_exame *head;
    head = listaE; /* Precisa-se para o argumento do remover */

    listaE = listaE->next;

    while (listaE != NULL) {
        if (data_cmp(listaE->info->data, data) <= 0) {
            /* Tem que desinscrever os alunos todos desse exame */
            listaE->info->alunos_inscritos = listaE->info->alunos_inscritos->next;
            if (listaE->info->alunos_inscritos != NULL) {
                while (listaE->info->alunos_inscritos != NULL) {
                    remover_listaExames(listaE->info->alunos_inscritos->info->exames_inscritos, listaE->info->data);
                    listaE->info->alunos_inscritos = listaE->info->alunos_inscritos->next;
                }
            }
            /* Por fim remove o exame da lista de exames */
            remover_listaExames(head, listaE->info->data);
        }
        listaE = listaE->next;
    }
}
