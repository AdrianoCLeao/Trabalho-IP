#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct jogo {
    char *nome;
    float preco;
    int qtd_estoque;
    char *genero;
    int classificacao_indicativa;
    char *data_adicao;
} Jogo;

void registrarTexto(const char *arquivo, const char *texto) {
    FILE *fp = fopen(arquivo, "a");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo ");
        exit(EXIT_FAILURE);
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(fp, "%02d/%02d/%04d %02d:%02d - %s\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, texto);
    fclose(fp);
}

char* lerString(const char* prompt) {
    char buffer[100];
    printf("%s: ", prompt);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    char *str = malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(str, buffer);
    return str;
}

void adicionarJogo(Jogo **jogos, int *count) {

    *jogos = realloc(*jogos, (*count + 1) * sizeof(Jogo));
    if (*jogos == NULL) {
        perror("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }


    Jogo *novoJogo = &(*jogos)[*count];
    novoJogo->nome = malloc(100 * sizeof(char));
    novoJogo->genero = malloc(50 * sizeof(char));

    printf("Nome do Jogo: ");
    fgets(novoJogo->nome, 100, stdin);
    novoJogo->nome[strcspn(novoJogo->nome, "\n")] = '\0';

    printf("Preco: ");
    scanf("%f", &novoJogo->preco);
    setbuf(stdin, NULL); 

    printf("Genero: ");
    fgets(novoJogo->genero, 50, stdin);
    novoJogo->genero[strcspn(novoJogo->genero, "\n")] = '\0';

    printf("Classificacao Indicativa: ");
    scanf("%d", &novoJogo->classificacao_indicativa);
    getchar();

    int qtdAdicionada;
    novoJogo->qtd_estoque = 0;
    
    printf("Quantidade de copias a adicionar: ");
    scanf("%d", &qtdAdicionada);
    getchar();

    novoJogo->qtd_estoque += qtdAdicionada;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char data[11];
    snprintf(data, sizeof(data), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    novoJogo->data_adicao = malloc((strlen(data) + 1) * sizeof(char));
    strcpy(novoJogo->data_adicao, data);

    (*count)++;

    char registro[200];
    snprintf(registro, sizeof(registro), "%s - %d copias adicionadas.", novoJogo->nome, qtdAdicionada);
    registrarTexto("registro.txt", registro);
}

void removerCopias(Jogo *jogos, int count) {
    int i;
    char nome[100];
    int qtdRemover;

    printf("Nome do Jogo a remover copias: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Quantidade de copias a remover: ");
    scanf("%d", &qtdRemover);
    getchar();

    for (i = 0; i < count; i++) {
        if (strcmp(jogos[i].nome, nome) == 0) {
            jogos[i].qtd_estoque -= qtdRemover;
            if (jogos[i].qtd_estoque < 0) jogos[i].qtd_estoque = 0;

            char registro[200];
            snprintf(registro, sizeof(registro), "%s - %d copias removidas.", jogos[i].nome, qtdRemover);
            registrarTexto("registro.txt", registro);

            return;
        }
    }

    printf("Jogo nao encontrado.\n");
}

void procurarJogoPorNome(Jogo* lista, int count, const char* nome) {
    int i;
    
    for (i = 0; i < count; i++) {
        if (strcmp(lista[i].nome, nome) == 0) {
            printf("Jogo encontrado:\n");
            printf("Nome: %s\n", lista[i].nome);
            printf("Preco: %.2f\n", lista[i].preco);
            printf("Quantidade em Estoque: %d\n", lista[i].qtd_estoque);
            printf("Genero: %s\n", lista[i].genero);
            printf("Classificacao Indicativa: %d\n", lista[i].classificacao_indicativa);
            return;
        }
    }
    printf("Jogo nao encontrado.\n");
}

void gerarRelatorioPorCategoria(Jogo* jogos, int count, const char* categoria, const char* valor) {
    int i;

    printf("Jogos com %s %s:\n", categoria, valor);
    for (i = 0; i < count; i++) {
        if ((strcmp(categoria, "genero") == 0 && strcmp(jogos[i].genero, valor) == 0) ||
            (strcmp(categoria, "classificacao") == 0 && jogos[i].classificacao_indicativa == atoi(valor))) {
            printf("- Nome: %s\n", jogos[i].nome);
        }
    }
}

void gerarRelatorioPorData(Jogo *jogos, int count) {
    int i, j;
    printf("Relatorio por Data de Adicao:\n");

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (strcmp(jogos[i].data_adicao, jogos[j].data_adicao) > 0) {
                Jogo temp = jogos[i];
                jogos[i] = jogos[j];
                jogos[j] = temp;
            }
        }
    }

    for (i = 0; i < count; i++) {
        printf("Data %s:\n", jogos[i].data_adicao);
        for (j = 0; j < count; j++) {
            if (strcmp(jogos[i].data_adicao, jogos[j].data_adicao) == 0) {
                printf("- Nome do Jogo: %s\n", jogos[j].nome);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Jogo *jogos = NULL;
    int count = 0;
    int opcao, i;
    char* nomeParaProcurar;

    system("cls");

    do {
        printf("1. Adicionar Jogo\n2. Remover Copias de Jogo\n3. Consultar jogo\n4. Gerar relatorio por categoria\n5. Gerar relatorio por data\n6. Sair\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                adicionarJogo(&jogos, &count);
                break;
            case 2:
                removerCopias(jogos, count);
                break;
            case 3:
                nomeParaProcurar = lerString("Digite o nome do jogo a procurar");
                procurarJogoPorNome(jogos, count, nomeParaProcurar);
                free(nomeParaProcurar);
                break;
            case 4: {
                char* categoria = lerString("Digite a categoria (genero/classificacao)");
                char* valor = lerString("Digite o valor da categoria");
                gerarRelatorioPorCategoria(jogos, count, categoria, valor);
                free(categoria);
                free(valor);
                break;
            }    
            case 5:
                gerarRelatorioPorData(jogos, count);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 6);

    for (i = 0; i < count; i++) {
        free(jogos[i].nome);
        free(jogos[i].genero);
    }
    free(jogos);

    return 0;
}

