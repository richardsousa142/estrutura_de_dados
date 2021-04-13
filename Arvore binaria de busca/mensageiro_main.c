#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mensageiro.h"
int main(){
    int i, m, n;
    int chave_cartao = 0, numero_autoridade;
    char *texto_cartao = calloc(1, sizeof(char[10]));
    p_no arvore; 
    while( scanf("%d %d", &m, &n) != EOF ){// le a quantidade de cartao e a quantidade de autoridades
        for(i = 0; i < m; i++){
            scanf("%d \"%[^\"]\"%*c ", &chave_cartao, texto_cartao);
            if(i == 0)
                arvore = criar_arvore(chave_cartao, texto_cartao, NULL, NULL, NULL);
            else
                arvore = inserir(arvore, chave_cartao, texto_cartao);
            limpa_texto(texto_cartao);
        }
        for(i = 0; i < n; i++){
            scanf("%d ", &numero_autoridade);
            arvore = procura_triade(arvore, numero_autoridade);
        }
        printf("\n");
        inordem(arvore);
        destruir_arvore(arvore);
    }
    free(texto_cartao);
    return 0;
}
