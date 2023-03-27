#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meios.h"


/**
 * @brief 
 * 
 * @param inicio 
 * @return int 
 */
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


/**
 * @brief 
 * 
 * @param inicio 
 * @return int 
 */
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


/**
 * @brief 
 * 
 * @param inicio 
 * @param cod 
 * @return int 
 */
int existeMeio(Meio* inicio, int cod)
{while(inicio!=NULL)
  {if (inicio->cod_m == cod) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}


/**
 * @brief 
 * 
 * @param inicio 
 * @param cod_m 
 * @param tipo 
 * @param bateria 
 * @param autonomia 
 * @param preco 
 * @param geocodigo 
 * @param estado 
 * @return Meio* 
 */
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


/**
 * @brief 
 * 
 * @return Meio* 
 */
Meio* lerMeios()
{
    FILE* fp;
    int cod_m, estado;
    float bateria, autonomia, preco;
    char tipo[100], geocodigo[50];
    Meio* aux = NULL;

    fp = fopen("meios.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d;%[^;\n];%f;%f;%f;%[^;\n];%d\n", &cod_m, tipo, &bateria, &autonomia, &preco, geocodigo, &estado) == 7) {
            aux = inserirMeio(aux, cod_m, tipo, bateria, autonomia, preco, geocodigo, estado);
        }
        fclose(fp);
    } 

    return (aux);
}


/**
 * @brief 
 * 
 * @param inicio 
 */
void listarMeios(Meio * inicio)
{while (inicio != NULL)
 {printf("%d;%s;%.2f;%.2f;%.2f;%s;%d\n\n",inicio->cod_m,inicio->tipo, 
		             inicio->bateria, inicio->autonomia, inicio->preco, inicio->geocodigo, inicio->estado);
  inicio = inicio->seguinte;
 }
}



/**
 * @brief 
 * 
 * @param inicio 
 * @param cod 
 * @return Meio* 
 */
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

/**
 * @brief 
 * 
 * @param inicio 
 */
void listarMeiosPorAutonomia(Meio* inicio) 
{
    Meio *p, *q;
    float i;
    int troca;

    if (inicio == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    do {
        troca = 0;
        p = inicio;

        while (p->seguinte != NULL) 
        {

            q = p->seguinte;

            if (p->autonomia < q->autonomia) 
            {
               i = p->autonomia;
                p->autonomia = q->autonomia;
                q->autonomia = i;
                troca = 1;
            }

            p = p->seguinte;
        }
    } while (troca);
   
    printf("Lista de meios por ordem decrescente de autonomia:\n");
    while (inicio != NULL) {
        printf("%d;%s;%.2f;%.2f;%.2f;%s;%d\n", inicio->cod_m, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->preco, inicio->geocodigo, inicio->estado);
        inicio = inicio->seguinte;
    }
}

/**
 * @brief 
 * 
 * @param inicio 
 */
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
/**
 * @brief 
 * 
 * @param inicio 
 * @param cod 
 * @param tipo 
 * @param bateria 
 * @param autonomia 
 * @param preco 
 * @param geocodigo 
 * @param estado 
 * @return int 
 */
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


/**
 * @brief 
 * 
 * @param inicio 
 */
void meiodisponivel(Meio *inicio) 
{
    Meio *atual = inicio;
    int encontrou_disponivel = 0;
    printf("Meios de transporte disponiveis:\n");
    while (atual != NULL) {
        if (atual->estado == 0) {
            printf("Codigo: %d | Tipo: %s | Preco : %.2f | Bateria: %.2f | Autonomia: %.2f | Geocodigo: %s\n", 
                    atual->cod_m, atual->tipo, atual->preco, atual->bateria, atual->autonomia, atual->geocodigo);
                    }
        atual = atual->seguinte;
    }

    }


