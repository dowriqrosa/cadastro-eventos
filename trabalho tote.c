#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
//usuario administrador
#define usuario_adm "admin"
#define senha_adm "admin"
//funções.
void cadastrar_usarios();//cadastros dos usuarios no banco de dados.
void menu_inicial();//meunu que irar aparecer quando abrir o programa.
int verifica_usuario(char *usuario);//função que verificar se o usuario consta no banco de dados.
int login();//função que irar da acesso ao sitema se o usuario estiver cadastrado.
int verificar_senha(char *senha);//função que verifica se a senha do usuario é valida.
void menu();//menu que irar apresentar depois que o usuario logar no sistema.
void cadastrar_evento();//menu de cadastro de enventos.
int verifica_evento();//função que verifica se o evento esta cadastrado.
void menu_consulta();//função consultar evento.
void exibe_evento();//função exibir o evento.
void menu_editar_evento();//função que ira apresentar o menu para editar evento.
void editar_evento();//armazena as informação do banco de dados em um vetor de struct para serem editada.
void atualizar_banco_dados();//atulizar o banco de dados com alterações que foi inserida na struct.
void menu_relatorio();//menu que so pode ser acessado pelo administrador que ira exibir os relatorios de usuarios e eventos. 
//variaveis e structs globais.
struct usuarios{
	char login[10];
	char senha[8];
	int boolean;
}*USUARIOS;

struct cadastro_eventos{
	char nome_evento[20];
	int indentificador;
	char local[100];
	char data[10];
	char contato[50];
	char nome_idealizador[20];
	int boolean;
}*EVENTOS;

int opcao;//variavel que armazena as escolhas dos usuarios no menu.
int numero_usuario;//variavel que ira armazenar em qual linha esta alocado o usuario para depois usa para verificar se a senha coresponde ao usuario. 
char arquivo[50];//vareavel que vai armazenar as linhas do arquivo da imagem principal.
int i;//vareavel que serar usada como um contador nos laços.
int evento_numero;//variavel que em que posiçao vai esta armazenado o evento que sera exibido.
int total_evento=0;//variavel que irar armazenar o numero total de eventos cadastrados.
int indetificador_adm=0;
FILE *cadastros;
FILE *evento;
FILE *imagem;

int main(){
	setlocale(LC_ALL, "Portuguese");
	EVENTOS = malloc(sizeof(EVENTOS));
	USUARIOS = malloc(sizeof(USUARIOS));
	menu_inicial();
	return 0;
}

void menu_inicial(){
	FILE *informacao;
	do{
		system("cls");
		imagem = fopen("PRINCIPAL.txt", "r");
		if(imagem == NULL){
			printf("Falha ao abrir o arquivo");
			exit(1);
		}else{
			while(fgets(arquivo,50,imagem) != NULL){//Este while exibi a imagem principal do programa.
				printf("%s",arquivo);
			}
			fclose(imagem);
			char informacao_programa[3000];
			printf("\n\n\n");
			printf("Digite: \n");
			printf("[1] - Para logar no sistema\n");
			printf("[2] - Para cadastra usuarios.\n");
			printf("[3] - Para infomaçoes sobre o progama.\n");
			printf("[0] - Para fechar o programa.\n");
			fflush(stdin);
			scanf("%i",&opcao);
			switch(opcao){
				case 1:
					system("cls");
					if(login()==1){
						menu();
					}
					opcao=1;
					indetificador_adm=0;
					break;
				case 2:
					cadastrar_usarios();
					opcao=1;
					break;
				case 0:
					exit(1);
					break;
				case 3:
					system("cls");
					fflush(stdin);
					informacao = fopen("informações.txt", "r");
					while(fgets(informacao_programa,3000,informacao) != NULL){
						printf("%s",informacao_programa);
					}
					fclose(informacao);
					system ("pause");
					fflush(stdin);
					opcao = 1;
					break;
				default:
					printf("       Opção invalida! \7 \n");
					system ("pause");
					fflush(stdin);
					opcao = 1;
					break;
			}
		}
	}while(opcao!=0);
}

