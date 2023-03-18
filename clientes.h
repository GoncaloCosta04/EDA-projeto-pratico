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
