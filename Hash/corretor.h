#ifndef PROFESSOR_CARLOS_H
#define PROFESSOR_CARLOS_H
#define MAX 100
enum bool{false = 0, true = 1};
typedef struct No{
    char chave[26];
    //int dado;
    struct No *prox;
    struct No *coli;
}No;
typedef No * p_no; 
typedef struct {
    p_no vetor[MAX];
} Hash;
typedef Hash * p_hash;
p_hash criar_hash();
int hash(char *chave);
p_no inserir_lista(p_no lista, char *text);
//funcao para inserir novos elementos na hash, e caso ocorra colisao o for procura uma posicao vazia
void inserir(p_hash t, char *chave);
//funcao q sera usada para dar o valor minimo nas operacoes da funcao levenshtein
int min(int a, int b, int c);
//funcao para comparar duas str's, usa uma matriz e compara as palavras letra a letra verificando a diferenca entre elas
//podendo ser uma diferenca de adc uma letra, remover ou permutar
//sempre colocando o minimo de op na matrix diagonal e no fim retorna esse valor de mudancas que precisam ser feitas
int levenshtein(char *s1, char *s2);
//essa funcao fica responsavel por preencher toda a tabela hash e retornar na funcao main
p_hash preenche_hash(p_hash hash_table, int n);
//funcao para limpar texto  a partir da pos fornecida
void limpa_texto(char *texto, int pos);
int ti_ce_cf(char *str, char *palavra); //ti = tamanho igual / ce = caractere extra / cf = caractere faltando
int ti_ct(char *str, char *palavra);   //ti = tamanho igual / ct = caractere trocado
int arranjo_trocado(char *str, char *palavra);//tamanho igual, porem tem caracteres permutados
//casca para verificar quando o tam da str e palavra sao iguais
int compara_tam_igual(char *st_hash, char *palavra);
//nessa funcao vamos verificar onde ocorre o caractere a mais na str
int um_caractere_mais(char *str, char *palavra);
//aqui vericamos se o caractere a mais da str ta no inicio
//se for o caso, retorna true
int um_caractere_mais_inicio(char *str, char *palavra);
//se strlen(st_hash) == (strlen(palavra) - 1) entao a palavra do usuario é maior em apenas um caractere
//entao chamamos uma das funcoes um_caractere_mais ou um_caractere_mais_inicio
//retornando true ou false 
int compara_maior(char *st_hash, char *palavra);
//essa funcao e usada somente na funcao um_caractere_menos, e copia a str a partir da pos fornecida
void copia_partir_de(char *str, char *palavra,int pos);
int um_caractere_menos(char *str, char *palavra);
//verifica se o tam str da hash - 1 = tam str palavra(usuario), se sim chama a funcao
//um_caractere_menos e verifica se a palavra é a msm da hash e retorna true ou false 
int compara_menor(char *st_hash, char *palavra);
//essa funcao funciona como uma casca para fazer a busca
//recebe a palavra(errada) e compara o tamanho com as palavras da hash
//se for strlen() for igual, usamos um jeito para verificar se e a msm palavra, da msm forma para os outros casos
int procura(p_hash t, char *palavra);
void destroi_lista(p_hash hash);

#endif