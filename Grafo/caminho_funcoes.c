#include "caminho.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
p_grafo cria_grafo(){
    p_grafo g = malloc(sizeof(Grafo)); //cria a estrutura do grafo com atributo adj q é um pno
    g->tam = 0;
    g->adj = NULL;
    return g;
}
p_no insere_na_lista(p_no lista, Cord pos, int tipo, int indice){
    p_no novo = malloc(sizeof(No));
    novo->pos.x = pos.x;
    novo->pos.y = pos.y;
    novo->indice = indice;
    novo->tipo = tipo;
    novo->prox = lista;
    return novo;
}
p_no inverter_lista(p_no lista) {
    p_no atual, ant, invertida = NULL;
    atual = lista;
    while (atual != NULL) {
        ant = atual;
        atual = ant->prox;
        ant->prox = invertida;
        invertida = ant;
    }
    return invertida;
}
p_no cria_arestas(p_no lista){
    p_no aux = lista;
    p_no teste = lista;
    for(aux = lista; aux != NULL; aux = aux->prox){
        while(teste != NULL){
            if(teste != aux)
                aux->arestas = insere_na_lista(aux->arestas, teste->pos, teste->tipo, teste->indice);
            teste = teste->prox;
        }
        teste = lista;
    } 
    return lista;
}
p_pilha cria_pilha(){
    p_pilha p = malloc(sizeof(Lista));
    p->topo = NULL;
    return p;
}
void empilhar(p_pilha pilha, p_no vertice){
    p_lista novo = malloc(sizeof(No));
    novo->vertice = vertice;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}
p_no desempilhar(p_pilha pilha){
    p_lista topo = pilha->topo;
    p_no vertice = topo->vertice;
    pilha->topo = pilha->topo->prox;
    free(topo);
    return vertice;
}
int pilha_vazia(p_pilha pilha){
    return (pilha->topo == NULL);
}
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
double calcula_distancia(Cord origem, Cord destino){
    return sqrt( pow(origem.x - destino.x, 2) + pow(origem.y - destino.y, 2) );
}
int retorna_tipo_vertice(char *tipo){
    int i = strcmp(tipo, "pokestop");
    return  i == 0 ? POKESTOP : LUGIA;
}
p_no acha_igual(p_no vertice, p_no arestas){
    p_no ret;
    for(ret = vertice; ret != NULL; ret = ret->prox){
        if(ret->indice == arestas->indice 
           && ret->pos.x == arestas->pos.x
           && ret->pos.y == arestas->pos.y 
           && ret->tipo == arestas->tipo)
            return ret;
    }
    return ret;
}   
int busca_em_profundidade(p_grafo g, double *dist, int k, int tipo) {
    int cont = 0, *visitado = calloc(g->tam, sizeof(int));
    double ret_dist = 0.0;
    p_no t, aux, ret_no_igual;
    p_pilha p = cria_pilha();
    empilhar(p, g->adj);
    while(!pilha_vazia(p)) {
        t = desempilhar(p);
        visitado[t->indice] = 1;
        aux = t->arestas;
        while (aux != NULL){
            ret_dist = calcula_distancia(t->pos, aux->pos);
            if( ret_dist <= k && !visitado[aux->indice]){
                ret_no_igual = acha_igual(g->adj, aux);
                empilhar(p, ret_no_igual);
                dist[cont] = calcula_distancia(t->pos, aux->pos);
                cont++;
                if(aux->tipo == tipo) return true;
                break;
            }
            aux = aux->prox;
        }
    }
    destruir_pilha(p);
    free(visitado);
    return false;
}
int retorna_maior(double *dist_caminho, p_grafo g){
    double maior= 0.0; 
    int i;
    for(i = 0; i < g->tam; i++)
        if(dist_caminho[i] > maior) maior = dist_caminho[i];
    return ceil(maior);
}
int procura_caminho(p_grafo grafo){
    int k, ret_maior; 
    double *dist_caminho = calloc(grafo->tam, sizeof(double));
    for (k = 0; k < grafo->tam; k++){
        if(busca_em_profundidade(grafo, dist_caminho, k, LUGIA)){
            ret_maior = retorna_maior(dist_caminho, grafo);
            free(dist_caminho);
            return printf("%d\n", ret_maior);
        }
    }
    return false;
}
void destroi_grafo(p_grafo g) {
    p_no aux;
    for (g->adj = g->adj; g->adj != NULL; g->adj = g->adj->prox){
        for(aux = g->adj->arestas; aux != NULL; aux = aux->prox)
            free(aux);   
        free(g->adj);
    }
    free(g); 
}