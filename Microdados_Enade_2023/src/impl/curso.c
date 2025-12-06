#include"../header/curso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../header/util.h"

typedef struct Nodo {
    int id;
    Curso *curso;
    struct Nodo *prox; // para tratar colisões com lista encadeada
} Nodo;

#define TAM_HASH 1000
Nodo* tabela[TAM_HASH];

//maior código é 53 
#define NUM_UFS 54
Nodo* tabelaUF[NUM_UFS]; 

int* cursosInseridos = NULL;
static int totalCursos = 0;
static FILE *arquivoParaLer;

void descartaPrimeiraLinha();
void InsereCursoBaseadoNaLinha(char *linha);
void printaCurso(Curso *curso);
void insereNosIndices(Curso* novoCurso);
void insereNoIndiceUF(Curso* novoCurso);
void liberaIndices();
void liberaIndicePorUF();

void carregarCursos(char *nomeArquivo) {
    arquivoParaLer = fopen(nomeArquivo, "r");
    
    if (arquivoParaLer == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    descartaPrimeiraLinha();
    char linha[1048];

    while (fgets(linha, sizeof(linha), arquivoParaLer)) {

        // Verifica se a linha está vazia
        if (strlen(linha) == 0) {
            printf("Erro: Linha está vazia.\n");
            continue;
        }
        InsereCursoBaseadoNaLinha(linha);
    }
    fclose(arquivoParaLer);
}

void insereCursoNaTabela(Curso* novoCurso) {
    if(cursosInseridos != NULL){
        cursosInseridos = realloc(cursosInseridos, (totalCursos + 1) * sizeof(int));
    }
    else{
        cursosInseridos = malloc(sizeof(int));
    }

    int indice = funcaoHash(novoCurso->CO_CURSO, TAM_HASH);
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->id = novoCurso->CO_CURSO;
    novoNodo->curso = novoCurso;
    novoNodo->prox = tabela[indice];
    tabela[indice] = novoNodo;
    insereNosIndices(novoCurso);
}

void insereNosIndices(Curso* novoCurso) {
    insereNoIndiceUF(novoCurso);
}

void insereNoIndiceUF(Curso* novoCurso) {
    int index = novoCurso->CO_UF_CURSO;

    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->id = index;
    novoNodo->curso = novoCurso;
    novoNodo->prox = tabelaUF[index];
    tabelaUF[index] = novoNodo;
}

Curso* getCurso(int CO_CURSO) {
    int indice = funcaoHash(CO_CURSO, TAM_HASH);

    Nodo* atual = tabela[indice];
    while (atual != NULL) {
        if (atual->id == CO_CURSO) {
            return atual->curso;
        }
        atual = atual->prox;
    }
    return NULL;
}

void createAndInsertCurso(Curso novoCurso) {
    Curso* cursoPtr = (Curso*)malloc(sizeof(Curso));
    *cursoPtr = novoCurso;
    insereCursoNaTabela(cursoPtr);
    totalCursos++;
    if(cursosInseridos != NULL){
        cursosInseridos = realloc(cursosInseridos, totalCursos * sizeof(int));
    }
    else{
        cursosInseridos = malloc(totalCursos * sizeof(int));
    }
    cursosInseridos[totalCursos - 1] = novoCurso.CO_CURSO;
}

void InsereCursoBaseadoNaLinha(char *linha) {
    
    char *token;

    // Descarta o primeiro campo (NU_ANO)
    token = strtok(linha, ";");
    if (token == NULL) {
        printf("Erro: Linha está malformada (campo NU_ANO ausente). Linha: %s\n", linha);
        exit(1);
    }

    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha está malformada (campo CO_CURSO ausente). Linha: %s\n", linha); exit(1); }
    int CO_CURSO = atoi(token);
    Curso* curso = getCurso(CO_CURSO);
    if(curso != NULL){
        // Curso já existe, não insere novamente
        return;
    }

    Curso novoCurso;
    novoCurso.CO_CURSO = CO_CURSO;
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha está malformada (campo CO_IES ausente). Linha: %s\n", linha); exit(1); }
    novoCurso.CO_IES = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha está malformada (campo CO_CATEGAD ausente). Linha: %s\n", linha); exit(1); }
    novoCurso.CO_CATEGAD = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha está malformada (campo CO_ORGACAD ausente). Linha: %s\n", linha); exit(1); }
    novoCurso.CO_ORGACAD = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha está malformada (campo CO_GRUPO ausente). Linha: %s\n", linha); exit(1); }
    novoCurso.CO_GRUPO = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha está malformada (campo CO_MODALIDADE ausente). Linha: %s\n", linha); exit(1); }
    novoCurso.CO_MODALIDADE = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha está malformada (campo CO_MUNIC_CURSO ausente). Linha: %s\n", linha); exit(1); }
    novoCurso.CO_MUNIC_CURSO = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha está malformada (campo CO_UF_CURSO ausente). Linha: %s\n", linha); exit(1); }
    novoCurso.CO_UF_CURSO = atoi(token);
    
    token = strtok(NULL, ";");
    if (token == NULL) { printf("Erro: Linha está malformada (campo CO_REGIAO_CURSO ausente). Linha: %s\n", linha); exit(1); }
    novoCurso.CO_REGIAO_CURSO = atoi(token);
    
    // Verifica se há tokens extras
    token = strtok(NULL, ";");
    if (token != NULL) {
        printf("Erro: Linha contém mais campos do que o esperado. Token extra: %s. Linha: %s\n", token, linha);
        exit(1);
    }

    createAndInsertCurso(novoCurso);
}

void printarCursos(){
    for(int i = 0; i < totalCursos; i++){
        int CO_CURSO = cursosInseridos[i];
        Curso* curso = getCurso(CO_CURSO);
        if(curso != NULL){
            printf("CO_CURSO: %d, CO_IES: %d, CO_CATEGAD: %d, CO_ORGACAD: %d, CO_GRUPO: %d, CO_MODALIDADE: %d, CO_MUNIC_CURSO: %d, CO_UF_CURSO: %d, CO_REGIAO_CURSO: %d\n",
                curso->CO_CURSO,
                curso->CO_IES,
                curso->CO_CATEGAD,
                curso->CO_ORGACAD,
                curso->CO_GRUPO,
                curso->CO_MODALIDADE,
                curso->CO_MUNIC_CURSO,
                curso->CO_UF_CURSO,
                curso->CO_REGIAO_CURSO
            );
        }
    }
    printf("%d cursos carregados.\n", totalCursos);
}

void mostraInformacoesSobreCurso(int CO_CURSO){
    Curso* curso = getCurso(CO_CURSO);
    if(curso != NULL){
        printaCurso(curso);
    } else {
        printf("Curso com CO_CURSO %d não encontrado.\n", CO_CURSO);
    }
}

void printaComBaseEmUF(int CO_UF_CURSO){
    int index = CO_UF_CURSO;
    Nodo* atual = tabelaUF[index];
    if(atual == NULL){
        printf("Nenhum curso encontrado para a UF com código %d.\n", CO_UF_CURSO);
        return;
    }
    printf("Cursos na UF com código %d:\n", CO_UF_CURSO);
    while(atual != NULL){
        printaCurso(atual->curso);
        atual = atual->prox;
    }
}

void printaCurso(Curso *curso){
    if(curso != NULL){
        printf("CO_CURSO: %d, CO_IES: %d, CO_CATEGAD: %d, CO_ORGACAD: %d, CO_GRUPO: %d, CO_MODALIDADE: %d, CO_MUNIC_CURSO: %d, CO_UF_CURSO: %d, CO_REGIAO_CURSO: %d\n",
            curso->CO_CURSO,
            curso->CO_IES,
            curso->CO_CATEGAD,
            curso->CO_ORGACAD,
            curso->CO_GRUPO,
            curso->CO_MODALIDADE,
            curso->CO_MUNIC_CURSO,
            curso->CO_UF_CURSO,
            curso->CO_REGIAO_CURSO
        );
    }
}

void liberarCursos(){
    for(int i = 0; i < TAM_HASH; i++){
        Nodo* atual = tabela[i];
        while(atual != NULL){
            Nodo* temp = atual;
            atual = atual->prox;
            free(temp->curso);
            free(temp);
        }
    }
    free(cursosInseridos);
    liberaIndices();
}

void descartaPrimeiraLinha(){
    char linha[256];
    fgets(linha, sizeof(linha), arquivoParaLer); //descarta primeira linha
}

void liberaIndices(){
    liberaIndicePorUF();
}

void liberaIndicePorUF(){
    for(int i = 0; i < NUM_UFS; i++){
        Nodo* atual = tabelaUF[i];
        while(atual != NULL){
            Nodo* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}