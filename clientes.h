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
Cliente* carregar_saldo(Cliente *inicio, int cod,  float valor);
int guardarClientebinario(Cliente* inicio);