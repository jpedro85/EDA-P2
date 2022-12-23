#include "lista_ligada_produtos.h"


struct Fila_Produtos
{
	Lista_Produtos lista;
};

//adiciona um nono produto
void adicionar(Fila_Produtos& fila, Produto produto);
//remove o primeiro
void remover(Fila_Produtos& fila);
//retorna o primeiro retorna produto Nulo se a fila estiver vazia
