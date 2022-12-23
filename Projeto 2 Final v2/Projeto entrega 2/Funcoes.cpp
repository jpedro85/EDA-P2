#include <iostream>
#include "Funcoes.h"
#include <string>
#include "produto.h"
#include "horta.h"
#include "arrays_string.h"
#include <Windows.h>
//#define INT_MAX 5

using namespace std;

void menu_title(std::string titulo) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11);
    cout << titulo << endl << endl;
    SetConsoleTextAttribute(hConsole, 3);
}

void escrever_dia(Lista_Produtos& armazem, Lista_Produtos& lst_colhidos, Lista_Produtos& lst_removidos , Lista_Produtos& lst_plantados, int plantados, int perdidos, horta plantacao[], int capacidade , int dia) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 31);
    cout << "----------------------------------------------------------------------Dia " << dia << "----------------------------------------------------------------------" << endl;

    SetConsoleTextAttribute(hConsole, 3);
    cout << "Foram plantados: " << plantados << " produtos !" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 2);
    escrever(lst_plantados);
    SetConsoleTextAttribute(hConsole, 3);
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << "Foram colhidos: " << lst_colhidos.n_produtos << " produtos !" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 6);
    escrever(lst_colhidos);
    SetConsoleTextAttribute(hConsole, 3);
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;

    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Foram perdidos: " << lst_removidos.n_produtos - perdidos << " produtos !" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 12);
    escrever(lst_removidos, lst_removidos.n_produtos - perdidos);
    SetConsoleTextAttribute(hConsole, 3);
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;

    escrever_plantacao(plantacao, capacidade);
    cout << endl;

    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Armazem: " << armazem.n_produtos << " Produtos" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 8);
    escrever(armazem);
    SetConsoleTextAttribute(hConsole, 3);

}

void escrever_opcoes(char& choice) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 12);
    cout << endl << "(s) eguinte ********** (g) estao ********** (f) echar" << endl;
    SetConsoleTextAttribute(hConsole, 10);
    cin >> choice;
    SetConsoleTextAttribute(hConsole, 3);
    system("CLS");
}

void ColherProduto(horta ary[],int tamanho, Lista_Produtos& lst_colhidos) {
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    string prod;
    SetConsoleTextAttribute(hConsole, 4);
    cout << "Introduza o nome do Produto que deseja colher" << endl;
    cin.ignore();
    SetConsoleTextAttribute(hConsole, 10);
	getline(cin, prod);
    SetConsoleTextAttribute(hConsole, 3);
    remover_da_plantacao_colheita(ary, tamanho, prod,lst_colhidos);
    cout << endl;
}

void AtualizarRega(Lista_Produtos& armazem, horta plantacao[], int capacidade) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    string prod;
    SetConsoleTextAttribute(hConsole, 4);
    cout << "Insira o Nome do Produto que pretende alterar o tempo de rega" << endl;
    cin.ignore();
    SetConsoleTextAttribute(hConsole, 10);
    getline(cin, prod);


    int novo_tempo = NULL;
    bool cond = false;

    while (true) {

        SetConsoleTextAttribute(hConsole, 4);
        cout << "Insira novo tempo de rega:" << endl;
        SetConsoleTextAttribute(hConsole, 10);
        cin >> novo_tempo;

        if (cin.fail())
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << endl << "Iserio um numero invalido" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else if (novo_tempo < 1 || novo_tempo > 5)
        {
            SetConsoleTextAttribute(hConsole, 12);
            cout << endl << "Iserio um numero fora do intervalo permitiodo: [1,5] !!" << endl;
        }
        else
            break;
    }

    SetConsoleTextAttribute(hConsole, 3);
    tempo_rega_plantacao(plantacao, prod, capacidade, novo_tempo);
    modificar_tempo_de_rega(armazem, prod, novo_tempo);
    cout << endl;

}

void GravarPlantacao(horta plantacao[], int capacidade, Lista_Produtos& armazem, Lista_Produtos& removidos, std::string diretorio_plantacao, std::string diretorio_colhidos, std::string diretorio_armazem, std::string diretorio_removidos, int dia) {

    save_plantacao(diretorio_plantacao, diretorio_colhidos, plantacao, capacidade, dia);
    guardar(diretorio_armazem, armazem);
    guardar(diretorio_removidos, removidos);
}

void CarregarPlantacao(horta*& plantacao, int& capacidade, Lista_Produtos& armazem, Lista_Produtos& removidos,Lista_Produtos& lst_colhidos, Lista_Produtos& lst_plantados, std::string diretorio_plantacao, std::string diretorio_colhidos, std::string diretorio_armazem, std::string diretorio_removidos, int& dia) {
    limpar_plantacao(plantacao, capacidade);
    limpar(armazem);
    limpar(lst_plantados);
    limpar(lst_colhidos);
    limpar(removidos);

    capacidade = tamanho_plantacao(diretorio_plantacao);

    plantacao = new horta[capacidade];

    import_plantacao(diretorio_plantacao, diretorio_colhidos, plantacao, capacidade, dia);
    carregar(diretorio_armazem, armazem);
    carregar(diretorio_removidos, removidos);
}

