#include <iostream>
#include <fstream>
#include <cstring>
	//Tharlon Eduardo Costa Lopes, Lucélia Condé, Talita - 10A - Conta Bancária Internacional
using namespace std;
	struct Cliente{               //Essa struct recebe os dados de cada campo de um determinado cliente(n).
		char id[5];
		char nome[50]; //string com espaço, vale lembrar que o tipo string também pode ser classificado como vetor de characteres.
		char sexo;
		short idade;
		short anoNascimento;
		double saldo;     
		char cotacao[10]; //string sem espaço.
		char tipoCartao;
		char classificacao;
	};
	int partisiona_idd(Cliente vetor[], int comec, int fim){ //Partisiona por idade;
		Cliente pivo, aux = vetor[comec];
		pivo.anoNascimento = vetor[comec].anoNascimento;
		int i = comec+1, j = fim;
		while(i <= j)
		{
			if(vetor[i].anoNascimento < pivo.anoNascimento) i++;
				else if(pivo.anoNascimento < vetor[j].anoNascimento) j--;
					else{
						swap(vetor[i], vetor[j]);
						i++;
						j--;
					}
				}
					vetor[comec] = vetor[j];
					vetor[j] = aux;
					return j;
		}
	 int partisiona_saldo(Cliente vetor[], int comec, int fim){ //Partisiona por saldo;
		Cliente pivo, aux = vetor[comec];
		pivo.saldo = vetor[comec].saldo;
		int i = comec+1, j = fim;
		while(i <= j)
		{
			if(vetor[i].saldo < pivo.saldo) i++;
				else if(pivo.saldo < vetor[j].saldo) j--;
					else{
						swap(vetor[i], vetor[j]);
						i++;
						j--;
					}
				}
					vetor[comec] = vetor[j];
					vetor[j] = aux;
					return j;
		}
	  int partisiona_ID(Cliente vetor[], int comec, int fim){ //Partisiona por saldo;
		Cliente pivo, aux = vetor[comec];
		pivo = vetor[comec];
		int i = comec+1, j = fim;
		while(i <= j)
		{
			if(strcmp(vetor[i].id, pivo.id) < 0) i++;
				else if(strcmp(pivo.id, vetor[j].id) < 0) j--;
					else{
						swap(vetor[i], vetor[j]);
						i++;
						j--;
					}
				}
					vetor[comec] = vetor[j];
					vetor[j] = aux;
					return j;
		}
		void quick_sort(Cliente vetor[], int pos_pivo, int fim, char tipoPartisiona){ //Quick_sort com dois tipos de ordenação embutidos, um por idade e outro por saldo bancário.
			int pos_novo_pivo;
			if(pos_pivo < fim){
				if(tipoPartisiona == 'i'){
				pos_novo_pivo = partisiona_idd(vetor, pos_pivo, fim);
			}else if(tipoPartisiona == 's'){
				pos_novo_pivo = partisiona_saldo(vetor,pos_pivo,fim);
			}else if(tipoPartisiona == 'D'){
				pos_novo_pivo = partisiona_ID(vetor,pos_pivo,fim);
			}
				quick_sort(vetor, pos_pivo, pos_novo_pivo - 1, tipoPartisiona);
				quick_sort(vetor, pos_novo_pivo + 1, fim, tipoPartisiona);
			}
		}
		void busca_bin_idd(Cliente vetor[], int inicio, int fim, short buscado){
			int meio = (inicio+fim)/2;
			if(inicio > fim){
				cout << "Cliente nao encontrado!" << endl;
				return;
			}
			if(vetor[meio].idade == buscado){
			cout << "Cliente encontrado. Dados atuais:" << endl;
			cout << "ID: " << vetor[meio].id << endl;
            cout << "Nome: " << vetor[meio].nome << endl;
            cout << "Sexo: " << vetor[meio].sexo << endl;
            cout << "Idade: " << vetor[meio].idade << endl;
            cout << "Ano de Nascimento: " << vetor[meio].anoNascimento << endl;
            cout << "Saldo: " << vetor[meio].saldo << ",00" << endl;
            cout << "Cotacao: " << vetor[meio].cotacao << endl;
            cout << "Tipo de Cartao: " << vetor[meio].tipoCartao << endl;
            cout << "Classificacao: " << vetor[meio].classificacao << endl;
		}
			else if(buscado > vetor[meio].idade){
				busca_bin_idd(vetor, meio+1, fim, buscado);
			}else{
				busca_bin_idd(vetor, inicio, meio-1,buscado);
			}
		}
		void busca_bin_ID(Cliente vetor[], int inicio, int fim, char buscando[]){
			int meio = (inicio+fim)/2;
			if(inicio > fim){
				cout << "Cliente nao encontrado!" << endl;
				return;
			}
			if(strcmp(vetor[meio].id, buscando) == 0){
			cout << "Cliente encontrado. Dados atuais:" << endl;
			cout << "ID: " << vetor[meio].id << endl;
            cout << "Nome: " << vetor[meio].nome << endl;
            cout << "Sexo: " << vetor[meio].sexo << endl;
            cout << "Idade: " << vetor[meio].idade << endl;
            cout << "Ano de Nascimento: " << vetor[meio].anoNascimento << endl;
            cout << "Saldo: " << vetor[meio].saldo << ",00" << endl;
            cout << "Cotacao: " << vetor[meio].cotacao << endl;
            cout << "Tipo de Cartao: " << vetor[meio].tipoCartao << endl;
            cout << "Classificacao: " << vetor[meio].classificacao << endl;
		}
			else if(strcmp(vetor[meio].id, buscando) < 0){
				busca_bin_ID(vetor, meio+1, fim, buscando);
			}else{
				busca_bin_ID(vetor, inicio, meio-1,buscando);
			}
		}
				
		//-------------------------Função Salvamento Binário--------------------------------------------------------------------------------------------------------------------
		void salvarArquivoBinario(Cliente clienteDN[], int clientesPreenchidos){
		ofstream ArqB("clientes.bin", ios::binary);
		if(!ArqB){
        cout << "Erro ao criar arquivo binario!" << endl;
		}else{
		ArqB.write(reinterpret_cast<char*>(clienteDN), clientesPreenchidos * sizeof(Cliente));
		ArqB.close();
	}
}
		//---------------------------Função de Redimensionamento------------------------------------------------------------------------------------------------------------------
	void redimensionar(Cliente *&vetor, int& numClientes) {
    int novoTamanho = numClientes + 10;
    Cliente* novoVetor = new Cliente[novoTamanho];
    memcpy(novoVetor, vetor, numClientes * sizeof(Cliente));
    delete[] vetor;
    vetor = novoVetor;
    numClientes = novoTamanho;
}
	
	void adicionarCliente(Cliente *&vetor, int& clientesPreenchidos, int& numClientes){
    if (clientesPreenchidos == numClientes) {
        redimensionar(vetor, numClientes);
    }
    Cliente novo;
    string novoIdStr;
    if(clientesPreenchidos < 100){
		novoIdStr = "0" + to_string(clientesPreenchidos + 1);
	}else
	{
		novoIdStr = to_string(clientesPreenchidos + 1);
	}
    strcpy(novo.id, novoIdStr.c_str());
	cout << "ID novo do cliente: " << novo.id << endl;
    cout << "Digite o nome: ";
    cin.ignore();
    cin.getline(novo.nome, 50);
    
    cout << "Digite o sexo (M/F): ";
    cin >> novo.sexo;
    
    cout << "Digite a idade: ";
    cin >> novo.idade;
    
    cout << "Digite o ano de nascimento: ";
    cin >> novo.anoNascimento;
    
    cout << "Digite o saldo: ";
    cin >> novo.saldo;
    
    cout << "Digite a cotacao (sem espaco): ";
    cin.ignore();
    cin.getline(novo.cotacao, 10);
    
    cout << "Digite o tipo de cartao (char): ";
    cin >> novo.tipoCartao;
    
    cout << "Digite a classificacao (C, S, G, D, P): ";
    cin >> novo.classificacao;
    cout << clientesPreenchidos << endl;
    vetor[clientesPreenchidos] = novo;
     clientesPreenchidos++;
    cout << "Cliente adicionado com sucesso!" << endl;
}
	void removerCliente(Cliente vetor[], int& clientesPreenchidos, const char idParaRemover[5]){
    bool encontrado = false;
	int indiceEncontrado = -1;
    for (int i = 0; i < clientesPreenchidos; i++) {
        if (!encontrado && strcmp(vetor[i].id, idParaRemover) == 0) {
            encontrado = true;
            indiceEncontrado = i;
        }

        // Após encontrar, desloca os dados para trás
        if (encontrado && i < clientesPreenchidos - 1) {
            vetor[i] = vetor[i + 1];
        }
    }
    if(encontrado){
		for (int i = indiceEncontrado; i < clientesPreenchidos - 1; i++){ //Altera o id dos clientes posteriores
            string novoIdStr = "0" + to_string(i + 1);
            strcpy(vetor[i].id, novoIdStr.c_str());
        }
	}
    if (encontrado){
        clientesPreenchidos--;
        cout << "Cliente removido com sucesso." << endl;
    } else {
        cout << "ID não encontrado. Nenhum cliente foi removido." << endl;
    }
}

