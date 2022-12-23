#include <iostream>
#include <fstream>
#include <string>
#include "arrays_string.h"
#include "lista_ligada_produtos.h"
#include <iomanip>

void inserir(Lista_Produtos& lista, Produto produto, int indice) {

	if (indice < 0 || indice > lista.n_produtos)
	{
		std::cout << "indice fora do intervalo!";
		std::abort();
	}
	else
	{
		if (indice == 0)
		{
			if (lista.item_base == NULL)
			{
				lista.item_base = new Lista_Produtos::Item;
				lista.item_base->produto = produto;
			}
			else
			{
				Lista_Produtos::Item* novo = new Lista_Produtos::Item;
				novo->seguinte = lista.item_base;
				novo->produto = produto;
				lista.item_base = novo;
			}
		}
		else if (indice == lista.n_produtos)
		{
			Lista_Produtos::Item* iterador;
			iterador = lista.item_base;

			while (iterador->seguinte != NULL)
			{
				iterador = iterador->seguinte;
			}

			Lista_Produtos::Item* novo = new Lista_Produtos::Item;
			iterador->seguinte = novo;
			novo->produto = produto;
		}
		else
		{
			int atual = 0;

			Lista_Produtos::Item* iterador;
			iterador = lista.item_base;

			while (iterador != NULL)
			{
				if (atual == indice - 1)
				{
					Lista_Produtos::Item* novo = new Lista_Produtos::Item;
					novo->seguinte = iterador->seguinte;
					iterador->seguinte = novo;
					novo->produto = produto;

					break;
				}

				iterador = iterador->seguinte;
				atual++;
			}

		}

		lista.n_produtos++;
	}
}

void replace(Lista_Produtos& lista, Produto produto, int indice) {

	if (indice < 0 || indice >= lista.n_produtos)
	{
		std::cout << "indice fora do intervalo!";
		std::abort();
	}
	else
	{
		int atual = 0;

		Lista_Produtos::Item* iterador = lista.item_base;

		while (iterador != NULL)
		{
			if (atual == indice)
			{
				iterador->produto = produto;

				break;
			}

			iterador = iterador->seguinte;
			atual++;
		}	
	}
}

void remover(Lista_Produtos& lista, int indice) {

	if (indice < 0 || indice >= lista.n_produtos)
	{
		std::cout << "indice fora do intervalo!";
		std::abort();
	}
	else
	{
		if (indice == 0)
		{
			Lista_Produtos::Item* auxiliar = lista.item_base->seguinte;

			delete lista.item_base;
			lista.item_base = auxiliar;
		}
		else
		{
			int atual = 0;

			Lista_Produtos::Item* iterador = lista.item_base;

			while (iterador != NULL)
			{
				if (atual == indice-1 )
				{
					Lista_Produtos::Item* auxiliar = iterador->seguinte;
					iterador->seguinte = iterador->seguinte->seguinte;

					delete auxiliar;
				
					break;
				}

				iterador = iterador->seguinte;
				atual++;
			}
		}

		lista.n_produtos--;

	}
}

void limpar(Lista_Produtos& lista) {

	int lim = lista.n_produtos;


	for (int i = 0; i < lim; i++)
	{
		remover(lista);
	}
}

Produto* get(Lista_Produtos& lista, int indice) {

	if (indice < 0 || indice >= lista.n_produtos)
	{
		std::cout << "indice fora do intervalo!";
		std::abort();
	}
	else
	{
		int atual = 0;
		Lista_Produtos::Item* iterador = lista.item_base;

		while (iterador != NULL)
		{
			if (atual == indice) 
			{
				return &iterador->produto;
			}
				
			iterador = iterador->seguinte;
			atual++;

		}
	}

}

int procurar(Lista_Produtos& lista, Produto produto) {

	int atual = 0;
	Lista_Produtos::Item* iterador = lista.item_base;

	while (iterador != NULL)
	{
		if (Produto_igual(produto,iterador->produto))
		{
			return atual;
		}

		iterador = iterador->seguinte;
		atual++;

	}

	return -1;

}

void modificar_tempo_de_rega(Lista_Produtos& lista, std::string nome, int novo_tempo) {

	Lista_Produtos::Item* iterador = lista.item_base;

	while (iterador != NULL)
	{
		if (nome == iterador->produto.nome)
		{
			iterador->produto.tempo_rega = novo_tempo;
		}

		iterador = iterador->seguinte;
		
	}

}

