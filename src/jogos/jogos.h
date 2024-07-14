#include <stdio.h>

typedef struct jogo {
    char *nome;
    float preco;
    int qtd_estoque;
    char *data_lancamento;
    int qtd_reservado;
    char *genero;
    char *plataforma;
    int classificacao_indicativa;
    float nota;
    char *modo_jogo;
} Jogo;

Jogo criarJogo(const char *nomeArquivoBanco);

void encontrarJogo(const char *chave, const char *valorBusca, struct jogo **lista, int *count);

void editarJogo(const char *nomeJogoEditar);

int verificar_classificacao(int idade, int classificacao_indicativa);