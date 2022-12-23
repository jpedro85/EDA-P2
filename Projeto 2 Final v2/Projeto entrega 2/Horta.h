#pragma once
#include <string>
#include "Produto.h"
#include "Arvore.h"
#include "lista_ligada_produtos.h"

struct horta
{
    char nome = NULL;//id da horta (A,B,C,...)
    std::string area = "";//aletorio do array de areas
    std::string responsavel = "";//inserido pelo utilizador
    int capacidade = 3;//quantidade de produtos que pode ter na horta
    int n_colhidos = 0;
    Lista_Produtos plantados;
    colhidos* colhidos = NULL;

};

//lista dos Ids das hortas
const char id[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
//cria uma horta para ser adicionada a plantaçao
horta criar_horta(std::string areas[], int tamanho_areas, char id);
//cria a plantaçao no inicio do programa
void inicializar_plantacao(horta plantacao[], std::string areas[], int tamanho_areas, const char id[], int capacidade_hortas);
//adiciona á plantação
int adicionar_produtos_plantacao(Lista_Produtos& lista_armazem, Lista_Produtos& lst_plantados, horta plantacao[], int capacidade);
//limpa
void limpar_plantacao(horta*& plantacao, int capacidade);
//escreve a plantação
void escrever_plantacao(horta plantacao[], int capacidade_hortas);

//executar ciclo
void executar_ciclo(horta plantacao[], int capacidade, Lista_Produtos& lst_perdidos, Lista_Produtos& lst_colhidos, int ciclos);

//saves
void save_plantacao(std::string directory, std::string diretorio_colhidos, horta plantacao[], int capacidade_hortas, int dia);

//imports
void import_plantacao(std::string directory, std::string directory_colhidos, horta plantacao[], int capacidade_hortas, int& dia);

int tamanho_plantacao(std::string nome);

int remover_da_plantacao_colheita(horta plantacao[], int capacidade, std::string nome, Lista_Produtos& lst_colhidos);

void tempo_rega_plantacao(horta plantacao[], std::string nome, int capacidade, int novo_tempo);