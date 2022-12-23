#include "Horta.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "arrays_string.h"
#include <Windows.h>
#include <iomanip>


 // na horta.h #include "Armazem.h" ,  Prosuto.h

using namespace std;

horta criar_horta(std::string areas[],int tamanho_areas, char id){
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 6);
    horta h;
    int indice_areas = rand() % tamanho_areas;
    h.area = areas[indice_areas];
    h.capacidade = 3 + rand() % 6;
    h.nome = id;
    string responsavel="";

    cout << "Escreva o nome do responsavel da horta "<<id<<" ." << endl;
    SetConsoleTextAttribute(hConsole, 10);
    getline(cin, responsavel);
    h.responsavel = responsavel;
  
    return h;
}

void inicializar_plantacao(horta plantacao[], std::string areas[], int tamanho_areas, const char id[], int capacidade_hortas) {
   
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "A criar hortas :" << endl;

    for (int i = 0; i < capacidade_hortas; i++) {
        plantacao[i] = criar_horta(areas, tamanho_areas, id[i]);
    }
}

int adicionar_produtos_plantacao(Lista_Produtos& lista_armazem, Lista_Produtos& lst_plantados, horta plantacao[], int capacidade) {

    limpar(lst_plantados);

    Produto auxiliar;
    int contador = 0, i_produto = 0;
    bool removido = false;

    while ( i_produto < lista_armazem.n_produtos && contador < 10)
    {
        auxiliar = *get(lista_armazem, i_produto);
        removido = false;

        for (int i_horta = 0; i_horta < capacidade; i_horta++)
        {

            if ( plantacao[i_horta].area == auxiliar.area && plantacao[i_horta].plantados.n_produtos + 1 <= plantacao[i_horta].capacidade)
            {
                inserir(lst_plantados, auxiliar, lst_plantados.n_produtos);
                inserir(plantacao[i_horta].plantados, auxiliar, plantacao[i_horta].plantados.n_produtos);
                remover(lista_armazem, i_produto);
                removido = true;
                contador++;

                break;
                
            }

        }
        
        if (!removido) 
        {
            i_produto++;
        }       
    }

    return contador;
}

int remover_da_plantacao(horta& hortinha, int capacidade, Produto produto) {

    int i_produto = 0, contador = 0;
    Produto auxiliar;

    while (i_produto < hortinha.plantados.n_produtos)
    {
        auxiliar = *get(hortinha.plantados, i_produto);

        if (Produto_igual(auxiliar,produto)) 
        {
            hortinha.colhidos = inserirColhidos(hortinha.colhidos, auxiliar);
            remover(hortinha.plantados, i_produto);
            contador++;
        }
        else
            i_produto++;
    }
   
    return contador;
}

int remover_da_plantacao_colheita(horta plantacao[], int capacidade, string nome , Lista_Produtos& lst_colhidos) {

    int i_produto = 0, contador = 0;
    Produto auxiliar;

    for (int i_horta = 0; i_horta < capacidade; i_horta++)
    {
        i_produto = 0;
        while (i_produto < plantacao[i_horta].plantados.n_produtos)
        {
            auxiliar = *get(plantacao[i_horta].plantados, i_produto);

            if (nome ==  auxiliar.nome) {

                inserir(lst_colhidos,auxiliar,lst_colhidos.n_produtos);
                plantacao[i_horta].colhidos = inserirColhidos(plantacao[i_horta].colhidos, auxiliar);
                remover(plantacao[i_horta].plantados, i_produto);
                contador++;
            }
            else
                i_produto++;
        }
    } 

    return contador;
}

void limpar_plantacao(horta*& plantacao,int capacidade) {

    for ( int len = 0 ; len < capacidade; len++)
    {

        deleteArvore(plantacao[len].colhidos);

        if (plantacao[len].plantados.n_produtos != 0)
        {
            limpar(plantacao[len].plantados);
        }
           
    }

    delete[]plantacao;
    plantacao = NULL;


}

void tempo_rega_plantacao(horta plantacao[], std::string nome, int capacidade, int novo_tempo) {
    
    for (int i = 0; i < capacidade; i++) {
        modificar_tempo_de_rega(plantacao[i].plantados, nome, novo_tempo);
    }

}

