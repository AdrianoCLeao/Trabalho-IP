#include <stdio.h>

typedef struct endereco
{
    char *cep;
    char *bairro;
    char *cidade;
    char *estado;
} Endereco;

typedef struct cliente {
    char *cpf;
    char *nome;
    int idade;
    Endereco endereco; 
} Cliente;

FILE* criarBancoClientes();
FILE* conectarBancoClientes();
Cliente criarCliente();