#pragma once
#include <string>

struct Produto
{
	std::string nome = "";
	std::string area = "";
	std::string fornecedor;
	int tempo_rega = 1; // ciclo +1 % plantado 
	int tempo_plantação = 0;
	float resistência = 0;
};

//copia o Produto a para b
void copiar(Produto& a,Produto& b);
//devolve true se os produtos forem iguais
bool Produto_igual(Produto& a, Produto& b);
//criao um produto aleatório
Produto criar_Produto_aleatorio(std::string nomes[], std::string fornecedores[], std::string areas[], int tamanho_nomes, int tamanho_fornecedores, int tamanho_areas);
//criao um produto se não dor dado argumentos cria o produto vazio
Produto criar_Produto(std::string nome = "Nulo", std::string area = "Nulo", std::string fornecedor = "Nulo", int restencia = 0, int tempo_plantação = 0, int tempo_rega = 0);
//Transforma um Produto em string do formato: nome,area,fornecedor,res..,temp_plantação,temp_rega
std::string Produto_To_String(Produto produto);
//Transforma uma string do formato: nome,area,fornecedor,res..,temp_plantação,temp_rega para Produto
Produto String_To_Produto(std::string produto);


