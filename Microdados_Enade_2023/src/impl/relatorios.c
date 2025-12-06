#include "../header/relatorios.h"
#include "../header/cursoNotas.h"
#include "../header/curso.h"
#include "../header/cursoAndNota.h"
#include <stdio.h>
#include <stdlib.h>

void fazJoinComCursoEPrintaGer(CursoENota* listaDeNotas);
void fazJoinComCursoEPrintaEspec(CursoENota* listaDeNotas);
void liberaNotas(CursoENota* listaDeNotas);

void printaSobreCurso(int CO_CURSO){
    mostraInformacoesSobreCurso(CO_CURSO);
}
void carregarCursosNotasRelatorio(char *arquivo){
    carregarCursosNotas(arquivo);
}
void carregarInfosCursosRelatorio(char *arquivo){
    carregarCursos(arquivo);
}

void pesquisarNotasDoCurso(int CO_CURSO){
    mostrarInformacoesSobreNotasDoCurso(CO_CURSO);
}

void pesquisarMaioresNotas(int nNotas, int geral){
    if(geral == 1){
        printf("As %d maiores notas gerais são:\n", nNotas);
        CursoENota* maioresNotasGerais = getNMaioresNotasGerais(nNotas);
        fazJoinComCursoEPrintaGer(maioresNotasGerais);
        liberaNotas(maioresNotasGerais);
    } else {
        printf("As %d maiores notas específicas são:\n", nNotas);
        CursoENota* maioresNotasEspecificas = getNMaioresNotasEspecificas(nNotas);
        fazJoinComCursoEPrintaEspec(maioresNotasEspecificas);
        liberaNotas(maioresNotasEspecificas);
    }
}

void liberaNotas(CursoENota* listaDeNotas){
    CursoENota* atual = listaDeNotas;
    while(atual != NULL){
        CursoENota* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

void fazJoinComCursoEPrintaGer(CursoENota* listaDeNotas){
    CursoENota* atual = listaDeNotas;
    Curso* curso = NULL;
    while(atual != NULL){
        if(curso == NULL || curso->CO_CURSO != atual->CO_CURSO){
            curso = getCurso(atual->CO_CURSO);//pesquisa curso apenas se necessário
        }
        Curso* curso = getCurso(atual->CO_CURSO);
        printf("CO_CURSO: %d, NT_GER: %.2f, IES: %d\n", curso->CO_CURSO, atual->notaGenerica, curso->CO_IES);
        atual = atual->prox;
    }
}

void fazJoinComCursoEPrintaEspec(CursoENota* listaDeNotas){
    CursoENota* atual = listaDeNotas;
    Curso* curso = NULL;
    while(atual != NULL){
        if(curso == NULL || curso->CO_CURSO != atual->CO_CURSO){
            curso = getCurso(atual->CO_CURSO);//pesquisa curso apenas se necessário
        }
        Curso* curso = getCurso(atual->CO_CURSO);
        printf("CO_CURSO: %d, NT_CE: %.2f, IES: %d\n", curso->CO_CURSO, atual->notaGenerica, curso->CO_IES);
        atual = atual->prox;
    }
}

void pesquisaCursoPorUF(int CO_UF_CURSO){
    printaComBaseEmUF(CO_UF_CURSO);
}

void pesquisaCursoPorIES(int CO_IES){
    printaComBaseEmIES(CO_IES);
}

void pesquisaCursoPorGRUPO(int CO_GRUPO){
    printaComBaseEmGrupo(CO_GRUPO);
}

void liberaMemoria(){
    liberarCursosNotas();
    liberarCursos();
}

void printarrCursos(){
    printarCursos();
}