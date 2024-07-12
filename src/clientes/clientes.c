#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "../utils/utils.h"

Cliente criarCliente() {
    FILE *bancoClientes = conectarBanco("clientes.txt");
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
    FILE *bancoClientes = conectarBanco("clientes.txt");
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
            campo[strcspn(campo, "\n")] = '\0';
            strcpy((*cliente).endereco.estado, campo);                    

            return 1;
        }
    };

    printf("Nao encontrado\n");

    return 0;
}

void removerCliente(char *cpfRemover) {
    FILE *bancoClientes = conectarBanco("clientes.txt");
    FILE *novoBancoClientes = criarBanco("temp-clientes.txt", "CPF;NOME;IDADE;CEP;BAIRRO;CIDADE;ESTADO");

    char buffer[3100];
    for (int i = 0; fgets(buffer, sizeof(buffer), bancoClientes); i++) {
        if (i == 0) {
            continue;
        }
        char *campo = strtok(buffer, ";");
        if(strcmp(campo, cpfRemover) != 0) {
            Cliente clienteMantido;
            encontrarCliente(campo, &clienteMantido);
            fprintf(novoBancoClientes, "\n%s;%s;%d;%s;%s;%s;%s", clienteMantido.cpf, clienteMantido.nome, clienteMantido.idade, clienteMantido.endereco.cep, clienteMantido.endereco.bairro, clienteMantido.endereco.cidade, clienteMantido.endereco.estado);
        }
    }

    rename("clientes.txt", "backup-clientes.txt");
    rename("temp-clientes.txt", "clientes.txt");
    fclose(bancoClientes);
    fclose(novoBancoClientes);
}