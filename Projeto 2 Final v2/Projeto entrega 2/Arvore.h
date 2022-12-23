#pragma once
#include "Produto.h"
#include <fstream>
#include <string>

struct colhidos {
    Produto produto;
    colhidos* esquerda;
    colhidos* direita;
};

colhidos* novoColhidos(Produto produto);

colhidos* inserirColhidos(colhidos* raiz, Produto produto);

int altura(colhidos* no);

int contaNos(colhidos* no);

void travessiaPrefixa(colhidos* no);

void travessiaInfixa(colhidos* no);

void travessiaSufixa(colhidos* no);

void deleteArvore(colhidos*& raiz);





