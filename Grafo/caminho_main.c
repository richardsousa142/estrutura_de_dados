#include <stdio.h>
#include "caminho.h"
#include <string.h>
int main(){
    p_grafo grafo_pokemon; grafo_pokemon = cria_grafo();
    Cord pos;
    char tipo_vertice[15];
    scanf("%lf %lf", &pos.x, &pos.y);
    grafo_pokemon->adj = insere_na_lista(grafo_pokemon->adj, pos, ORIGEM, 0);
    while ( scanf("%lf %lf", &pos.x, &pos.y) != EOF ){
        scanf("%s", tipo_vertice);
        grafo_pokemon->tam++;
        grafo_pokemon->adj = insere_na_lista(grafo_pokemon->adj, pos, retorna_tipo_vertice(tipo_vertice), grafo_pokemon->tam);
    }
    grafo_pokemon->adj = inverter_lista(grafo_pokemon->adj);//inverte a lista para que a origem esteja no começo da lista, mais para trabalhar com a lista com uma mentalidade de vetor
    grafo_pokemon->adj = cria_arestas(grafo_pokemon->adj); //cria arestas, ou seja, de qlq vertice X eu consigo ir para qlq outro vertice. Entao todo vertice é aresta de X menos da origem e ele msm
    procura_caminho(grafo_pokemon);//funcao de procura caminho
    destroi_grafo(grafo_pokemon);
    return 0;
}    