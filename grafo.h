#include "meio.h"
#include "cliente.h"
#include "gestor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct registo1 
{
    char vertice[250]; 
    struct registo2 *adjacentes;
    Meio* meios;
    Cliente* clientes;
    int visitado;
    float distancia;
    struct registo1 *seguinte;
} *Grafo;

typedef struct registo2 {
    char vertice[250];
    float peso;
    Meio* meios;
    Grafo grafos;  
    int visitado;
    struct registo2* seguinte;
} *Adjacente;

int criarVertice(Grafo *g, char novoId[]);
int existeVertice(Grafo g, char vertice[]); 
void saveVertices(Grafo g);
void saveVerticesbin(Grafo g); 
void readVertices(Grafo* g);
int criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso);
void saveArestas(Grafo g);
void saveArestasbin(Grafo g); 
void readArestas(Grafo* g);
int inserirMeioNoGrafo(Grafo g, char geocodigo[], int codigom, char tipo[], float bateriam, float autonomia, float preco, int estado, float espacom);
void saveMeios(Grafo g);
void saveMeiosbin(Grafo g);
void readMeios(Grafo* g);
int inserirClienteNoGrafo(Grafo g, char geocodigo[], int codigoc, char nome[], int NIF, float saldo, char morada[]);
void saveClientes(Grafo g);
void saveClientesbin(Grafo g);
void readClientes(Grafo* g);
Grafo procurarVertice(Grafo g, const char* geocodigo); 
void listarMeiosGrafo(Grafo g, char vertice[]);
void listarClientesGrafo(Grafo g, char vertice[]);
void listarMeiosBaixaBateria(Grafo g);
int clienteExiste(Grafo g, char geoccode[]);
Grafo findNode(Grafo g, char geocode[]);
void traverseEdgesDFS(Grafo node, char type[], float radius, float currentWeight, Grafo g);
void listVehiclesPerRadius(Grafo g, char geocode[], char type[], float radius);
void Visitados(Grafo g);    
void printPath(Grafo node, int caminhoAtual);
void findShortestPaths(Grafo g, char* inicio);
void IIItraverseNodesDFS(Grafo node, Grafo g, int caminhoAtual);
void apresentarMeiosEstadoBateria(Grafo grafo);

