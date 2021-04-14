#ifndef LISTAS_LEGAIS_H
#define LISTAS_LEGAIS_H

enum Cor{VERMELHO, PRETO};
typedef struct No{
    long long int chave;
    int frequencia;
    enum Cor cor;
    struct No *esq, *dir;
} No;
typedef No *p_no;
typedef struct Lista{
    p_no raiz;
    struct Lista *prox;
}Lista;
typedef Lista * p_lista;
//struct da pilha q tem um membro do tipo p_lista e p_lista tem um membro de p_no.
//entao cada elemento da pilha vai ter um p_no
typedef struct Pilha{
    p_lista topo;
}Pilha;
typedef Pilha * p_pilha;
p_pilha cria_pilha ();
int pilha_vazia(p_pilha pilha);
void empilhar(p_pilha pilha, p_no raiz_arvore);
//Funcao para desempilhar o ultimo no de arvore da stack
//e devolver um p_no para ser usado na funcao operacao3
//controlar o fluxo do codigo na arvore
p_no desempilhar(p_pilha pilha);
//essa funcao serve para desempilhar a pilha na funcao destruir_pilha
//a funcao desempilhar é uma funcao especifica para ser utilizada na funcao operacao3 pq retorna um p_no
void desempilhar_pilha(p_pilha pilha);
void destruir_pilha(p_pilha pilha);
p_no criar_arvore(long long int x, p_no esq, p_no dir);
void destruir_arvore(p_no arvore);
int ehVermelho(p_no x);
int ehPreto(p_no x);
p_no rotaciona_para_esquerda(p_no raiz);
p_no rotaciona_para_direita(p_no raiz);
void sobe_vermelho(p_no raiz);
p_no inserir_rec(p_no raiz, long long int chave) ;
//inserir tbm é usado na operacao1
p_no inserir(p_no raiz, long long int chave);
p_no buscar(p_no raiz, long long int chave);
//operacao 2, recebe o no da arvore e retorna a quantidade de vezes que ele ja apareceu na lista
int retorna_frequencia(p_no arvore);
//percorre a arvore toda e a cada elemento verifica se arvore->chave é > frequencia
//se for verdade significa q esse elemento teria q ser removido para fazer a lista ser uma lista legal
int operacao3(p_no arvore);


#endif