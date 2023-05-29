/**
 * @file grafo.c
 * @author Gonçalo (a26024@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */



#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "grafo.h"

/**
 * @brief 
 * 
 * @param g 
 * @param novoId 
 * @return int 
 */
int criarVertice(Grafo *g, char novoId[]) {
    if ( g== NULL) {
        return 0; 
    }

    Grafo novo = malloc(sizeof(struct registo1));
    if (novo != NULL) {
        strcpy(novo->vertice, novoId);
        novo->adjacentes = NULL;
        novo->meios = NULL;
        novo->clientes = NULL;
        novo->seguinte = *g;
        *g = novo;
        return 1;
    } else {
        return 0;
    }
}



/**
 * @brief 
 * 
 * @param g 
 * @param vertice 
 * @return int 
 */

int existeVertice(Grafo g, char vertice[]) {
    while (g != NULL) {
        if (strcmp(g->vertice, vertice) == 0)
            return 1;
        g = g->seguinte;
    }
    return 0;
}



/**
 * @brief 
 * 
 * @param g 
 */
void saveVertices(Grafo g) {
    FILE* fp;
    fp = fopen("vertices.txt", "w");

    if (fp != NULL) {
        Grafo vertice = g;

        while (vertice != NULL) {
            fprintf(fp, "%s\n", vertice->vertice);
            vertice = vertice->seguinte;
        }

        fclose(fp);
        printf("Vertices guardados com sucesso no ficheiro vertices.txt\n");
    } else {
        printf("Erro ao abrir ficheiro vertices.txt\n");
    }
}


/**
 * @brief 
 * 
 * @param g 
 */
void saveVerticesbin(Grafo g) {
    FILE* fp;
    fp = fopen("vertices.bin", "wb");

    if (fp != NULL) {
        Grafo vertice = g;

        while (vertice != NULL) {
            fwrite(vertice, sizeof(struct registo1), 1, fp);
            vertice = vertice->seguinte;
        }

        fclose(fp);
        printf("Vertices guardados com sucesso\n");
    } else {
        printf("Erro\n");
    }
}



/**
 * @brief 
 * 
 * @param g 
 */
void readVertices(Grafo* g) {
    FILE* fp = fopen("vertices.txt", "r");

    if (fp != NULL) {
        char linha[250];

        while (fgets(linha, sizeof(linha), fp) != NULL) {
            linha[strcspn(linha, "\n")] = '\0';

            criarVertice(g, linha);
        }

        fclose(fp);
        printf("Vertices lidos com sucesso do ficheiro vertices\n");
    } else {
        printf("Erro ao abrir o ficheiro  vertices\n");
    }
}


/**
 * @brief 
 * 
 * @param g 
 * @param vOrigem 
 * @param vDestino 
 * @param peso 
 * @return int 
 */
int criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso) {
    if (existeVertice(g, vOrigem) && existeVertice(g, vDestino)) {
        Grafo origem = g;
        while (strcmp(origem->vertice, vOrigem) != 0)
            origem = origem->seguinte;

        Adjacente novo = malloc(sizeof(struct registo2));
        if (novo != NULL) {
            strcpy(novo->vertice, vDestino);
            novo->peso = peso;
            novo->meios = NULL;
            novo->grafos = NULL;
            novo->visitado = 0;
            novo->seguinte = origem->adjacentes;
            origem->adjacentes = novo;
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

/**
 * @brief 
 * 
 * @param g 
 */
void saveArestas(Grafo g) {
    FILE* fp;
    fp = fopen("arestas.txt", "w");

    if (fp != NULL) {
        Grafo vertice = g;

        while (vertice != NULL) {
            Adjacente adj = vertice->adjacentes;
            while (adj != NULL) {
                fprintf(fp, "%s %s %.2f\n", vertice->vertice, adj->vertice, adj->peso);
                adj = adj->seguinte;
            }
            
            vertice = vertice->seguinte;
        }

        fclose(fp);
        printf("Arestas guardadas com sucesso no ficheiro arestas\n");
    } else {
        printf("Erro ao abrir o ficheiro arestas\n");
    }
}




/**
 * @brief 
 * 
 * @param g 
 */
void saveArestasbin(Grafo g) {
    FILE* fp;
    fp = fopen("arestas.bin", "wb");

    if (fp != NULL) {
        Grafo vertice = g;

        while (vertice != NULL) {
            Adjacente adj = vertice->adjacentes;
            while (adj != NULL) {
                fwrite(vertice, sizeof(struct registo1), 1, fp);
                fwrite(adj, sizeof(struct registo2), 1, fp);
                adj = adj->seguinte;
            }
            
            vertice = vertice->seguinte;
        }

        fclose(fp);
        printf("Arestas guardadas com sucesso no arquivo arestas.bin\n");
    } else {
        printf("Erro ao abrir o arquivo arestas.bin\n");
    }
}

/**
 * @brief 
 * 
 * @param g 
 */
void readArestas(Grafo* g) {
    FILE* fp = fopen("arestas.txt", "r");

    if (fp != NULL) {
        char vOrigem[250], vDestino[250];
        float peso;

        while (fscanf(fp, "%s %s %f", vOrigem, vDestino, &peso) == 3) {
            criarAresta(*g, vOrigem, vDestino, peso);
        }

        fclose(fp);
        printf("Arestas lidas com sucesso do ficheiro arestas\n");
    } else {
        printf("Erro ao abrir o ficheiro arestas\n");
    }
}


/**
 * @brief 
 * 
 * @param g 
 * @param geocodigo 
 * @param codigom 
 * @param tipo 
 * @param bateriam 
 * @param autonomia 
 * @param preco 
 * @param estado 
 * @param espacom 
 * @return int 
 */
int inserirMeioNoGrafo(Grafo g, char geocodigo[], int codigom, char tipo[], float bateriam, float autonomia, float preco, int estado, float espacom) {
    while (g != NULL && strcmp(g->vertice, geocodigo) != 0) {
        g = g->seguinte;
    }
    
    if (g == NULL) {
        return 0; // Vértice não encontrado no grafo
    } else {
        Meio* novo = malloc(sizeof(Meio));
        novo->codm = codigom;
        strcpy(novo->geocodigo, geocodigo);
        strcpy(novo->tipo, tipo);
        novo->bateria = bateriam;
        novo->autonomia = autonomia;
        novo->preco = preco;
        novo->estado = estado;
        novo->espaco = espacom;
        novo->seguinte = g->meios;
        g->meios = novo;
        return 1; // Inserção bem-sucedida
    }
}
 


/**
 * @brief 
 * 
 * @param g 
 */
void saveMeios(Grafo g) {
    FILE* fp;
    fp = fopen("meiosg.txt", "w");

    if (fp != NULL) {
        Grafo vertice = g;

        while (vertice != NULL) {
            Meio* meio = vertice->meios;
            while (meio != NULL) {
                fprintf(fp, "%s %d %s %.2f %.2f %.2f %d %.2f\n", vertice->vertice, meio->codm, meio->tipo, meio->bateria, meio->autonomia, meio->preco, meio->estado, meio->espaco);
                meio = meio->seguinte;
            }
            
            vertice = vertice->seguinte;
        }

        fclose(fp);
        printf("Meios guardados com sucesso no arquivo meios\n");
    } else {
        printf("Erro ao abrir o ficheiro meios\n");
    }
}


/**
 * @brief 
 * 
 * @param g 
 */
void saveMeiosbin(Grafo g) {
    FILE* fp;
    fp = fopen("meiosg.bin", "wb");

    if (fp != NULL) {
        Grafo vertice = g;

        while (vertice != NULL) {
            Meio* meio = vertice->meios;
            while (meio != NULL) {
                fwrite(meio, sizeof(Meio), 1, fp);
                meio = meio->seguinte;
            }
            
            vertice = vertice->seguinte;
        }

        fclose(fp);
        printf("Meios guardados com sucesso no arquivo meios.bin\n");
    } else {
        printf("Erro ao abrir o arquivo meios.bin\n");
    }
}



/**
 * @brief 
 * 
 * @param g 
 */
void readMeios(Grafo* g) {
    FILE* fp = fopen("meiosg.txt", "r");

    if (fp != NULL) {
        char vVertice[250], vTipo[100];
        int vCodm, vEstado;
        float vBateria, vAutonomia, vPreco, vEspaco;

        while (fscanf(fp, "%s %d %s %f %f %f %d %f", vVertice, &vCodm, vTipo, &vBateria, &vAutonomia, &vPreco, &vEstado, &vEspaco) == 8) {
            inserirMeioNoGrafo(*g, vVertice, vCodm, vTipo, vBateria, vAutonomia, vPreco, vEstado, vEspaco);
        }

        fclose(fp);
        printf("Meios lidos com sucesso do ficheiro meios\n");
    } else {
        printf("Erro ao abrir o ficheiro meios\n");
    }
}




/**
 * @brief 
 * 
 * @param g 
 * @param geocodigo 
 * @param codigoc 
 * @param nome 
 * @param NIF 
 * @param saldo 
 * @param morada 
 * @return int 
 */
int inserirClienteNoGrafo(Grafo g, char geocodigo[], int codigoc, char nome[], int NIF, float saldo, char morada[]) {
    while (g != NULL && strcmp(g->vertice, geocodigo) != 0) {
        g = g->seguinte;
    }
    
    if (g == NULL) {
        return 0; 
    } else {
        Cliente* novo = malloc(sizeof(Cliente));
        novo->codc = codigoc;
        strcpy(novo->geocodigoc, geocodigo);
        strcpy(novo->nome, nome);
        novo->NIF = NIF;
        novo->saldo = saldo;
        strcpy(novo->morada, morada);
        novo->seguinte = g->clientes;
        g->clientes = novo;
        return 1;
    }
}



/**
 * @brief 
 * 
 * @param g 
 */
void saveClientes(Grafo g) {
    FILE* fp;
    fp = fopen("clientesg.txt", "w");

    if (fp != NULL) {
        Grafo vertice = g;

        while (vertice != NULL) {
            Cliente* cliente = vertice->clientes;
            while (cliente != NULL) {
                fprintf(fp, "%s %d %s %s  %.2f\n", vertice->vertice, cliente->codc, cliente->nome, cliente->morada,  cliente->saldo);
                cliente = cliente->seguinte;
            }
            
            vertice = vertice->seguinte;
        }

        fclose(fp);
        printf("Clientes guardados com sucesso no ficheiro clientes\n");
    } else {
        printf("Erro ao abrir o ficheiro clientes\n");
    }
}



/**
 * @brief 
 * 
 * @param g 
 */
void saveClientesbin(Grafo g) {
    FILE* fp;
    fp = fopen("clientesg.bin", "wb");

    if (fp != NULL) {
        Grafo vertice = g;

        while (vertice != NULL) {
            Cliente* cliente = vertice->clientes;
            while (cliente != NULL) {
                fwrite(cliente, sizeof(Cliente), 1, fp);
                cliente = cliente->seguinte;
            }
            
            vertice = vertice->seguinte;
        }

        fclose(fp);
        printf("Clientes guardados com sucesso no arquivo clientes.bin\n");
    } else {
        printf("Erro ao abrir o arquivo clientes.bin\n");
    }
}



/**
 * @brief 
 * 
 * @param g 
 */
void readClientes(Grafo* g) {
    FILE* fp = fopen("clientesg.txt", "r");

    if (fp != NULL) {
        char vVertice[250], vNome[100], vMorada[100];
        int vCodc, vNIF;
        float vSaldo;

        while (fscanf(fp, "%s %d %s %d %f", vVertice, &vCodc, vNome, &vNIF, &vSaldo) == 5) {
            inserirClienteNoGrafo(*g, vVertice, vCodc, vNome, vNIF, vSaldo, vMorada);
        }

        fclose(fp);
        printf("Clientes lidos com sucesso do ficheiro clientes\n");
    } else {
        printf("Erro ao abrir o ficheiro clientes\n");
    }
}



/**
 * @brief 
 * 
 * @param g 
 * @param geocodigo 
 * @return Grafo 
 */
Grafo procurarVertice(Grafo g, const char* geocodigo) 
{
    while (g != NULL) {
        if (strcmp(g->vertice, geocodigo) == 0) {
            return g;
        }
        g = g->seguinte;
    }
    return NULL; 
}




/**
 * @brief 
 * 
 * @param g 
 * @param vertice 
 */
void listarMeiosGrafo(Grafo g, char vertice[])
{
    Grafo verticeEncontrado = procurarVertice(g, vertice);
    
    if (verticeEncontrado != NULL)
    {
        printf("Vértice: %s\n", verticeEncontrado->vertice);
        Meio* aux = verticeEncontrado->meios;
        
        if (aux == NULL)
        {
            printf("Sem meios de transporte\n");
        }
        else
        {
            while (aux != NULL)
            {
                printf("Código meio: %d, Bateria: %.2f, Espaço: %.2f\n", aux->codm, aux->bateria, aux->espaco);
                aux = aux->seguinte;
            }
        }
    }
    else
    {
        printf("Vértice não encontrado\n");
    }
}



/**
 * @brief 
 * 
 * @param g 
 * @param vertice 
 */
void listarClientesGrafo(Grafo g, char vertice[])
{
    Grafo verticeEncontrado = procurarVertice(g, vertice);
    
    if (verticeEncontrado != NULL)
    {
        printf("Vértice: %s\n", verticeEncontrado->vertice);
        Cliente* aux = verticeEncontrado->clientes;
        
        if (aux == NULL)
        {
            printf("Sem clientes\n");
        }
        else
        {
            while (aux != NULL)
            {
                printf("Código cliente: %d\n", aux->codc);
                aux = aux->seguinte;
            }
        }
    }
    else
    {
        printf("Vértice não encontrado\n");
    }
}


Grafo findNode(Grafo g, char geocode[]) 
{
    while (g != NULL) 
    {
        if (strcmp(g->vertice, geocode) == 0 && (g->visitado == 0 || g->visitado == 1)) 
        {
            return g;
        }
        g = g->seguinte;
    }
    return NULL;
}

void listVehiclesPerRadius(Grafo g, char geocode[], char type[], float radius) 
{
    if (g != NULL) {
        Grafo clientNode = findNode(g, geocode);
        if (clientNode == NULL) 
        {
            printf("Geocode doesn't exist in the graph!\n");
            return;
        }
        traverseEdgesDFS(clientNode, type, radius, 0.0, g);
    } else 
    {
        printf("Nodes list is empty!\n");
    }
}

void traverseEdgesDFS(Grafo node, char type[], float radius, float currentWeight, Grafo g) 
{
    if ((node->visitado == 1) || (node->visitado == 2) || currentWeight > radius) return;
    node->visitado = 1;

    Meio* meios = node->meios;
    while (meios != NULL) 
    {
        if (strcmp(meios->tipo, type) == 0 && currentWeight <= radius) 
        {
            node->visitado = 2;
            printf("Vehicle: %s -> %d -> %s -> %.2f -> %.2f -> %d;\n",
                   meios->geocodigo, meios->codm, meios->tipo,
                   meios->bateria, meios->preco, meios->estado);
        }
        meios = meios->seguinte;
    }

    Adjacente adjacentes = node->adjacentes;
    while (adjacentes != NULL) 
    {
        printf("\t-> %s\n", adjacentes->vertice);
        Grafo nextNode = findNode(g, adjacentes->vertice);
        if (nextNode != NULL) 
        {
            float newWeight = currentWeight + adjacentes->peso;
            traverseEdgesDFS(nextNode, type, radius, newWeight, g);
        }
        adjacentes = adjacentes->seguinte;
    }

    if (node->visitado == 1) node->visitado = 0;
}




/**
 * @brief 
 * 
 * @param g 
 */
void Visitados(Grafo g) 
{
    while (g != NULL) {
        g->visitado = 0;
        g = g->seguinte;
    }
}



/**
 * @brief 
 * 
 * @param grafo 
 */
void apresentarMeiosEstadoBateria(Grafo grafo) {
    Grafo atual = grafo;

    while (atual != NULL) {
        Meio* meioAtual = atual->meios;

        while (meioAtual != NULL) {
            if (meioAtual->estado == 0 && meioAtual->bateria < 50.0) {
                Grafo verticeAtual = grafo;
                int repetido = 0;

                while (verticeAtual != atual) {
                    if (strcmp(verticeAtual->vertice, atual->vertice) == 0) {
                        repetido = 1;
                        break;
                    }
                    verticeAtual = verticeAtual->seguinte;
                }

                if (!repetido) {
                    printf("Vertice: %s, Codigo do Meio: %d, bateria: %.2f, estado: %d\n", atual->vertice, meioAtual->codm, meioAtual->bateria, meioAtual->estado);
                }
            }

            meioAtual = meioAtual->seguinte;
        }

        atual = atual->seguinte;
    }
}



/**
 * @brief 
 * 
 */
void printPath(Grafo node, int caminhoAtual) {
    if (node == NULL)
        return;

    printf("Caminho %d: ", caminhoAtual);
    while (node != NULL) {
        printf("%s -> ", node->vertice);
        node = node->seguinte;
    }
    printf("\n");
}

/**
 * @brief 
 * 
 * @param g 
 * @param inicio 
 */
void findShortestPaths(Grafo g, char* inicio) {
    if (g == NULL) {
        printf("Graph is empty!\n");
        return;
    }
    Grafo currentNode = g;
    while (currentNode != NULL) {
        currentNode->distancia = INT_MAX;
        currentNode->visitado = 0;
        currentNode = currentNode->seguinte;
    }
    Grafo startNode = findNode(g, inicio);
    if (startNode == NULL) {
        printf("Start node not found!\n");
        return;
    }
    startNode->distancia = 0;    
    int caminhoAtual = 1; 
    IIItraverseNodesDFS(startNode, g, caminhoAtual);
    currentNode = g;
    while (currentNode != NULL) {
        if (currentNode->distancia < INT_MAX && currentNode->distancia > 0)
            printPath(currentNode, currentNode->caminho);
        currentNode = currentNode->seguinte;
    }
}

/**
 * @brief 
 * 
 * @param node 
 * @param g 
 * @param caminhoAtual 
 */
void IIItraverseNodesDFS(Grafo node, Grafo g, int caminhoAtual) 
{
    if (node == NULL || node->visitado == 1)
        return;

    node->visitado = 1;
    node->caminho = caminhoAtual;
    Meio* meioAtual = node->meios;
    while (meioAtual != NULL) {
        if (meioAtual->bateria < 50.0) {
            meioAtual->estado = 2; 
        }
        meioAtual = meioAtual->seguinte;
    }
    Adjacente adjacenteAtual = node->adjacentes;
    while (adjacenteAtual != NULL) {
        Grafo adjacentNode = findNode(g, adjacenteAtual->vertice);
        if (adjacentNode != NULL && adjacentNode->visitado == 0) {
            float weight = adjacenteAtual->peso;
            float newDistance = node->distancia + weight;
            if (adjacentNode->meios != NULL && adjacentNode->meios->bateria < 50.0) {
                if (newDistance < adjacentNode->distancia) {
                    adjacentNode->distancia = newDistance;
                }
            }

            IIItraverseNodesDFS(adjacentNode, g, caminhoAtual);
        }
        adjacenteAtual = adjacenteAtual->seguinte;
    }
}