void cadastrar_usarios(){
	char usuario[10],senha[8];
	int retorno;
	do{
		system("cls");
		imagem = fopen("PRINCIPAL.txt", "r");
		if(imagem == NULL){
			printf("\nFalha ao abrir o arquivo do layout");
			exit(1);
		}else{
			while(fgets(arquivo,50,imagem) != NULL){//Este while exibi a imagem principal do programa.
				printf("%s",arquivo);
			}
			fclose(imagem);
			printf("\n\n\n");
			printf("digite o nome de usuario: \n");
			fflush(stdin);
			scanf("%s",usuario);
			printf("digite senha: \n");
			fflush(stdin);
			scanf("%s",senha);
			retorno=verifica_usuario(usuario);
			if(retorno == 1){
				printf("Usuario ja cadastrado! \7 \n");
				printf("[0]- Para voltar ao menu ou qualquer numero para tentar novamente. \n");
				fflush(stdin);
				scanf("%i",&opcao);
			}else{
				cadastros = fopen("cadastro_usuario.txt", "a+");
				if(cadastros == NULL){
					printf("\nFalha ao abrir o arquivo do banco de dados cadastros_usuarios");
					exit(1);
				}
				fprintf(cadastros,"%s\n",usuario);
				fprintf(cadastros,"%s\n",senha);
				fclose(cadastros);
				printf("usuario cadastrado com sucesso\n");
				opcao=0;
				system("pause");
			}
				
		}
	}while(opcao !=0);
}

int verifica_usuario(char *usuario){
	cadastros = fopen("cadastro_usuario.txt", "r");
	char usuario_banco[10];
	if(cadastros == NULL){
		printf("\nFalha ao abrir o arquivo do banco de dados cadastros_usuarios");
		exit(1);
	}
	numero_usuario=0;
	while(!feof(cadastros)){
		fscanf(cadastros,"%s\n",usuario_banco);
		numero_usuario++;
		if(strcmp(usuario_banco,usuario)==0){
			fclose(cadastros);
			return 1;
		} 
		fscanf(cadastros,"%s\n",usuario_banco);
	}
	return 0;
}

int login(){
	char usuario[10],senha[8];
	system("cls");
	imagem = fopen("PRINCIPAL.txt", "r");
	if(imagem == NULL){
		printf("\nFalha ao abrir o arquivo do layout");
		exit(1);
	}else{
		while(fgets(arquivo,50,imagem) != NULL){//Este while exibi a imagem principal do programa.
			printf("%s",arquivo);
		}
		fclose(imagem);
		printf("\n\n\n");
		printf("Digite nome de usuario:\n");
		fflush(stdin);
		scanf("%s",usuario);
		printf("Digite senha:\n");
		fflush(stdin);
		scanf("%s",senha);
		if(strcmp(usuario,usuario_adm) == 0 && strcmp(senha,senha_adm) == 0){
			indetificador_adm = 1;
			return 1;
		} 
		if(verifica_usuario(usuario) == 1){
			if(verificar_senha(senha)==1) return 1;
			else{
				printf("\nUsuario ou senha invalida!\7\n");
				system("pause");
				return 0;
			}
		}else{
			printf("\nUsuario ou senha invalida!\7\n");
			system("pause");
			return 0;
		}
	}
}

int verificar_senha(char *senha){
	cadastros = fopen("cadastro_usuario.txt", "r");
	int contador_senha=0;
	char senha_banco[10];
	if(cadastros == NULL){
		printf("\nFalha ao abrir o arquivo do banco de dados cadastros_usuarios");
		exit(1);
	}
	while(!feof(cadastros)){
		fscanf(cadastros,"%s\n",senha_banco);
		fscanf(cadastros,"%s\n",senha_banco);
		contador_senha++;
			if(strcmp(senha_banco,senha)==0 && numero_usuario == contador_senha){
			fclose(cadastros);
			return 1;
		} 
	}
	fclose(cadastros);
	return 0;
}

void menu(){
	do{
		system("cls");
		imagem = fopen("PRINCIPAL.txt", "r");
		if(imagem == NULL){
			printf("Falha ao abrir o arquivo");
			exit(1);
		}else{
			while(fgets(arquivo,50,imagem) != NULL){//Este while exibi a imagem principal do programa.
				printf("%s",arquivo);
			}
			fclose(imagem);
			printf("\n\n\n");
			printf("digite: \n");
			printf("[1] - Cadastrar um evento.\n");
			printf("[2] - Consultar um evento.\n");
			printf("[3] - Editar um evento.\n");
			printf("[4] - Relatorios.\n");
			printf("[0] - logout.\n");
			//printf("[] - ");
			fflush(stdin);
			scanf("%i",&opcao);
			switch(opcao){
				case 1:
					cadastrar_evento();
					opcao = 1;
					break;
				case 2:
					menu_consulta();
					opcao = 1;
					break;
				case 3:
					menu_editar_evento();
					opcao = 1;
					break;
				case 4:
					menu_relatorio();
					opcao = 1;
					break;
				case 0:
					opcao = 0;
					break;
				default:
					printf("		Opção invalida!\7 \n");
					system ("pause");
					break;
			}
		}
	}while(opcao!=0);
}