void escrever_plantacao(horta plantacao[], int capacidade_hortas) {
   
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 3);
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Plantacao:" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;


    Produto produto;
    for (int i_horta = 0; i_horta < capacidade_hortas; i_horta++) {
        
        SetConsoleTextAttribute(hConsole, 6);
        cout << "Horta:" << plantacao[i_horta].nome << " | Responsavel: " << plantacao[i_horta].responsavel << " | Capacidade: " << plantacao[i_horta].capacidade << " | Produtos: " << plantacao[i_horta].plantados.n_produtos << " | Area: " << plantacao[i_horta].area << endl;
        SetConsoleTextAttribute(hConsole, 15);
        for (int i_produto = 0; i_produto < plantacao[i_horta].plantados.n_produtos; i_produto++)
        {
            produto = *get(plantacao[i_horta].plantados, i_produto);
            cout << "Produto: " << produto.nome
                << " | Rega : " << produto.tempo_rega
                << " | Resistencia: " << setprecision(3) << produto.resistência
                << " | Tempo: " << produto.tempo_plantação
                << " | Fornecedor" << produto.fornecedor << endl;

        }
        cout << "-------------------------" << endl;
    }

    SetConsoleTextAttribute(hConsole, 3);
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

}

//ciclo
void executar_ciclo(horta plantacao[], int capacidade, Lista_Produtos& lst_perdidos, Lista_Produtos& lst_colhidos, int ciclos) {

    int i_produto = 0;
    Produto* temporario;
    Produto* temporarioteste;

    limpar(lst_colhidos);
    
    for (int i_horta = 0; i_horta < capacidade; i_horta++)
    {
        i_produto = 0;
        while(i_produto < plantacao[i_horta].plantados.n_produtos)
        {
            
            temporario = get(plantacao[i_horta].plantados, i_produto);

            if ((1 + rand() % 100) <= 25) //probabilidade de ser colhido
            {   
               
                plantacao[i_horta].colhidos = inserirColhidos(plantacao[i_horta].colhidos, *temporario);

                inserir(lst_colhidos, *temporario);

                temporarioteste = get(plantacao[i_horta].plantados, i_produto);
                remover(plantacao[i_horta].plantados, i_produto);

            }
            else
            {
                if (((ciclos + 1) % temporario->tempo_rega) == 0 && (rand() / (RAND_MAX + 1.0)) < (1 - temporario->resistência)) // pragas
                {
                    inserir(lst_perdidos, *temporario);

                    temporarioteste = get(plantacao[i_horta].plantados, i_produto);
                    remover(plantacao[i_horta].plantados, i_produto);
                }
                else {

                    temporario->tempo_plantação++;
                    temporario = NULL;
                    i_produto++;
                }
            }
        }
    }
}


//saves
void save_produto(colhidos* raiz, fstream& file) {
    if (!raiz) return;
    file << raiz->produto.nome << " ; " << raiz->produto.fornecedor << " ; " << raiz->produto.area << " ; " << raiz->produto.resistência << " ; " << raiz->produto.tempo_plantação << " ; " << raiz->produto.tempo_rega << endl;
    save_produto(raiz->esquerda, file);
    save_produto(raiz->direita, file);
}

void save_colhidos(std::string directory, horta plantacao[], int capacidade_hortas) {
    fstream colhidos;
    int i = 0;
    colhidos.open(directory, std::fstream::out);
    if (colhidos.is_open())
    {
        for (int i = 0; i < capacidade_hortas; i++)
        {
            colhidos << plantacao[i].nome << endl;
            save_produto(plantacao[i].colhidos, colhidos);
            colhidos << endl;
        }
    }
    colhidos.close();
}

void save_plantacao(std::string directory, std::string diretorio_colhidos, horta plantacao[], int capacidade_hortas,int dia) {

    fstream file;

    file.open(directory, fstream::out);

    if (file.is_open()) {

        save_colhidos(diretorio_colhidos, plantacao, capacidade_hortas);
        file << dia << endl;
        for (int i = 0; i < capacidade_hortas; i++)
        {
            file << plantacao[i].nome << " ; "
                << plantacao[i].responsavel << " ; "
                << plantacao[i].capacidade << " ; "
                << plantacao[i].area << " ; "
                << plantacao[i].n_colhidos << " ; "
                << plantacao[i].plantados.n_produtos << endl;

            int lim = plantacao[i].plantados.n_produtos;

            for (int j = 0; j < lim; j++)
            {
                std::string str = Produto_To_String(*get(plantacao[i].plantados, j)) + '\n';
                file.write(str.c_str(), str.length());
            }

            file << endl;
        }

    }
    file.close();
}

