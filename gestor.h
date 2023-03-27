/**
 * @file gestor.h
 * @author Gonçalo Costa (a26024@alunos.ipca.pt)
 * @brief 
 * @version 1.0
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>

typedef struct gestor
{
int cod_g;
int password;
int contacto;
char username[100];
struct gestor* seguinte;
} Gestor;


int guardarGestor(Gestor* inicio);
Gestor* lerGestor();
int existeGestor(Gestor* inicio, int cod);
Gestor* inserirGestor(Gestor* inicio, int cod_g,int password,int contacto, char username[]);
Gestor* removerGestor(Gestor* inicio, int cod);
int  alterargestor(Gestor *inicio, int cod, int pass, char novo_username[100], int nova_password);
void listarGestor(Gestor * inicio);
int guardarGestor(Gestor* inicio);
int guardarGestorembinario(Gestor* inicio);