#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "diadeuber.h"
int main(){
    p_fp corridas = criar_filaprio(500);
    //atr_corridas serve para atribuir valores ao item q vai ser inserido na fila // atr_aux serve para atribuir o retorno funcao extrai_maximo e usar o valores dos membros
    Item atr_corridas = inicializa(atr_corridas), atr_aux = inicializa(atr_aux);
    char operacao, nome[16];
    double rendiment_bruto = 0.0, despesas = 0.0, rendimento_liquido = 0.0;
    int km_total = 0,  km_ret_fi = 0, cancelamentos = 0; // km_ret_fi é o contador de km rodados e que serao considerados pela uber na hora de pagar
    //c_x_d e c_y_d vai servir para guardar as cordenadas de destino do ultimo cliente
    //entao quando tiver uma nova corrida, usaremos essas variaveis para contar o km percorrido até o novo cliente. Incrementando o km_total .
    int c_x_d = 0, c_y_d = 0; 
    int primeira_corrida = false;  
    while( (scanf(" %c", &operacao) != EOF) && (operacao != 'T') ){
        if(operacao == 'A'){
            scanf("%s %lf %d %d %d %d", atr_corridas.nome, &atr_corridas.chave, &atr_corridas.origem.x, &atr_corridas.origem.y, &atr_corridas.destino.x, &atr_corridas.destino.y);
            if(vazia(corridas)){//se lista vazia, temos uma primeira corrida, então esse cliente deve ter prioridade maxima no heap, pra isso a verificacao
                atr_corridas.prioridade = true;
                insere(corridas, atr_corridas);
                atr_corridas.prioridade = false;//transforma prioridade em false, para que os proximos clientes nao tenham o valor como true e quebre o codigo
            }else
                insere(corridas, atr_corridas);
            printf("Cliente %s foi adicionado(a)\n", atr_corridas.nome);
        }else if(operacao == 'F'){
            //chama a funcao heapsort e transforma a heap numa heap de max e apos isso coloca em ordem crescente, sempre garantindo que o cliente com maior prioridade fique no topo
            heapsort(corridas, corridas->n );
            if(primeira_corrida) // caso seja a primeira corrida, n usaremos c_x_d e c_y_d como sendo do ultimo cliente, mas sim como o ponto (0, 0) casa do motorista
                primeira_corrida = false;
            else
                c_x_d = atr_aux.destino.x, c_y_d = atr_aux.destino.y;
            atr_aux = extrai_maximo(corridas);
            km_total  += calcula_distancia(c_x_d, c_y_d, atr_aux.origem.x, atr_aux.origem.y); 
            km_total  += calcula_distancia(atr_aux.origem.x, atr_aux.origem.y, atr_aux.destino.x, atr_aux.destino.y);
            km_ret_fi += calcula_distancia(atr_aux.origem.x, atr_aux.origem.y, atr_aux.destino.x, atr_aux.destino.y);
            muda_prioridade(corridas);//apos finalizar uma corrida, o cliente que estava em segundo na lista de espera passara a ter prioridade maxima
            printf("A corrida de %s foi finalizada\n", atr_aux.nome);
        }else if(operacao == 'C'){
            cancelamentos += 7;
            scanf("%s", nome);
            cancelou_corrida(corridas, nome);
            printf("%s cancelou a corrida\n", nome);
        }
    }
    printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\n", km_total);
    rendiment_bruto = (km_ret_fi * 1.4) + cancelamentos;
    printf("Rendimento bruto: %.2lf\n", rendiment_bruto);
    despesas = ( ((double)km_total / 10) * 4.104) + 57;
    printf("Despesas: %.2lf\n", despesas);
    rendimento_liquido = rendiment_bruto - (rendiment_bruto * 0.25) - despesas;
    printf("Rendimento liquido: %.2lf\n", rendimento_liquido);
    free(corridas->v);
    free(corridas); 
    return 0;
}
