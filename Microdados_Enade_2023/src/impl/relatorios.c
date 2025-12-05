#include "../header/relatorios.h"
#include "../header/cursoNotas.h"
#include "../header/curso.h"
#include <stdio.h>

void mostraInformacoesSobreCurso(int CO_CURSO){
    printaInformacoesSobreCurso(CO_CURSO);
}
void carregarCursosNotasRelatorio(char *arquivo){
    carregarCursosNotas(arquivo);
}
void carregarInfosCursosRelatorio(char *arquivo){
    carregarCursos(arquivo);
}

void liberaMemoria(){
    liberarCursosNotas();
    liberarCursos();
}

void printarrCursos(){
    printarCursos();
}

void printaCursosBaseadoNaUF(int CO_UF_CURSO){
    getCursosPorUF(CO_UF_CURSO);
}