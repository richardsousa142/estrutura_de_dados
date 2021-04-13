#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corretor.h"

p_hash criar_hash(){
    int i;
    p_hash novo_hash = malloc(sizeof(Hash));
    for(i = 0; i < MAX; i++){
        novo_hash->vetor[i] = NULL;
    }
    return novo_hash;
}
int hash(char *chave) {
    int i, n = 0;
    for (i = 0; i < strlen(chave); i++)
        n = (256 * n + chave[i]) % MAX;
    return n;
}
p_no inserir_lista(p_no lista, char *text){
    p_no novo;
    novo = malloc(sizeof(No));
    strcpy(novo->chave, text);
    novo->prox = lista;
    return novo;
}
//funcao para inserir novos elementos na hash, e caso ocorra colisao o for procura uma posicao vazia
void inserir(p_hash t, char *chave){//, int dado) {
    int i = 0, n = hash(chave);
    if(t->vetor[n] == NULL){
        t->vetor[n] = inserir_lista(t->vetor[n], chave);
    }else{
        for(i = 0; i <= MAX ; i++){//for para procurar uma posicao vazia quando ocorrer colisao
            if( (t->vetor[i] == NULL) && (i < MAX) ){
                t->vetor[i] = inserir_lista(t->vetor[i], chave);
                t->vetor[n]->coli = t->vetor[i];
                break;
            }
        } 
    }
}
//funcao q sera usada para dar o valor minimo nas operacoes da funcao levenshtein
int min(int a, int b, int c){	
	if(a <= b && a <= c){
		return a;
	}
	else if(b <= a && b <= c){
		return b;
	}
	else if(c <= a && c <= b){
		return c;
	}
    return 1;
}
//funcao para comparar duas str's, usa uma matriz e compara as palavras letra a letra verificando a diferenca entre elas
//podendo ser uma diferenca de adc uma letra, remover ou permutar
//sempre colocando o minimo de op na matrix diagonal e no fim retorna esse valor de mudancas que precisam ser feitas
int levenshtein(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len, cost;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[MAX+1][MAX+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++){
            cost = (s1[y-1] == s2[x-1] ? 0 : 1);
            matrix[x][y] = min(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] +  cost);
        }
    return(matrix[s2len][s1len]);
}
//essa funcao fica responsavel por preencher toda a tabela hash e retornar na funcao main
p_hash preenche_hash(p_hash hash_table, int n){
    int i;
    char nome[26];
    for(i = 0; i < n; i++){
        scanf("%s", nome);
        inserir(hash_table, nome);
    }
    return hash_table;
}
//funcao para limpar texto  a partir da pos fornecida
void limpa_texto(char *texto, int pos){
    int i;
    for(i = pos; i <= 24; i++){
        strcpy(&texto[i], "");
    }
}
int ti_ce_cf(char *str, char *palavra){ //ti = tamanho igual / ce = caractere extra / cf = caractere faltando
    int i, j, k, l, pos;
    char aux[26]; limpa_texto(aux, 0);
    for(i = 0; i < strlen(str) ; i++){//percorre toda a str
        //inia aux com as palavras da pos 0 e 1
        aux[i] = palavra[i];
        aux[i+1] = palavra[i+2];
        for(j = i+1; j < strlen(palavra); j++){ //percorre a str toda da pos i+1 e vai testando todas as possibilidades novamente
            aux[j+1] = palavra[j+2];
            pos = j+1;
            for(k = 97; k <= 122; k++){
                aux[pos+1] = k;
                for(l = pos+1; l < strlen(palavra); l++){//copia o resto da str apos ser feito as mudancas
                    aux[l+1] = palavra[l+1];
                }
                if(strcmp(str, aux) == 0) return true;
            }
        } 
        if(strcmp(str, aux) == 0) return true;
        limpa_texto(aux, i+1);
    }
    return false;
}
int ti_ct(char *str, char *palavra){    //ti = tamanho igual / ct = caractere trocado
    int i, j;
    char aux[26]; limpa_texto(aux, 0);
    strcpy(aux, palavra);//copia toda a palavra para aux
    for(i = 0; i < strlen(palavra); i++){//percorre toda a str
        for(j = 97; j <= 122; j++){//testa todas as possibilidades em cada pos da palavra
            aux[i] = j;
            if(strcmp(str, aux) == 0) return true;
        }
        aux[i] = palavra[i];//caso a palavra troca n seja a errada, colocamos ela de volta em aux, desfazendo o teste
    }
    return false;
}
int arranjo_trocado(char *str, char *palavra){//tamanho igual, porem tem caracteres permutados
    int i, j, k, l;
    char aux[26]; limpa_texto(aux, 0);
    strcpy(aux, palavra);//copia toda palavra para aux
    for(l = 0; l < strlen(palavra); l++){//percorre toda a str
        for(i = 97; i <= 122; i++){//vai testar todas as possibilidades('a' ate 'z') em cada posicao da str
            aux[l] = i;
            for(k = 1; k < strlen(palavra); k++){//percorre toda a str
                for(j = 97; j <= 122; j++){// testa todas as possibilidades novamente, porem da pos l+1 
                    aux[k] = j;
                    if(strcmp(str, aux) == 0) return true;
                }
                aux[k] = palavra[k];//caso o teste na pos k n tenha ocasionado no sucesso, entao desfazemos a mudanca na pos k e seguimos 
            }
        }
        aux[l] = palavra[l]; //caso a mudanca feita n tenha ajudado a encontrar a str, entao n era esse caractere o errado assim desfazemos a mudanca
    }
    return false;
}
//casca para verificar quando o tam da str e palavra sao iguais
int compara_tam_igual(char *st_hash, char *palavra){
    int ret = false;
    ret = ti_ce_cf(st_hash, palavra);//quando o tam é igual, porem tem um caractere a mais e um caractere a menso
    if(ret){
        return true;
    }else if(ti_ct(st_hash, palavra)){//tam igual porem tem um caractere trocado
        return true;
    }else if(arranjo_trocado(st_hash, palavra)){
        return true;
    }
    return false;
}
//nessa funcao vamos verificar onde ocorre o caractere a mais na str
int um_caractere_mais(char *str, char *palavra){
    int i, j;
    char aux[26]; limpa_texto(aux, 0);
    for(i = 0; i < strlen(palavra); i++){
        aux[i] = palavra[i];
        //inica o for com j sendo uma pos a mais q i, com isso ignoramos uma letra 
        for(j = i+1; j < strlen(palavra); j++){
            aux[j] = palavra[j+1];//copia o resto da str para aux
        }
        if(strcmp(str, aux) == 0) return true;//testa se agr aux e igual a str da hash, se sim retorna true
        //se apos ignorar uma letra e n acharmos a str limpamos aux de i+1 ate o fim, pois assumimos q o problema ocorre dps de i e n antes
        limpa_texto(aux, i+1);
    } 
    return false;
}
//aqui vericamos se o caractere a mais da str ta no inicio
//se for o caso, retorna true
int um_caractere_mais_inicio(char *str, char *palavra){
    int i;
    char aux[26]; limpa_texto(aux, 0);
    for(i = 0; i < strlen(palavra); i++){//copia palavra para aux, porem ignorando a primeira letra
        aux[i] = palavra[i+1];
    }
    if(strcmp(str, aux) == 0) return true;
    return false;
}
//se strlen(st_hash) == (strlen(palavra) - 1) entao a palavra do usuario é maior em apenas um caractere
//entao chamamos uma das funcoes um_caractere_mais ou um_caractere_mais_inicio
//retornando true ou false 
int compara_maior(char *st_hash, char *palavra){
    int ret;
    char aux[26]; limpa_texto(aux, 0);
    if(strlen(st_hash) == (strlen(palavra) - 1)){
        ret = um_caractere_mais(st_hash, palavra);
        if(ret){
            return true;
        }else if(um_caractere_mais_inicio(st_hash, palavra)){
            return true;
        }
    }
    return false; 
}
//essa funcao e usada somente na funcao um_caractere_menos, e copia a str a partir da pos fornecida
void copia_partir_de(char *str, char *palavra,int pos){
    int i;
    for(i = pos; i < strlen(palavra); i++){
        strcpy(&str[pos], &palavra[pos-1]);
    }
}
int um_caractere_menos(char *str, char *palavra){
    int i, j;
    char aux[26]; limpa_texto(aux, 0);
    //copia str palavra para aux, porem da 1 pos em diante
    //como falta uma letra, deixamos uma pos 'vazia' no inio de aux 
    //e vamos testando todas as possibilidades com o for de dentro
    copia_partir_de(aux, palavra, 1);
    for(i = 0; i < strlen(str); i++){
        //esse for vai rodar a tabela ASCII de a ate z e vai inserir inserir na str aux
        for(j = 97; j <= 122; j++){
            aux[i] = j;
            if(strcmp(str, aux) == 0) return true;//caso a mudanca feita ja torne a str aux igual a da hash, retorna true
        }
        //quando testamos todas as possibilidades e nao achamos a str, entao aquela letra nao era a errada
        //desfazemos a alteracao aq 
        aux[i] = palavra[i];
    }
    return false;//se n achar a str retorna false
}
//verifica se o tam str da hash - 1 = tam str palavra(usuario), se sim chama a funcao
//um_caractere_menos e verifica se a palavra é a msm da hash e retorna true ou false 
int compara_menor(char *st_hash, char *palavra  ){
    int ret;
    char aux[26]; limpa_texto(aux, 0);
    if((strlen(st_hash) - 1) == strlen(palavra)){
        ret = um_caractere_menos(st_hash, palavra);
        if(ret)
            return true;
    }
    return false;
}
//essa funcao funciona como uma casca para fazer a busca
//recebe a palavra(errada) e compara o tamanho com as palavras da hash
//se for strlen() for igual, usamos um jeito para verificar se e a msm palavra, da msm forma para os outros casos
int procura(p_hash t, char *palavra){
    int i, cont = 0, n = hash(palavra);
    if(t->vetor[n]->chave != NULL){//verifica se a palavra dada é a msm q ta na pos do hash, se for, retorna verde
        if(strcmp(t->vetor[n]->chave, palavra) == 0){
            printf("verde\n");
            return true;
        }
    }
    for (i = 0; i <  MAX; i++){//roda a hash toda ate achar a palavra correta da que foi fornecida pelo usuario
        if(t->vetor[i]->chave != NULL){
            if(strcmp(t->vetor[i]->chave, palavra) == 0){//quando a palavra dada é correta, porem n ta na pos do hash pq teve colisao
                printf("verde\n");
                return true;
            }
            if(strlen(palavra) == strlen(t->vetor[i]->chave))
                cont = compara_tam_igual(t->vetor[i]->chave, palavra);
            else if(strlen(palavra) > strlen(t->vetor[i]->chave))
                cont = compara_maior(t->vetor[i]->chave, palavra);
            else
                cont = compara_menor(t->vetor[i]->chave, palavra);
            if(cont){//cont recebe valor 'true' ou 'false', se achou entra no if e chama levenshtein para verificar a distancia entre as str's
                printf("%s\n", levenshtein(t->vetor[i]->chave, palavra) == 1? "amarelo": "vermelho");
                return true;
            }
            cont = 0; 
        }
    }
    printf("vermelho\n");//caso rode a hash toda e nao ache a palavra dada pelo usuario, printa vermelho e retorna false
    return false;
}
void destroi_lista(p_hash hash){
    int i;
    for(i = 0; i < MAX; i++){
        free(hash->vetor[i]);
    }
    free(hash);
}
