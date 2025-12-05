#include <stdio.h>
#include <stdlib.h>
#include "header/curso.h"
#include "header/cursoNotas.h"

int main(){
    //carregarCursos("DADOS/microdados2023_arq1.txt");
    carregarCursosNotas("DADOS/microdados2023_arq3.txt");
    printarCursosNotas();
    liberarCursosNotas();
    //printarCursos();
    //liberarCursos();
    return 0;
}