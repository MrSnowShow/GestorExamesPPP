#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

/*
 * Primeiro declaram-se as estruturas
 * 1. Data
 * 2. Hora
 * 3. Disciplina
 * 4. Aluno (com lista ligada de exames inscritos definida em baixo)
 * 5. Exame (com lista ligada de alunos inscritos definida em baixo)
 */

typedef struct data {
    int dia, mes, ano;
} Data;

typedef struct hora {
    int horas, minutos;
} Hora;

typedef struct disciplina {
    char *nome;
    char *docente;
} Disciplina;

typedef struct aluno {
    int id;
    int matricula;
    char *curso;
    char *regime;
    struct lista_exames *exames_inscritos;
} Aluno;

typedef struct exame {
    Disciplina disciplina;
    Data data;
    Hora duracao;
    char *epoca;
    int sala;
    struct lista_alunos *alunos_inscritos;
} Exame;

/*
 * Depois as listas ligadas
 * 1. Lista_alunos
 * 2. Lista_exames
 * 3. Lista_disciplinas
 */

typedef struct lista_alunos {
    Aluno *info;
    struct lista_aluno *next;
} Lista_alunos;

typedef struct lista_exames {
    Exame *info;
    struct lista_exame *next;
} Lista_exames;

typedef struct lista_disciplinas {
    Disciplina info;
    struct lista_disciplinas *next;
} Lista_disciplinas;

#endif /* STRUCTS_H_INCLUDED */