void salvarCSV(Cliente vetor[], int qtd) {
    ofstream arq("clientes_atualizado.csv");
    if (!arq) {
        cout << "Erro ao criar o arquivo CSV!" << endl;
        return;
    }

    arq << "id,nome,sexo,idade,anoNascimento,saldo,cotacao,tipoCartao,classificacao\n";
    for (int i = 0; i < qtd; i++) {
        arq << vetor[i].id << ","
            << vetor[i].nome << ","
            << vetor[i].sexo << ","
            << vetor[i].idade << ","
            << vetor[i].anoNascimento << ","
            << vetor[i].saldo << ","
            << vetor[i].cotacao << ","
            << vetor[i].tipoCartao << ","
            << vetor[i].classificacao << "\n";
    }

    arq.close();
    cout << "Arquivo CSV salvo como 'clientes_atualizado.csv' com sucesso!" << endl;
}

	void alterarCliente(Cliente vetor[], int clientesPreenchidos) {
    char id[5];
    cout << "Digite o ID do cliente que deseja alterar: " << endl;
    cin.ignore();
    cin.getline(id, 5);

    bool encontrado = false;
    for (int i = 0; i < clientesPreenchidos; i++) {
        if (strcmp(vetor[i].id, id) == 0) {
            encontrado = true;

            cout << "Cliente encontrado. Dados atuais:" << endl;
            cout << "Nome: " << vetor[i].nome << endl;
            cout << "Sexo: " << vetor[i].sexo << endl;
            cout << "Idade: " << vetor[i].idade << endl;
            cout << "Ano de Nascimento: " << vetor[i].anoNascimento << endl;
            cout << "Saldo: " << vetor[i].saldo << endl;
            cout << "Cotacao: " << vetor[i].cotacao << endl;
            cout << "Tipo de Cartao: " << vetor[i].tipoCartao << endl;
            cout << "Classificacao: " << vetor[i].classificacao << endl;

            cout << "Digite os novos dados (pressione ENTER para manter o valor atual):" << endl;
            // Atualiza sexo
            char novoSexo;
            cout << "Novo sexo (M/F): ";
            cin.get(novoSexo);
            cin.ignore();
            if (novoSexo == 'M' || novoSexo == 'F') vetor[i].sexo = novoSexo;

            // Saldo
            string saldoStr;
            cout << "Novo saldo: ";
            getline(cin, saldoStr);
            if (!saldoStr.empty()) vetor[i].saldo = stod(saldoStr);

            // Cotação
            char cotacaoNova[10];
            cout << "Nova cotacao: ";
            cin.getline(cotacaoNova, 10);
            if (strlen(cotacaoNova) > 0) strcpy(vetor[i].cotacao, cotacaoNova);

            // Tipo de cartão
            char novoCartao;
            cout << "Novo tipo de cartao: ";
            cin.get(novoCartao);
            cin.ignore();
            if (novoCartao != '\n' && novoCartao != '\0') vetor[i].tipoCartao = novoCartao;

            // Classificação
            char novaClasse;
            cout << "Nova classificacao (C, S, G, D, P): ";
            cin.get(novaClasse);
            cin.ignore();
            if (novaClasse != '\n' && novaClasse != '\0') vetor[i].classificacao = novaClasse;

            cout << "Dados alterados com sucesso.";
            return;
        }
    }

    if (!encontrado) {
        cout << "Cliente com ID " << id << " nao encontrado.\n";
    }
}
	void imprimir(Cliente clienteDN[], int clientesPreenchidos){         //Procedimendo(Subprograma) que imprime os dados dos clientes, quando chamado.
		for (int i = 0; i < clientesPreenchidos; i++) {  // impressão apenas das posições preenchidas do vetor
			cout << "----------------------------------------------------" << endl;
			cout << "ID DO CLIENTE: " << clienteDN[i].id << endl;
			cout << "NOME COMPLETO: " << clienteDN[i].nome << endl;
			cout << "SEXO: " << clienteDN[i].sexo << endl;
			cout << "IDADE: " << clienteDN[i].idade << " " << "Anos" << endl;
			cout << "Ano de Nascimento: " << clienteDN[i].anoNascimento << endl;
			cout << "Saldo em conta: " << clienteDN[i].saldo << ",00" << endl;
			cout << "Cotacao Monetaria: " << clienteDN[i].cotacao << endl;
			cout << "Tipo de Cartao: " << clienteDN[i].tipoCartao << endl;
			switch(clienteDN[i].classificacao){ //Mostra a classificação do cliente(Copper, Silver, Gold, Diamond, Platine).
				case 'C': //Copper
				cout << "Nivel: Bronze" << endl;
				break;
				case 'S': //Silver
				cout << "Nivel: Prata" << endl;
				break;
				case 'G': //Gold
				cout << "Nivel: Ouro" << endl;
				break;
				case 'D': //Diamond
				cout << "Nivel: Diamante" << endl;
				break;
				case 'P': //Plate
				cout << "Nivel: Platina" << endl;
				break;
			}
		}
		cout << "----------------------------------------------------" << endl;
	}
	void imprimir_parcialmente(Cliente clienteDN[], int inicio, int fim){  //Procedimendo(Subprograma) que imprime os dados dos clientes, quando chamado.
		int i = 0;
		i = inicio;
		while(i < fim){  // impressão apenas das posições preenchidas do vetor
			cout << "----------------------------------------------------" << endl;
			cout << "ID DO CLIENTE: " << clienteDN[i].id << endl;
			cout << "NOME COMPLETO: " << clienteDN[i].nome << endl;
			cout << "SEXO: " << clienteDN[i].sexo << endl;
			cout << "IDADE: " << clienteDN[i].idade << " " << "Anos" << endl;
			cout << "Ano de Nascimento: " << clienteDN[i].anoNascimento << endl;
			cout << "Saldo em conta: " << clienteDN[i].saldo << ",00" << endl;
			cout << "Cotacao Monetaria: " << clienteDN[i].cotacao << endl;
			cout << "Tipo de Cartao: " << clienteDN[i].tipoCartao << endl;
			switch(clienteDN[i].classificacao){ //Mostra a classificação do cliente(Copper, Silver, Gold, Diamond, Platine).
				case 'C': //Copper
				cout << "Nivel: Bronze" << endl;
				break;
				case 'S': //Silver
				cout << "Nivel: Prata" << endl;
				break;
				case 'G': //Gold
				cout << "Nivel: Ouro" << endl;
				break;
				case 'D': //Diamond
				cout << "Nivel: Diamante" << endl;
				break;
				case 'P': //Plate
				cout << "Nivel: Platina" << endl;
				break;
			}
			i++;
		}
		cout << "----------------------------------------------------" << endl;
	}
	void mostrar_menu(bool mostrar){
		cout << "________________________________________________________________________________________________________________________";
		cout << " _    _                  " << "    " << "                                                                        __-----__\n";
		cout << "|  \\/  |                  " << "    " << "                                                                  ..;;;--'~~~`--;;;..\n";
		cout << "| .  . |  ___  _ __   _   _ " << "    " << "                                                               /-~IN GOD WE TRUST~-\\\n";
		cout << "| |\\/| | / _ \\ '_ \\ | | | |" << "    " <<"                                                              //      ,;;;;;;;;     \\\\\n";
		cout << "| |  | ||  __/ | | || |_| |" << "    " <<"                                                             //      ;;;;;    \\      \\\\\n";
		cout << "\\_|  |_/ \\___|_| |_| \\____|" << "    " <<"                                                            ||       ;;;;(   /.|      ||\n";
		cout << "CHOSE YOUR OPTION:        " << "    " << "                                                             ||       ;;;;;;;   _\\     ||\n";
		cout << " 1-LIST CUSTOMERS         " << "    " << "                                                             ||       ';;;;;;;;=       ||\n";
		cout << " 2-ORDENATION             " << "    " << "                                                             ||LIBERTY | ''\\;;;;;;     ||\n";
		cout << " 3-SEARCH                 " << "    " << "                                                              \\\\     ,| '\\  '|><| 1995 //\n";
		cout << " 4-ADD DATA TO THE FILE   " << "    " << "                                                               \\\\   |     |      \\  A //\n";
		cout << " 5-REMOVE A CLIENT        " << "    " << "                                                                `;.,|.    |      '\\.-'/\n";
		cout << " 6-SAVE CSV               " << "    " << "                                                                  ~~;;;,._|___.,-;;;~'\n";
		cout << " 7-UPDATE A CLIENT'S DATA " << "    " << "                                                                    ''=----------='\n";
		cout << " 8-EXIT                   " << "    " << "                                           \n";
		cout << "________________________________________________________________________________________________________________________";
	}
