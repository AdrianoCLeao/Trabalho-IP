#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#include "src/utils/utils.h"
#include "src/jogos/jogos.h"
#include "src/clientes/clientes.h"

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao, idade;
    char chave[20], valorBusca[50], nomeJogoEditar[50];
    Jogo *listaJogos = NULL;
    int count = 0;
    int i;

    do {
        menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                criarJogo("jogos.txt");
                break;
            case 2:
                printf("Chave de busca (nome/genero/plataforma): ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';
                printf("Valor da busca: ");
                fgets(valorBusca, sizeof(valorBusca), stdin);
                valorBusca[strcspn(valorBusca, "\n")] = '\0';
                encontrarJogo(chave, valorBusca, &listaJogos, &count);
                for (i = 0; i < count; i++) {
                    printf("Jogo encontrado: %s;%f;%d;%s;%d;%s;%s;%d;%f;%s\n",
                           listaJogos[i].nome, listaJogos[i].preco, listaJogos[i].qtd_estoque, listaJogos[i].data_lancamento,
                           listaJogos[i].qtd_reservado, listaJogos[i].genero, listaJogos[i].plataforma,
                           listaJogos[i].classificacao_indicativa, listaJogos[i].nota, listaJogos[i].modo_jogo);
                }
                break;
            case 3:
                printf("Nome do jogo a editar: ");
                fgets(nomeJogoEditar, sizeof(nomeJogoEditar), stdin);
                nomeJogoEditar[strcspn(nomeJogoEditar, "\n")] = '\0';
                editarJogo(nomeJogoEditar);
                break;
            case 4:
                printf("Digite a idade do usuário: ");
                scanf("%d", &idade);
                printf("Digite a classificação indicativa do jogo: ");
                int classificacao_indicativa;
                scanf("%d", &classificacao_indicativa);
                if (verificar_classificacao(idade, classificacao_indicativa)) {
                    printf("O usuário está autorizado a pegar este jogo.\n");
                } else {
                    printf("O usuário não está autorizado a pegar este jogo.\n");
                }
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    for (i = 0; i < count; i++) {
        free(listaJogos[i].nome);
        free(listaJogos[i].data_lancamento);
        free(listaJogos[i].genero);
        free(listaJogos[i].plataforma);
        free(listaJogos[i].modo_jogo);
    }
    free(listaJogos);

    return 0;
}