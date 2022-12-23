#pragma once
#include "Produto.h"

struct Lista_Produtos {

	struct Item
	{
		Produto produto;
		Item* seguinte = NULL;
	};

	Item* item_base = NULL;
	int n_produtos = 0;

};

//insere um novo prosuto numa posição
void inserir(Lista_Produtos& lista, Produto produto, int indice = 0);
//troca o elemento de uma posição
void replace(Lista_Produtos& lista, Produto produto, int indice = 0);
//remove o produto de um dado indice
void remover(Lista_Produtos& lista, int indice = 0);
//retorna o produto de um dado indice
Produto* get(Lista_Produtos& lista, int indice);
//limpa a lista toda
void limpar(Lista_Produtos& lista);
//inmprime na consola 
void escrever(Lista_Produtos& lista);
void escrever(Lista_Produtos& lista, int lim);
//guarda no fincehiro
void guardar(std::string ficheiro, Lista_Produtos& lista);
//carrega
void carregar(std::string ficheiro, Lista_Produtos& lista);
//devolve o indice do 1 produto igual ao produto;
int procurar(Lista_Produtos& lista, Produto produto);
//altera o tempo de rega de um produto;
void modificar_tempo_de_rega(Lista_Produtos& lista, std::string nome, int novo_tempo);
//troca produtos de posições 
void trocar(Lista_Produtos& lista, int indice_a, int indice_b);
//
void copiar(Lista_Produtos& lista_a, Lista_Produtos& lista_b);
//ordenar 
void ordenar_nome(Lista_Produtos& lista);

//Funções para o armazem
void inicializar_armazem(Lista_Produtos& lista, int quantidade, std::string nomes[], std::string fornecedores[], std::string areas[], int tamanho_nomes, int tamanho_fornecedores, int tamanho_areas);

