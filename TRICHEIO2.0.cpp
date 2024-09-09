#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>
#include<string.h>
#include<conio.h>

typedef struct { // Definacao das informacoes da reserva

	char nome [15];
	int numeroPessoas;
	int numeroQuarto;
	float valor;
	char cidade [40];
	int codigoReserva;

} INFO;

typedef struct { // Definicao das infoirmacoes de mes e dia da reserva

	char mes [15];
	int dia;

} DIA;

typedef struct LISTA { // Definicao da struct LISTA, com todas as informacoes

	INFO cadastro;
	DIA entrada;
	DIA saida;
	LISTA* prox;

} LISTA;

typedef struct noGRAFO { // Definicao de cada no do grafo

	int vertice;
	char nome[15];
	struct noGRAFO *prox;
	struct noGRAFO *baixo;

} noGRAFO;

typedef struct GRAFO { // Definicao do GRAFO

	int quantV;   // Quantidade de Vertices
	noGRAFO *inicio; // Inicio --> Onde come?a o 1 vertice

} GRAFO;

// CABECALHO DAS FUNCOES

noGRAFO* criaApontador( char nomeDestino[] );
void InserirFimVertice(GRAFO *g, noGRAFO *auxiliar);
void InserirPrimeiroVertice(GRAFO *g, noGRAFO *auxiliar);
void ImprimeGrafoCompleto(GRAFO *g);
void adicionarIndicacao( GRAFO *g, LISTA* *reserva, char nomeAtual[] );
void valor(LISTA *aux);
void infoConfirma(LISTA *aux,char confirma[]);
void imprime_lista( LISTA* reserva );
void buscarNome(LISTA *pReserva);
void inclui_ordenado( LISTA * *reserva, char nomeAtual[] );
void excluirNodo(LISTA **reserva);
void geraNomes( GRAFO *g, int vertices );
void criaLista( LISTA **reserva );
void entradaNome( LISTA *aux );
void ordena_lista( LISTA * *reserva );
void entradaDestino(LISTA *aux);
void entradaPessoas( LISTA *aux );
void entradaChecks(LISTA *aux);
noGRAFO* criaNodo( int valor );
void criaGrafo(GRAFO *grafo);
GRAFO *adicionaNoGrafo( GRAFO *g, int origem, int destino, char nomeOrigem[], char nomeDestino[] );

int main() { // CHAMADA DA FUNCAO PRINCIPAL

	setlocale(LC_ALL,"Portuguese");
	int op, vertices = 15, i;
	char nomeAtual[15];

	//DELCARACAO DAS VARIAVEIS
	GRAFO g;
	LISTA *reserva;

	criaGrafo ( &g );
	criaLista( &reserva );
	adicionaNoGrafo( &g, 0, 1, "MATHEW", "KYLE" );
	adicionaNoGrafo( &g, 0, 2, "MATHEW", "GUS" );
	adicionaNoGrafo( &g, 1, 3, "KYLE", "BRUNA" );
	adicionaNoGrafo( &g, 2, 4, "GUS", "NEYMAR" );
	adicionaNoGrafo( &g, 5, 0, "LUCAS", "MATHEW" );
	// MENU PARA EXECUCAO DAS FUNCOES
	while( 1 ) {
		printf( "\n Bem vindo ao Tricheio"  );
		printf( "\n\n [ 1 ]  Criar Reserva" );
		printf( "\n [ 2 ]  Excluir Reserva" );
		printf( "\n [ 3 ]  Buscar Reserva " );
		printf( "\n [ 4 ]  Imprime Reservas");
		printf( "\n [ 5 ]  Imprime grafo");
		printf( "\n [ 6 ]  Encerrar Programa");
		printf( "\n \n Qual operacao voce deseja realizar?: ");
		fflush(stdin);
		scanf("%i",&op);
		switch(op) {

			case 1:
				inclui_ordenado(&reserva, nomeAtual);
				getch();//PARADA DE TELA
				ordena_lista(&reserva);
				adicionarIndicacao( &g, &reserva, nomeAtual);
				system("cls");//LIMPA TELA
				break;

			case 2:
				excluirNodo(&reserva); // FUNCAO PARA EXLCUIR NODO POR NOME
				getch();//PARADA DE TELA
				system("cls");//LIMPA TELA
				break;
			case 3:
				buscarNome(reserva); // FUNCAO PARA BUSCAR RESERVA POR NOME
				getch();//PARADA DE TELA
				system("cls");//LIMPA TELA
				break;
			case 4:
				imprime_lista(reserva ); // FUNCAO PARA PRINTAR TODAS AS RESERVAS
				getch();//PARADA DE TELA
				system("cls");//LIMPA TELA
				break;

			case 5:
				ImprimeGrafoCompleto(&g);
				getch();//PARADA DE TELA
				system("cls");//LIMPA TELA
				break;
				
			case 6:
				exit(1);
				break;
		}
	}
	return 0;
}

