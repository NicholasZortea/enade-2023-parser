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



#define TAM_HASH 1001
Nodo* notasHashTable[TAM_HASH];
int* cursosNotasInseridos;
int totalCursos = 0;
FILE* arquivoParaLer;

CursoENota* HASH_NOTAS_GERAIS[TAM_HASH];
CursoENota* HASH_NOTAS_ESPECIFICAS[TAM_HASH];

void descartaPrimeiraLinhaNotas();
void InsereCursoNotasBaseadoNaLinha(char* linha);
void insereNanotasHashTable(CursoNotas* novoCursoNotas);
void calculaMedias(CursoNotas* notas);
void insereNosIndicesDeNota(CursoNotas* cursoNotas);
void liberaIndicesNotas();

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
    novoCursoNotas->notasCalculadas = 0;

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

void insereNosIndicesDeNota(CursoNotas* cursoNotas){
        int indexGerais = cursoNotas->NT_GER[cursoNotas->numberOfNT_GER - 1] * 10;
    int indexEspecificas = cursoNotas->NT_CE[cursoNotas->numberOfNT_CE - 1] * 10;

    CursoENota* novoNodoGerais = (CursoENota*)malloc(sizeof(CursoENota));
    novoNodoGerais->CO_CURSO = cursoNotas->CO_CURSO;
    novoNodoGerais->notaGenerica = cursoNotas->NT_GER[cursoNotas->numberOfNT_GER - 1];
    novoNodoGerais->prox = NULL;

    if (HASH_NOTAS_GERAIS[indexGerais] == NULL) {
        HASH_NOTAS_GERAIS[indexGerais] = novoNodoGerais;
    } else {

        CursoENota* atual = HASH_NOTAS_GERAIS[indexGerais];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoNodoGerais;
    }

    CursoENota* novoNodoEspecificas = (CursoENota*)malloc(sizeof(CursoENota));
    novoNodoEspecificas->CO_CURSO = cursoNotas->CO_CURSO;
    novoNodoEspecificas->notaGenerica = cursoNotas->NT_CE[cursoNotas->numberOfNT_CE - 1];
    novoNodoEspecificas->prox = NULL;

    if (HASH_NOTAS_ESPECIFICAS[indexEspecificas] == NULL) {
        HASH_NOTAS_ESPECIFICAS[indexEspecificas] = novoNodoEspecificas;
    } else {
        CursoENota* atual = HASH_NOTAS_ESPECIFICAS[indexEspecificas];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoNodoEspecificas;
    }
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

CursoENota* getNMaioresNotasGerais(int n) {
    CursoENota* maioresNotas = NULL;
    int count = 0;

    for (int i = TAM_HASH - 1; i >= 0 && count < n; i--) {
        CursoENota* atual = HASH_NOTAS_GERAIS[i];
        while (atual != NULL && count < n) {
            // Cria um novo nó para a lista de maiores notas
            CursoENota* novo = (CursoENota*)malloc(sizeof(CursoENota));
            novo->CO_CURSO = atual->CO_CURSO;
            novo->notaGenerica = atual->notaGenerica;
            novo->prox = maioresNotas;
            maioresNotas = novo;

            count++;
            atual = atual->prox;
        }
    }

    return maioresNotas;
}

CursoENota* getNMaioresNotasEspecificas(int n) {
    CursoENota* maioresNotas = NULL; // Lista encadeada para armazenar as maiores notas
    int count = 0;

    // Percorre a tabela hash de notas específicas em ordem decrescente
    for (int i = TAM_HASH - 1; i >= 0 && count < n; i--) {
        CursoENota* atual = HASH_NOTAS_ESPECIFICAS[i];
        while (atual != NULL && count < n) {
            // Cria um novo nó para a lista de maiores notas
            CursoENota* novo = (CursoENota*)malloc(sizeof(CursoENota));
            novo->CO_CURSO = atual->CO_CURSO;
            novo->notaGenerica = atual->notaGenerica;
            novo->prox = maioresNotas;
            maioresNotas = novo;

            count++;
            atual = atual->prox;
        }
    }

    return maioresNotas;
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
    insereNosIndicesDeNota(cursoNotas);
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
            free(temp->curso->NT_CE);
            free(temp->curso->NT_GER);
            free(temp->curso);
            free(temp);
        }
    }
    free(cursosNotasInseridos);
    liberaIndicesNotas();
}

void liberaIndicesNotas(){
    for(int i = 0; i < TAM_HASH; i++){
        CursoENota* atual = HASH_NOTAS_GERAIS[i];
        while(atual != NULL){
            CursoENota* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    for(int i = 0; i < TAM_HASH; i++){
        CursoENota* atual = HASH_NOTAS_ESPECIFICAS[i];
        while(atual != NULL){
            CursoENota* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}

void mostrarInformacoesSobreNotasDoCurso(int CO_CURSO){
    int indice = funcaoHash(CO_CURSO, TAM_HASH);
    Nodo* atual = notasHashTable[indice];

    while (atual != NULL) {
        if (atual->id == CO_CURSO) {
            CursoNotas* curso = atual->curso;
            if(atual->curso->notasCalculadas == 0){
                //calcula medias
                calculaMedias(curso);
                atual->curso->notasCalculadas = 1;
            }
            printf("Informações sobre o curso %d:\n", CO_CURSO);
            printf("notas NT_GER: ");
            for (int j = 0; j < curso->numberOfNT_GER; j++) {
                printf("%.2f ", curso->NT_GER[j]);
            }
            printf("\nNotas NT_CE: ");
            for (int j = 0; j < curso->numberOfNT_CE; j++) {
                printf("%.2f ", curso->NT_CE[j]);
            }
            printf("\nMédia NT_GER: %.2f\n", curso->media_NT_GER);
            printf("Média NT_CE: %.2f\n", curso->media_NT_CE);
            printf("\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Curso com CO_CURSO %d não encontrado.\n", CO_CURSO);
}

void calculaMedias(CursoNotas* notas){
    notas->media_NT_CE = 0.0;
    notas->media_NT_GER = 0.0;
    for(int i = 0; i < notas->numberOfNT_CE; i++){
        notas->media_NT_CE += notas->NT_CE[i];
    }
    for(int i = 0; i < notas->numberOfNT_GER; i++){
        notas->media_NT_GER += notas->NT_GER[i];
    }
    notas->media_NT_CE = notas->numberOfNT_CE > 0 ? notas->media_NT_CE / notas->numberOfNT_CE : 0.0;
    notas->media_NT_GER = notas->numberOfNT_GER > 0 ? notas->media_NT_GER / notas->numberOfNT_GER : 0.0;
}



