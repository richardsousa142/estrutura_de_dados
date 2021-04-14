#ifndef DIADEUBER_H
#define DIADEUBER_H
enum bool {false = 0, true = 1};
//struct contendo duas variaveis inteiras para representar as coordenadas x e y de cada cliente
typedef struct {
    int x, y;
}Cord;
typedef struct {
    char nome[20];
    double chave; //avaliacao do cliente
    Cord origem;  //coordenadas de origem
    Cord destino; //coordenadas de destino
    int prioridade; //prioridade do cliente
} Item;
typedef struct {
    Item *v;
    int n, tamanho;
} FP;
typedef FP * p_fp;
p_fp criar_filaprio(int tam);
void troca(Item *a, Item *b);
//verifica se a lista é vazia, util para quando for inserir na fila de corridas
//dessa forma ja coloca a primeira pessoa a solicitar um uber com prioridade maxima
int vazia(p_fp fila_espera);
void desce_no_heap(p_fp heap, int n, int k);
//acha onde esta localizado o cara com maior prioridade na lista e retorna sua posicao
int acha_prioridade(p_fp corridas, int tam);
void heapsort(p_fp corridas, int n);
//funcao para inserir os elementos na heap, porem sem organizar como heap max ja de inicio.
//a construcao da heap ocorre dentro da funcao main com a chamada da heapsort
void insere(p_fp fprio, Item item);
//a funcao extrai_maximo retorna sempre a ultima posicao da lista heap
//como a chamada dessa funcao so ocorre apos qd a heap em ordem crescente
//temos a garantia de que o cliente com a maior avaliacao ou com a maior prioridade estara na ultima pos
Item extrai_maximo(p_fp fprio);
int calcula_distancia(int c_x_o, int c_y_o, int c_x_d, int c_y_d);
//a funcao cancelou_corrida usa o for para percorrer a heap até encontrar a pessoa, comparando os nomes
//quando o for loop parar, temos a pos do cliente que cancelou entao basta trocar ele com o elemento da ultima pos (n - 1) e subtrair 1 de n
void cancelou_corrida(p_fp corridas, char nome[16]);
//a funcao inicializa serve para colocar valores nos membros da struct item
//dessa forma evita termos erros de atribuir valor para variaveis nao inicializadas
Item inicializa(Item atributos);
//funcao para mudar a prioridade de um cliente
void muda_prioridade(p_fp corridas);
#endif