void criaLista( LISTA **reserva ) { // CRIA LISTA

	*reserva = NULL;
}

void inclui_ordenado( LISTA * *reserva, char nomeAtual[]) { // INCLUI NA LISTA COM TODAS AS INFORMACOES DA RESERVA

	int confirmacao;
	LISTA *novo = (LISTA*) malloc(sizeof(LISTA));

	if(novo == NULL) {
		printf("Nao foi possivel alocar memoria.\n");
	} else {

		LISTA *aux2 = *reserva, *aux1 = NULL;
		char confirma[1];

		entradaNome(novo); // NOME
		entradaChecks(novo); // DIA E MES
		system("cls"); // LIMPA TELA
		entradaDestino(novo); // ESCOLHER UMA CIDADE
		entradaPessoas(novo); // NUMERO DE PESSOAS
		valor(novo); // CALCULA UM VALOR
		system("cls");//LIMPA TELA
		infoConfirma(novo, confirma	);// CONFIRMA A RESERVA
		confirmacao = strcmp(confirma, "N"); //VALIDACAO DA CONFIRMACAO DA RESERVA
		strcpy( nomeAtual, novo->cadastro.nome);

		if(confirmacao == 0)
			inclui_ordenado(reserva, nomeAtual);
		else
			printf("\n Sua reserva foi criada com sucesso! ");
		while(aux2 != NULL && aux2->cadastro.nome < novo->cadastro.nome) {
			aux1 = aux2;
			aux2 = aux2->prox;
		}

		if(aux1 == NULL) {
			novo->prox = aux2;
			*reserva = novo;
		} else {
			aux1->prox = novo;
			novo->prox = aux2;
		}
	}
}

void entradaDestino(LISTA *aux) {//ESCOLHE A CIDADE DESTINO

	int verdade = 0, i;

	//VETOR PRE DEFINIDO COM CIDADES, QUALQUER CIDADE DIFIRENTE QUE FOR DIGITADA ELE DA ERRO E PEDE NOVAMENTE PRA INSERIR
	char *cidades[] = {"PORTO ALEGRE", "SALVADOR DO SUL","CACHOEIRA DO SUL","SAO PAULO","RIO DE JANEIRO","BELO HORIZONTE","PORTO DE GALINHAS","PORTO SEGURO"
	                   ,"FERNANDO DE NORONHA", "GRAMADO"
	                  };
	char palavraAux;

	do {

		printf(" \n Escolha seu destino!");
		printf(" \n\n Regiao Sul:\n\n");

		printf(" Porto Alegre\n");
		printf(" Salvador do Sul\n");
		printf(" Cachoeira do Sul\n");
		printf(" Gramado");

		printf(" \n\n Regiao Sudeste:\n\n");

		printf(" Sao paulo\n");
		printf(" Rio de Janeiro\n");
		printf(" Belo Horizonte");


		printf(" \n\n Regiao Nordeste:\n\n");

		printf(" Porto de Galinhas\n");
		printf(" Porto Seguro\n");
		printf(" Fernando de Noronha");

		printf(" \n \n Para qual cidade voce deseja viajar? ");

		fflush(stdin);
		gets(aux->cadastro.cidade);
		strupr(aux->cadastro.cidade);

		// VERIFICA SE O QUE FOI DIGITADO E VALIDO, CASO NAO E PEDIDO PARA INSERIR NOVAMENTE
		for( i = 0; i < 10; i++) {

			if( strcmp( aux->cadastro.cidade, cidades[i] )== 0) {

				verdade = 1;
				break;
			}
		}
		if( verdade != 1) {
			system("cls");
			printf("\n Destino invalido, Digite novamente: ");

		}
	} while( verdade != 1);

}

