#ifndef RELATORIOS_H
#define RELATORIOS_H

void printaSobreCurso(int CO_CURSO);
void carregarCursosNotasRelatorio(char *arquivo);
void carregarInfosCursosRelatorio(char *arquivo);
void liberaMemoria();
void printarrCursos();
void pesquisaCursoPorUF(int CO_UF_CURSO);
void pesquisaCursoPorIES(int CO_IES);
void pesquisaCursoPorGRUPO(int CO_GRUPO);

#endif