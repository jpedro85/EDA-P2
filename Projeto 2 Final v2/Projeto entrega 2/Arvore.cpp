#include "Arvore.h"
#include "arrays_string.h"
#include <iomanip>
#include <iostream>


using namespace std;

colhidos* novoColhidos(Produto produto) {
	colhidos* novo = new colhidos;
	novo->produto = produto;
	novo->direita = NULL;
	novo->esquerda = NULL;
	return novo;
}

colhidos* inserirColhidos(colhidos* raiz, Produto produto) {
	string copia;
	string copia2;
	if (raiz == NULL) {
		return raiz = novoColhidos(produto);
	}
	else
	{
		copia = raiz->produto.nome;
		copia2 = produto.nome;
		trim(copia);
		trim(copia2);
		to_lower(copia);
		to_lower(copia2);
		if (copia2 <= copia)
		{
			raiz->esquerda = inserirColhidos(raiz->esquerda, produto);
		}
		else
		{
			raiz->direita = inserirColhidos(raiz->direita, produto);
		}
	}
	return raiz;
}

int altura(colhidos* produto) {
	if (produto == NULL) {
		return 0;
	}
	int altE = altura(produto->esquerda);
	int altD = altura(produto->direita);
	if (altE > altD) {
		return altE + 1;
	}
	else
	{
		return altD + 1;
	}
}

int contaNos(colhidos* produto) {
	if (produto == NULL)
	{
		return 0;
	}
	int nosE = contaNos(produto->esquerda);
	int nosD = contaNos(produto->direita);
	return nosE + nosE + 1;
}
//R,E,D
void travessiaPrefixa(colhidos* no) {
	if (no == NULL)
	{
		return;
	}
	cout << "Nome: " << no->produto.nome << " | " << "Rega: " << no->produto.tempo_rega << " | " << "Resistencia: " << setprecision(3) << no->produto.resistência << " | " << "Area: " << no->produto.area << " | " << "Fornecedor:" << no->produto.fornecedor << std::endl;
	travessiaPrefixa(no->esquerda);
	travessiaPrefixa(no->direita);
}
//E,R,D
void travessiaInfixa(colhidos* no) {
	if (no == NULL) {
		return;
	}
	travessiaInfixa(no->esquerda);
	cout << "Nome: " << no->produto.nome << " | " << "Rega: " << no->produto.tempo_rega << " | " << "Resistencia: " << setprecision(3) << no->produto.resistência << " | " << "Area: " << no->produto.area << " | " << "Fornecedor:" << no->produto.fornecedor << std::endl;
	travessiaInfixa(no->direita);
}
//E,D,R
void travessiaSufixa(colhidos* no) {
	if (no == NULL) {
		return;
	}
	travessiaSufixa(no->esquerda);
	travessiaSufixa(no->direita);
	cout << "Nome: " << no->produto.nome << " | " << "Rega: " << no->produto.tempo_rega << " | " << "Resistencia: " << setprecision(3) << no->produto.resistência << " | " << "Area: " << no->produto.area << " | " << "Fornecedor:" << no->produto.fornecedor << std::endl;
}

void deleteArvore(colhidos*& raiz) {
	if (raiz == NULL) {
		return;
	}

	deleteArvore(raiz->esquerda);
	deleteArvore(raiz->direita);

	//apaga o nodo atual
	delete raiz;

	//coloca o apontador como null
	raiz = NULL;
}