void entradaNome( LISTA *aux ) {// ENTRADA DE UM NOME PARA A RESERVA

	printf( "\n Digite o nome do titular da reserva: " );
	fflush( stdin );
	gets( aux->cadastro.nome );
	strupr( aux->cadastro.nome);
	aux->prox = NULL;
}

void entradaPessoas( LISTA *aux ) { // NUMERO DE PESSOAS QUE ESTAO NA RESERVA

	printf("\n Para quantas pessoas e a reserva? ");
	fflush(stdin);
	scanf("%i", &aux->cadastro.numeroPessoas );

}

void entradaChecks(LISTA *aux) { // MES E DIA DO ANO

	int true1 = 0, true2 = 0, true3 = 0, true4 = 0, i;

	// VETOR PRE DEFINIDO COM TODOS OS MESES, QUALQUER MES DIFERENTE DESSES ESTARA ERRADO E O PROGRAMA VAI PEDIR NOVAMENTE
	char *meses[] = {"JANEIRO","FEVEREIRO","MARCO","ABRIL","MAIO","JUNHO","JULHO","AGOSTO","SETEMBRO","OUTUBRO",
	                 "NOVEMBRO","DEZEMBRO"
	                };
	// VERIFICACAO SE O MES ESTA DIGITADO CORRETAMENTE
	do {

		printf("\n Qual mes voce gostaria de fazer o check-in? ");
		fflush(stdin);
		scanf("%s", aux->entrada.mes);
		strupr( aux->entrada.mes);

		for( i = 0; i < 12; i++) {

			if( strcmp( aux->entrada.mes, meses[i] )== 0) {

				true1 = 1;
				break;
			}
		}
		if( true1 != 1) {

			system("cls");
			printf("\n Mes invalido (precisa ser escrito por extenso).\n");
		}
	} while( true1 != 1);

	// VERIFICACAO SE O DIA DIGITADO E VALIDO
	do {

		printf("\n Qual dia voce quer fazer o check-in? ");
		fflush(stdin);
		scanf("%d", &aux->entrada.dia);

		for( i = 1; i <= 31; i++) {

			if( aux->entrada.dia == i ) {

				true4 = 1;
				break;
			}
		}

		if( true4 != 1) {

			system("cls");
			printf("\n Dia invalido.\n");
		}
	} while( true4 != 1);

	// VERIFICACAO SE O MES ESTA DIGITADO CORRETAMENTE
	do {

		printf("\n Qual mes voce gostaria de fazer o check-out? ");
		fflush(stdin);
		scanf("%s", aux->saida.mes);
		strupr( aux->saida.mes);

		for( i = 0; i < 12; i++) {

			if( strcmp( aux->saida.mes, meses[i] )== 0) {

				true2 = 1;
				break;
			}
		}

		if( true2 != 1) {

			system("cls");
			printf("\n Mes invalido (precisa ser escrito por extenso).\n");
		}
	} while( true2 != 1);

	// VERIFICACAO SE O DIA DIGITADO E VALIDO
	do {

		printf("\n Qual o dia do check-out? ");
		fflush(stdin);
		scanf("%d", &aux->saida.dia);

		for( i = 1; i <= 31; i++) {

			if( aux->saida.dia == i ) {

				true3 = 1;
				break;
			}
		}
		if( true3 != 1) {

			system("cls");
			printf("\n Dia invalido.\n");
		}
	} while( true3 != 1);
}