void ImprimirPlantacao(Lista_Produtos& armazem ,horta plantacao[],int capacidade) {
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Lista_Produtos aux;

    SetConsoleTextAttribute(hConsole, 3);
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Plantacao: " << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i_horta = 0; i_horta < capacidade; i_horta++) {
        SetConsoleTextAttribute(hConsole, 6);
        cout << "Horta:" << plantacao[i_horta].nome << " | Responsavel: " << plantacao[i_horta].responsavel << " | Capacidade: " << plantacao[i_horta].capacidade << " | Produtos: " << plantacao[i_horta].plantados.n_produtos << " | Area: " << plantacao[i_horta].area << endl;
        
        SetConsoleTextAttribute(hConsole, 15);
        limpar(aux);
        copiar(plantacao[i_horta].plantados, aux);
        ordenar_nome(aux);
        escrever(aux);
        cout << "-------------------------------------------------" << endl;
    }

    SetConsoleTextAttribute(hConsole, 3);
    cout << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Armazem: " << armazem.n_produtos << " Produtos" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    
    SetConsoleTextAttribute(hConsole, 8);
    copiar(armazem, aux);
    ordenar_nome(aux);
    escrever(aux);
    limpar(aux);
    SetConsoleTextAttribute(hConsole, 3);
}

void ImprimirProdutosColhidos(horta plantacao[], int capacidade) {
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char prod;
    SetConsoleTextAttribute(hConsole, 4);
    cout << "Introduza o ID da Horta desejada" << endl;
    SetConsoleTextAttribute(hConsole, 10);
    cin>>prod;
    for (int i = 0; i < capacidade; i++) {
        if (plantacao[i].nome == prod) {
            SetConsoleTextAttribute(hConsole, 15);
            travessiaInfixa(plantacao[i].colhidos);
            break;
        }
        else if (i == capacidade - 1) {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "O ID e invalido" << endl;
            SetConsoleTextAttribute(hConsole, 3);
        }
    }

}

int CriarArea(std::string*& ary,int tamanho) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	string area = "";
    SetConsoleTextAttribute(hConsole, 4);
	cout << "Indique o nome da noa area: " << endl;
    SetConsoleTextAttribute(hConsole, 10);
	cin.get();
	getline(cin, area);
    int len = tamanho;
    for (int i = 0; i < len; i++) {
        if (ary[i] == area) {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "A Area ja existe!!!" << endl;
            SetConsoleTextAttribute(hConsole, 3);
        }
        else if (i == len - 1) {
            SetConsoleTextAttribute(hConsole, 4);
            tamanho = inserir(ary,0,area,tamanho);
            cout << "Areas disponiveis" << endl;
            SetConsoleTextAttribute(hConsole, 15);
            escrever(ary, tamanho);
            SetConsoleTextAttribute(hConsole, 3);
        }
    }
	return tamanho;
}

void AlterarArea(std::string areas_atuais[],int tamanho_areas_atuais, horta plantacao[], int capacidade,Lista_Produtos& removidos) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char linha;
    string area;
    SetConsoleTextAttribute(hConsole, 4);
	cout << "Indique o ID da Horta" << endl;
	cin.get();
    SetConsoleTextAttribute(hConsole, 10);
	cin>> linha;

    for (int i = 0; i < capacidade; i++) {

        if (plantacao[i].nome == linha) {

            SetConsoleTextAttribute(hConsole, 4);
            cout << "Indique a Area desejada" << endl;
            SetConsoleTextAttribute(hConsole, 10);
            cin.ignore();
            getline(cin,area);
            SetConsoleTextAttribute(hConsole, 3);

            for (int j = 0; j < tamanho_areas_atuais; j++) {
                
                if (area == areas_atuais[j]) {

                    for (int k = 0; k < plantacao[i].plantados.n_produtos; k++) {
                        inserir(removidos, *get(plantacao[i].plantados, k), 0);
                    }
                    limpar(plantacao[i].plantados);
                    plantacao[i].area = area;

                    break;
                }
                else if (j == tamanho_areas_atuais - 1) {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Area Invalida!!!" << endl;
                    SetConsoleTextAttribute(hConsole, 3);
                }
                
            }

            break;
        }
        else if (i == capacidade - 1) {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "ID Invalido!!!" << endl;
            SetConsoleTextAttribute(hConsole, 3);
        }
        
    }
    
}