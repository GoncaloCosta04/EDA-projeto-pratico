#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meios.h"
#include "clientes.h"


int guardarMeios(Meio* inicio)
{FILE* fp;
 fp = fopen("meios.txt","w");
 if (fp!=NULL)
 {
 Meio* aux= inicio;
 while (aux != NULL)
 {
  fprintf(fp,"%d;%s;%f;%f;%f;%s;%d\n", aux->cod_m,aux->tipo, aux->bateria, 
	                      aux->autonomia, aux->preco, aux->geocodigo, aux->estado);
  aux = aux->seguinte;
 }
 fclose(fp);
 return(1);
 }
 else return(0);
}

int guardarMeiosembinario(Meio* inicio)
{
    FILE* fp;
    fp = fopen("meios.bin", "wb"); 
    if (fp != NULL)
    {
        Meio* aux = inicio;
        while (aux != NULL)
        {
            fwrite(aux, sizeof(Meio), 1, fp);
            aux = aux->seguinte;
        }
        fclose(fp);
        return (1);
    }
    else 
        return (0);
}

Meio* lerMeios()
{
    FILE* fp;
    int cod_m, estado;
    float bateria, autonomia, preco;
    char tipo[100], geocodigo[50];
    Meio* aux = NULL;

    fp = fopen("meios.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d;%99[^;\n];%f;%f;%f;%49[^;\n];%d\n", &cod_m, tipo, &bateria, &autonomia, &preco, geocodigo, &estado) == 7) {
            aux = inserirMeio(aux, cod_m, tipo, bateria, autonomia, preco, geocodigo, estado);
        }
        fclose(fp);
    } else {
        printf("Erro ao abrir o arquivo de meios de transporte.\n");
    }

    return aux;
}



int existeMeio(Meio* inicio, int cod)
{while(inicio!=NULL)
  {if (inicio->cod_m == cod) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}

Meio* inserirMeio(Meio* inicio, int cod_m, char tipo[], float bateria, float autonomia, float preco, char geocodigo[], int estado)
{
    if (!existeMeio(inicio, cod_m))
    {
        Meio* novo = malloc(sizeof(struct meio));
        if (novo != NULL)
        {
            novo->cod_m = cod_m;
            strcpy(novo->tipo, tipo);
            novo->bateria = bateria;
            novo->autonomia = autonomia;
            novo->preco = preco;
            strcpy(novo->geocodigo, geocodigo);
            novo->estado = estado;
            novo->seguinte = inicio;
            inicio = novo; 
        }
    }
    return inicio; 
}




void listarMeios(Meio * inicio)
{while (inicio != NULL)
 {printf("%d;%s;%.2f;%.2f;%.2f;%s;%d\n\n",inicio->cod_m,inicio->tipo, 
		             inicio->bateria, inicio->autonomia, inicio->preco, inicio->geocodigo, inicio->estado);
  inicio = inicio->seguinte;
 }
}




Meio* removerMeio(Meio* inicio, int cod) 
{
 Meio *anterior=inicio, *atual=inicio, *aux;

 if (atual==NULL) return(NULL);
 else if (atual->cod_m == cod)
 {aux = atual->seguinte;
  free(atual);
  return(aux);
 }
 else
 {while ((atual!=NULL)&&(atual->cod_m!=cod)) 
  {anterior = atual;
   atual = atual->seguinte;
  }
  if (atual==NULL) return(inicio);
  else
  {anterior->seguinte = atual->seguinte;
   free(atual);
   return(inicio);
  }
 }
}

void listarMeiosPorAutonomia(Meio* inicio) 
{
    Meio *p, *q;
    float temp;
    int flag;

    if (inicio == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    do {
        flag = 0;
        p = inicio;

        while (p->seguinte != NULL) 
        {

            q = p->seguinte;

            if (p->autonomia < q->autonomia) {
                
                temp = p->autonomia;
                p->autonomia = q->autonomia;
                q->autonomia = temp;
                flag = 1;
            }

            p = p->seguinte;
        }
    } while (flag);
   
    printf("Lista de meios por ordem decrescente de autonomia:\n");
    while (inicio != NULL) {
        printf("%d;%s;%.2f;%.2f;%.2f;%s;%d\n", inicio->cod_m, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->preco, inicio->geocodigo, inicio->estado);
        inicio = inicio->seguinte;
    }
}


void procurarMeio(Meio* inicio) 
{
    char geocod[50];
    int encontrado = 0;
    printf("Insira o geocodigo: ");
    scanf("%s", geocod);


    while (inicio != NULL) 
    {
        if (strcmp(inicio->geocodigo, geocod) == 0) 
        {
            printf("Meio encontrado:\n");
            printf("Codigo: %d\n", inicio->cod_m);
            printf("Estado: %d\n", inicio->estado);
            encontrado = 1;
        }
        inicio = inicio->seguinte;
    }

    if (!encontrado) 
    {
    printf("Nao foi encontrado nenhum meio com o geocodigo inserido.\n");
    }
}

int alterarmeio(Meio* inicio, int cod, char tipo[100], float bateria, float autonomia, float preco, char geocodigo[50], int estado)
{
    Meio* atual = inicio;
    
    while (atual != NULL)
    {
        if (atual->cod_m == cod)
        {
            
            strcpy(atual->tipo, tipo);
            atual->bateria = bateria;
            atual->autonomia = autonomia;
            atual->preco = preco;
            strcpy(atual->geocodigo, geocodigo);
            atual->estado = estado;
            return 1;
        }
        atual = atual->seguinte;
    }
    
    
    return 0;
}



void meiodisponivel(Meio *inicio) 
{
    Meio *atual = inicio;
    int encontrou_disponivel = 0;
    printf("Meios de transporte disponíveis:\n");
    while (atual != NULL) {
        if (atual->estado == 0) {
            printf("Código: %d | Tipo: %s | Preço por km: %.2f | Bateria: %.2f | Autonomia: %.2f\n", 
                    atual->cod_m, atual->tipo, atual->preco, atual->bateria, atual->autonomia);
                    }
        atual = atual->seguinte;
    }

}


