/**
 * @file clientes.h
 * @author Gonçalo Costa (a26024@alunos.ipca.pt)
 * @brief 
 * @version 1.0
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>

typedef struct cliente 
{
int cod_c; 
char nome[100];
int NIF; 
float saldo; 
char morada[250]; 
struct cliente* seguinte; 
} Cliente;

int guardarCliente(Cliente* inicio);
Cliente* lerCliente();
int existeCliente(Cliente* inicio, int cod);
Cliente* inserirCliente(Cliente* inicio, int cod_c, char nome[], int NIF, float saldo, char morada[]);
void listarClientes(Cliente * inicio);
Cliente* removerCliente(Cliente* inicio, int cod);
int alterarcliente(Cliente *inicio, int cod_c, int nif, char nova_morada[250]);
Cliente* carregarsaldo(Cliente *inicio, int cod,  float valor);
int guardarClientebinario(Cliente* inicio);

