#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/* Funcoes de print das estruturas */

void print_aluno(Aluno *a);
void print_disciplina(Disciplina d);
void print_data(Data d);
void print_hora(Hora h);
void print_exame(Exame *e);

/* Funcoes para criar as estruturas */

Data cria_data();
Hora cria_hora();
Disciplina cria_disciplina();
Aluno* cria_aluno();
Exame* cria_exame();

#endif /* FUNCOES_H_INCLUDED */
