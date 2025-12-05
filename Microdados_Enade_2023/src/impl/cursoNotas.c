#include"../header/cursoNotas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct CursoNotas {
    double* NT_CE;//componente especifico
    double* NT_GER; //componente geral
    double media_NT_CE;
    double media_NT_GER;
    int CO_CURSO;
    int numberOfNT_CE;
    int numberOfNT_GER;
} CursoNotas;

typedef struct Nodo {
    int id;
    CursoNotas *curso;
    struct Nodo *prox; // para tratar colisões com lista encadeada
} Nodo;

#define TAM_HASH 1000
Nodo* tabela[TAM_HASH];
int* cursosInseridos;
int totalCursos = 0;
FILE* arquivoParaLer;

void descartaPrimeiraLinhaNotas();
void InsereCursoNotasBaseadoNaLinha(char* linha);
void insereNaTabela(CursoNotas* novoCursoNotas);


int funcaoHash(int chave) {
    unsigned int hash = chave * 2654435761u;
    return hash % TAM_HASH;
}

CursoNotas* getOrCreateCursoNotas(int CO_CURSO) {
    if(CO_CURSO == 50623){
        printf("DebugAqui");
    }
    int indice = funcaoHash(CO_CURSO);
    Nodo* atual = tabela[indice];

    while (atual != NULL) {
        if (atual->id == CO_CURSO) {
            return atual->curso;
        }
        atual = atual->prox;
    }

    CursoNotas* novoCursoNotas = (CursoNotas*)malloc(sizeof(CursoNotas));
    novoCursoNotas->CO_CURSO = CO_CURSO;
    novoCursoNotas->NT_CE = NULL;
    novoCursoNotas->NT_GER = NULL;
    novoCursoNotas->media_NT_CE = 0.0;
    novoCursoNotas->media_NT_GER = 0.0;
    novoCursoNotas->numberOfNT_CE = 0;
    novoCursoNotas->numberOfNT_GER = 0;

    insereNaTabela(novoCursoNotas);

    return novoCursoNotas;
}

void insereNaTabela(CursoNotas* novoCursoNotas) {
    if(cursosInseridos != NULL){
        cursosInseridos = realloc(cursosInseridos, (totalCursos + 1) * sizeof(int));
    }
    else{
        cursosInseridos = malloc(sizeof(int));
    }
    
    totalCursos++;
    cursosInseridos[totalCursos - 1] = novoCursoNotas->CO_CURSO;

    int indice = funcaoHash(novoCursoNotas->CO_CURSO);
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->id = novoCursoNotas->CO_CURSO;
    novoNodo->curso = novoCursoNotas;
    novoNodo->prox = tabela[indice];
    tabela[indice] = novoNodo;
}

void carregarCursosNotas(char *arquivo) {
    arquivoParaLer = fopen(arquivo, "r");
    
    if (arquivoParaLer == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    descartaPrimeiraLinhaNotas();
    char linha[2048];

    while (fgets(linha, sizeof(linha), arquivoParaLer)) {
        // Verifica se a linha está vazia
        if (strlen(linha) == 0) {
            printf("Erro: Linha está vazia.\n");
            continue;
        }
        InsereCursoNotasBaseadoNaLinha(linha);
    }
    fclose(arquivoParaLer);
}

void descartaPrimeiraLinhaNotas(){
    char linha[2048];
    fgets(linha, sizeof(linha), arquivoParaLer);
}

void descartaColuna(int qntsColunasDescartar){
    char* token = NULL;
    for(int i = 0; i < qntsColunasDescartar; i++){
        token = strtok(NULL, ";");
        if(token == NULL){
            return;
        }
    }
    return;
}

double* insertInArray(double* array, double newValue, int currentSize) {
    if (array == NULL) {
        array = malloc((currentSize + 1) * sizeof(double));
    } else {
        array = realloc(array, (currentSize + 1) * sizeof(double));
    }
    if (array == NULL) {
        printf("Erro ao realocar memória.\n");
        exit(1);
    }
    array[currentSize] = newValue; // Adiciona o novo valor na última posição
    return array;
}


void InsereCursoNotasBaseadoNaLinha(char* linha) {
    char* token = NULL;
    strtok(linha, ";");//descarta NU_ANO
    int CO_CURSO;
    CO_CURSO = atoi(strtok(NULL, ";"));//pega CO_CURSO
    printf("CO_CURSO lido: %d\n", CO_CURSO);
    descartaColuna(22);
    token = strtok(NULL, ";");
    double NT_GER = token == NULL ? 0.0 : atof(token);
    descartaColuna(6);
    token = strtok(NULL, ";");
    double NT_CE = token == NULL ? 0.0 : atof(token);//pega NT_CE
    CursoNotas* cursoNotas = getOrCreateCursoNotas(CO_CURSO);
    if(CO_CURSO == 50623){
        printf("DebugAqui2\n");
    }
    cursoNotas->NT_GER = insertInArray(cursoNotas->NT_GER, NT_GER, cursoNotas->numberOfNT_GER);
    cursoNotas->numberOfNT_GER++;
    cursoNotas->NT_CE = insertInArray(cursoNotas->NT_CE, NT_CE, cursoNotas->numberOfNT_CE);
    cursoNotas->numberOfNT_CE++;
}

void printarCursosNotas() {
    for (int i = 0; i < totalCursos; i++) {
        int CO_CURSO = cursosInseridos[i];
        int indice = funcaoHash(CO_CURSO);
        Nodo* atual = tabela[indice];

        while (atual != NULL) {
            if (atual->id == CO_CURSO) {
                CursoNotas* curso = atual->curso;
                printf("CO_CURSO: %d\n", curso->CO_CURSO);
                printf("NT_GER: ");
                for (int j = 0; j < curso->numberOfNT_GER; j++) {
                    printf("%.2f ", curso->NT_GER[j]);
                }
                printf("\nNT_CE: ");
                for (int j = 0; j < curso->numberOfNT_CE; j++) {
                    printf("%.2f ", curso->NT_CE[j]);
                }
                printf("\n\n");
                break;
            }
            atual = atual->prox;
        }
    }
}



