#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "../utils/utils.h"

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
            fputs("CPF;NOME;IDADE;CEP;BAIRRO;CIDADE;ESTADO", bancoClientes);
            fclose(bancoClientes);
            bancoClientes = fopen("clientes.txt", "a+");
            printf("Banco de clientes criado\n");
            return bancoClientes;
        }
    } else {
        fclose(bancoClientes);
        bancoClientes = fopen("clientes.txt", "a+");
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
        bancoClientes = fopen("clientes.txt", "a+");
        printf("Conectado ao banco de clientes\n");
        return bancoClientes;
    }
}

Cliente criarCliente() {
    FILE *bancoClientes = conectarBancoClientes();
    Cliente novoCliente;

    lerString(&novoCliente.cpf, "CPF");
    lerString(&novoCliente.nome, "Nome");
    printf("Idade: ");
    scanf("%d", &novoCliente.idade);
    lerString(&novoCliente.endereco.cep, "CEP");
    lerString(&novoCliente.endereco.bairro, "Bairro");
    lerString(&novoCliente.endereco.cidade, "Cidade");
    lerString(&novoCliente.endereco.estado, "Estado");

    fprintf(bancoClientes, "\n%s;%s;%d;%s;%s;%s;%s", novoCliente.cpf, novoCliente.nome, novoCliente.idade, novoCliente.endereco.cep, novoCliente.endereco.bairro, novoCliente.endereco.cidade, novoCliente.endereco.estado);
    fclose(bancoClientes);

    return novoCliente;
}

int encontrarCliente(char *cpfBusca, Cliente *cliente) {
    FILE *bancoClientes = conectarBancoClientes();
    char buffer[3100];

    while (fgets(buffer, sizeof(buffer), bancoClientes)) {
        char *campo = strtok(buffer, ";");
        if (!strcmp(cpfBusca, campo)) {
            (*cliente).cpf = malloc(strlen(campo) * sizeof(char));
            strcpy((*cliente).cpf, campo);                    

            campo = strtok(NULL, ";");
            (*cliente).nome = malloc(strlen(campo) * sizeof(char));
            strcpy((*cliente).nome, campo);                    

            campo = strtok(NULL, ";");
            (*cliente).idade = atoi(campo);

            campo = strtok(NULL, ";");
            (*cliente).endereco.cep = malloc(strlen(campo) * sizeof(char));
            strcpy((*cliente).endereco.cep, campo);                    

            campo = strtok(NULL, ";");
            (*cliente).endereco.bairro = malloc(strlen(campo) * sizeof(char));
            strcpy((*cliente).endereco.bairro, campo);                    

            campo = strtok(NULL, ";");
            (*cliente).endereco.cidade = malloc(strlen(campo) * sizeof(char));
            strcpy((*cliente).endereco.cidade, campo);                    

            campo = strtok(NULL, ";");
            (*cliente).endereco.estado = malloc(strlen(campo) * sizeof(char));
            strcpy((*cliente).endereco.estado, campo);                    

            return 1;
        }
    };

    printf("Nao encontrado\n");

    return 0;
}
