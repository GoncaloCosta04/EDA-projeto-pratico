 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "grafo.h"











int alugarMeio(Cliente* c, Meio* m) 
{
    int codCliente, codMeio;
    printf("Introduza o seu  codigo de cliente: ");
    scanf("%d", &codCliente);
    printf("Introduza o codigo do meio que pretende alugar: ");
    scanf("%d", &codMeio);


    Cliente* clienteAtual = c;
    while (clienteAtual != NULL) 
    {
        if (clienteAtual->codc == codCliente) 
        {
            break;
        }
        clienteAtual = clienteAtual->seguinte;
    }


    Meio* meioAtual = m;
    while (meioAtual != NULL) 
    {
        if (meioAtual->codm == codMeio) 
        {
            break;
        }
        meioAtual = meioAtual->seguinte;
    }


    if (clienteAtual == NULL || meioAtual == NULL) 
    {
        printf("Erro: Codigo de cliente ou meio invalido!\n");
        return 0;
    }


    if (meioAtual->estado == 1) 
    {
        printf("Meio ja alugado!\n");
        return 0;
    }


    if (clienteAtual->saldo < meioAtual->preco) 
    {
        printf("Saldo insuficiente!\n");
        return 0;
    }


    meioAtual->estado = 1;
    clienteAtual->saldo -= meioAtual->preco;
    printf("Meio de código %d alugado com sucesso para %s!\n", meioAtual->codm, clienteAtual->nome);
     FILE *fp;
    fp = fopen("alugar.txt", "a");
    fprintf(fp, "Cliente: %s, Codigo: %d, NIF: %d\n", clienteAtual->nome, clienteAtual->codc, clienteAtual->NIF);
    fprintf(fp, "Meio: %s, Codigo: %d, Tipo: %s, Bateria: %.2f, Autonomia: %.2f, Preço: %.2f, Geocodigo: %s\n", meioAtual->tipo, meioAtual->codm, meioAtual->tipo, meioAtual->bateria, meioAtual->autonomia, meioAtual->preco, meioAtual->geocodigo);
    fprintf(fp, "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(fp);
    return 1;

}
 

void registoaluger() 
{
    FILE *fp;
    char linha[100];

    fp = fopen("alugar.txt", "r");

    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    printf("Sucesso\n");

    while (fgets(linha, 100, fp) != NULL) {
        printf("%s", linha);
    }

    fclose(fp);
}

int main()
{
    Meio* meios = NULL; // Lista ligada vazia
    //int op;
    int codm;
    char tipo[100];
    float bateria;
    float autonomia;
    float preco;
    char geocodigo[250];
    int estado;
    int espaco;

    Cliente* clientes = NULL; //Lista ligada vazia
    int codc;
    char nome[100];
    int NIF;
    float saldo;
    char morada[250];
    char geocodigoc[250];

    Gestor* gestores = NULL;
    int codg;
    int password;
    int contacto;
    char username[100];
    float valor;
    int cod;

   Grafo grafo = NULL;


    int opcao;
    int opcaocliente;
    int opcaogestor;
    int opcaografo;
    do
    {
        printf("===== MENU PRINCIPAL =====\n");
        printf("1 - Registar Cliente\n");
        printf("2 - Menu Cliente\n");
        printf("3 - Registar Gestor\n");
        printf("4 - Menu Gestor\n");
        printf("5 - Menu Grafo\n");
        printf("6 - Carregar Dados\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        system("cls");
        switch (opcao)
        {
            case 1:
                printf("Codigo?\n");
                scanf("%d", &codc);
                scanf("%*c");
                printf("Nome\n");
                scanf(" %[^\n]s", nome);
                printf("NIF?\n");
                scanf("%d", &NIF);
                printf("Saldo\n");
                scanf("%f", &saldo);
                scanf("%*c");
                printf("Morada\n");
                scanf(" %[^\n]s", morada);
                scanf("%*c");
                printf("Geocodigo\n");
                scanf("%[^\n]s", geocodigoc);
                clientes = inserirCliente(clientes, codc, nome, NIF, saldo, morada, geocodigoc);
                break;
            case 2:
                do
                {
                    printf("===== MENU CLIENTE =====\n");
                    printf("1 - Alterar seus dados\n");
                    printf("2 - Ver meios\n");
                    printf("3 - Ver meios por autonomia\n");
                    printf("4 - Recarregar saldo\n");
                    printf("5 - Requisitar aluguel\n");
                    printf("6 - Procurar meio por geocodigo\n");
                    printf("7 - Ajuda de Gestores\n");
                    printf("8 - Apagar conta\n");
                    printf("0 - Sair\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaocliente);
                    system("cls");
                    switch (opcaocliente)
                    {
                            case 1:
            {
int codc;
int nif;
char nova_morada[250];
printf("Introduza o codigo de cliente: ");
scanf("%d", &codc);
printf("Introduza o NIF: ");
scanf("%d", &nif);
printf("Introduza a nova morada\n");
scanf("%s",nova_morada);
int sucesso = alterarcliente(clientes,  codc,  nif, nova_morada);
  if (sucesso)
    {
        printf("Dados do alterados com sucesso.\n");
    }
    else
    {
        printf("Nao foi possivel alterar os dados.\n");
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
            printf("Introduza o codigo\n");
            scanf("%d", &cod);
            printf("Introduza o valor\n");
            scanf("%f",&valor);
            clientes = carregarsaldo(clientes, cod, valor);
            break;
                         case 5:
            meiodisponivel(meios); 
            alugarMeio(clientes, meios);
            break;
                         case 6:
            procurarMeio(meios); 
            break;
            case 7:
            contactarGestor(gestores);
            break;
                       case 8:
            printf("Codigo do cliente a remover?\n");
            scanf("%d",&cod);
            clientes = removerCliente(clientes, cod);
            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao Invalida!\n");
                            break;
                    }
                } while (opcaocliente != 0);
                break;
                    case 3:
  printf("Codigo?\n");
  scanf("%d",&codg);
  printf("Password\n");
  scanf("%d",&password);
  printf("Contacto\n");
  scanf("%d",&contacto);
  scanf("%*c");
  printf("Username\n");
 scanf("%[^\n]s",username);
 gestores = inserirGestor(gestores, codg, password, contacto, username); 
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
                    printf("11 - Guardar informacao\n");
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
                                int espaco;
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
                                printf("Estado: ");
                                scanf("%d", &estado);
                                printf("Espaco: ");
                                scanf("%d", &espaco);
                                
                                int sucesso = alterarmeio(meios, cod, tipo, bateria, autonomia, preco, geocodigo, estado, espaco);
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
                                printf("Introduza o codigo de gestor: ");
                                scanf("%d", &cod);
                                printf("Introduza a password : ");
                                scanf("%d", &pass);
                                printf("Digite os novos dados do meio:\n");
                                printf("Username\n");
                                scanf("%s",novousername);
                                printf("Password\n");
                                scanf("%d",&novapassword);
                                int sucesso = alterargestor(gestores,  cod,  pass, novousername, novapassword);
                                if (sucesso)
                                    {
                                        printf("Dados  alterados com sucesso.\n");
                                    }
                                    else
                                    {
                                        printf("Nao foi possivel alterar os dados.\n");
                                    }
                                }
                        break;

                        case 9:
                    printf("Codigo?\n");
                    scanf("%d",&codm);
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
                    printf("Espaco?\n");
                    scanf("%d",&espaco);
                    system("cls");
                        meios = inserirMeio(meios,codm,tipo,bateria,autonomia, preco, geocodigo, estado, espaco);
                        break;

                        case 10:
                    printf("Codigo?\n");
	                scanf("%d",&codc);
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
                    printf("Geocodigo\n");
                    scanf("%[^\n]s",geocodigoc);
                    printf("%s\n", geocodigoc);
                    clientes = inserirCliente(clientes,  codc,  nome,  NIF,  saldo,  morada, geocodigoc);
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
                        printf("Regresso ao menu principal...\n");
                        break;
                     }
                }while (opcaogestor != 0);
                break;
            case 5:
              
    do
    {
        printf("\n--- Menu Grafo ---\n");
        printf("1. Criar vértice\n");
        printf("2. Criar aresta\n");
        printf("3. Inserir meio no grafo\n");
        printf("4. Inserir cliente no grafo\n");
        printf("5. Guardar em txt\n");
        printf("6. Guardar em binário\n");
        printf("7. Ler informação\n");
        printf("8. Listar meios de transporte do grafo\n");
        printf("9. Listar clientes do grafo\n");
        printf("10. Procurar meio por raio\n");
        printf("11. Meios a recolher\n");
        printf("12. Caixeiro viajante\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcaografo);

        switch (opcaografo)
        {
            case 1:
    criarVertice(&grafo, "Braga");
    criarVertice(&grafo, "Porto");
    criarVertice(&grafo, "Aveiro");
    criarVertice(&grafo, "Coimbra");
    criarVertice(&grafo, "Lisboa");
    criarVertice(&grafo, "Faro");
                break;
            case 2:
    criarAresta(grafo, "Braga", "Porto", 50.0);
    criarAresta(grafo, "Braga", "Aveiro", 120.0);
    criarAresta(grafo, "Aveiro", "Porto", 350.0);
    criarAresta(grafo, "Porto", "Aveiro", 70.0);
    criarAresta(grafo, "Porto", "Lisboa", 70.0);
               break;
            case 3:
    inserirMeioNoGrafo(grafo, "Lisboa", 1, "Carro", 12.0, 200.0, 10.0, 1, 5.0);
    inserirMeioNoGrafo(grafo, "Lisboa", 11, "Carro", 12.0, 200.0, 10.0, 0, 5.0);
    inserirMeioNoGrafo(grafo, "Porto", 2, "Bicicleta", 0.0, 50.0, 5.0, 0, 2.0);
    inserirMeioNoGrafo(grafo, "Coimbra", 3, "Moto", 80.0, 150.0, 8.0, 1, 3.0);
    inserirMeioNoGrafo(grafo, "Faro", 4, "Carro", 90.0, 180.0, 9.0, 1, 4.0);
                break;
            case 4:
    inserirClienteNoGrafo(grafo, "Lisboa", 1, "João", 123456789, 100.0, "Rua A");
    inserirClienteNoGrafo(grafo, "Porto", 2, "Maria", 987654321, 50.0, "Rua B");
    inserirClienteNoGrafo(grafo, "Coimbra", 3, "Pedro", 246813579, 200.0, "Rua C");
    inserirClienteNoGrafo(grafo, "Faro", 4, "Ana", 135792468, 150.0, "Rua D");
            break;
            case 5:
    saveVertices(grafo);
    saveArestas(grafo);
    saveMeios(grafo);
    saveClientes(grafo);
  
                break;
            case 6:
    saveVerticesbin(grafo);
    saveArestasbin(grafo);  
    saveMeiosbin(grafo);
    saveClientesbin(grafo);
                break;
            case 7:
    readVertices(&grafo);
    readArestas(&grafo);
    readMeios(&grafo);
    readClientes(&grafo);
                break;
            case 8:
    listarMeiosGrafo(grafo, "Coimbra");
    listarMeiosGrafo(grafo, "Lisboa");
                break;
            case 9:
    listarClientesGrafo(grafo, "Porto");
                break;
            case 10:
    char geocode[] = "Aveiro";
    char type[] = "Carro";
    float radius = 500.0;
    listVehiclesPerRadius(grafo, geocode, type, radius);
                break;
            case 11:
apresentarMeiosEstadoBateria(grafo);
            break;
                case 12:
findShortestPaths(grafo, "Porto");
    break;

            case 0:
                printf("Regresso ao menu principal...\n");
                break;
        }
    } while (opcaografo != 0);
    break;
    case 6:
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

