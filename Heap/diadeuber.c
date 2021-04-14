#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "diadeuber.h"
#define PAI(i) ((i-1)/2)
#define F_ESQ(i) (2*i+1) /*Filho esquerdo de i*/
#define F_DIR(i) (2*i+2) /*Filho direito de i*/
//struct contendo duas variaveis inteiras para representar as coordenadas x e y de cada cliente
p_fp criar_filaprio(int tam) {
    p_fp fprio = malloc(sizeof(FP));
    fprio->v = malloc(tam * sizeof(Item));
    fprio->n = 0;
    fprio->tamanho = tam;
    return fprio;
}
void troca(Item *a, Item *b) {
    Item t = *a;
    *a = *b;
    *b = t;
}
//verifica se a lista é vazia, util para quando for inserir na fila de corridas
//dessa forma ja coloca a primeira pessoa a solicitar um uber com prioridade maxima
int vazia(p_fp fila_espera){
    return fila_espera->n == 0? true : false;
}
void desce_no_heap(p_fp heap, int n, int k) {
    int maior_filho; 
    if (F_ESQ(k) < n) {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < n && heap->v[F_ESQ(k)].chave < heap->v[F_DIR(k)].chave )
            maior_filho = F_DIR(k);
        if (heap->v[k].chave < heap->v[maior_filho].chave ) {
            troca(&heap->v[k], &heap->v[maior_filho]);
            desce_no_heap(heap, n, maior_filho);
        }
    }
}
//acha onde esta localizado o cara com maior prioridade na lista e retorna sua posicao
int acha_prioridade(p_fp corridas, int tam){
    int i;
    for(i = 0; i < tam; i++){
        if(corridas->v[i].prioridade == true)
            break;
    }
    return i;
}
void heapsort(p_fp corridas, int n) {
    int k, i;
    for (k = n/2; k >= 0; k--) /* transforma em heap */
        desce_no_heap(corridas, n, k);
    //atribui a i o valor da pos do cara com a maior prioridade na lista
    i = acha_prioridade(corridas, n);
    //pega o cara com maior prioridade na lista e coloca no final da lista, na pos n - 1, feito isso, diminuimos n em 1
    troca(&corridas->v[i], &corridas->v[corridas->n - 1]);
    n--;
    //apos colocar o cara com a maior prioridade no final da lista (n - 1), transformamos a lista em um heap novamente, porem, até a pos n - 2. Assim o cara com a maior prioridade nunca saira do 'topo' da lista
    for (k = n/2; k >= 0; k--) /* transforma em heap */
        desce_no_heap(corridas, n, k);
    //faz a lista ficar em ordem crescente porem somente ate n - 2, deixando o v[i] com maior prioridade na pos n - 1
    while (n >= 1) { /* extrai o máximo */
        troca(&corridas->v[0], &corridas->v[n - 1]);
        n--;
        desce_no_heap(corridas, n, 0);
    }
}
//funcao para inserir os elementos na heap, porem sem organizar como heap max ja de inicio.
//a construcao da heap ocorre dentro da funcao main com a chamada da heapsort
void insere(p_fp fprio, Item item) {
    fprio->v[fprio->n] = item;
    fprio->n++;
}
//a funcao extrai_maximo retorna sempre a ultima posicao da lista heap
//como a chamada dessa funcao so ocorre apos qd a heap em ordem crescente
//temos a garantia de que o cliente com a maior avaliacao ou com a maior prioridade estara na ultima pos
Item extrai_maximo(p_fp fprio) {
    Item item = fprio->v[fprio->n - 1];
    fprio->n--;
    return item;
}
int calcula_distancia(int c_x_o, int c_y_o, int c_x_d, int c_y_d){
    int dist = abs(c_x_o - c_x_d) + abs(c_y_o - c_y_d);
    return dist ;
}
//a funcao cancelou_corrida usa o for para percorrer a heap até encontrar a pessoa, comparando os nomes
//quando o for loop parar, temos a pos do cliente que cancelou entao basta trocar ele com o elemento da ultima pos (n - 1) e subtrair 1 de n
void cancelou_corrida(p_fp corridas, char nome[16]){
    int i;
    for(i = 0; strcmp(corridas->v[i].nome, nome) != 0; i++);
    troca(&corridas->v[i], &corridas->v[corridas->n - 1]);
    corridas->n--;
}
//a funcao inicializa serve para colocar valores nos membros da struct item
//dessa forma evita termos erros de atribuir valor para variaveis nao inicializadas
Item inicializa(Item atributos){
    Item item;
    strcpy(item.nome, "");
    item.chave = 0.0;
    item.origem.x = 0, item.origem.y = 0;
    item.destino.x = 0, item.destino.y = 0;
    item.prioridade = false;
    return item;
}
//funcao para mudar a prioridade de um cliente
void muda_prioridade(p_fp corridas){
    //o bloco if - else a seguir serve para garantir que nao tentaremos acessar uma pos invalida da heap e alterar o valor do membro 'prioridade'
    if((corridas->n - 1) < 0){
        
    }else
        corridas->v[corridas->n - 1].prioridade = true;
}
