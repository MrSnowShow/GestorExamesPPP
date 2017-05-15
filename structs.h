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
    struct node_exame *exames_inscritos;
} Aluno;

typedef struct exame {
    Disciplina *disciplina;
    Data data;
    Hora duracao;
    char *epoca;
    int sala;
    struct node_aluno *alunos_inscritos;
} Exame;

/*
 * Depois os nodes (nós em portugues) das listas ligadas
 * 1. Lista_alunos
 * 2. Lista_exames
 * 3. Lista_disciplinas
 */

typedef struct node_aluno {
    Aluno *info;
    struct node_aluno *next;
} Node_aluno;

typedef struct node_exame {
    Exame *info;
    struct node_exame *next;
} Node_exame;

typedef struct node_disciplina {
    Disciplina *info;
    struct node_disciplina *next;
} Node_disciplina;

#endif /* STRUCTS_H_INCLUDED */
