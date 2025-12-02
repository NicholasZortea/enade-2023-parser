#include <stdio.h>
#include <stdlib.h>
#include "header/curso.h"

int main(){
    carregarCursos("DADOS/microdados2023_arq1.txt");
    printarCursos();
    liberarCursos();
    return 0;
}