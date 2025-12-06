#ifndef CURSO_AND_NOTA_H
#define CURSO_AND_NOTA_H
typedef struct CursoENota{
    int CO_CURSO;
    double notaGenerica;
    struct CursoENota* prox;
} CursoENota;
#endif