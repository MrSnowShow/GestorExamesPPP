#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/* Funcoes de print das estruturas */

void print_data(Data d);
void print_hora(Hora h);
void print_disciplina(Disciplina *d);
void print_aluno(Aluno *a);
void print_exame(Exame *e);

/* Funcoes para dar print as listas ligadas */

void print_listaD(Node_disciplina *listaD);
void print_listaA(Node_aluno *listaA);
void print_listaE(Node_exame *listaE);

/* Funcoes para criar as estruturas */

Data cria_data();
Hora cria_hora();
Disciplina* cria_disciplina();
Aluno* cria_aluno();
Exame* cria_exame();

/* Funcoes para inicializar (criar) as listas ligadas */

Node_disciplina* init_listaD();
Node_aluno* init_listaA();
Node_exame* init_listaE();

/* Funcoes para inserir nas listas ligadas */

void inserir_listaD(Node_disciplina *listaD, Disciplina *novaD);
void inserir_listaA(Node_aluno *listaA, Aluno *novoA);

#endif /* FUNCOES_H_INCLUDED */
