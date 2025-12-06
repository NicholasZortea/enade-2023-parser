#include <stdio.h>
#include <stdlib.h>
#include "header/relatorios.h"

void printaMenuGeral();
void processaEntrada(int opcao);
void procurarCursoEspecifico();
void listarCursosPorIES();
void listarCursosPorUF();
void listarCursosPorGrupo();
void listarNotasCurso();

int main(){

    carregarInfosCursosRelatorio("DADOS/microdados2023_arq1.txt");
    carregarCursosNotasRelatorio("DADOS/microdados2023_arq3.txt");
    int opcao;
    do{
        printaMenuGeral();
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        processaEntrada(opcao);
    } while(opcao != 0);

    liberaMemoria();
    return 0;
}

void processaEntrada(int opcao){
    switch(opcao){
        case 1:
            procurarCursoEspecifico();
            break;
        case 2:
            listarCursosPorIES();
            break;
        case 3:
            listarCursosPorUF();
            break;
        case 4:
            listarCursosPorGrupo();
            break;
        case 5:
            listarNotasCurso();
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
    }
}

void listarCursosPorIES(){
    printf("Digite o código da IES desejada: ");
    int codigoIES;
    scanf("%d", &codigoIES);
    pesquisaCursoPorIES(codigoIES);
}

void listarCursosPorUF(){
    printf("Digite o código da UF desejada: ");
    int codigoUF;
    scanf("%d", &codigoUF);
    pesquisaCursoPorUF(codigoUF);
}

void listarCursosPorGrupo(){
    printf("Digite o código do grupo desejado: ");
    int codigoGrupo;
    scanf("%d", &codigoGrupo);
    pesquisaCursoPorGRUPO(codigoGrupo);
}

void listarNotasCurso(){
    printf("Funcionalidade listarNotasCurso ainda não implementada.\n");
}

void procurarCursoEspecifico(){
    printf("Digite o número do curso desejado: ");
    int codigoCurso;
    scanf("%d", &codigoCurso);
    printaSobreCurso(codigoCurso);
}

void printaMenuGeral(){
    printf("-------------------------------------------------\n");
    printf("Escolha uma das opções abaixo:\n");
    printf("1. Listar informações de um curso específico\n");
    printf("2. Listar cursos por IES\n");
    printf("3. Listar cursos por UF\n");
    printf("4. Listar cursos por grupo (área de enquadramento)\n");
    printf("5. Listar notas de um curso específico\n");
    printf("0. Sair\n");
    printf("--------------------------------------------------\n");
}