void ordena_lista( LISTA * *reserva ) { // ORDENA AS RESERVA EM ORDEM ALFABETICA

	// VERIFICA LISTA VAZIA
	if (*reserva == NULL) {
		printf("A lista esta vazia!\n");

		// VERIFICA E REALIZA A TROCA
	} else {
		LISTA *aux1 = *reserva, *aux2;
		INFO nomeAux;

		while (aux1 != NULL) {
			aux2 = aux1->prox;
			while (aux2 != NULL) {
				if (strcmp(aux1->cadastro.nome, aux2->cadastro.nome) > 0) {
					nomeAux = aux1->cadastro;
					aux1->cadastro = aux2->cadastro;
					aux2->cadastro = nomeAux;
				}
				aux2 = aux2->prox;
			}
			aux1 = aux1->prox;
		}
	}
}

void excluirNodo(LISTA **reserva) {

	int achou = 0;

	if(*reserva == NULL) {
		printf("\n Não existe nenhuma reserva no sistema.\n");

	} else {
		char apagaNome[15];
		LISTA *pReserva = *reserva;
		LISTA *antes = *reserva;

		printf("\n Em nome de quem esta a reserva a ser excluida? ");
		fflush(stdin);
		gets(apagaNome);
		strupr(apagaNome);

		if(strcmp( pReserva->cadastro.nome, apagaNome)==0) {

			*reserva = (*reserva) -> prox;
			free(pReserva);
			printf("\n Reserva Excluida!\n\n");

		} else {
			while( pReserva != NULL ) {

				if(strcmp(apagaNome, pReserva->cadastro.nome) == 0) {

					antes->prox = pReserva->prox;
					free(pReserva);
					printf("\n Reserva Excluida.\n\n");
					achou = 1;
					break;
				}

				else
					antes = pReserva;
				pReserva = pReserva -> prox;
			}
			if( achou == 0)
				printf("\n Reserva não encontrada");
		}
	}
}

void buscarNome(LISTA *pReserva) { // BUSCA UMA RESERVA POR NOME

	int aux = 0;
	char consultaNome[15];

	//VERIFICA SE A LISTA ESTA VAZIA
	if( pReserva == NULL )
		printf("\n Não existe nenhuma reserva no sistema. ");
	else {
		printf("\n Digite o nome que esta registrado na reserva: ");
		fflush(stdin);
		gets(consultaNome);
		strupr(consultaNome);

		while( pReserva != NULL) { // VERIFICA O NOME INSERIDO E O NOME QUE ESTA NO BANCO DE DADOS

			if(strcmp(consultaNome, pReserva->cadastro.nome) == 0) {

				aux = aux + 1;
				break;
			}

			pReserva = pReserva->prox;
		}
		if( aux == 1) { // CASO O NOME ESTEJA CORRETO A RESERVA E PRINTADA

			printf(" \n Nome:%s\n", pReserva->cadastro.nome);
			printf(" Cidade: %s\n", pReserva->cadastro.cidade);
			printf(" Numero de pessoas: %i\n",  pReserva->cadastro.numeroPessoas);
			printf(" Data check-in: %i de %s\n", pReserva->entrada.dia,  pReserva->entrada.mes );
			printf(" Data check-out: %i de %s\n", pReserva->saida.dia,  pReserva->saida.mes );
			printf(" O valor da diaria e de R$ %.2f\n",  pReserva->cadastro.valor);

		} else
			printf("\n Reserva não encontrada! ");
	}

}

