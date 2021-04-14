#ifndef CAMINHO_H
#define CAMINHO_H
enum tipo_vertice{ORIGEM = 2, POKESTOP = 3, LUGIA = 4};
enum bool{false = 0, true = 1};
typedef struct Cord{
    double x;
    double y;
}Cord;
typedef struct No{
    Cord pos;
    int tipo;
    int indice;
    struct No *arestas;
    struct No *prox;
}No;
typedef No * p_no;
typedef struct{
    p_no adj;
    int tam;
}Grafo;
typedef Grafo * p_grafo;
typedef struct Lista{
    p_no vertice;
    struct Lista * prox;
}Lista;
typedef Lista * p_lista;
typedef struct Pilha{
    p_lista topo;
}Pilha;
typedef Pilha * p_pilha;
p_grafo cria_grafo();
void destroi_grafo(p_grafo g);
p_no insere_na_lista(p_no lista, Cord pos, int tipo, int indice);
//inverter a lista
p_no inverter_lista(p_no lista);
//funcao para criar arestas em cada vertice da lista ligada. ou seja, de qlq vertice X podemos ir para todos os outros vertices
p_no cria_arestas(p_no lista);
p_pilha cria_pilha();
int pilha_vazia(p_pilha pilha);
//essa desempilha é usada apenas na funcao destruir pilha
void desempilhar_pilha(p_pilha pilha);
void destruir_pilha(p_pilha pilha);
void empilhar(p_pilha pilha, p_no vertice);
//essa funcao desempilha retorna p_no para ajudar a direcionar o fluxo pelo grafo na funcao busca_em_profundidade
p_no desempilhar(p_pilha pilha);
//funcao para calcular distancia entre dois pokestops
double calcula_distancia(Cord origem, Cord destino);
//funcao para saber qual o tipo do vertice, se é ORIGEM / POKESTOPS / LUGIA
int retorna_tipo_vertice(char *tipo);
//essa funcao vai rodar o grafo e procurar um caminho da origem ate o lugia, caso exista um caminho retorna 1
//
int busca_em_profundidade(p_grafo g, double *dist, int k, int tipo);
//essa funcao chama busca_em_profundidade e testa um caminho por vez
//iniciando com k = 0 e caso ache um caminho retorna o trecho de maior distancia
//caso nao ache o caminho, incrementa k em 1;
int procura_caminho(p_grafo grafo);
#endif