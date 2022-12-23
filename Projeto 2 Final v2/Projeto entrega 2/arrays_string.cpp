#include <iostream>
#include <string>

using namespace std;

// Arrays de strings

//lê e imprime os valores do array
void escrever(const string* ary,int tamanho) {
	
	for (int i = 0; i < tamanho; i++)
	{
		cout << ary[i] << endl;
	}
}

//insere numa posição aumentando o tamanhodo array sem eleminar o elemento
int inserir(string*& ary, int posisao, string valor, int tamanho) {

	string* aux = new string[tamanho + 1]; // criação de um auxiliar array com um tamanho maior em 1,

	if (posisao == 0) { // quando a posição é a primeira

		aux[0] = valor; // aux[0] recebe o valor e depois aux de 1,tamanho copia os valores de ary
		for (int i = 0; i < tamanho; i++)
		{
			aux[i + 1] = ary[i];
		}
	}
	else if (posisao == tamanho - 1) { // quando a posição é a ultima
		 
		aux[tamanho] = valor; // aux[ultima posição = tamanho ] recebe o valor e depois aux de 0,tamanho copia os valores de ary
		for (int i = 0; i < tamanho; i++)
		{
			aux[i] = ary[i];
		}
	}
	else {

		for (int i = 0; i < tamanho+1; i++) // no meio
		{
			if (i == posisao) // quando i = á posição aux[i] = valor
				aux[i] = valor;
			else if (i > posisao) // depois de aux ter o valor houve uma posição de ary que foi saltada por isso i-1;
				aux[i] = ary[i - 1];
			else {  
				aux[i] = ary[i]; // até i = á posição copia os valores de ary
			}
		}
	}

	delete[] ary; // apaga o ary antigo
	ary = aux; // atualixza o apontador para o novo array aux

	return tamanho + 1; //retorna o tamanho
}

//remove o elemento da posição dada
int remover(string*& ary, int posisao, int tamanho) {
	
	if (tamanho - 1 == 0) {

	}
	else {


	}
	string* aux = new string[tamanho - 1]; // criação de um auxiliar array com um tamanho menor em 1 pois um elemento é vai ser removido,

	if (posisao == 0) { // quando a posição é a primeira o aux coipia todos os valores de ary exeto o 1º

		for (int i = 0; i + 1 < tamanho; i++) 
		{
			aux[i] = ary[i + 1];
		}
	}
	else if (posisao == tamanho - 1) { // quando a posição é a ultima o aux coipia todos os valores de ary exeto o ultimoº

		for (int i = 0; i < tamanho - 1; i++)
		{
			aux[i] = ary[i];
		}
	}
	else {

		for (int i = 0; i + 1 < tamanho; i++) // quando no meio é a primeira o aux coipia todos os valores de ary exeto o a posição removidaº
		{
			if (i >= posisao)
				aux[i] = ary[i + 1];
			else
				aux[i] = ary[i];
		}
	}

	delete[] ary; // apaga o ary antigo
	ary = aux; // atualixza o apontador para o novo array aux

	return tamanho - 1; // reorna tamanho -1
}

//remove todas as occorencias de str
int strip(string*& ary, string str, int tamanho) {
	
	int tamanhofinal = tamanho;
	for (int i = 0; i < tamanho; i++)
	{
		if ( ary[i] == str)
		{	
			tamanhofinal--; // o tamanho é redosido em 1 por cada elemento = a str encontrado
			tamanho = remover(ary,i,tamanho);
		}
	}
	return tamanhofinal; //retorna o tamanho
}

//divide o ary em dois 
void split(const string* ary, int posisao, int tamanho, string** a, int* tamanho_a, string** b, int* tamanho_b) {

	if (posisao != 0 and posisao != tamanho - 1) {
		
		//cria variavei de apontador e tamanho para os novos arrays
		*tamanho_a = posisao + 1;
		*tamanho_b = tamanho - posisao - 1;
		*a = new string[*tamanho_a];
		*b = new string[*tamanho_b];

		//copia os palores para cada um dos arrays utilizando a posiçãocomo divisão
		for (int i = 0; i < tamanho; i++)
		{
			if (i < *tamanho_a) {
				(*a)[i] = ary[i];
			}
			else {
				(*b)[i - posisao - 1] = ary[i];
			}
		}
	}
}

//retorna a posição da 1ª ocorrencia do valor igual a str
int procurar(const string* ary, string str, int tamanho) {

	for (int i = 0; i < tamanho; i++) 
	{
		if (ary[i] == str) {
			return i;	
		}
	}
	return 0;
}

void trim(std::string& n) {

	while (n.find(" ") != -1) {
		n.erase(n.find(" "), 1);
	}
}

void to_lower(std::string& n) {
	
	char a;
	for (int i_ch = 0; i_ch < n.length(); i_ch++)
	{
		a = n[i_ch];
		switch (a) {

			case 'A': n.replace(i_ch, 1, "a"); 
				break;
			case 'B': n.replace(i_ch, 1, "b"); 
				break;
			case 'C': n.replace(i_ch, 1, "c"); 
				break;
			case 'D': n.replace(i_ch, 1, "d"); 
				break;
			case 'E': n.replace(i_ch, 1, "e"); 
				break;
			case 'F': n.replace(i_ch, 1, "f"); 
				break;
			case 'G': n.replace(i_ch, 1, "g"); 
				break;
			case 'H': n.replace(i_ch, 1, "h"); 
				break;
			case 'I': n.replace(i_ch, 1, "i"); 
				break;
			case 'J': n.replace(i_ch, 1, "j"); 
				break;
			case 'K': n.replace(i_ch, 1, "k"); 
				break;
			case 'L': n.replace(i_ch, 1, "l"); 
				break;
			case 'M': n.replace(i_ch, 1, "m"); 
				break;
			case 'N': n.replace(i_ch, 1, "n"); 
				break;
			case 'O': n.replace(i_ch, 1, "o"); 
				break;
			case 'P': n.replace(i_ch, 1, "p"); 
				break;
			case 'Q': n.replace(i_ch, 1, "q"); 
				break;
			case 'R': n.replace(i_ch, 1, "r"); 
				break;
			case 'S': n.replace(i_ch, 1, "s"); 
				break;
			case 'T': n.replace(i_ch, 1, "t"); 
				break;
			case 'U': n.replace(i_ch, 1, "u"); 
				break;
			case 'V': n.replace(i_ch, 1, "v"); 
				break;
			case 'W': n.replace(i_ch, 1, "w"); 
				break;
			case 'X': n.replace(i_ch, 1, "x"); 
				break;
			case 'Y': n.replace(i_ch, 1, "y"); 
				break;
			case 'Z': n.replace(i_ch, 1, "z"); 
				break;
			default:
				break;

		}
	}
}