void escrever(Lista_Produtos& lista) {

	Lista_Produtos::Item* iterador = lista.item_base;

	while (iterador != NULL)
	{
		std::cout << "Nome: " << iterador->produto.nome << " | " 
				  << "Rega: " << iterador->produto.tempo_rega << " | "
				  << "Resistencia: "<< std::setprecision(3) << iterador->produto.resistência << " | "
			      << "Area: " << iterador->produto.area << " | " 
				  << "Fornecedor:" << iterador->produto.fornecedor << "\n"; 

		iterador = iterador->seguinte;
	}
}

void escrever(Lista_Produtos& lista, int lim) {
	
	Lista_Produtos::Item* iterador = lista.item_base;
	int contador = 0;

	while (iterador != NULL && contador < lim)
	{
		std::cout << "Nome: " << iterador->produto.nome << " | "
			<< "Rega: " << iterador->produto.tempo_rega << " | "
			<< "Resistencia: " << iterador->produto.resistência << " | "
			<< "Area: " << iterador->produto.area << " | " << "Fornecedor:"
			<< iterador->produto.fornecedor << "\n"; //////->

		iterador = iterador->seguinte;
		contador++;
	}
}

void guardar(std::string ficheiro, Lista_Produtos& lista) {

	std::fstream file(ficheiro, std::fstream::out);

	if (file.is_open() && file.good()) {

		try {

			int lim = lista.n_produtos;

			for (int i = 0; i < lim; i++)
			{
				std::string str = Produto_To_String(*get(lista, i)) + '\n';
				file.write(str.c_str(), str.length());
			}

		}
		catch(std::exception e)
		{
			std::cout << "Nao foi posivel gravar !!!" << std::endl;
		}
		
		file.close();
	}
	else {
		std::cout << "O ficheiro está corronpido ou não foi aberto corretamente" << std::endl;
		file.close();
	}

}

void carregar(std::string ficheiro, Lista_Produtos& lista) {

	std::fstream file(ficheiro, std::fstream::in);

	if (file.is_open() && file.good()) {

		std::string linha = "";
	
		while (true) {

			getline(file, linha);
			if (linha == "")
				break;

				inserir(lista, String_To_Produto(linha), lista.n_produtos);
	
		}
		file.close();

	}
	else {
		std::cout << "Nao foi posivel carregar!" << '\n' << "Porque ficheiro está corronpido ou nao foi aberto corretamente !" << std::endl;
		file.close();
	}

}

void trocar(Lista_Produtos& lista, int indice_a, int indice_b) {

	if (indice_a < 0 || indice_a >= lista.n_produtos || indice_b < 0 || indice_b >= lista.n_produtos)
	{
		std::cout << "indice fora do intervalo!";
		std::abort();
	}
	else
	{
		Produto auxiliar = *get(lista, indice_a);
		replace(lista, *get(lista, indice_b), indice_a);
		replace(lista, auxiliar, indice_b);
	}
}

void ordenar_nome(Lista_Produtos& lista) {

	bool trocado = true;
	std::string str_anterior = "", str_atual = "";

	for (int i = 0; i < lista.n_produtos && trocado; i++)
	{
		trocado = false;
		for (int j = lista.n_produtos - 1; j > i; j--)
		{

			str_anterior = get(lista,j-1)->nome;
			trim(str_anterior);
			to_lower(str_anterior);

			str_atual = get(lista,j)->nome;
			trim(str_atual);
			to_lower(str_atual);

			if (str_atual < str_anterior)
			{
				trocar(lista, j, j - 1);
				trocado = true;
			}
		}
	}
}

// Funções para o armazem 
void inicializar_armazem(Lista_Produtos& lista , int quantidade , std::string nomes[], std::string fornecedores[], std::string areas[], int tamanho_nomes, int tamanho_fornecedores, int tamanho_areas) {

	Produto p;
	for (int i = 0; i < quantidade; i++)
	{
		inserir(lista, criar_Produto_aleatorio(nomes, fornecedores, areas, tamanho_nomes, tamanho_fornecedores, tamanho_areas), lista.n_produtos);
	}

}

void copiar(Lista_Produtos& lista_a, Lista_Produtos& lista_b) {

	Lista_Produtos::Item* iterador = lista_a.item_base;

	while (iterador != NULL)
	{
		inserir(lista_b, iterador->produto, lista_b.n_produtos);
		iterador = iterador->seguinte;
	}

}