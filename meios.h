#include <stdio.h>

typedef struct meio
{
int cod_m;
char tipo[100];
float bateria;
float autonomia;
float preco;
char geocodigo[50];
int estado;
struct meio* seguinte;
} Meio;