noGRAFO* criaNodo( int valor ) { //CRIA NODO PARA O GRAFO

	noGRAFO *aux;
	aux = (noGRAFO*) malloc(sizeof(noGRAFO)); // ALOCANDO MEMORIA DINAMICAMENTE
	aux->vertice = valor;        // ATRIBUINDO O NUMERO DO VERTICE PARA AUX->NUMERO
	aux->prox = NULL;           // ATUALIZANDO O PONTEIRO PARA NULL (ARESTAS)
	aux->baixo = NULL;          // ATUALIZANDO O PONTEIRO PARA NULL (VERTICES)
	return aux;
}

void criaGrafo( GRAFO *grafo ) { // CRIA O GRAFO

	grafo->quantV = 0;    // SETANDO A QUANTIDADE DE VERTICES EM 0
	grafo->inicio = NULL; // MARCA ONDE COMEÇA O PRIMEIRO VERTICE
}

/*void geraNomes( GRAFO *g, int vertices ) { // GERA UM NOME ALEATORIO PARA SER COLCOADO NA RESERVA

	char nomeOrigem[15], nomeDestino[15];
	int i, j, x;

	//VETOR PRE DEFINIDO
	char *nomes[] = {"DANIELA","RICHARLISSON","VINICIUS","LAURA","GABRIELA","NEYMAR","CECILIA",
	                 "JULIA","ANTONY","BRUNA","RODRYGO","ISABELA",
	                 "ALISSON","RAPHINA","HAKIMI"
	                };

	srand( time(NULL) );

	for( i= 0; i < vertices; i++ ) {

		j = rand() % 15; // SORTEIA UM NUMERO
		strcpy(nomeOrigem, nomes[ j ]);

		if( j < 7 )
			x = j + 4;
		else
			x = j--;

		strcpy(nomeDestino, nomes[ x ]); // COPIA O NOME GERADO PARA A VARIAVEL DESTINO

		adicionaNoGrafo( g, j, x, nomeOrigem, nomeDestino); // ADICIONA NOME NO GRAFO
	}
}	precisa ajustar a função de incluir no grafo, fora isso está zero balaa*/ 

GRAFO *adicionaNoGrafo( GRAFO *g, int origem, int destino, char nomeOrigem[], char nomeDestino[] ) {

	//ADICIONA OS NOMES GERADOS NO GRAFO
	int afirmativo = 0, achou = 1;
	noGRAFO *aux1 = g->inicio;
	
	while(aux1 != NULL) {//VERIFICA SE EXISTE O NOME DO DESTINO

			achou = strcmp( nomeDestino, aux1->nome);
			if(achou==0) {
				break;
				
			}
			else
				 achou = 1;
				 aux1=aux1->baixo;
				 
			}
	
	if(achou == 1){//SE NÃO EXISTIR
		noGRAFO *aux = criaNodo( destino );//CRIA VERTICE DESTINO
		strcpy(aux->nome, nomeDestino);//BOTA O NOMEDESTINO NO VERTICE
		if (g->quantV != 0) {  // SE EXISTIR VERTICES INSERE NO FIM
			while (aux->baixo != NULL) { 
				aux = aux->baixo;
			}
			InserirFimVertice( g, aux);
		}
	
		else//SE NAO EXISTIR INSERE O PRIMEIRO VERTICE
			InserirPrimeiroVertice( g, aux);
	}
	
	noGRAFO *aux2 = g->inicio;
	
	while( aux2 != NULL) {//VERIFICA SE EXISTE O VERTICE COM O NOME DE ORIGEM

		if(strcmp(nomeOrigem,  aux2->nome)==0)//SE EXISTIR INCLUI O NOME DESTINO NA LISTA DE ADJACENTES 
			if (aux2->prox == NULL) {//SE N EXISTIR ADJACENTES INCLUI NO INICIO
				aux2->prox = criaApontador(nomeDestino);
				afirmativo=1;
				return g;
			}	
		
			else{
				while(aux2->prox != NULL ){
					aux2 = aux2->prox;
				}
				aux2->prox = criaApontador(nomeDestino);//INCLUI NO FINAL DA LISTA
				afirmativo=1;
				break;
			} 
			
			aux2 = aux2->baixo;//PERCORRE LISTA DE VERTICES
		
	}
	
	if( afirmativo == 0 ) {//SE NAO EXISTIR VERTICE DE ORIGEM

		noGRAFO *no = criaNodo( origem );//CRIA O VERTICE DE ORIGEM
		if (no->prox == NULL) {
			no->prox = criaApontador(nomeDestino);//INCLUI O VERTICE DE DESTINO NA PRIMEIRA POSICAO
		} 
		else
			while (no->prox != NULL) { //VAI ATE A ULTIMA POSICAO DOS ADJACENTES
				no = no->prox;
			}
		no->prox = criaApontador(nomeDestino);//INCLUI O VERTICE DE DESTINO NA ULTIMA POSICAO
		strcpy(no->nome, nomeOrigem);//ATRIBUI O NOME DE ORIGEM AO VERTICE ORIGEM
		InserirFimVertice( g, no);//INCLUI O VERTICE ORIGEM NA ULTIMA POSICAO DA LISTA DE VERTICES
	}
	
}

