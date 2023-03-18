#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "clientes.h"


int guardarCliente(Cliente* inicio)
{FILE* fp;
 fp = fopen("clientes.txt","w");
 if (fp!=NULL)
 {
 Cliente* aux= inicio;
 while (aux != NULL)
 {
  fprintf(fp,"%d;%s;%d;%f;%s\n", aux->cod_c,aux->nome, aux->NIF, 
	                      aux->saldo, aux->morada);
  aux = aux->seguinte;
 }
 fclose(fp);
 return(1);
 }
 else return(0);
}

int guardarClientebinario(Cliente* inicio)
{
    FILE* fp;
    fp = fopen("clientes.bin", "wb"); 
    if (fp != NULL)
    {
        Cliente* aux = inicio;
        while (aux != NULL)
        {
            fwrite(aux, sizeof(Cliente), 1, fp); 
            aux = aux->seguinte;
        }
        fclose(fp);
        return (1);
    }
    else 
        return (0);
}

Cliente* lerCliente()
{FILE* fp;
 int cod_c; 
char nome[100];
int NIF; 
float saldo; 
char morada[1000]; 
 Cliente* aux=NULL;
 fp = fopen("clientes.txt","r");
 if (fp!=NULL)
 {while (!feof(fp))
  { fscanf(fp,"%d;%[^\n]s;%d;%f;%[^\n]s\n", &cod_c, nome, &NIF, &saldo, morada);
    aux = inserirCliente(aux, cod_c, nome, NIF, saldo, morada);
  }
 fclose(fp);
 }
 return(aux);
}
int existeCliente(Cliente* inicio, int cod)
{while(inicio!=NULL)
  {if (inicio->cod_c == cod) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}

Cliente* inserirCliente(Cliente* inicio, int cod_c, char nome[], int NIF, float saldo, char morada[])
{
    if (!existeCliente(inicio, cod_c))
    {
        Cliente* novo = malloc(sizeof(struct cliente));
        if (novo != NULL)
        {
            novo->cod_c = cod_c;
            strcpy(novo->nome, nome);
            novo->NIF = NIF;
            novo->saldo = saldo;
            strcpy(novo->morada, morada);
            novo->seguinte = inicio;
            inicio = novo; 
        }
    }
    return inicio; 
}

void listarClientes(Cliente * inicio)
{while (inicio != NULL)
 {printf("%d;%s;%d;%.2f;%s\n\n",inicio->cod_c,inicio->nome, 
		             inicio->NIF, inicio->saldo, inicio->morada);
  inicio = inicio->seguinte;
 }
}



Cliente* removerCliente(Cliente* inicio, int cod) 
{
 Cliente *anterior=inicio, *atual=inicio, *aux;

 if (atual==NULL) return(NULL);
 else if (atual->cod_c == cod)
 {aux = atual->seguinte;
  free(atual);
  return(aux);
 }
 else
 {while ((atual!=NULL)&&(atual->cod_c!=cod)) 
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


int alterarcliente(Cliente *inicio, int cod_c, int nif, char nova_morada[250]) 
{
    Cliente * atual = inicio;
    while (atual != NULL) 
    {
        if (atual->cod_c == cod_c && atual->NIF == nif) {
            
            strcpy(atual->morada, nova_morada);
            
            return 1;
        }
        atual = atual->seguinte;
    }
    
    return 0;
}


Cliente* carregar_saldo(Cliente *inicio, int cod, float valor) 
{
    Cliente *cliente = inicio;
    while (cliente != NULL) 
    {
        if (cliente->cod_c == cod ) 
        {
            cliente->saldo += valor;
            printf("Saldo atualizado com sucesso! Novo saldo: %.2f\n", cliente->saldo);
            return cliente;
        }
        cliente = cliente->seguinte;
    }
    printf("Cliente não encontrado.\n");
    return NULL;
}