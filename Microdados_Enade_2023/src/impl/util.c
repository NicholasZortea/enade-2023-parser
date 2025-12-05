#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../header/util.h"

int funcaoHash(int chave, int TAM_HASH) {
    unsigned int hash = chave * 2654435761u;
    return hash % TAM_HASH;
}