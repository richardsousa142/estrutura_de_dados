#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mensageiro.h"
p_pilha cria_pilha () {
    p_pilha p = malloc (sizeof (Lista));
    p->topo = NULL;    
    return p;
}
int pilha_vazia(p_pilha pilha){
    return (pilha->topo == NULL);
}
//funcao para adc um item ao topo da pilha
void empilhar(p_pilha pilha, p_no raiz_arvore){
    p_lista novo = malloc(sizeof(No));
    novo->raiz = raiz_arvore;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}
//Funcao para desempilhar o ultimo no da arvore
//e devolver um p_no para ser usado na funcao procura_triade
//controlar o fluxo do codigo na arvore
p_no desempilhar(p_pilha pilha) {
    p_lista topo = pilha->topo;
    p_no raiz_p_arvore = topo->raiz; // essa variavel é retornada somente para usar no direcionamento da arvore na funcao procura triade
    pilha->topo = pilha->topo->prox;
    free(topo);
    return raiz_p_arvore;
}
//essa funcao serve para desempilhar a pilha na funcao destruir_pilha
//a funcao desempilhar é uma funcao especifica para ser utilizada na funcao procura_triade pq retorna um p_no
void desempilhar_pilha(p_pilha pilha){
    p_lista topo = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(topo);
}
void destruir_pilha(p_pilha pilha){ //liberar a memoria alocada para pilha
    while(!pilha_vazia(pilha)){
        desempilhar_pilha(pilha);
    }
    free(pilha);
}
p_no criar_arvore(int x, char *texto_cartao, p_no esq, p_no dir, p_no pai) {
    p_no r = malloc(sizeof(No));
    r->chave = x;
    strcpy(r->texto, texto_cartao);
    r->esq = esq;
    r->dir = dir;
    r->pai = pai;
    return r;
}
p_no inserir(p_no raiz,  int chave, char *texto_cartao) {
    p_no novo; static p_no pai;
    if (raiz == NULL){
        novo = malloc(sizeof(No));
        //novo->texto = calloc(10000, sizeof(char) );
        novo->esq = novo->dir = NULL;
        novo->pai = pai;
        novo->chave = chave;
        strcpy(novo->texto, texto_cartao);
        //novo = criar_arvore(chave, texto_cartao, NULL, NULL, pai);
        return novo;
    }
    if (chave < raiz->chave){
        pai = raiz;
        raiz->esq = inserir(raiz->esq, chave, texto_cartao);
    }else{
        pai = raiz;
        raiz->dir = inserir(raiz->dir, chave, texto_cartao);
    }
    return raiz;
}
void destruir_arvore(p_no arvore){
    if(arvore != NULL){
        destruir_arvore(arvore->esq);
        destruir_arvore(arvore->dir);
        free(arvore);
    }
}
void inordem(p_no raiz) {
    if (raiz != NULL) {
        inordem(raiz->esq);
        printf("%s", raiz->texto); /* visita raiz */
        inordem(raiz->dir);
    }
}
void limpa_texto(char texto[]){
    int i;
    for (i = 0; texto[i] != '\0'; i++){
        strcpy(&texto[i], "");
    }
}
p_no buscar(p_no raiz, int chave){
    while (raiz != NULL && chave != raiz->chave){
        if (chave < raiz->chave)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    return raiz;
}
void remover_sucessor(p_no raiz) {
    p_no min = raiz->dir; 
    p_no pai = raiz; 
    while (min->esq != NULL) {
        pai = min;
        min = min->esq;
    }
    if (pai->esq == min)
        pai->esq = min->dir;
    else
        pai->dir = min->dir;
    raiz->chave = min->chave;
    strcpy(raiz->texto, min->texto);
    free(min);
}
p_no remover_rec(p_no raiz, int chave) {
    p_no aux;
    if (raiz == NULL)
        return NULL;
    if (chave < raiz->chave)
        raiz->esq = remover_rec(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = remover_rec(raiz->dir, chave);
    else if (raiz->esq == NULL){
        aux = raiz->dir;
        free(raiz);
        return aux;
    }else if (raiz->dir == NULL){
        aux = raiz->esq;
        free(raiz);
        return aux;
    }else
        remover_sucessor(raiz);
    return raiz;
}
//essa funcao recebe o vetor de triade e concatena as str's e soma a chave de cada um
//feito isso cria uma nova raiz de arvore e retorna para a triade_encontrade na funcao procura_triade
p_no concatena(p_no *triade){
    char *text = calloc(1, sizeof(char[10000]));
    p_no triade_conc; 
    int i, soma = 0;
    for(i = 0; i < 3; i++){
        soma += triade[i]->chave;
        strcat(text, triade[i]->texto);
    }
    triade_conc = criar_arvore(soma, text, NULL, NULL, NULL);
    free(text);
    return triade_conc;
}
p_no minimo(p_no raiz) {
    while (raiz != NULL && raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}
p_no ancestral_a_direita(p_no x) {
    if (x == NULL)
        return NULL;
    if (x->pai == NULL || x->pai->esq == x)
        return x->pai;
    else
        return ancestral_a_direita(x->pai);
}
p_no sucessor(p_no x) {
    if (x->dir != NULL)
        return minimo(x->dir);
    else   
        return ancestral_a_direita(x);
}
//funcao para iniciar o vetor de triades com valor null
//se tentar iniciar com criar_arvore o valgrind reclama
p_no triade_null(){
    return NULL;
}
//funcao principal do codigo, serve para procurar as 3 raizes da arvore que somadas dao o valor da autoridade
//quando encontrado a triade, chama a funcao concatena. Depois insere a soma e a str concatenada na arvore original e retorna para a funcao main
//com as novas caracteristicas e atribui a arvore na funcao main, pos isso, chama essa funcao dnv com um novo numero de autoridade
p_no procura_triade(p_no arvore, int autoridade){
    // esse vetor de int é usado na funcao remover_rec, aos inves de chamar a funcao passando os indices da triade, usa-se esse vetor como aux
    //pq pode ocorrer da funcao remover_rec apagar uma raiz da arvore e atribuir os dados do indice seguinte da triade[i] para o indice q acabou
    //de ser apagado e assim gerar 'lixo' na arvore e atrapalhar na hora de imprimir
    int g_chave[3];
    p_no triade_encontrada;
    // vetor de p_no q ira conter os ponteiros de cada no que satisfaça as condicoes para soma 
    p_no triade[3]; triade[0] = triade_null(); triade[1] = triade_null(); triade[2] = triade_null(); 
    p_no arvore_atual; arvore_atual = arvore; /*   */ p_no arvore_atual2; arvore_atual2 = arvore; 
    p_pilha p; p = cria_pilha(); /*   */ p_pilha p2; p2 = cria_pilha();
    int achou_triade = 0, i; 
    while(arvore_atual2 != NULL || !pilha_vazia(p2)){
        while(arvore_atual2 != NULL){
            empilhar(p2, arvore_atual2);
            arvore_atual2 = arvore_atual2->esq;
        }
        arvore_atual2 = desempilhar(p2);
        triade[0] = arvore_atual2;
        while (arvore_atual != NULL || !pilha_vazia(p)){
            while(arvore_atual != NULL){
                empilhar(p, arvore_atual);
                arvore_atual = arvore_atual->esq;
            }
            arvore_atual = desempilhar(p);
            if(arvore_atual->chave != triade[0]->chave){//garante que tride[0]/[1] nunca iniciem com o mesmo valor
                triade[1] = arvore_atual;
            }
            //apos atribuir valores a triade[0]/[1], fazemos uma busca na arvore pelo valor q falta para fechar a triade. oq for retornado é atribuido a triade[2]
            if(triade[1] != NULL){//o if a cima sempre na primeira 'rodada' do while mais interno ira garantir q os valores n iniciem iguais e por isso triade[1] sera igual a NULL na primeira 'rodada'
                triade[2] =  buscar(arvore, autoridade - (triade[0]->chave + triade[1]->chave ) ) ;
            }
            if(triade[2] != NULL ){
                if( (triade[0]->chave + triade[1]->chave + triade[2]->chave) == autoridade){
                    achou_triade = 1;
                    break;
                }
            }
            arvore_atual = arvore_atual->dir;
        }
        if(achou_triade == 1){ break ;}
        arvore_atual2 = arvore_atual2->dir; 
        arvore_atual = arvore;
    }
    triade_encontrada = concatena(triade);
    for(i = 0; i < 3; i++){
        g_chave[i] = triade[i]->chave;
    }
    for(i = 0; i < 3; i++){
        arvore = remover_rec(arvore, g_chave[i]); 
    }
    arvore = inserir(arvore, triade_encontrada->chave, triade_encontrada->texto); //inserindo na arvore original a triade_encontrada
    destruir_pilha(p ); 
    destruir_pilha(p2);
    destruir_arvore(triade_encontrada);
    return arvore;
}