void cadastrar_evento(){
	do{
		system ("cls");
		imagem = fopen("PRINCIPAL.txt", "r");//faz a abertura do arquivo onde comtem a imagem que vai aparecer no menu do programa.
		if(imagem == NULL){//verifica se o arquivo da imagem existe mesmo, se existir exibi a imagem e continua a execulçao do programa normal, se não existir para o programa.
			printf("Falha ao abrir o arquivo");
			exit(1);
		}else{
			while(fgets(arquivo,50,imagem) != NULL){
			printf("%s",arquivo);
			}
			fclose(imagem);
			printf("\n\n\n");
			printf("nome do evento: ");
			fflush(stdin);
			gets(EVENTOS[0].nome_evento);
			if(verifica_evento()!= 0){
				printf("evento ja cadastrado\7 \n");
				printf("[0]- Para voltar ao menu ou qualquer numero para tentar novamente. \n");
				fflush(stdin);
				scanf("%i",&opcao);
			}else{
				printf("Responsavel pelo evento: ");
				fflush(stdin);
				gets(EVENTOS[0].nome_idealizador);
				printf("contato: ");
				fflush(stdin);
				gets(EVENTOS[0].contato);
				printf("local: ");
				fflush(stdin);
				gets(EVENTOS[0].local);
				printf("data: ");
				fflush(stdin);
				gets(EVENTOS[0].data);
				evento = fopen("eventos.txt", "a+");
				if(evento == NULL){
					printf("erro ao abrir banco de dados de eventos!");
					exit(1);
				}else{
					fprintf(evento,"%s\n",EVENTOS[0].nome_evento);
					fprintf(evento,"%s\n",EVENTOS[0].data);
					fprintf(evento,"%s\n",EVENTOS[0].nome_idealizador);
					fprintf(evento,"%s\n",EVENTOS[0].contato);
					fprintf(evento,"%s\n",EVENTOS[0].local);
					fprintf(evento,"%i\n",numero_usuario);
					fclose(evento);
					opcao = 0;
					printf("Evento cadastrado com sucesso!\n");
					system("pause");
					
				}
			}
		}
	}while(opcao != 0);
}

int verifica_evento(){
	char nome[100];
	evento_numero = 0;
	evento = fopen("eventos.txt", "r");
	if(evento == NULL){
		printf("Falha ao abrir o arquivo");
		exit(1);
	}
	while(!feof (evento)){
		fscanf(evento,"%s\n",nome);
		if(strcmp(EVENTOS[0].nome_evento,nome) == 0) return 1;
		evento_numero++;
	   	fscanf(evento,"%s\n",nome);
	   	fscanf(evento,"%s\n",nome);
	   	fscanf(evento,"%s\n",nome);
	   	fscanf(evento,"%s\n",nome);
	   	fscanf(evento,"%s\n",nome);
	}
	return 0;
}

