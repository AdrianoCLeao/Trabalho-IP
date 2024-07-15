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

void encontrarJogo(const char *chave, const char *valorBusca, struct jogo **lista, int *count) {
    FILE *bancoJogos = conectarBanco("jogos.txt");
    char buffer[3100];

    while (fgets(buffer, sizeof(buffer), bancoJogos)) {
        struct jogo jogoAtual;
        char *campo = strtok(buffer, ";");

        jogoAtual.nome = malloc((strlen(campo) + 1) * sizeof(char));
        strcpy(jogoAtual.nome, campo);                    

        campo = strtok(NULL, ";");
        jogoAtual.preco = atof(campo);

        campo = strtok(NULL, ";");
        jogoAtual.qtd_estoque = atoi(campo);

        campo = strtok(NULL, ";");
        jogoAtual.data_lancamento = malloc((strlen(campo) + 1) * sizeof(char));
        strcpy(jogoAtual.data_lancamento, campo);                    

        campo = strtok(NULL, ";");
        jogoAtual.qtd_reservado = atoi(campo);

        campo = strtok(NULL, ";");
        jogoAtual.genero = malloc((strlen(campo) + 1) * sizeof(char));
        strcpy(jogoAtual.genero, campo);                    

        campo = strtok(NULL, ";");
        jogoAtual.plataforma = malloc((strlen(campo) + 1) * sizeof(char));
        strcpy(jogoAtual.plataforma, campo);                    

        campo = strtok(NULL, ";");
        jogoAtual.classificacao_indicativa = atoi(campo);

        campo = strtok(NULL, ";");
        jogoAtual.nota = atof(campo);

        campo = strtok(NULL, ";");
        jogoAtual.modo_jogo = malloc((strlen(campo) + 1) * sizeof(char));
        campo[strcspn(campo, "\n")] = '\0';
        strcpy(jogoAtual.modo_jogo, campo);                    

        if ((!strcmp(chave, "nome") && !strcmp(valorBusca, jogoAtual.nome)) ||
            (!strcmp(chave, "genero") && !strcmp(valorBusca, jogoAtual.genero)) ||
            (!strcmp(chave, "plataforma") && !strcmp(valorBusca, jogoAtual.plataforma))) {
            adicionarJogoNaLista(lista, count, jogoAtual);
        } else {
            free(jogoAtual.nome);
            free(jogoAtual.data_lancamento);
            free(jogoAtual.genero);
            free(jogoAtual.plataforma);
            free(jogoAtual.modo_jogo);
        }
    }

    fclose(bancoJogos);
}

void editarJogo(const char *nomeJogoEditar) {
    FILE *bancoJogos = conectarBanco("jogos.txt");
    FILE *novoBancoJogos = criarBanco("temp-jogos.txt", "NOME;PRECO;QTD_ESTOQUE;DATA_LANCAMENTO;QTD_RESERVADO;GENERO;PLATAFORMA;CLASSIFICACAO_INDICATIVA;NOTA;MODO_JOGO");
    int numEdicoes = 0;

    char buffer[3100];
    while (fgets(buffer, sizeof(buffer), bancoJogos)) {
        char *campo = strtok(buffer, ";");
        struct jogo jogoBanco;

        jogoBanco.nome = strdup(campo);

        campo = strtok(NULL, ";");
        jogoBanco.preco = atof(campo);

        campo = strtok(NULL, ";");
        jogoBanco.qtd_estoque = atoi(campo);

        campo = strtok(NULL, ";");
        jogoBanco.data_lancamento = strdup(campo);

        campo = strtok(NULL, ";");
        jogoBanco.qtd_reservado = atoi(campo);

        campo = strtok(NULL, ";");
        jogoBanco.genero = strdup(campo);

        campo = strtok(NULL, ";");
        jogoBanco.plataforma = strdup(campo);

        campo = strtok(NULL, ";");
        jogoBanco.classificacao_indicativa = atoi(campo);

        campo = strtok(NULL, ";");
        jogoBanco.nota = atof(campo);

        campo = strtok(NULL, ";");
        jogoBanco.modo_jogo = strdup(campo);
        jogoBanco.modo_jogo[strcspn(jogoBanco.modo_jogo, "\n")] = '\0';

        if(strcmp(jogoBanco.nome, nomeJogoEditar) == 0) {
            printf("Jogo encontrado: %s;%f;%d;%s;%d;%s;%s;%d;%f;%s\n",
                   jogoBanco.nome, jogoBanco.preco, jogoBanco.qtd_estoque, jogoBanco.data_lancamento,
                   jogoBanco.qtd_reservado, jogoBanco.genero, jogoBanco.plataforma,
                   jogoBanco.classificacao_indicativa, jogoBanco.nota, jogoBanco.modo_jogo);
            struct jogo jogoEdicao = criarJogo("temp-jogos.txt");
            numEdicoes++;
        } else {
            fprintf(novoBancoJogos, "%s;%f;%d;%s;%d;%s;%s;%d;%f;%s\n",
                    jogoBanco.nome, jogoBanco.preco, jogoBanco.qtd_estoque, jogoBanco.data_lancamento,
                    jogoBanco.qtd_reservado, jogoBanco.genero, jogoBanco.plataforma,
                    jogoBanco.classificacao_indicativa, jogoBanco.nota, jogoBanco.modo_jogo);
        }

        free(jogoBanco.nome);
        free(jogoBanco.data_lancamento);
        free(jogoBanco.genero);
        free(jogoBanco.plataforma);
        free(jogoBanco.modo_jogo);
    }

    if (numEdicoes == 0) {
        remove("temp-jogos.txt");
    } else {
        remove("jogos.txt");
        rename("temp-jogos.txt", "jogos.txt");
    }

    fclose(bancoJogos);
    fclose(novoBancoJogos);
}

int verificar_classificacao(int idade, int classificacao_indicativa) {
    return idade >= classificacao_indicativa;
}