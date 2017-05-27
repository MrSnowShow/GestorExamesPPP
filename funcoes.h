#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

/* Funcoes auxiliares */
void remove_barraN(char *minha_string);
Hora fim_exame(Exame *e);
int exame_sobreposto(Node_exame *listaE, Exame *e);

/* Funcoes para inicializar (fazer mallocs) as estruturas de pointeiros */
Disciplina* init_disciplina();
Aluno* init_aluno();
Exame* init_exame();

/* Funcoes para inicializar (fazer malloc e por a NULL) as listas ligadas */
Node_disciplina* init_nodeDisciplina();
Node_aluno* init_nodeAluno();
Node_exame* init_nodeExame();

/* Funcoes para criar as estruturas apartir do utilizador */
Hora cria_hora();
Data cria_data();
Disciplina* cria_disciplina();
Aluno* cria_aluno();
Exame* cria_exame(Node_disciplina *disciplinas_existentes, Node_exame *exames_existentes);

/* Funcoes de print das estruturas */
void print_hora(Hora h);
void print_data(Data d);
void print_disciplina(Disciplina *d);
void print_aluno(Aluno *a);
void print_exame(Exame *e);

/* Funcoes para dar print a cada elemento da lista ligada */
void print_listaDisciplinas(Node_disciplina *listaD);
void print_listaAlunos(Node_aluno *listaA);
void print_listaExames(Node_exame *listaE);

/* Funcoes para procurar nas listas ligadas */
Node_disciplina* procurar_listaDisciplinas(Node_disciplina *listaD, char *nome);

/* Funcoes para inserir nas listas ligadas */
void inserir_listaDisciplinas(Node_disciplina *listaD, Disciplina *novaD);
void inserir_listaAlunos(Node_aluno *listaA, Aluno *novoA);
void inserir_listaExames(Node_exame *listaE, Exame *novoE);

/* Funcoes para remover da lista ligada */
void remover_listaDisciplinas(Node_disciplina *listaD, char *nome);

/* Funcoes para ler dos ficheiros */
Node_disciplina* ler_disciplinas(char *ficheiro);
Node_aluno* ler_alunos(char *ficheiro);
Node_exame* ler_exames(char *ficheiro);

#endif /* FUNCOES_H_INCLUDED */