void import_colhidos(std::string directory, horta plantacao[], int capacidade_horta) {
    fstream colhidos;
    int i = 0;
    char ID;
    string line = "";
    string produto = "";
    string area = "";
    string fornecedor = "";
    int tempo_rega = 0;
    float resistencia = 0;
    int tempo_plantacao = 0;
    Produto temp;

    colhidos.open(directory, std::fstream::in);
    if (colhidos.is_open())
    {
        while (i < capacidade_horta)
        {
            getline(colhidos, line);
            if (line == "") {
                continue;
            }
            ID = line[0];
            while (true)
            {
                getline(colhidos, line);
                if (line == "")
                {
                    break;
                }
                produto = line.substr(0, line.find(';') - 1);
                line = line.substr(line.find(';') + 2, line.length() - 1);
                fornecedor = line.substr(0, line.find(';') - 1);
                line = line.substr(line.find(';') + 2, line.length() - 1);
                area = line.substr(0, line.find(';') - 1);
                line = line.substr(line.find(';') + 2, line.length() - 1);
                resistencia = stof(line.substr(0, line.find(';')));
                line = line.substr(line.find(';') + 2, line.length() - 1);
                tempo_plantacao = stoi(line.substr(0, line.find(';')));
                line = line.substr(line.find(';') + 2, line.length() - 1);
                tempo_rega = stoi(line.substr(0, line.find(';')));
                temp.nome = produto;
                temp.fornecedor = fornecedor;
                temp.area = area;
                temp.resistência = resistencia;
                temp.tempo_plantação = tempo_plantacao;
                temp.tempo_rega = tempo_rega;
                plantacao[i].colhidos = inserirColhidos(plantacao[i].colhidos, temp);
            }
            i++;
        }
    }
    colhidos.close();
}

void import_plantacao(std::string directory, std::string directory_colhidos, horta plantacao[], int capacidade_hortas,int& dia) {
    
    fstream file;
    string line;
    char ID;
    string responsavel = "";
    int capacidade_da_horta = 0;
    string area = "";
    int n_plantados = 0;
    int n_colhidos = 0;
    int i = 0;
    string fornecedor = "";

    file.open(directory, fstream::in);
    if (file.is_open()) {
        import_colhidos(directory_colhidos, plantacao, capacidade_hortas);
        
        getline(file, line);
        dia = stoi(line);

        for (int i = 0; i < capacidade_hortas; i++)
        {
            getline(file, line);
            ID = line.substr(0, line.find(';') - 1)[0];
            line = line.substr(line.find(';') + 2, line.length() - 1);
            responsavel = line.substr(0, line.find(';') - 1);
            line = line.substr(line.find(';') + 2, line.length() - 1);
            capacidade_da_horta = stoi(line.substr(0, line.find(';')));
            line = line.substr(line.find(';') + 2, line.length() - 1);
            area = line.substr(0, line.find(';') - 1);
            line = line.substr(line.find(';') + 2, line.length() - 1);
            n_colhidos = stoi(line.substr(0, line.find(';')));

            plantacao[i].nome = ID;
            plantacao[i].responsavel = responsavel;
            plantacao[i].capacidade = capacidade_da_horta;
            plantacao[i].area = area;
            plantacao[i].n_colhidos = n_colhidos;
            while (true) {

                getline(file, line);
                if (line == "") {
                    break;
                }
                inserir(plantacao[i].plantados, String_To_Produto(line), plantacao[i].plantados.n_produtos);

            }
        }
    }
}

int tamanho_plantacao(std::string nome) {
    fstream ficheiro;
    string line;
    int i = 0;
    ficheiro.open(nome, ifstream::in);
    if (ficheiro.is_open()) {
        while (getline(ficheiro, line)) {
            if (line == "") i++;
        }
    }
    ficheiro.close();
    return i;
}