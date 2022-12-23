#pragma once
#include "lista_ligada_produtos.h"
#include "Horta.h"

void menu_title(std::string titulo);

void escrever_opcoes(char& choice);

void escrever_dia(Lista_Produtos& armazem, Lista_Produtos& lst_colhidos, Lista_Produtos& lst_removidos, Lista_Produtos& lst_plantados, int plantados, int perdidos, horta plantacao[], int capacidade, int dia);

void ColherProduto(horta ary[], int tamanho, Lista_Produtos& lst_colhidos);

void AtualizarRega(Lista_Produtos& armazem, horta plantacao[], int capacidade);

void GravarPlantacao(horta plantacao[], int capacidade, Lista_Produtos& armazem, Lista_Produtos& removidos, std::string diretorio_plantacao, std::string diretorio_colhidos, std::string diretorio_armazem, std::string diretorio_removidos, int dia);

void CarregarPlantacao(horta*& plantacao, int& capacidade, Lista_Produtos& armazem, Lista_Produtos& removidos, Lista_Produtos& lst_colhidos, Lista_Produtos& lst_plantados, std::string diretorio_plantacao, std::string diretorio_colhidos, std::string diretorio_armazem, std::string diretorio_removidos, int& dia);

void ImprimirPlantacao(Lista_Produtos& armazem, horta plantacao[], int capacidade);

void ImprimirProdutosColhidos(horta plantacao[], int capacidade);

int CriarArea(std::string*& ary, int tamanho);

void AlterarArea(std::string areas_atuais[], int tamanho_areas_atuais, horta plantacao[], int capacidade, Lista_Produtos& removidos);