void imprime_lista( LISTA * aux) { // PRINTF DE TODAS AS RESERVA

	int i= 0;

	//VERIFICA SE A LISTA ESTA VAZIA
	if( aux == NULL )
		printf( "\n Não existe nenhuma reserva no sistema." );
	else { // SE TIVER ELEMENTOS ESTES SERAO PRINTADOS

		LISTA *inicio = aux;

		do {
			printf(" \n Nome:%s\n", aux->cadastro.nome);
			printf(" Cidade: %s\n", aux->cadastro.cidade);
			printf(" Numero de pessoas: %i\n", aux->cadastro.numeroPessoas);
			printf(" Data check-in: %i de %s\n",aux->entrada.dia, aux->entrada.mes );
			printf(" Data check-out: %i de %s\n",aux->saida.dia, aux->saida.mes );
			printf(" O valor da diaria e de R$ %.2f\n", aux->cadastro.valor);

			aux = aux->prox;

		} while( aux!= NULL );
	}
}

void infoConfirma(LISTA *aux,char confirma[]) {// CONFIRMA A RESERVA CRIADA

	//PRINTA A RESERVA
	printf(" \n Nome:%s\n", aux->cadastro.nome);
	printf(" Cidade: %s\n", aux->cadastro.cidade);
	printf(" Numero de pessoas: %i\n", aux->cadastro.numeroPessoas);
	printf(" Data check-in: %i de %s\n",aux->entrada.dia, aux->entrada.mes );
	printf(" Data check-out: %i de %s\n",aux->saida.dia, aux->saida.mes );
	printf(" O valor da diaria e de R$ %.2f\n", aux->cadastro.valor);

	//PEDE A CONFIRMACAO DESSA RESERVA OU NAO
	printf("\n Voce quer confirmar essa reserva? [ S ] / [ N ]: ");
	fflush(stdin);
	gets(confirma);
	strupr(confirma);

}

void valor(LISTA *aux) {

	// CALCULA VALOR COM BASE NO NUMERO DE PESSOAS
	aux->cadastro.valor = aux->cadastro.numeroPessoas *210;
}

