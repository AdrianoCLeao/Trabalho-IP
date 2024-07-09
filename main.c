#include <stdio.h>
#include <string.h>

struct jogos {
    char nome[50];
    float preco;
    int qtd_estoque;
    char data_lancamento[10];
    int qtd_reservado; // Qtas vezes foi reservado
    char genero[15];
    char plataforma[15]; // Xbox, PC, Playstation ...
    int classificacao_indicativa;
    float nota; // De 0 a 10
    char modo_jogo[15]; // Singleplayer, multiplayer
};

struct cliente {
    char cpf[15];
    char nome[50];
    int idade;
    char endereco[50]; 
    int genero_favorito;
    int qtd_reservados;
    int historico;
};

struct estoque {
    struct jogos jogo[50];
    struct cliente cliente[50];
    int qtd_jogos;
};

int verificar_classificacao(int idade, int classificacao_indicativa) {
    if (classificacao_indicativa == 0) return 1;
    else if (classificacao_indicativa == 10 && idade >= 10) return 1;
    else if (classificacao_indicativa == 12 && idade >= 12) return 1;
    else if (classificacao_indicativa == 14 && idade >= 14) return 1;
    else if (classificacao_indicativa == 16 && idade >= 16) return 1;
    else if (classificacao_indicativa == 18 && idade >= 18) return 1;
    return 0;
}

void salvar_jogos(struct estoque *estoque) {
    int i;

    FILE *arquivo = fopen("../Jogos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (i = 0; i < estoque->qtd_jogos; i++) {
        fprintf(arquivo, "Nome: %s\n", estoque->jogo[i].nome);
        fprintf(arquivo, "Preco: %.2f\n", estoque->jogo[i].preco);
        fprintf(arquivo, "Quantidade em Estoque: %d\n", estoque->jogo[i].qtd_estoque);
        fprintf(arquivo, "Data de Lancamento: %s\n", estoque->jogo[i].data_lancamento);
        fprintf(arquivo, "Quantidade Reservada: %d\n", estoque->jogo[i].qtd_reservado);
        fprintf(arquivo, "Genero: %s\n", estoque->jogo[i].genero);
        fprintf(arquivo, "Plataforma: %s\n", estoque->jogo[i].plataforma);
        fprintf(arquivo, "Classificacao Indicativa: %d\n", estoque->jogo[i].classificacao_indicativa);
        fprintf(arquivo, "Nota: %.2f\n", estoque->jogo[i].nota);
        fprintf(arquivo, "Modo de Jogo: %s\n", estoque->jogo[i].modo_jogo);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Jogos salvos com sucesso em Jogos.txt.\n");
}

void ler_jogos(struct estoque *estoque) {
    int i;

    printf("Quantos jogos deseja cadastrar? ");
    scanf("%d", &estoque->qtd_jogos);
    getchar(); 

    for (i = 0; i < estoque->qtd_jogos; i++) {
        printf("Digite o nome do jogo: ");
        fgets(estoque->jogo[i].nome, 50, stdin);
        estoque->jogo[i].nome[strcspn(estoque->jogo[i].nome, "\n")] = '\0'; 

        printf("Digite o preco do jogo: ");
        scanf("%f ", &estoque->jogo[i].preco);

        printf("Digite a quantidade em estoque: ");
        scanf("%d", &estoque->jogo[i].qtd_estoque);
        getchar(); 

        printf("Digite a data de lancamento (dd/mm/yyyy): ");
        fgets(estoque->jogo[i].data_lancamento, 10, stdin);
        estoque->jogo[i].data_lancamento[strcspn(estoque->jogo[i].data_lancamento, "\n")] = '\0'; 

        estoque->jogo[i].qtd_reservado = 0; 

        getchar(); 
        printf("Digite o genero do jogo: ");
        fgets(estoque->jogo[i].genero, 15, stdin);
        estoque->jogo[i].genero[strcspn(estoque->jogo[i].genero, "\n")] = '\0'; 

        printf("Digite a plataforma do jogo (Xbox, PC, Playstation, etc.): ");
        fgets(estoque->jogo[i].plataforma, 15, stdin);
        estoque->jogo[i].plataforma[strcspn(estoque->jogo[i].plataforma, "\n")] = '\0'; 

        printf("Digite a classificacao indicativa do jogo: ");
        scanf("%d", &estoque->jogo[i].classificacao_indicativa);
        getchar(); 

        printf("Digite a nota do jogo (0 a 10): ");
        scanf("%f", &estoque->jogo[i].nota);
        getchar(); 

        printf("Digite o modo de jogo (Singleplayer, Multiplayer): ");
        fgets(estoque->jogo[i].modo_jogo, 15, stdin);
        estoque->jogo[i].modo_jogo[strcspn(estoque->jogo[i].modo_jogo, "\n")] = '\0'; 

        printf("\n");
    }
}

int main() {
    struct estoque estoque;

    ler_jogos(&estoque);

    salvar_jogos(&estoque);

    return 0;
}
