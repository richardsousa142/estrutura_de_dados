#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corretor.h"
int main(){
    p_hash hash_table = criar_hash();
    char nome[26];
    int i, n, q;
    scanf("%d %d", &n, &q);   
    hash_table = preenche_hash(hash_table, n);
    for(i = 0; i < q; i++){
        scanf("%s", nome);
        procura(hash_table, nome);
    }
    destroi_lista(hash_table);
    return 0;
} 