void adicionarIndicacao( GRAFO *g, LISTA* *reserva, char nomeAtual[] ) {//FUNCAO USADA PARA DEFINIR AS INFORMACOES DE 'ADICIONANOGRAFO'

	int codigoOrigem, codigoDestino, i, achou = 1;
	char nomeIndicacao[15], confirma[1];


	printf("\n\n Você gostaria de nos informar sobre quem lhe indicou? [ S ] / [ N ] ");
	gets(confirma);
	strupr(confirma);


	if(strcmp( confirma, "S")==0) {

		printf("\n Qual o nome da pessoa que lhe informou? ");
		gets(nomeIndicacao);//NOME DE ORIGEM
		strupr(nomeIndicacao);

		noGRAFO* aux1 = g->inicio;

		while(aux1 != NULL) {//SE JA EXISTIR NOME DE ORIGEM, INSERE NO VERTICE QUE JA EXISTE

			achou = strcmp( nomeIndicacao, aux1->nome);
			if(achou==0) {

				codigoOrigem = aux1->vertice;
				adicionaNoGrafo( g, codigoOrigem, (*reserva)->cadastro.codigoReserva, nomeIndicacao, nomeAtual );
				break;
				
			}
			else
				 achou = 1;
				 aux1=aux1->baixo;
				 
			}
			
		

		if( achou == 1) {
			srand(time(NULL));
			(*reserva)->cadastro.codigoReserva = rand()%100 + 20;
			codigoOrigem = rand()%200 + 24;
			adicionaNoGrafo( g, codigoOrigem, (*reserva)->cadastro.codigoReserva, nomeIndicacao, nomeAtual );
		}//SE NAO EXISTIR VAI TER QUE CRIAR UM NOVO

	}
}

void ImprimeGrafoCompleto(GRAFO *g) {//FUNCAO USADA PARA IMPRIMIR NOSSA LISTA DE GRAFOS E SEUS ADJACENTES
	noGRAFO *auxV = g->inicio;//USAMOS PARA PERCORRER A LISTA PARA BAIXO
	noGRAFO *auxA;//USAMOS PARA PERCORRER A LISTA PARA O LADO
	printf("\n CLIENTE        INDICAÇÕES\n\n");
	while (auxV != NULL) {
		auxA = auxV;//SETAMOS O AUXA COMO O PRIMEIRO NODO DA LINHA
		if( auxA != NULL)
			printf(" %s  ------>", auxV->nome);
		if (auxA->prox == NULL) {
			printf(" NÃO INDICOU NINGUÉM \n");
		} else {
			auxA = auxV->prox;
			while (auxA != NULL) {
				printf(" %s ->", auxA->nome);
				auxA = auxA->prox;// PERCORREMOS A LINHA
			}
			printf("\n");
		}
		auxV = auxV->baixo;//ANDAMOS PARA A PROXIMA LINHA
	}
}

void InserirFimVertice(GRAFO *g, noGRAFO *auxiliar) {//FUNCAO USADA PARA INSERIR VERTICES NO FIM DA LISTA
	int pos = g->quantV;
	int cont = 0;
	noGRAFO *aux = g->inicio;
	while (cont < (pos - 1)) {//PERCORREMOS ATE O FINAL DA LISTA
		aux = aux->baixo;
		cont++;
	}
	auxiliar->baixo = aux->baixo;//FAZEMOS O AUXILIAR SUBSTITUIR O AUX COMO ULTIMO DA LISTA
	aux->baixo = auxiliar;
	g->quantV++;//SOMAMOS 1 NO NOSSO CONTADOR DE VERTICES
}

void InserirPrimeiroVertice(GRAFO *g, noGRAFO *auxiliar) {//FUNCAO USADA PARA INSERIR O PRIMEIRO VERTICE
	g->quantV++;//FAZEMOS O NOSSO CONTADOR SER 1
	auxiliar->baixo = g->inicio;//FAZEMOS O AUXILIAR VIRAR O PRIMEIRO ITEM DA LISTA DE VERTICES
	g->inicio = auxiliar;
}

noGRAFO* criaApontador( char nomeDestino[] ) { //CRIA NODO PARA LISTA DE ADJACENCIA(QUE NÃO É INSERIDO NA LISTA DE VERTICES)

	srand(time(NULL));
	noGRAFO *aux;
	aux = (noGRAFO*) malloc(sizeof(noGRAFO)); 
	aux->vertice = rand()%500+72;        
	aux->prox = NULL;           
	aux->baixo = NULL;          
	strcpy(aux->nome, nomeDestino);
	return aux;
}
