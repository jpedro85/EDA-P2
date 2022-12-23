#include <iostream>
#include "Produto.h"
#include <stdlib.h>
#include <time.h>
#include "arrays_string.h"
//string esta incluido no .h

void copiar(Produto& a, Produto& b) {

	b.area = a.area;
	b.fornecedor = a.fornecedor;
	b.nome = a.nome;
	b.resistência = a.resistência;
	b.tempo_plantação = a.tempo_plantação;
	b.tempo_rega = a.tempo_rega;

}

bool Produto_igual(Produto& a, Produto& b) {
	
	return a.area == b.area && a.nome == b.nome && a.fornecedor == b.fornecedor && a.resistência == b.resistência && a.tempo_plantação == b.tempo_plantação && a.tempo_rega == b.tempo_rega;
}

Produto criar_Produto_aleatorio(std::string nomes[], std::string fornecedores[], std::string areas[], int tamanho_nomes, int tamanho_fornecedores, int tamanho_areas) {

	int indice_Produtos = rand() % (tamanho_nomes);
	int indice_fornecedores = rand() % (tamanho_fornecedores);
	int indice_areas = rand() % (tamanho_areas);
	float floor = 0.2;
	float ceiling = 0.8;
	float range = (ceiling - floor);
	float rnd = floor + (range * rand()) / (RAND_MAX + 1.0); //rand()/rand_max vai de 0 a 1 inclusive e multiplicando pelo range vai permitir ter um numero entre 0 a 0.6 e somando 0.2 da 0.2 a 0.8
	
	Produto p;
	p.nome = nomes[indice_Produtos];
	p.area = areas[indice_areas];
	p.fornecedor = fornecedores[indice_fornecedores];
	p.tempo_rega = 1 + rand() % 5;
	p.resistência = rnd;
	p.tempo_plantação = 0;
	return p;
}

Produto criar_Produto(std::string nome, std::string area, std::string fornecedor,int restencia, int tempo_plantação, int tempo_rega) {

	Produto novo;
	novo.nome = nome;
	novo.area = area;
	novo.fornecedor = fornecedor;
	novo.resistência = restencia;
	novo.tempo_plantação = tempo_plantação;
	novo.tempo_rega = tempo_rega;

	return novo;
}

std::string Produto_To_String(Produto produto) {

	std::string str = produto.nome + ';' 
					+ produto.area + ';' 
					+ produto.fornecedor + ';' 
					+ std::to_string(produto.resistência) + ';'
					+ std::to_string(produto.tempo_plantação) + ';'
					+ std::to_string(produto.tempo_rega);

	return str;
}

Produto String_To_Produto(std::string produto) {

	Produto novo;

	try {

		//stoi converte de string para int microsoft c++ reference
		//substr devolve uma substring da string;

		novo.nome = produto.substr(0, produto.find(';'));
		produto = produto.substr(produto.find(';') + 1, produto.length() - 1);

		novo.area = produto.substr(0, produto.find(';'));
		produto = produto.substr(produto.find(';') + 1, produto.length() - 1);

		novo.fornecedor = produto.substr(0, produto.find(';'));
		produto = produto.substr(produto.find(';') + 1, produto.length() - 1);

		novo.resistência = stof(produto.substr(0, produto.find(';')));
		produto = produto.substr(produto.find(';') + 1, produto.length() - 1);

		novo.tempo_plantação = stof(produto.substr(0, produto.find(';')));
		produto = produto.substr(produto.find(';') + 1, produto.length() - 1);

		novo.tempo_rega = stof(produto.substr(0, produto.find(';')));
		produto = produto.substr(produto.find(';') + 1, produto.length() - 1);

		return novo;

	}catch(std::exception e)
	{
		std::cout << "Nao foi possivel carregar produto" << std::endl;
		std::abort();
	}
	
}

