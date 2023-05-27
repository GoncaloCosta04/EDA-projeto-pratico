#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "grafo.h"


int criarVertice(Grafo *g, char novoId[]) {
    if ( g== NULL) {
        return 0; // Verifica se o ponteiro g é nulo
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





int existeVertice(Grafo g, char vertice[]) {
    while (g != NULL) {
        if (strcmp(g->vertice, vertice) == 0)
            return 1;
        g = g->seguinte;
    }
    return 0;
}




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
 



void saveMeios(Grafo g) {
    FILE* fp;
    fp = fopen("meios.txt", "w");

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



void saveMeiosbin(Grafo g) {
    FILE* fp;
    fp = fopen("meios.bin", "wb");

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

void readMeios(Grafo* g) {
    FILE* fp = fopen("meios.txt", "r");

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





int inserirClienteNoGrafo(Grafo g, char geocodigo[], int codigoc, char nome[], int NIF, float saldo, char morada[]) {
    while (g != NULL && strcmp(g->vertice, geocodigo) != 0) {
        g = g->seguinte;
    }
    
    if (g == NULL) {
        return 0; // Vértice não encontrado no grafo
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
        return 1; // Inserção bem-sucedida
    }
}




void saveClientes(Grafo g) {
    FILE* fp;
    fp = fopen("clientes.txt", "w");

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


void saveClientesbin(Grafo g) {
    FILE* fp;
    fp = fopen("clientes.bin", "wb");

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


void readClientes(Grafo* g) {
    FILE* fp = fopen("clientes.txt", "r");

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




Grafo procurarVertice(Grafo g, const char* geocodigo) 
{
    while (g != NULL) {
        if (strcmp(g->vertice, geocodigo) == 0) {
            return g;
        }
        g = g->seguinte;
    }
    return NULL; // Vértice não encontrado
}





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


int clienteExiste(Grafo g, char geoccode[]) {
    while (g != NULL) {
        Cliente* aux = g->clientes;
        while (aux != NULL) {
            if (strcmp(aux->geocodigoc, geoccode) == 0) {
                return 1; // Cliente encontrado
            }
            aux = aux->seguinte;
        }
        g = g->seguinte;
    }
    
    return 0; // Cliente não encontrado
}


Grafo findNode(Grafo g, char geocode[]) 
{
    while (g != NULL) 
    {
        if (strcmp(g->vertice, geocode) == 0 && g->visitado == 0) 
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
    if ((node->visitado == 1) || (node->visitado == 2) || currentWeight>radius) return;
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
}




void listarMeiosBaixaBateria(Grafo g) 
{
    int encontrouMeios = 0; // Variável para verificar se há meios com menos de 50% de bateria
    
    while (g != NULL) {
        printf("Vértice: %s\n", g->vertice);
        
        Meio* meio = g->meios;
        while (meio != NULL) {
            if (meio->bateria < 50.0) 
            {
                encontrouMeios = 1;
                printf("Meio com baixa bateria: Código: %d, Tipo: %s, Bateria: %.2f\n",
                       meio->codm, meio->tipo, meio->bateria);
            }
            meio = meio->seguinte;
        }
        
        g = g->seguinte;
    }
    
    if (!encontrouMeios) {
        printf("Não foram encontrados meios com menos de 50%% de bateria em nenhum vértice.\n");
    }
}


void Visitados(Grafo g) 
{
    while (g != NULL) {
        g->visitado = 0;
        g = g->seguinte;
    }
}


/*void printPathAndWeight(Grafo node, float weight) {
    if (node != NULL) {
        printPathAndWeight(node->seguinte, weight + node->distancia);
        printf("%s -> ", node->vertice);
    }
}

void IItraverseEdgesDFS(Grafo node, float batteryThreshold, float currentWeight, Grafo g, int searchType, char path[], float pathWeight) {
    if (node->visitado == 1) return;
    node->visitado = 1;

    if (searchType == 1) {
        Meio* meios = node->meios;
        while (meios != NULL) {
            if (meios->bateria < batteryThreshold)
             {
                printf("Path: ");
                printPathAndWeight(node, pathWeight);
                printf("%s (Battery: %.2f)\n", meios->geocodigo, meios->bateria);
            }
            meios = meios->seguinte;
        }
    }

    Adjacente adjacentes = node->adjacentes;
    while (adjacentes != NULL) {
        Grafo nextNode = findNode(g, adjacentes->vertice);
        if (nextNode != NULL) {
            float newWeight = currentWeight + adjacentes->peso;
            char newPath[500];
            sprintf(newPath, "%s -> %s", path, nextNode->vertice);
            IItraverseEdgesDFS(nextNode, batteryThreshold, newWeight, g, searchType, newPath, pathWeight + adjacentes->peso);
        }
        adjacentes = adjacentes->seguinte;
    }
}

void findPathsLowBattery(Grafo g, float batteryThreshold) 
{
    Grafo currentNode = g;
    while (currentNode != NULL) {
        if (currentNode->visitado == 0 && currentNode->meios != NULL) {
            char path[500];
            sprintf(path, "%s", currentNode->vertice);
            IItraverseEdgesDFS(currentNode, batteryThreshold, 0.0, g, 1, path, 0.0);
        }
        currentNode = currentNode->seguinte;
    }
}

void listAllPathsLowBattery(Grafo g, float batteryThreshold) 
{
    Grafo currentNode = g;
    while (currentNode != NULL) {
        IItraverseEdgesDFS(currentNode, batteryThreshold, 0.0, g, 1, "", 0.0);
        resetVisitedFlag(g);
        currentNode = currentNode->seguinte;
    }
}

void resetVisitedFlag(Grafo g) 
{
    Grafo currentNode = g;
    while (currentNode != NULL) {
        currentNode->visitado = 0;
        currentNode = currentNode->seguinte;
    }
}*/

