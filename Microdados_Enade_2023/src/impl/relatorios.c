#include "../header/relatorios.h"
#include "../header/cursoNotas.h"
#include "../header/curso.h"
#include <stdio.h>

void printaSobreCurso(int CO_CURSO){
    mostraInformacoesSobreCurso(CO_CURSO);
}
void carregarCursosNotasRelatorio(char *arquivo){
    carregarCursosNotas(arquivo);
}
void carregarInfosCursosRelatorio(char *arquivo){
    carregarCursos(arquivo);
}

void pesquisaCursoPorUF(int CO_UF_CURSO){
    printaComBaseEmUF(CO_UF_CURSO);
}

void liberaMemoria(){
    liberarCursosNotas();
    liberarCursos();
}

void printarrCursos(){
    printarCursos();
}