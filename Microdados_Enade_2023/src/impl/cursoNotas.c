#include"../header/cursoNotas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../header/util.h"

typedef struct Nodo {
    int id;
    CursoNotas *curso;
    struct Nodo *prox; // para tratar colisões com lista encadeada
} Nodo;

#define TAM_HASH 1000
Nodo* notasHashTable[TAM_HASH];
int* cursosNotasInseridos;
int totalCursos = 0;
FILE* arquivoParaLer;

void descartaPrimeiraLinhaNotas();
void InsereCursoNotasBaseadoNaLinha(char* linha);
void insereNanotasHashTable(CursoNotas* novoCursoNotas);

CursoNotas* getOrCreateCursoNotas(int CO_CURSO) {
    int indice = funcaoHash(CO_CURSO, TAM_HASH);
    Nodo* atual = notasHashTable[indice];

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

    insereNanotasHashTable(novoCursoNotas);

    return novoCursoNotas;
}

void insereNanotasHashTable(CursoNotas* novoCursoNotas) {
    if(cursosNotasInseridos != NULL){
        cursosNotasInseridos = realloc(cursosNotasInseridos, (totalCursos + 1) * sizeof(int));
    }
    else{
        cursosNotasInseridos = malloc(sizeof(int));
    }
    
    totalCursos++;
    cursosNotasInseridos[totalCursos - 1] = novoCursoNotas->CO_CURSO;

    int indice = funcaoHash(novoCursoNotas->CO_CURSO, TAM_HASH);
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    novoNodo->id = novoCursoNotas->CO_CURSO;
    novoNodo->curso = novoCursoNotas;
    novoNodo->prox = notasHashTable[indice];
    notasHashTable[indice] = novoNodo;
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
    descartaColuna(22);
    token = strtok(NULL, ";");
    double NT_GER = token == NULL ? 0.0 : atof(token);
    descartaColuna(6);
    token = strtok(NULL, ";");
    double NT_CE = token == NULL ? 0.0 : atof(token);//pega NT_CE
    CursoNotas* cursoNotas = getOrCreateCursoNotas(CO_CURSO);
    cursoNotas->NT_GER = insertInArray(cursoNotas->NT_GER, NT_GER, cursoNotas->numberOfNT_GER);
    cursoNotas->numberOfNT_GER++;
    cursoNotas->NT_CE = insertInArray(cursoNotas->NT_CE, NT_CE, cursoNotas->numberOfNT_CE);
    cursoNotas->numberOfNT_CE++;
}

void printarCursosNotas() {
    for (int i = 0; i < totalCursos; i++) {
        int CO_CURSO = cursosNotasInseridos[i];
        int indice = funcaoHash(CO_CURSO, TAM_HASH);
        Nodo* atual = notasHashTable[indice];

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

void liberarCursosNotas() {
    for (int i = 0; i < TAM_HASH; i++) {
        Nodo* atual = notasHashTable[i];
        while (atual != NULL) {
            Nodo* temp = atual;
            atual = atual->prox;
            if(temp->curso != NULL){
                if(temp->curso->NT_CE != NULL) free(temp->curso->NT_CE);
                if(temp->curso->NT_GER != NULL) free(temp->curso->NT_GER);
                free(temp->curso);
            }
            free(temp);
        }
    }
    free(cursosNotasInseridos);
}



