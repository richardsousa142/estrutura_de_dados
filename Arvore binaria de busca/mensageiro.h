#ifndef MENSAGEIRO_H
#define MENSAGEIRO_H
typedef struct No {
    int chave;
    char texto[10000];
    struct No *esq, *dir, *pai; /*pai é opcional , usado em sucessor e antecessor*/
} No;
typedef No * p_no;
// definindo cada item do topo da pilha como raiz de arvore
typedef struct Lista{
    p_no raiz;
    struct Lista *prox;
}Lista;
typedef Lista * p_lista;
//definicao para contruir a pilha com 'n' itens de raiz de arvores
typedef struct Pilha{
    p_lista topo;
}Pilha;
typedef Pilha * p_pilha;

p_pilha cria_pilha ();
int pilha_vazia(p_pilha pilha);
//funcao para adc um item ao topo da pilha
void empilhar(p_pilha pilha, p_no raiz_arvore);
//Funcao para desempilhar o ultimo no da arvore
//e devolver um p_no para ser usado na funcao procura_triade
//controlar o fluxo do codigo na arvore
p_no desempilhar(p_pilha pilha);
//essa funcao serve para desempilhar a pilha na funcao destruir_pilha
//a funcao desempilhar é uma funcao especifica para ser utilizada na funcao procura_triade pq retorna um p_no
void desempilhar_pilha(p_pilha pilha);
void destruir_pilha(p_pilha pilha); //liberar a memoria alocada para pilha
p_no criar_arvore(int x, char *texto_cartao, p_no esq, p_no dir, p_no pai);
p_no inserir(p_no raiz,  int chave, char *texto_cartao);
void destruir_arvore(p_no arvore);
void inordem(p_no raiz);
void limpa_texto(char texto[]);
p_no buscar(p_no raiz, int chave);
void remover_sucessor(p_no raiz);
p_no remover_rec(p_no raiz, int chave);
//essa funcao recebe o vetor de triade e concatena as str's e soma a chave de cada um
//feito isso cria uma nova raiz de arvore e retorna para a triade_encontrade na funcao procura_triade
p_no concatena(p_no *triade);
p_no minimo(p_no raiz) ;
p_no ancestral_a_direita(p_no x);
p_no sucessor(p_no x);
//funcao para iniciar o vetor de triades com valor null
//se tentar iniciar com criar_arvore o valgrind reclama
p_no triade_null();//funcao principal do codigo, serve para procurar as 3 raizes da arvore que somadas dao o valor da autoridade
//quando encontrado a triade, chama a funcao concatena. Depois insere a soma e a str concatenada na arvore original e retorna para a funcao main
//com as novas caracteristicas e atribui a arvore na funcao main, pos isso, chama essa funcao dnv com um novo numero de autoridade
p_no procura_triade(p_no arvore, int autoridade);


#endif