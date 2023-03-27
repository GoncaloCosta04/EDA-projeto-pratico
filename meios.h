/**
 * @file meios.h
 * @author Gonçalo Costa (a26024@alunos.ipca.pt)
 * @brief 
 * @version 1.0
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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

void meiodisponivel(Meio *inicio); 
int alterarmeio(Meio* inicio, int cod, char tipo[100], float bateria, float autonomia, float preco, char geocodigo[50], int estado);
void procurarMeio(Meio* inicio);
void listarMeiosPorAutonomia(Meio* inicio);
Meio* removerMeio(Meio* inicio, int cod);
void listarMeios(Meio * inicio);
Meio* lerMeios();
Meio* inserirMeio(Meio* inicio, int cod_m, char tipo[], float bateria, float autonomia, float preco, char geocodigo[], int estado);
int guardarMeios(Meio* inicio);
int guardarMeiosembinario(Meio* inicio);