int main(){
	string linha; // Apaga cabeçalho do arquivo
	int numClientes = 0,m_opcao = 0;
	ifstream ArqE("arquivo.csv");
	getline(ArqE, linha);
	ArqE >> numClientes; //Recebe número total de clientes
	ArqE.ignore();  //ignora o buffer do \n anterior
	Cliente *clienteDN = new Cliente[numClientes]; //Tipo == Nome da Struct, vetor alocado = clienteDN(De número...)
	for (int i = 0; i < numClientes; i++) //For que pega todos os dados do arquivo.
	{
		ArqE.getline(clienteDN[i].id, 5, ',');
		ArqE.getline(clienteDN[i].nome, 50, ',');
		ArqE >> clienteDN[i].sexo;
		ArqE.ignore();
		ArqE >> clienteDN[i].idade;
		ArqE.ignore();
		ArqE >> clienteDN[i].anoNascimento;
		ArqE.ignore();
		ArqE >> clienteDN[i].saldo;
		ArqE.ignore();
		ArqE.getline(clienteDN[i].cotacao, 10, ',');
		ArqE >> clienteDN[i].tipoCartao;
		ArqE.ignore();
		ArqE >> clienteDN[i].classificacao;
		ArqE.ignore();
	}  
	int clientesPreenchidos = numClientes; 	 // Quantos clientes de fato foram lidos/preenchidos
	bool menu_init = false;
	 //Inicio da Interface Abaixo:
		cout << "------------------------------------------------------------------------------------------------------------------------";
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "                         /$$$$$$$$  /$$$      /$$             /$$$$$$$   /$$$$$$  /$$   /$$ /$$   /$$\n";
		cout << "                        |__  $$__/ /$$ $$    | $$            | $$__  $$ /$$__  $$| $$$ | $$| $$  /$$/\n";
		cout << "                           | $$   |  $$$     | $$            | $$  \\ $$| $$  \\ $$| $$$$| $$| $$ /$$/ \n";
		cout << "                           | $$    /$$ $$/$$ | $$            | $$$$$$$ | $$$$$$$$| $$ $$ $$| $$$$$/  \n";
		cout << "                           | $$   | $$  $$_/ | $$            | $$__  $$| $$__  $$| $$  $$$$| $$  $$  \n";                 
		cout << "                           | $$   | $$\\  $$  | $$            | $$  \\ $$| $$  | $$| $$\\  $$$| $$\\  $$ \n";
		cout << "                           | $$   |  $$$$/$$|  $$$$$$$$      | $$$$$$$/| $$  | $$| $$ \\  $$| $$ \\  $$\n";
		cout << "                           |__/    \\____/\\_/ |________/      |_______/ |__/  |__/|__/  \\__/|__/  \\__/\n";
		while(!menu_init){
		cout << "________________________________________________________________________________________________________________________";
		cout << " _    _                  " << "    " << "                                                                        __-----__\n";
		cout << "|  \\/  |                  " << "    " << "                                                                  ..;;;--'~~~`--;;;..\n";
		cout << "| .  . |  ___  _ __   _   _ " << "    " << "                                                               /-~IN GOD WE TRUST~-\\\n";
		cout << "| |\\/| | / _ \\ '_ \\ | | | |" << "    " <<"                                                              //      ,;;;;;;;;     \\\\\n";
		cout << "| |  | ||  __/ | | || |_| |" << "    " <<"                                                             //      ;;;;;    \\      \\\\\n";
		cout << "\\_|  |_/ \\___|_| |_| \\____|" << "    " <<"                                                            ||       ;;;;(   /.|      ||\n";
		cout << "CHOSE YOUR OPTION:        " << "    " << "                                                             ||       ;;;;;;;   _\\     ||\n";
		cout << " 1-LIST CLIENT'S          " << "    " << "                                                             ||       ';;;;;;;;=       ||\n";
		cout << " 2-ORDENATION             " << "    " << "                                                             ||LIBERTY | ''\\;;;;;;     ||\n";
		cout << " 3-SEARCH                 " << "    " << "                                                              \\\\     ,| '\\  '|><| 1995 //\n";
		cout << " 4-ADD DATA TO THE FILE   " << "    " << "                                                               \\\\   |     |      \\  A //\n";
		cout << " 5-REMOVE A CLIENT        " << "    " << "                                                                `;.,|.    |      '\\.-'/\n";
		cout << " 6-SAVE CSV               " << "    " << "                                                                  ~~;;;,._|___.,-;;;~'\n";
		cout << " 7-SAVE BINARY            " << "    " << "                                                                    ''=----------='\n";
		cout << " 8-UPDATE A CLIENT'S DATA " << "    " << "                                           \n";
		cout << " 9-EXIT                   " << "    " << "                                           \n";
		cout << "________________________________________________________________________________________________________________________";
		menu_init = true;
		//Fim da Interface.
		//Parte funcional do menu abaixo:
		bool menu_verif = false;
		bool menu_ordverif = false;
		bool menu_buscverif = false;
		bool menu_listtverif = false;
		int m_ord_opcao;
		//----------------While do menu geral------------------------------------------------------------------------------------------------
		while(!menu_verif){
			cin >> m_opcao;
			if(m_opcao == 1){
				cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "CHOSE YOUR PRINTING:        " << endl;
				cout << " 1-LIST ALL CUSTOMERS	     " << endl;
				cout << " 2-PARTIALLY LIST CUSTOMERS " << endl;
				cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
				int list_option;
				int end_list, init_list;
				while(!menu_listtverif){
					cin >> list_option;
					if(list_option == 1){
					imprimir(clienteDN, clientesPreenchidos);
					menu_listtverif = true;
					}else if(list_option == 2){
						bool verif_tam_list = true;
						while(verif_tam_list){
						cout << "DIGITE O INICIO DA LISTA: " << endl;
						cin >> init_list;
						cout << "DIGITE O FIM DA LISTA: " << endl;
						cin >> end_list;
							if(end_list <= clientesPreenchidos and init_list >= 1){
							imprimir_parcialmente(clienteDN, init_list-1, end_list);
							verif_tam_list = false;
							}else{
								cout << "INVALID VALUE, MUST BE BETWEEN 1 AND 100, TRY AGAIN!" << endl;
							}
						}
						menu_listtverif = true;
					}else{
						cout << "INVALID OPTION!" << endl;
					}
					mostrar_menu(true);
				}
			}else if(m_opcao == 2){
				menu_verif = true;
				cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << "CHOSE YOUR ORDENATION:    " << endl;
				cout << " 1-LIST FOR AGE           " << endl;
				cout << " 2-LIST FOR BALANCE       " << endl;
				cout << " 3-LIST FOR ID            " << endl;
				cout << " 4-RETURN TO MENU         " << endl;
				cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
				while(!menu_ordverif){ //-------------------------------------While do menu de ordenação-----------------------------------------------
				cin >> m_ord_opcao;
				bool list_YorN_verif = true;
				bool save_YorN_verif = false;
					if(m_ord_opcao == 1)
					{
					quick_sort(clienteDN,0,clientesPreenchidos-1,'i');
					list_YorN_verif = false;
					}else if(m_ord_opcao == 2){
					quick_sort(clienteDN,0,clientesPreenchidos-1,'s');
					list_YorN_verif = false;
					}else if(m_ord_opcao == 3){
					quick_sort(clienteDN,0,clientesPreenchidos-1,'D');
					list_YorN_verif = false;	
					}
					else if(m_ord_opcao == 4){
						menu_init = false;
						menu_ordverif = true;
					}
					else
					{
						cout << "INVALID OPTION!!" << endl;
					}
						while(!save_YorN_verif){
						cout << "WANTING SAVE THE CHANGES ON BINARY? Y or N" << endl;
						char save_YorN;
						cin >> save_YorN;
							if(save_YorN == 'Y' or save_YorN == 'y'){
								salvarArquivoBinario(clienteDN, clientesPreenchidos);
								cout << "SAVED" << endl;
								save_YorN_verif = true;
								menu_init = false;
							}else if(save_YorN == 'N' or save_YorN == 'n'){
								save_YorN_verif = true;
								menu_init = false;
							}else
							{
								cout << "INVALID OPTION!!" << endl;
							}
						}
						while(!list_YorN_verif){
						cout << "WANTING LIST ALL CLIENTES? Y or N" << endl;
						char list_YorN;
						cin >> list_YorN;
							if(list_YorN == 'Y' or list_YorN == 'y'){
								imprimir(clienteDN, clientesPreenchidos);
								list_YorN_verif = true;
								menu_init = false;
							}else if(list_YorN == 'N' or list_YorN == 'n'){
								list_YorN_verif = true;
								menu_init = false;
							}else
							{
								cout << "INVALID OPTION!!" << endl;
							}
						}
						menu_ordverif = true;
					}
			}
			else if(m_opcao == 3){
			int type_search = false;
			cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "CHOSE YOUR SEARCH:          " << endl;
			cout << " 1-SEARCH FOR AGE           " << endl;
			cout << " 2-SEARCH FOR ID            " << endl;
			cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
			while(!menu_buscverif){ //-------------------------------------While do menu de busca--------------------------------------------------------------
			short buscado;
			char  buscado2[5];
			cin >> type_search;
			if(type_search == 1)
			{
				cout << "Digite a idade buscada: " << endl;
				cin >> buscado;
				quick_sort(clienteDN, 0, clientesPreenchidos-1, 'i');
				busca_bin_idd(clienteDN, 0, clientesPreenchidos-1, buscado);
				menu_buscverif = true;
			}else if(type_search == 2)
			{
				cout << "Digite o id buscado: (Ex.: 049)" << endl;
				cin >> buscado2;
				quick_sort(clienteDN, 0, clientesPreenchidos-1, 'D');
				busca_bin_ID(clienteDN, 0, clientesPreenchidos-1, buscado2);
				menu_buscverif = true;
			}else
			{
				cout << "INVALID OPTION!" << endl;
			}
		}
	}
			else if(m_opcao == 4){
			adicionarCliente(clienteDN, clientesPreenchidos, numClientes);
			salvarArquivoBinario(clienteDN, clientesPreenchidos);
		} 
			else if(m_opcao == 5){
			char id[5];
			cout << "Digite o ID do cliente que deseja remover (ex: 049): ";
			cin.ignore(); // limpa o buffer
			cin.getline(id, 6);
			removerCliente(clienteDN, clientesPreenchidos, id);
			salvarArquivoBinario(clienteDN, clientesPreenchidos);
			mostrar_menu(true);

		}
			else if(m_opcao == 6){
			salvarCSV(clienteDN, clientesPreenchidos);
			mostrar_menu(true);
		}
			else if(m_opcao == 7){
			salvarArquivoBinario(clienteDN, clientesPreenchidos);
			cout << "SAVED" << endl;
			mostrar_menu(true);
		}
			else if(m_opcao == 8){
			alterarCliente(clienteDN, clientesPreenchidos);
			salvarArquivoBinario(clienteDN, clientesPreenchidos);
			mostrar_menu(true);
		}
			else if(m_opcao == 9){
			menu_verif = true;
			cout << "Saindo..." << endl;
		}
		else{
                cout << "INVALID OPTION, TRY AGAIN" << endl;
            }
			}
			
		}
		//Fim da parte funcional do menu.
		delete [] clienteDN;
	return 0;
}
