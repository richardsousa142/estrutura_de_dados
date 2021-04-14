#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas_legais.h"
p_pilha cria_pilha () {
    p_pilha p = malloc (sizeof (Lista));
    p->topo = NULL;    
    return p;
}
int pilha_vazia(p_pilha pilha){
    return (pilha->topo == NULL);
}
void empilhar(p_pilha pilha, p_no raiz_arvore){
    p_lista novo = malloc(sizeof(No));
    novo->raiz = raiz_arvore;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}
//Funcao para desempilhar o ultimo no de arvore da stack
//e devolver um p_no para ser usado na funcao operacao3
//controlar o fluxo do codigo na arvore
p_no desempilhar(p_pilha pilha) {
    p_lista topo = pilha->topo;
    p_no raiz_p_arvore = topo->raiz; // essa variavel é retornada somente para usar no direcionamento da arvore na funcao procura triade
    pilha->topo = pilha->topo->prox;
    free(topo);
    return raiz_p_arvore;
}
//essa funcao serve para desempilhar a pilha na funcao destruir_pilha
//a funcao desempilhar é uma funcao especifica para ser utilizada na funcao operacao3 pq retorna um p_no
void desempilhar_pilha(p_pilha pilha){
    p_lista topo = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(topo);
}
void destruir_pilha(p_pilha pilha){
    while(!pilha_vazia(pilha)){
        desempilhar_pilha(pilha);
    }
    free(pilha);
}
p_no criar_arvore(long long int x, p_no esq, p_no dir) {
    p_no r = malloc(sizeof(No));
    r->chave = x;
    r->frequencia = 1;
    r->esq = esq;
    r->dir = dir;
    r->cor = PRETO;
    return r;
}
void destruir_arvore(p_no arvore){
    if(arvore != NULL){
        destruir_arvore(arvore->esq);
        destruir_arvore(arvore->dir);
        free(arvore);
    }
}
int ehVermelho(p_no x){
    if (x == NULL)
        return 0;
    return x->cor == VERMELHO;
}
int ehPreto(p_no x){
    if (x == NULL)
        return 1;
    return x->cor == PRETO;
}
p_no rotaciona_para_esquerda(p_no raiz) {
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}
p_no rotaciona_para_direita(p_no raiz) {
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}
void sobe_vermelho(p_no raiz) {
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}
p_no inserir_rec(p_no raiz, long long int chave) {
    p_no novo;
    if (raiz == NULL) {
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        novo->chave = chave;
        novo->frequencia = 1; //caso o no n exista na arvore, inicializa com 1; 
        novo->cor = VERMELHO;
        return novo;
    }
    //caso a chave ja exista na arvore, esse if é vdd e entao incrementa +1 na frequencia
    if (raiz->chave == chave){
        raiz->frequencia++;
        return raiz;
    }
    if (chave < raiz->chave)
        raiz->esq = inserir_rec(raiz->esq, chave);
    else
        raiz->dir = inserir_rec(raiz->dir, chave);

    if (ehVermelho(raiz->dir) && ehPreto(raiz->esq))
        raiz = rotaciona_para_esquerda(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq))
        raiz = rotaciona_para_direita(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
        sobe_vermelho(raiz);
        
    return raiz;
}
//inserir tbm é usado na operacao1
p_no inserir(p_no raiz, long long int chave) {
    raiz = inserir_rec(raiz, chave);
    raiz->cor = PRETO;
    return raiz;
}
p_no buscar(p_no raiz, long long int chave){
    while (raiz != NULL && chave != raiz->chave){
        if (chave < raiz->chave)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    return raiz;
}
//operacao 2, recebe o no da arvore e retorna a quantidade de vezes que ele ja apareceu na lista
int retorna_frequencia(p_no arvore){
    return arvore? arvore->frequencia : 0; 
}
//percorre a arvore toda e a cada elemento verifica se arvore->chave é > frequencia
//se for verdade significa q esse elemento teria q ser removido para fazer a lista ser uma lista legal
int operacao3(p_no arvore){
    p_no arvore_aux = arvore;
    p_pilha p; p = cria_pilha();
    int num_min_retirar = 0;
    while(arvore_aux != NULL || !pilha_vazia(p)){
        while(arvore_aux != NULL){
            empilhar(p, arvore_aux);
            arvore_aux = arvore_aux->esq;
        }
        //usa a funcao desempilhar q retorna um p_no e com isso conseguimos controlar o fluxo de acesso as raizes da arvore
        arvore_aux = desempilhar(p);
        //os blocos de if's a seguir tratam casos especificos para saber o numero minimo de elementos que devam ser retirados
        if(arvore_aux->chave > arvore_aux->frequencia || arvore_aux->frequencia > arvore_aux->chave ){
            // caso onde a freq > 1 porem < chave, entao basta somar a frequencia como qtd de elementos a serem removidos
            if(arvore_aux->frequencia > 1 && arvore_aux->frequencia < arvore_aux->chave) 
                num_min_retirar += arvore_aux->frequencia;
            // caso onde a freq > 1 e freq > chave, entao para saber qts elementos devem ser removidos, basta fazer a diferenca da freq - chave
            // pq saberemos quantas vezes o numero apareceu a mais do que seria necessario para lista ser legal
            else if (arvore_aux->frequencia > 1 && arvore_aux->frequencia > arvore_aux->chave) 
                num_min_retirar += (arvore_aux->frequencia - arvore_aux->chave );
            else
                num_min_retirar++;
        }
        arvore_aux = arvore_aux->dir; 
    }
    destruir_pilha(p);
    return num_min_retirar;
}
