#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lerString(char **string, char *textoInput) {
    char buffer[500];

    setbuf(stdin, NULL);
    printf("%s: ", textoInput);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    *string = malloc(strlen(buffer) * sizeof(char)); 
    strcpy(*string, buffer);
}

FILE* criarBanco(char *nomeArquivoBanco, char *textoInicial) {
    FILE *banco = fopen(nomeArquivoBanco, "r");

    if (banco == NULL) {
        printf("Tentando criar novo banco ...\n");
        banco = fopen(nomeArquivoBanco, "w");
        if (banco == NULL) {
            printf("Erro ao criar o banco\n");
            return NULL;
        } else {
            rewind(banco);
            fputs(textoInicial, banco);
            fclose(banco);
            banco = fopen(nomeArquivoBanco, "a+");
            printf("Banco criado\n");
            return banco;
        }
    } else {
        fclose(banco);
        banco = fopen(nomeArquivoBanco, "a+");
        return banco;
    }
}

FILE* conectarBanco(char *nomeArquivoBanco) {
    FILE *banco = fopen(nomeArquivoBanco, "r");

    if (banco == NULL) {
        printf("Erro ao conectar com o banco\n");
        char *textoInicial;
        lerString(&textoInicial, "Texto inicial para o novo banco");        
        banco = criarBanco(nomeArquivoBanco, textoInicial);
        if (banco == NULL) {
            return NULL;
        } else {
            printf("Conectado ao novo banco\n");
            return banco;
        }
    } else {
        fclose(banco);
        banco = fopen(nomeArquivoBanco, "a+");
        printf("Conectado ao banco\n");
        return banco;
    }
}