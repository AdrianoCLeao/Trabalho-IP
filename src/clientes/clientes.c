#include <stdio.h>
#include <stdlib.h>

FILE* criarBancoClientes() {
    FILE *bancoClientes = fopen("clientes.txt", "r");

    if (bancoClientes == NULL) {
        printf("Tentando criar novo banco de clientes...\n");
        bancoClientes = fopen("clientes.txt", "w");
        if (bancoClientes == NULL) {
            printf("Erro ao criar um banco de clientes\n");
            return NULL;
        } else {
            rewind(bancoClientes);
            fputs("Banco pronto para receber dados", bancoClientes);
            fclose(bancoClientes);
            bancoClientes = fopen("clientes.txt", "a");
            printf("Banco de clientes criado\n");
            return bancoClientes;
        }
    } else {
        fclose(bancoClientes);
        bancoClientes = fopen("clientes.txt", "a");
        return bancoClientes;
    }
}

FILE* conectarBancoClientes() {
    FILE *bancoClientes = fopen("clientes.txt", "r");

    if (bancoClientes == NULL) {
        printf("Erro ao conectar com o banco de clientes\n");        
        bancoClientes = criarBancoClientes();
        if (bancoClientes == NULL) {
            printf("Nao foi possivel se conectar ao banco de clientes\n");
            return(NULL);
        } else {
            printf("Conectado ao novo banco de clientes\n");
            return bancoClientes;
        }
    } else {
        fclose(bancoClientes);
        bancoClientes = fopen("clientes.txt", "a");
        printf("Conectado ao banco de clientes\n");
        return bancoClientes;
    }
}