void menu_consulta(){
	do{
		system("cls");
		imagem = fopen("PRINCIPAL.txt", "r");
		if(imagem == NULL){
			printf("\nFalha ao abrir o arquivo do layout");
			exit(1);
		}else{
			while(fgets(arquivo,50,imagem) != NULL){//Este while exibi a imagem principal do programa.
				printf("%s",arquivo);
			}
			fclose(imagem);
			printf("\n\n\n");
			printf("digite: \n");
			printf("[1] - Para consultar por nome do evento.\n");
			printf("[2] - Para mostra todos os eventos.\n");
			printf("[0] - para volta.\n");
			fflush(stdin);
			scanf("%i",&opcao);
			switch(opcao){
				case 1:
					system("cls");
					imagem = fopen("PRINCIPAL.txt", "r");
					if(imagem == NULL){
						printf("\nFalha ao abrir o arquivo do layout");
				  		exit(1);
	   		   		}else{
						while(fgets(arquivo,50,imagem) != NULL){//Este while exibi a imagem principal do programa.
							printf("%s",arquivo);
						}
						fclose(imagem);
						printf("\n\n\n");
						printf("Digite o nome do evento: \n");
						fflush(stdin);
						scanf("%s",EVENTOS[0].nome_evento);
						if(verifica_evento() != 0){
							exibe_evento();
						}
						else{
							printf("Nenhum evento com esse nome encontador.");
							system("pause");
						}
					}
					break;
				case 2:
					editar_evento();
					for(i=0;i<total_evento;i++){
						printf("%s\n",EVENTOS[i].nome_evento);
						printf("%s\n",EVENTOS[i].data);
						printf("%s\n",EVENTOS[i].nome_idealizador);
						printf("%s\n",EVENTOS[i].contato);
						printf("%s\n",EVENTOS[i].local);
						printf("%i\n",EVENTOS[i].indentificador);
						printf("\n");
					}
					system("pause");
					break;
				case 0:
					break;
				default :
					printf("		Opção invalida! \7 \n");
					system("pause");
					break;
			}
		}
	}while(opcao!=0);
}

void exibe_evento(){
	int contador=0;
	char nome[100];
	evento = fopen("eventos.txt", "r");
	if(evento == NULL){
		printf("Falha ao abrir banco de dados eventos"); 
		exit(1);
	}
	while(!feof (evento)){
		fscanf(evento,"%s\n",nome);
		if(strcmp(EVENTOS[0].nome_evento,nome) == 0 && contador == evento_numero){
			printf("%s\n",nome);
			fscanf(evento,"%s\n",nome);
			printf("%s\n",nome);
			fscanf(evento,"%s\n",nome);
			printf("%s\n",nome);
		   	fscanf(evento,"%s\n",nome);
		   	printf("%s\n",nome);
		   	fscanf(evento,"%s\n",nome);
		   	printf("%s\n",nome);
		   	system("pause");
			break;
		}
		contador++;
		fscanf(evento,"%s\n",nome);
	   	fscanf(evento,"%s\n",nome);
	   	fscanf(evento,"%s\n",nome);
	   	fscanf(evento,"%s\n",nome);
	   	fscanf(evento,"%s\n",nome);
	}
}

void menu_editar_evento(){
	do{
		system("cls");
		imagem = fopen("PRINCIPAL.txt", "r");
		if(imagem == NULL){
			printf("Falha ao abrir o arquivo");
			exit(1);
		}else{
			while(fgets(arquivo,50,imagem) != NULL){//Este while exibi a imagem principal do programa.
				printf("%s",arquivo);
			}
			fclose(imagem);
			printf("\n\n\n");
			printf("Nome do evento que deseja editar:\n");
			fflush(stdin);
			scanf("%s",EVENTOS[0].nome_evento);
			if(verifica_evento() == 1){
				editar_evento();
				if(EVENTOS[evento_numero].indentificador == numero_usuario || indetificador_adm == 1){
					printf("Digite para alterar:\n");
					printf("[1] -  data\n");
					printf("[2] - contato\n");
					printf("[3] - local\n");
					printf("[4] - apagar evento\n");
					printf("[0] - voltar\n");
					fflush(stdin);
					scanf("%i",&opcao);
					switch(opcao){
					
					case 1:
						printf("Digite a data:\n");
						fflush(stdin);
						gets(EVENTOS[evento_numero].data);
						printf("Evento atualizado com sucesso!\n");
						printf("[0]- Para voltar ao menu ou qualquer numero para tentar novamente. \n");
						fflush(stdin);
						scanf("%i",&opcao);
						break;
					case 2:
						printf("Digite o contato:\n");
						fflush(stdin);
						gets(EVENTOS[evento_numero].contato);
						printf("Evento atualizado com sucesso!\n");
						printf("[0]- Para voltar ao menu ou qualquer numero para tentar novamente. \n");
						fflush(stdin);
						scanf("%i",&opcao);
						break;
					case 3:
						printf("Digite o local:\n");
						fflush(stdin);
						gets(EVENTOS[evento_numero].local);
						printf("Evento atualizado com sucesso!\n");
						printf("[0]- Para voltar ao menu ou qualquer numero para tentar novamente. \n");
						fflush(stdin);
						scanf("%i",&opcao);
						break;
					case 4:
						printf("tem certeza que deseja excluir este evento!\n [1] sim.  [2]não.");
						fflush(stdin);
						scanf("%i",&opcao);
						if(opcao == 1) EVENTOS[evento_numero].boolean = 0;
						printf("Evento excluido com sucesso!\n");
						printf("[0]- Para voltar ao menu ou qualquer numero para tentar novamente. \n");
						fflush(stdin);
						scanf("%i",&opcao);
						break;
					case 0:
						break;
					default:
						break;
					}
				}else{
					printf("voce não tem permisão para editar este evento!\n");
					printf("[0]- Para voltar ao menu ou qualquer numero para tentar novamente. \n");
					fflush(stdin);
					scanf("%i",&opcao);
				}
			}else{
				printf("Evento não encontrado!\7\n");
				printf("[0]- Para voltar ao menu ou qualquer numero para tentar novamente. \n");
				fflush(stdin);
				scanf("%i",&opcao);
			}
		}
	}while(opcao != 0);
	atualizar_banco_dados();
}

