#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"
#include "../utils/utils.h"

Jogo criarJogo(char *nomeArquivoBanco) {
    FILE *bancoJogos = conectarBanco(nomeArquivoBanco);
    Jogo novoJogo;

    lerString(&novoJogo.nome, "Nome do Jogo");
    printf("Preço: ");
    scanf("%f", &novoJogo.preco);
    printf("Quantidade em Estoque: ");
    scanf("%d", &novoJogo.qtd_estoque);
    lerString(&novoJogo.data_lancamento, "Data de Lançamento (DD/MM/AAAA)");
    printf("Quantidade Reservada: ");
    scanf("%d", &novoJogo.qtd_reservado);
    lerString(&novoJogo.genero, "Gênero");
    lerString(&novoJogo.plataforma, "Plataforma");
    printf("Classificação Indicativa: ");
    scanf("%d", &novoJogo.classificacao_indicativa);
    printf("Nota: ");
    scanf("%f", &novoJogo.nota);
    lerString(&novoJogo.modo_jogo, "Modo de Jogo (Singleplayer/Multiplayer)");

    fprintf(bancoJogos, "%s;%f;%d;%s;%d;%s;%s;%d;%f;%s\n", 
            novoJogo.nome, novoJogo.preco, novoJogo.qtd_estoque, novoJogo.data_lancamento, 
            novoJogo.qtd_reservado, novoJogo.genero, novoJogo.plataforma, 
            novoJogo.classificacao_indicativa, novoJogo.nota, novoJogo.modo_jogo);
    fclose(bancoJogos);

    return novoJogo;
}

int verificar_classificacao(int idade, int classificacao_indicativa) {
    return idade >= classificacao_indicativa;
}