#include "fila_produtos.h"


void adicionar(Fila_Produtos& fila, Produto produto) {

	inserir(fila.lista, produto, fila.lista.n_produtos);

}

void remover(Fila_Produtos& fila) {

	if (fila.lista.item_base != NULL)
	{
		Lista_Produtos::Item* auxiliar = fila.lista.item_base->seguinte;
		delete fila.lista.item_base;
		fila.lista.item_base = auxiliar;

		fila.lista.n_produtos--;
	}
	
}
