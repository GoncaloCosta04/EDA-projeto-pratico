#include <stdio.h>
#include <stdlib.h>
#include "meios.h"
#include "clientes.h"
#include "gestores.h"



     int alugarMeio(Cliente* c, Meio* m) 
{
    int codCliente, codMeio;
    printf("Introduza o seu  código de cliente: ");
    scanf("%d", &codCliente);
    printf("Introduza o código do meio que pretende alugar: ");
    scanf("%d", &codMeio);


    Cliente* clienteAtual = c;
    while (clienteAtual != NULL) {
        if (clienteAtual->cod_c == codCliente) {
            break;
        }
        clienteAtual = clienteAtual->seguinte;
    }


    Meio* meioAtual = m;
    while (meioAtual != NULL) {
        if (meioAtual->cod_m == codMeio) {
            break;
        }
        meioAtual = meioAtual->seguinte;
    }


    if (clienteAtual == NULL || meioAtual == NULL) {
        printf("Erro: Código de cliente ou meio inválido!\n");
        return 0;
    }


    if (meioAtual->estado == 1) {
        printf("Erro: O meio de código %d já foi alugado!\n", meioAtual->cod_m);
        return 0;
    }


    if (clienteAtual->saldo < meioAtual->preco) 
    {
        printf("Erro: Saldo insuficiente!\n");
        return 0;
    }


    meioAtual->estado = 1;
    clienteAtual->saldo -= meioAtual->preco;
    printf("Meio de código %d alugado com sucesso para %s!\n", meioAtual->cod_m, clienteAtual->nome);
     FILE *fp;
    fp = fopen("alugar.txt", "a");
    fprintf(fp, "Aluguer realizado com sucesso!\n");
    fprintf(fp, "Cliente: %s, Código: %d, NIF: %d, Saldo: %.2f\n", clienteAtual->nome, clienteAtual->cod_c, clienteAtual->NIF, clienteAtual->saldo);
    fprintf(fp, "Meio: %s, Código: %d, Tipo: %s, Bateria: %.2f, Autonomia: %.2f, Preço: %.2f, Geocódigo: %s\n", meioAtual->tipo, meioAtual->cod_m, meioAtual->tipo, meioAtual->bateria, meioAtual->autonomia, meioAtual->preco, meioAtual->geocodigo);
    fprintf(fp, "----------------------------\n");
    fclose(fp);
    return 1;

}
 

void registoaluger() 
{
    FILE *fp;
    char linha[100];

    fp = fopen("alugar.txt", "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Conteúdo do arquivo alugar.txt:\n");

    while (fgets(linha, 100, fp) != NULL) {
        printf("%s", linha);
    }

    fclose(fp);
}

