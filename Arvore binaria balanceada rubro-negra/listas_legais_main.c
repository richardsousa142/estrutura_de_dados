#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas_legais.h"
int main(){
    int n, k, operacao,  i;
    long long int chave = 0, numero = 0; //n = numero de elementos / k = numero de operacoes
    p_no arvore_ll;//, arvore_aux;//arvore_ll -> arvore_listaslegais
    char lixo;
    //int ret_freq = 0;
    scanf("%d %d", &n, &k);
    for(i = 0; i < n; i++){
        scanf("%lld%c", &chave, &lixo);
        if(i == 0)
            arvore_ll = criar_arvore(chave, NULL, NULL);
        else
            arvore_ll = inserir(arvore_ll, chave);
    }
    for(i = 0; i < k; i++){
        scanf("%d%c", &operacao, &lixo);
        if(i == 0) 
            printf("\n");
        if(operacao == 1){
            scanf("%lld%c", &numero, &lixo);
            arvore_ll = inserir(arvore_ll, numero);
        }else if(operacao == 2){
            scanf("%lld%c", &numero, &lixo);
            printf("%d\n", retorna_frequencia(buscar(arvore_ll, numero))); 
        }else{
            printf("%d\n", operacao3(arvore_ll) ); 
        }
    }  
    destruir_arvore(arvore_ll);
    return 0;
}