void editar_evento(){
	total_evento=0;
	evento = fopen("eventos.txt","r");
	if(evento == NULL){
		printf("Erro ao abrir o banco de dados de eventos");
		exit(1);
	}else{
		while(!feof(evento)){
			fscanf(evento,"%s\n",EVENTOS[total_evento].nome_evento);
			fscanf(evento,"%s\n",EVENTOS[total_evento].data);
			fscanf(evento,"%s\n",EVENTOS[total_evento].nome_idealizador);
			fscanf(evento,"%s\n",EVENTOS[total_evento].contato);
			fscanf(evento,"%s\n",EVENTOS[total_evento].local);
			fscanf(evento,"%i\n",&EVENTOS[total_evento].indentificador);
			EVENTOS[total_evento].boolean = 1;
			total_evento++;
		}
	}
	fclose(evento);	
}

void atualizar_banco_dados(){
	evento = fopen("eventos.txt","w+");
	for(i=0;i<total_evento;i++){
		if(EVENTOS[i].boolean != 0){
		fprintf(evento,"%s\n",EVENTOS[i].nome_evento);
		fprintf(evento,"%s\n",EVENTOS[i].data);
		fprintf(evento,"%s\n",EVENTOS[i].nome_idealizador);
		fprintf(evento,"%s\n",EVENTOS[i].contato);
		fprintf(evento,"%s\n",EVENTOS[i].local);
		fprintf(evento,"%i\n",EVENTOS[i].indentificador);	
		}			
	}
	fclose(evento);
}

void menu_relatorio(){
	char nome[10];
	do{
		system("cls");
		imagem = fopen("PRINCIPAL.txt", "r");
		if(imagem == NULL){
			printf("Falha ao abrir o arquivo");
			exit(1);
		}else{
			while(fgets(arquivo,50,imagem) != NULL){//Este while exibi a imagem principal do programa.
				printf("%s",arquivo);
			}
			if(indetificador_adm != 1){
				printf("\n\n\n");
				printf("Usuario não tem permisão de acesso a este menu!\n");
				system("pause");
				opcao = 0;
			}else{
				printf("\n\n\n");
				printf("Digite:\n");
				printf("[1] - Quantidade de usuarios cadastrados.\n");
				printf("[2] - Quantidade de eventos cadastrados.\n");
				printf("[3] - exibir todos os eventos.\n");
				printf("[0] - voltar.\n");
				fflush(stdin);
				scanf("%i",&opcao);
				switch(opcao){
				case 1:
					verifica_usuario(nome);
					printf("São %i usuarios cadastrados.",numero_usuario);
					system("pause");
					break;
				case 2:
					editar_evento();
					printf("São %i eventos cadastrados",total_evento);
					system("pause");
					break;
				case 3:
					editar_evento();
					for(i=0;i<total_evento;i++){
						printf("%s\n",EVENTOS[i].nome_evento);
						printf("%s\n",EVENTOS[i].data);
						printf("%s\n",EVENTOS[i].nome_idealizador);
						printf("%s\n",EVENTOS[i].contato);
						printf("%s\n",EVENTOS[i].local);
						printf("%i\n",EVENTOS[i].indentificador);
						printf("\n");
					}
					system("pause");
					break;
				case 0:
					break;
				default:
					printf("		Opção invalida!\7 \n");
					system ("pause");
					break;
				}
			}
		}
	}while(opcao != 0);
}
