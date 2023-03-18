#include <stdio.h>

typedef struct gestor
{
int cod_g;
int password;
int contacto;
char username[100];
struct gestor* seguinte;
} Gestor;
