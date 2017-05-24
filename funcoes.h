#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/* Funcoes auxiliares */

void remove_barraN(char *minha_string);

/* Funcoes de print das estruturas */

void print_data(Data d);
void print_hora(Hora h);
void print_disciplina(Disciplina *d);
void print_aluno(Aluno *a);
void print_exame(Exame *e);

/* Funcoes para dar print as listas ligadas */

void print_listaDisciplinas(Node_disciplina *listaD);
void print_listaAlunos(Node_aluno *listaA);
void print_listaExames(Node_exame *listaE);

/* Funcoes para criar as estruturas */

Data cria_data();
Hora cria_hora();
Disciplina* cria_disciplina();
Aluno* cria_aluno();
Exame* cria_exame();

/* Funcoes para inicializar (fazer mallocs) as estruturas de pointeiros */

Disciplina* init_disciplina();
Aluno* init_aluno();
Exame* init_exame();

/* Funcoes para inicializar (fazer malloc e por a NULL) as listas ligadas */

Node_disciplina* init_nodeDisciplina();
Node_aluno* init_nodeAluno();
Node_exame* init_nodeExame();

/* Funcoes para inserir nas listas ligadas */

void inserir_listaDisciplinas(Node_disciplina *listaD, Disciplina *novaD);
void inserir_listaAlunos(Node_aluno *listaA, Aluno *novoA);
void inserir_listaExames(Node_exame *listaE, Exame *novoE);

/* Funcoes para remover da lista ligada */
void remover_listaDisciplinas(Node_disciplina *listaD, char *nome);

/* Funcoes para ler dos ficheiros */

Node_disciplina* ler_disciplinas();

#endif /* FUNCOES_H_INCLUDED */
