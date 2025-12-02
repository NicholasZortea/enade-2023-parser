#include"../header/curso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

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

static int totalCursos = 0;
static Curso *listaCursos = NULL;
static FILE *arquivoParaLer;
static int linhaLida = 0;

void descartaPrimeiraLinha();
void InsereCursoBaseadoNaLinha(char *linha);

void carregarCursos(char *nomeArquivo) {
    arquivoParaLer = fopen(nomeArquivo, "r");
    
    if (arquivoParaLer == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    descartaPrimeiraLinha();
    char linha[1048];

    while (fgets(linha, sizeof(linha), arquivoParaLer)) {
        linhaLida++;

        // Verifica se a linha está vazia
        if (strlen(linha) == 0) {
            printf("Erro: Linha %d está vazia.\n", linhaLida);
            continue;
        }
        InsereCursoBaseadoNaLinha(linha);
    }
    fclose(arquivoParaLer);
}

void InsereCursoBaseadoNaLinha(char *linha) {
    Curso novoCurso;

    char *token;

    // Descarta o primeiro campo (NU_ANO)
    token = strtok(linha, ";");
    if (token == NULL) {
        printf("Erro: Linha %d está malformada (campo NU_ANO ausente). Linha: %s\n", linhaLida, linha);
        exit(1);
    }
    

    // Parseia os campos restantes
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha %d está malformada (campo CO_CURSO ausente). Linha: %s\n", linhaLida, linha); exit(1); }
    novoCurso.CO_CURSO = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha %d está malformada (campo CO_IES ausente). Linha: %s\n", linhaLida, linha); exit(1); }
    novoCurso.CO_IES = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha %d está malformada (campo CO_CATEGAD ausente). Linha: %s\n", linhaLida, linha); exit(1); }
    novoCurso.CO_CATEGAD = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha %d está malformada (campo CO_ORGACAD ausente). Linha: %s\n", linhaLida, linha); exit(1); }
    novoCurso.CO_ORGACAD = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha %d está malformada (campo CO_GRUPO ausente). Linha: %s\n", linhaLida, linha); exit(1); }
    novoCurso.CO_GRUPO = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha %d está malformada (campo CO_MODALIDADE ausente). Linha: %s\n", linhaLida, linha); exit(1); }
    novoCurso.CO_MODALIDADE = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha %d está malformada (campo CO_MUNIC_CURSO ausente). Linha: %s\n", linhaLida, linha); exit(1); }
    novoCurso.CO_MUNIC_CURSO = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha %d está malformada (campo CO_UF_CURSO ausente). Linha: %s\n", linhaLida, linha); exit(1); }
    novoCurso.CO_UF_CURSO = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha %d está malformada (campo CO_REGIAO_CURSO ausente). Linha: %s\n", linhaLida, linha); exit(1); }
    novoCurso.CO_REGIAO_CURSO = atoi(token);
    
    // Verifica se há tokens extras
    token = strtok(NULL, ";");
    if (token != NULL) {
        printf("Erro: Linha %d contém mais campos do que o esperado. Token extra: %s. Linha: %s\n", linhaLida, token, linha);
        exit(1);
    }

    // Adiciona o curso à lista
    totalCursos++;
    listaCursos = (Curso *)realloc(listaCursos, totalCursos * sizeof(Curso));
    if (listaCursos == NULL) {
        printf("Erro: Falha ao realocar memória para lista de cursos.\n");
        exit(1);
    }
    listaCursos[totalCursos - 1] = novoCurso;
}

void printarCursos(){
    for(int i = 0; i < totalCursos; i++){
        printf("Curso %d: CO_CURSO=%d, CO_IES=%d, CO_CATEGAD=%d, CO_ORGACAD=%d, CO_GRUPO=%d, CO_MODALIDADE=%d, CO_MUNIC_CURSO=%d, CO_UF_CURSO=%d, CO_REGIAO_CURSO=%d\n",
               i + 1,
               listaCursos[i].CO_CURSO,
               listaCursos[i].CO_IES,
               listaCursos[i].CO_CATEGAD,
               listaCursos[i].CO_ORGACAD,
               listaCursos[i].CO_GRUPO,
               listaCursos[i].CO_MODALIDADE,
               listaCursos[i].CO_MUNIC_CURSO,
               listaCursos[i].CO_UF_CURSO,
               listaCursos[i].CO_REGIAO_CURSO);
    }
}

void liberarCursos(){
    free(listaCursos);
    listaCursos = NULL;
    totalCursos = 0;
}

void descartaPrimeiraLinha(){
    char linha[256];
    fgets(linha, sizeof(linha), arquivoParaLer); //descarta primeira linha
}
