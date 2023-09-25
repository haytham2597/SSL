#pragma once

#ifndef AUTOMATAS_LIBS_COMMON_H
#define AUTOMATAS_LIBS_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h> //strtok

//Constants
//*, /, +, -  respectivamente //https://elcodigoascii.com.ar/ ordenado por precedencia de operadores
int operators[] = { 42,47,43,45, };

//Header
enum TipoDeCadena { none, octal, decimal, hexadecimal };
int get_size(const char* str);
int char_to_int(char ch);
int is_operator(int ascii);
int is_possible_calculate(const char* eq); 
int contain_operator(const char* str);
enum TipoDeCadena get_type(const char* str);
char* add_parenthesis(const char* eq);

inline int contain_operator(const char* str)
{
	const int len = get_size(str);
	for (int i = 0; i < len; i++)
		if (is_operator(str[i]))
			return 1;
	return 0;
}

inline int is_operator(const int ascii)
{
	for (size_t j = 0; j < sizeof(operators); j++)
		if (operators[j] == ascii)
			return 1;
	return 0;
}

inline enum TipoDeCadena get_type(const char* str)
{
	//WARNING: FIX
	const int len = get_size(str);
	enum TipoDeCadena explicit_type = none;
	for (int i = 0; i < len; i++)
	{
		const int low = tolower(str[i]); //https://www.programiz.com/c-programming/library-function/ctype.h/tolower
		if (is_operator(low)) //Excluir los que contienen operaciones, ya que solo validamos cadena aunque la cadena tenga signo con decimal, retorna decimal igual.
			continue;
		if (low < 48 || low > 102)
			return none;
		if (low >= 48 && low <= 55 && (int)explicit_type < octal)
			explicit_type = octal;
		if (low >= 55 && low <= 57 && (int)explicit_type < decimal)
			explicit_type = decimal;
		else if ((low >= 48 && low <= 57) || (low >= 97 && low <= 102) && (int)explicit_type < hexadecimal) //max
			explicit_type = hexadecimal;
	}
	return explicit_type;
}

inline int get_size(const char* str)
{
	//https://stackoverflow.com/questions/48367022/c-iterate-through-char-array-with-a-pointer
	const char* cop_str = NULL; //Se asigna en for
	int siz = 0;
	for (cop_str = str; *cop_str != '\0'; cop_str++) //Itera hasta terminacion nula
		siz++;
	return siz;
}

inline int charToInt(const char* ch)
{
	return (int)ch - 48;
	/*//TODO: Implement fix si una cadena tiene 15 por ejemplo debería returnar 15
	return tolower(ch);*/
}

inline int is_possible_calculate(const char* eq)
{
	const int siz = get_size(eq);
	return !(is_operator(eq[0]) || is_operator(eq[siz - 1]));
}

inline int ShouldAddParenthesis(char ch)
{
	return ch == operators[0] || ch == operators[1];
}

inline char* add_parenthesis(const char* eq)
{
	const int siz = get_size(eq);
	for (int i = 0; i < siz; i++)
	{

	}
}
#endif