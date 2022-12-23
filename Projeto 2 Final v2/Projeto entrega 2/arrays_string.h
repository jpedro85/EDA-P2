#pragma once

#include <string>

//Arrays string
//l� e imprime os valores do array
void escrever(const std::string* ary, int tamanho);
//insere numa posi��o aumentando o tamanhodo array sem eleminar o elemento
int inserir(std::string*& ary, int posisao, std::string valor, int tamanho);
//remove o elemento da posi��o dada
int remover(std::string*& ary, int posisao, int tamanho);
//remove todas as occorencias de str
int strip(std::string*& ary, std::string str, int tamanho);
//divide o ary em dois  na posi��o dada
void split(const std::string* ary, int posisao, int tamanho, std::string** a, int* tamanho_a, std::string** b, int* tamanho_b);
//retorna a posi��o da 1� ocorrencia do valor igual a str
int procurar(const std::string* ary, std::string str, int tamanho);
//retira todos os careteres iguais de uma string
void trim(std::string& n);
void to_lower(std::string& n);