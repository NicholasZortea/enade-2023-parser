#ifndef CURSO_NOTAS_H
#define CURSO_NOTAS_H
typedef struct CursoNotas {
    double* NT_CE;//componente especifico
    double* NT_GER; //componente geral
    double media_NT_CE;
    double media_NT_GER;
    int CO_CURSO;
    int numberOfNT_CE;
    int numberOfNT_GER;
} CursoNotas;

void carregarCursosNotas(char *arquivo);
void printarCursosNotas();
void liberarCursosNotas();
#endif