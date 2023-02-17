#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FUNCIONARIOS 100 // numero maximo de funcionarios

typedef enum {
    TELA_SAIR = -1,
    TELA_PRINCIPAL,
    TELA_CADASTRAR,
    TELA_LISTAR_TODOS,
    TELA_DESCADASTRAR
    
} Telas;

typedef struct {
    char nome[128];
    char matricula[64];
    char cargo[64];
    char salario[64];

} FuncionarioDados;

typedef struct {
    Telas menu;
    int totalFuncionarios;
    FuncionarioDados funcionarios [MAX_FUNCIONARIOS];

} RegistroEmpresarial;

void cabecalho();
void listaCabecalho();
void cadastroCabecalho();
void descadastarCabecalho();


int main(void){
    RegistroEmpresarial registro;
    //zerar todos os bytes do registro
    memset(&registro, 0x0, sizeof(registro));
 setlocale(LC_ALL, "PORTUGUESE"); // colocar os acentos 
 
 // menu do registro
 
  registro.menu = TELA_PRINCIPAL;
  
  FILE * bancoDeDados = fopen("funcionarios.bin", "rb");
  if (bancoDeDados == NULL){
      printf("Erro ao abrir o arquivo 'banco de dados' dos funcionarios.\n ");
      printf("Voc� deve criar o arquivo 'funcionarios.bin' na primeira execu��o.\n");
        return 1;
  }
  
  size_t lidos = fread(registro.funcionarios, sizeof(FuncionarioDados),
    MAX_FUNCIONARIOS, bancoDeDados);
    printf("N�mero de funcion�rios registrados: %zd\n", lidos);
    registro.totalFuncionarios = (int)lidos;
    fclose(bancoDeDados);
  
    while (registro.menu != TELA_SAIR){
        
        switch(registro.menu){
            
            case TELA_PRINCIPAL:{
                cabecalho();
            int op = -1;
            do
            {
               printf("Escolha sua opc�o: \n");
               printf("\tDigite 1 para cadastrar novo funcion�rio\n");  
               printf("\tDigite 2 para remover funcion�rio do cadastro\n"); 
               printf("\tDigite 3 para listar todos os funcion�rios\n");
               printf("\tDigite 0 para sair do programa\n"); 
               printf("\t ?");
               scanf("%d", &op);
               int c = 0;
               while ((c = getchar()) != '\n' && c != EOF) { }
               
            } while( op < 0 || op > 3);
            
                if(op == 0)
            registro.menu = TELA_SAIR;
            
                if(op == 1){
                    registro.menu = TELA_CADASTRAR;
                    if(registro.totalFuncionarios >= MAX_FUNCIONARIOS){
                        printf("\nO programa de Cadastro est� totalmente preenchido\n");
                        registro.menu = TELA_PRINCIPAL;
                    }
                }
                
                if(op == 2){
                    registro.menu = TELA_DESCADASTRAR;
                    if(registro.totalFuncionarios == 0){
                        printf("\nN�o h� funcion�rios para serem descadastrados\n");
                        registro.menu = TELA_PRINCIPAL;
                    }
                    
                }
                
                 if(op == 3){
                    registro.menu = TELA_LISTAR_TODOS;
                    if(registro.totalFuncionarios == 0){
                        printf("\nN�o h� funcion�rios para serem listados");
                    }
                    
                    
                    
                }

                    
            }
               
            break;
            
            case TELA_CADASTRAR:{
                cadastroCabecalho();
                    FuncionarioDados novo;
                    char opcao = 's';
                    printf("Deseja cadastrar novo funcionario?? clique enter para continuar\n");
                     int c = 0;
               while ((c = getchar()) != '\n' && c != EOF) { }
               
                do{
                     memset(&novo, 0x0, sizeof(novo)); // zerar dados 
                     printf("Digite o nome do funcion�rio: \n");
                     fgets(novo.nome, 128, stdin);
                     int id = 0;
                        while(novo.nome[id] != '\0' && novo.nome[id] != '\n')
                        id++;
                        novo.nome[id] = '\0';
                        printf("Digite a matricula do funcioario: \n");
                        fgets(novo.matricula,64,stdin);
                        id = 0;
                    while(novo.matricula[id] != '\0' && novo.matricula[id] != '\n')
                        id++;
                        novo.matricula[id] = '\0';
                        printf("Digite o cargo do funcionario: \n");
                        fgets(novo.cargo,64, stdin);
                        id = 0;
                        while(novo.cargo[id] != '\0' && novo.cargo[id] != '\n')
                        id++;
                        novo.cargo[id] = '\0';
                        printf("Insira o sal�rio do funcion�rio: \n");
                        fgets(novo.salario,64, stdin);
                        id = 0;
                        while(novo.salario[id] != '\0' && novo.cargo[id] != '\n')
                        id++;
                        printf("Confirma a operac�o: [s/n]\n");
                        opcao = getchar();
                        int c = 0;
                        while ((c = getchar()) != '\n' && c != EOF ) { }
                        
                }while(opcao == 'n' || opcao == 'N');
                
             
                  //Inser��o do funcionario no RegistroEmpresarial
                registro.funcionarios[registro.totalFuncionarios] = novo;
                registro.totalFuncionarios++;
                bancoDeDados = fopen("funcionarios.bin", "w+b");
                 if(bancoDeDados == NULL){
                     printf("Erro ao abrir 'funcionarios.bin'\n");
                     return 0;
                     
                 }
                 
                  
                    //Salvamento dos dados do funcioanrio no RegistroEmpresarial
                    size_t salvados = fwrite(registro.funcionarios, sizeof(FuncionarioDados),
                            registro.totalFuncionarios, bancoDeDados);
                            if(salvados != (size_t)registro.totalFuncionarios){
                                printf("Erro ao salvar contatos no banco de dados funcionarios.bin");
                                return 1;
                            }
                            fclose(bancoDeDados);
                
                registro.menu = TELA_PRINCIPAL;
            }
            break;
            
            case TELA_DESCADASTRAR:{
                descadastarCabecalho();
                int i;
                for (i = 0 ;i < registro.totalFuncionarios; i++){
                    printf("Funcion�rio n�%d/n",i);
                    printf("\tNome: %s\n", registro.funcionarios[i].nome);
                    printf("\tMatricula: %s\n", registro.funcionarios[i].matricula);
                    printf("-------------------------------------------------------------\n");
                }
                int indice = -1;
                do{
                    printf("Digite o indice do funcion�rio: entre 0 e %d", registro.totalFuncionarios - 1);
                    printf("?");
                    scanf("%d", &indice);
                      int c = 0;
               while ((c = getchar()) != '\n' && c != EOF) { }
               
                }while(indice < 0 || indice >= registro.totalFuncionarios);
                
                    for( i = indice; i < registro.totalFuncionarios - 1; i++)
                    registro.funcionarios[i] = registro.funcionarios[i + 1];
                        registro.totalFuncionarios--;
                
                    bancoDeDados = fopen("funcionarios.bin", "w+b");
                        if(bancoDeDados == NULL){
                            printf("Erro ao abrir 'funcionarios.bin'\n");
                            return 0;
                        }
                        size_t salvados = fwrite(registro.funcionarios, sizeof(FuncionarioDados),registro.totalFuncionarios, bancoDeDados);
                         if(salvados != (size_t)registro.totalFuncionarios){
                             printf("Erro ao salvar cadastro de funcionarios no banco de dados 'funcionarios.bin'\n ");
                             return 1;
                         }
                        fclose(bancoDeDados);
                
                //volta para a tela principal
                registro.menu = TELA_PRINCIPAL;
            }
            break;
            
            case TELA_LISTAR_TODOS:{
                listaCabecalho();
                int i;
                for(i = 0; i < registro.totalFuncionarios; i++){
                    printf("Funcionario %i \n", i);
                    printf("\nNome: %s \n", registro.funcionarios[i].nome);
                    printf("\nMatricula: %s \n", registro.funcionarios[i].matricula);
                    printf("\nCargo: %s \n", registro.funcionarios[i].cargo);
                    printf("\nSalario: %s \n", registro.funcionarios[i].salario);
                    printf("--------------------------------------------------------------\n");
                }
                
                
                //volta para a tela principal
                registro.menu = TELA_PRINCIPAL;
            
            }
            break;
            
            
            default:
                registro.menu = TELA_PRINCIPAL;
            break;
        }
    }
 
 
 

 return 0;
}
void cabecalho(){
    printf("\n------------------------------------\n");
    printf("\tREGISTRO DE FUNCION�RIOS\n");
    printf("------------------------------------\n");
}
void listaCabecalho(){
    printf("\n------------------------------------\n");
    printf("\tLISTAR FUNCION�RIOS\n");
    printf("------------------------------------\n");
}
void cadastroCabecalho(){
    printf("\n------------------------------------\n");
    printf("\tCADASTRAR FUNCION�RIOS\n");
    printf("------------------------------------\n");
}
void descadastarCabecalho(){
     printf("\n------------------------------------\n");
    printf("\tDESCADASTRAR FUNCION�RIOS\n");
    printf("------------------------------------\n");   
}


