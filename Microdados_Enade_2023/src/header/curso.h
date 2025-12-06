#ifndef CURSO_H
#define CURSO_H
typedef struct Curso {
    int CO_CURSO;
    int CO_IES;
    int CO_CATEGAD;
    int CO_ORGACAD;
    int CO_GRUPO;
    int CO_MODALIDADE;
    int CO_MUNIC_CURSO;
    int CO_UF_CURSO;
    int CO_REGIAO_CURSO;
} Curso;

void carregarCursos(char *arquivo);
void printarCursos();
void liberarCursos();
void mostraInformacoesSobreCurso(int CO_CURSO);
void printaComBaseEmUF(int CO_UF_CURSO);
#endif