int main() {
 


Meio* meios = NULL; // Lista ligada vazia 
int op;
int cod_m;
char tipo[100];
float bateria;
float autonomia;
float preco;
char geocodigo[50];
int estado;

Cliente* clientes = NULL; //Lista ligada vazia
int cod_c; 
char nome[100];
int NIF; 
float saldo; 
char morada[250]; 

Gestor* gestores = NULL; //Lista ligada vazia
int cod_g;
int password;
int contacto;
char username[100];

float valorapagar;
int codm;
int numkms;
float valor;
int cod;

    int opcao;
    int opcaocliente;
    int opcaogestor;
    do {
        printf("===== MENU PRINCIPAL =====\n");
        printf("1 - Registar Cliente\n");
        printf("2 - Menu Cliente\n");
        printf("3 - Registar Gestor\n");
        printf("4 - Menu Gestor\n");
        printf("5 - Carregar Dados\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        system("cls");
        switch (opcao) {
            case 1:
       printf("Codigo?\n");
	   scanf("%d",&cod_c);
	   scanf("%*c"); 
	   printf("Nome\n");
	   scanf("%[^\n]s",nome);
	  printf("NIF?\n");
	   scanf("%d",&NIF);
	   printf("Saldo\n");
	   scanf("%f",&saldo);
	   scanf("%*c"); 
       printf("Morada\n");
       scanf("%[^\n]s",morada);
	   clientes = inserirCliente(clientes,  cod_c,  nome,  NIF,  saldo,  morada);
                break;
            case 2:
                do {
                    printf("===== MENU CLIENTE =====\n");
                    printf("1 - Alterar seus dados\n");
                    printf("2 - Ver meios\n");
                    printf("3 - Ver meios por autonomia\n");
                    printf("4 - Requisitar aluger\n");
                    printf("5 - Procurar meio por geocodigo\n");
                    printf("6 - Ajuda de Gestores\n");
                    printf("7 - Apagar conta\n");
                    printf("0 - Sair\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaocliente);
                    system("cls");
                    switch (opcaocliente) {
                        case 1:
                            {
int cod_c;
int nif;
char nova_morada[250];
printf("Introduza o codigo do cliente que deseja alterar: ");
scanf("%d", &cod_c);
printf("Introduza o NIF do cliente que deseja alterar: ");
scanf("%d", &nif);
printf("Introduza a nova morada\n");
scanf("%s",nova_morada);
int sucesso = alterarcliente(clientes,  cod_c,  nif, nova_morada);
  if (sucesso)
    {
        printf("Dados do cliente alterados com sucesso.\n");
    }
    else
    {
        printf("Nao foi possivel alterar os dados do cliente.\n");
    }
}
                            break;
                        case 2:
                            listarMeios(meios);
                            break;
                        case 3:
                            listarMeiosPorAutonomia(meios); 
                            break;
                        case 4:
                            meiodisponivel(meios); 
                            alugarMeio(clientes, meios);
                            break;
                        case 5:
                           procurarMeio(meios); 
                            break;
                        case 6:
                            listarGestor(gestores);
                            break;
                        case 7:
                            printf("Codigo do cliente a remover?\n");
                            scanf("%d",&cod);
                            clientes = removerCliente(clientes, cod);
                            break;
                        case 0:
                            printf("Voltando ao menu principal...\n");
                            break;
                        default:
                            printf("Opcao invalida! Tente novamente.\n");
                    }
                } while (opcaocliente != 0);
                break;
            case 3:
  printf("Codigo?\n");
  scanf("%d",&cod_g);
  printf("Password\n");
  scanf("%d",&password);
  printf("Contacto\n");
  scanf("%d",&contacto);
  scanf("%*c");
  printf("Username\n");
 scanf("%[^\n]s",username);
 gestores = inserirGestor(gestores, cod_g, password, contacto, username); 
                break;
            case 4:
                do {
                    printf("===== MENU GESTOR =====\n");
                    printf("1 - Listar meios\n");
                    printf("2 - Listar clientes\n");
                    printf("3 - Listar Gestores\n");
                    printf("4 - Remover Clientes\n");
                    printf("5 - Remover Meio\n");
                    printf("6 - Apagar conta gestor\n");
                    printf("7 - Alterar dados de meio\n");
                    printf("8 - Alterar os seus dados de gestor\n");
                    printf("9 - Adicionar meio\n");
                    printf("10 - Adicionar cliente\n");
                    printf("11 - Guardar informação\n");
                    printf("12 - Registo de aluguel\n");
                    printf("0 - Sair\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaogestor);
                    system("cls");
                     switch (opcaogestor) 
                     {
                        case 1:
                            listarMeios(meios);
                        break;
                            
                        case 2:
                            listarClientes(clientes);
                        break;

                        case 3:
                            listarGestor(gestores);
                        break;

                        case 4:
                            printf("Codigo do cliente a remover?\n");
                            scanf("%d",&cod);
                            clientes = removerCliente(clientes, cod);
                        break;

                        case 5:
                            printf("Codigo do meio de mobilidade a remover?\n");
                            scanf("%d",&cod);
                            meios = removerMeio( meios,  cod);
                        break;

                        case 6:
                            printf("Codigo do gestor a remover?\n");
                            scanf("%d",&cod);
                            gestores =  removerGestor(gestores,  cod);
                        break;

                        case 7:
                            {
                                int cod;
                                char tipo[100];
                                float bateria, autonomia, preco;
                                char geocodigo[50];
                                int estado;
                                
                                printf("Introduza o codigo do meio que deseja alterar: ");
                                scanf("%d", &cod);
                                
                                printf("Introduza os novos dados do meio:\n");
                                printf("Tipo: ");
                                scanf("%s", tipo);
                                printf("Bateria: ");
                                scanf("%f", &bateria);
                                printf("Autonomia: ");
                                scanf("%f", &autonomia);
                                printf("Preco: ");
                                scanf("%f", &preco);
                                printf("Geocodigo: ");
                                scanf("%s", geocodigo);
                                printf("Estado: ");
                                scanf("%d", &estado);
                                
                                int sucesso = alterarmeio(meios, cod, tipo, bateria, autonomia, preco, geocodigo, estado);
                                if (sucesso)
                                {
                                    printf("Dados do meio alterados com sucesso.\n");
                                }
                                else
                                {
                                    printf("Nao foi possivel alterar os dados do meio.\n");
                                }
                            }
                        break;

                        case 8:
                                {
                                int cod;
                                int pass;
                                char novousername[100];
                                int novapassword;
                                printf("Digite o codigo do gestor que deseja alterar: ");
                                scanf("%d", &cod);
                                printf("Digite o NIF do gestor que deseja alterar: ");
                                scanf("%d", &pass);
                                printf("Digite os novos dados do meio:\n");
                                printf("Username\n");
                                scanf("%s",novousername);
                                printf("Password\n");
                                scanf("%d",&novapassword);
                                int sucesso = alterargestor(gestores,  cod,  pass, novousername, novapassword);
                                if (sucesso)
                                    {
                                        printf("Dados do cliente alterados com sucesso.\n");
                                    }
                                    else
                                    {
                                        printf("Nao foi possivel alterar os dados do cliente.\n");
                                    }
                                }
                        break;

                        case 9:
                    printf("Codigo?\n");
                    scanf("%d",&cod_m);
                    scanf("%*c"); 
                    printf("Tipo\n");
                    scanf("%[^\n]s",tipo);
                    printf("Nivel da bateria?\n");
                    scanf("%f",&bateria);
                    printf("Autonomia\n");
                    scanf("%f",&autonomia);
                    printf("Preco\n");
                    scanf("%f",&preco);
                    scanf("%*c");
                    printf("Geocodigo\n");
                    scanf("%[^\n]s",geocodigo);
                    printf("%s\n", geocodigo);
                    printf("Estado(0-livre/1-ocupado)?\n");
                    scanf("%d",&estado);
                    system("cls");
                        meios = inserirMeio(meios,cod_m,tipo,bateria,autonomia, preco, geocodigo, estado);
                        break;

                        case 10:
                    printf("Codigo?\n");
	                scanf("%d",&cod_c);
                    scanf("%*c"); 
                    printf("Nome\n");
                    scanf("%[^\n]s",nome);
                    printf("NIF?\n");
                    scanf("%d",&NIF);
                    printf("Saldo\n");
                    scanf("%f",&saldo);
                    scanf("%*c"); 
                    printf("Morada\n");
                    scanf("%[^\n]s",morada);
                    clientes = inserirCliente(clientes,  cod_c,  nome,  NIF,  saldo,  morada);
                        break;

                        case 11:
                        guardarMeios(meios);
                        guardarCliente(clientes);
                        guardarGestor(gestores);
                        break;
                          
                        case 12:
                        registoaluger();
                        break;
                        case 0:
                        printf("Voltando ao menu principal...\n");
                        break;
                     }
                }while (opcaogestor != 0);
                break;
                case 5:
                printf("A carregar dados...\n");
            gestores = lerGestor(gestores);
            meios = lerMeios(meios); 
            clientes = lerCliente(clientes);   
                break;

                case 0:
                printf("Obrigado pela visita\n");
                return 0;
               default:
                break;
        }
    }while (opcao!=0);
return 0; 
}
