#include <iostream>
#include <string>
#include "Funcoes.h"
#include "horta.h"
#include "Produto.h"
#include "files.h"
#include "arrays_string.h"
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[]) {

    string Produtos_diretorio = "";
    string Areas_diretorio = "";
    string Fornecedores_diretorio = "";
    string Armazem_diretorio = "";
    string Plantacao_diretorio = "";
    string Colhidos_diretorio = "";
    string Removidos_diretorio = "";

    if (argc == 8) {

        Produtos_diretorio = argv[1];
        Areas_diretorio = argv[2];
        Fornecedores_diretorio = argv[3];
        Armazem_diretorio = argv[4];
        Plantacao_diretorio = argv[5];
        Colhidos_diretorio = argv[6];
        Removidos_diretorio = argv[7];

    }
    else {

        Produtos_diretorio = "Produtos.txt";
        Areas_diretorio = "Areas.txt";
        Fornecedores_diretorio = "Fornecedores.txt";
        Armazem_diretorio = "Armazem.txt";
        Plantacao_diretorio = "Plantacao.txt";
        Colhidos_diretorio = "Colhidos.txt";
        Removidos_diretorio = "Perdidos.txt";
    }


    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //carregar Produtos
    int tamanho_produtos = tamanho(Produtos_diretorio);
    string* produtos = new string[tamanho_produtos];
    import_files(Produtos_diretorio, produtos);

    //carregar Areas
    int tamanho_areas = tamanho(Areas_diretorio);
    string* areas = new string[tamanho_areas];
    import_files(Areas_diretorio, areas);

    ///carregar Fornecedores
    int tamanho_forneecedores = tamanho(Fornecedores_diretorio);
    string* fornecedores = new string[tamanho_forneecedores];
    import_files(Fornecedores_diretorio, fornecedores);

    //inicializar plantação
    int capacidade = 5 + rand() % 6;
    horta* plantacao = new horta[capacidade];
    inicializar_plantacao(plantacao, areas, tamanho_areas, id, capacidade);

    //inicializar armazem
    Lista_Produtos armazem;
    inicializar_armazem(armazem, 15, produtos, fornecedores, areas, tamanho_produtos, tamanho_forneecedores, tamanho_areas);

    //criação da lista de removidos
    Lista_Produtos lst_removidos; // executar cico gravar plantação
    Lista_Produtos lst_colhidos;
    Lista_Produtos lst_plantados;

    system("CLS");

    escrever_plantacao(plantacao, capacidade);
    cout << endl;

    cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Armazem: " << armazem.n_produtos <<endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, 8);
    escrever(armazem);
    SetConsoleTextAttribute(hConsole, 3);
    cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    //vars auxiliares
    char choice = 'N';//seguinte ou gestor
    bool in_gestor = false;
    int dia = 0, plantados = 0, perdidos = 0;

    do {

        escrever_opcoes(choice);

        if (choice == 'g')
        {

            do {

                cout << endl;
                SetConsoleTextAttribute(hConsole, 3);
                cout << "* Bem Vindo Gestor **" << endl;
                SetConsoleTextAttribute(hConsole, 15);
                cout << "(1) .Colher Produto" << endl;
                cout << "(2) .Atualizar Tempo de rega" << endl;
                cout << "(3) .Gravar Plantacao" << endl;
                cout << "(4) .Carregar plantacao" << endl;
                cout << "(5) .Imprimir Plantacao" << endl;
                cout << "(6) .Imprimir produtos colhidos" << endl;
                cout << "(7) .Criar nova area" << endl;
                cout << "(8) .Alterar area" << endl;
                cout << "(0) .Voltar" << endl;
                SetConsoleTextAttribute(hConsole, 4);
                cout << "Seleccione a sua opcao" << endl;
                SetConsoleTextAttribute(hConsole, 10);
                cin >> choice;
                SetConsoleTextAttribute(hConsole, 3);
                system("CLS");

                switch (choice)
                {
                    case '1':

                        menu_title("Escolheu Colher Produto");

                        ColherProduto(plantacao, capacidade,lst_colhidos);

                        escrever_dia(armazem, lst_colhidos, lst_removidos, lst_plantados, plantados, perdidos, plantacao, capacidade, dia);

                        in_gestor = false;
                        break;
                    case '2':
                        menu_title("Escolheu Atualizar Tempo de rega");
                        
                        AtualizarRega(armazem, plantacao, capacidade);

                        escrever_dia(armazem, lst_colhidos, lst_removidos, lst_plantados, plantados, perdidos, plantacao, capacidade, dia);

                        in_gestor = false;
                        break;
                    case '3':
                        menu_title("Escolheu Gravar Plantacao");
                        
                        GravarPlantacao(plantacao, capacidade, armazem, lst_removidos, Plantacao_diretorio, Colhidos_diretorio, Armazem_diretorio, Removidos_diretorio, dia);
                        save_file(Areas_diretorio, areas, tamanho_areas);
                        
                        escrever_plantacao(plantacao, capacidade);
                        cout << endl;
                        cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        cout << "Armazem " << armazem.n_produtos << endl;
                        cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        SetConsoleTextAttribute(hConsole, 8);
                        escrever(armazem);
                        SetConsoleTextAttribute(hConsole, 3);
                        cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;

                        in_gestor = false;
                        break;
                    case '4':
                        menu_title("Escolheu Carregar plantacao");
                        
                        CarregarPlantacao(plantacao, capacidade, armazem, lst_removidos, lst_colhidos, lst_plantados, Plantacao_diretorio, Colhidos_diretorio, Armazem_diretorio, Removidos_diretorio, dia);
                        delete[]areas;
                        tamanho_areas = tamanho(Areas_diretorio);
                        areas = new string[tamanho_areas];
                        import_files(Areas_diretorio, areas);

                        perdidos = 0;
                        plantados = 0;

                        escrever_dia(armazem, lst_colhidos, lst_removidos, lst_plantados, plantados, perdidos, plantacao, capacidade, dia);
                     
                        in_gestor = false;
                        break;
                    case '5':
                        menu_title("Escolheu Imprimir plantacao");
                       
                        ImprimirPlantacao(armazem, plantacao, capacidade);

                        escrever_opcoes(choice);

                        in_gestor = false;
                        break;
                    case '6':
                        menu_title("Escolheu Imprimir produtos colhidos");

                        ImprimirProdutosColhidos(plantacao, capacidade);

                        in_gestor = false;
                        break;
                    case '7':
                        menu_title("Escolheu Criar nova area");

                        tamanho_areas = CriarArea(areas, tamanho_areas);

                        in_gestor = false;
                        break;
                    case '8':
                        
                        menu_title("Escolheu Alterar area");

                        AlterarArea(areas, tamanho_areas, plantacao, capacidade, lst_removidos);

                        escrever_dia(armazem, lst_colhidos, lst_removidos, lst_plantados, plantados, perdidos, plantacao, capacidade, dia);
                        escrever_opcoes(choice);

                        in_gestor = false;
                        break;
                    case '0':

                        menu_title("Escolheu Voltar");

                        if (dia != 0) {
                            escrever_dia(armazem, lst_colhidos, lst_removidos, lst_plantados, plantados, perdidos, plantacao, capacidade, dia);
                        }
                        else
                        {
                           
                            escrever_plantacao(plantacao, capacidade);
                            cout << endl;
                            SetConsoleTextAttribute(hConsole, 3);
                            cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                            cout << "Armazem" << armazem.n_produtos <<endl;
                            cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                            SetConsoleTextAttribute(hConsole, 8);
                            escrever(armazem);
                            SetConsoleTextAttribute(hConsole, 3);
                            cout << "---------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        }

                        in_gestor = false;
                        break;

                    default:
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "A sua escolha tem de ser entre 0 e 9!!!." << endl;
                        SetConsoleTextAttribute(hConsole, 3);
                        in_gestor = true;

                }

            } while (in_gestor || choice == 'g');

        }
        else if (choice == 's')
        {
           
            dia++;

            system("CLS");

            SetConsoleTextAttribute(hConsole, 11);
            cout << "Escolheu simular dia seguinte !!" << endl << endl;
            cout << endl;
            SetConsoleTextAttribute(hConsole, 3);

            perdidos = lst_removidos.n_produtos;

            executar_ciclo(plantacao, capacidade, lst_removidos, lst_colhidos, dia);

            inicializar_armazem(armazem, 10, produtos, fornecedores, areas, tamanho_produtos, tamanho_forneecedores, tamanho_areas);

            plantados = adicionar_produtos_plantacao(armazem,lst_plantados, plantacao, capacidade);

            escrever_dia(armazem, lst_colhidos, lst_removidos, lst_plantados, plantados, perdidos, plantacao, capacidade, dia);
            
        }
		else
		{
			SetConsoleTextAttribute(hConsole, 4);
            cout << "Opcao invalida !!!" << endl;
            SetConsoleTextAttribute(hConsole, 3);
		}
    } while (choice != 'f');
    cout << "A fechar o programa!!!" << endl;

}
