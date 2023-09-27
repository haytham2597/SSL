#pragma once

#ifndef AUTOMATAS_LIBS_COMMON_H
#define AUTOMATAS_LIBS_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h> //strtok

//Constants
//*, /, +, -  respectivamente //https://elcodigoascii.com.ar/ ordenado por precedencia de operadores
int operators[] = { 42,47,45,43 };

//Header
enum TipoDeCadena { none, octal, decimal, hexadecimal };
//int get_size(const char* str);
int char_to_int(char ch);
int is_operator(int ascii);
int is_possible_calculate(const char* eq); 
int contain_operator(const char* str);
int op_precedence(char c);
enum TipoDeCadena get_type(const char* str);
char* add_parenthesis(const char* eq);

inline int contain_operator(const char* str)
{
	for (size_t i = 0; i < strlen(str); i++) //https://learn.microsoft.com/es-es/cpp/c-runtime-library/reference/strlen-wcslen-mbslen-mbslen-l-mbstrlen-mbstrlen-l?view=msvc-170
		if (is_operator(str[i]))
			return 1;
	return 0;
}

inline int op_precedence(char c)
{
	if (c == '*' || c == '/')
		return 2;
	if (c == '+' || c == '-')
		return 1;
	return 0;
}

inline int is_operator(const int ascii)
{
	for (size_t i = 0; i < sizeof(operators)/sizeof(int); i++) //https://stackoverflow.com/questions/1597830/iterate-through-a-c-array
		if (operators[i] == ascii)
			return 1;
	return 0;
}

inline int get_operator(const int ascii)
{
	for (size_t i = 0; i < sizeof(operators) / sizeof(int); i++)
		if (operators[i] == ascii)
			return (int)i;
	return (sizeof(operators) / sizeof(int))+1;
}

inline enum TipoDeCadena get_type(const char* str)
{
	enum TipoDeCadena explicit_type = none;
	for (size_t i = 0; i < strlen(str); i++)
	{
		const int low = tolower(str[i]); //https://www.programiz.com/c-programming/library-function/ctype.h/tolower
		if (is_operator(low)) //Excluir los que contienen operaciones, ya que solo validamos cadena aunque la cadena tenga signo con decimal, retorna decimal igual.
			continue;
		if (low < 48 || low > 102)
			return none;
		if (low >= 48 && low <= 55) {
			if ((int)explicit_type < octal)
				explicit_type = octal;
			if (low > 55 && low <= 57)
				explicit_type = decimal;
		}
		else if (isdigit(low)) {
			if((int)explicit_type < decimal)
				explicit_type = decimal;
		}
		else
			explicit_type = hexadecimal;
	}
	return explicit_type;
}

inline int charToInt(char ch)
{
	return (int)ch - 48;
	/*//TODO: Implement fix si una cadena tiene 15 por ejemplo debería returnar 15
	return tolower(ch);*/
}

inline int is_possible_calculate(const char* eq)
{
	const size_t siz =strlen(eq);
	return !(is_operator(eq[0]) || is_operator(eq[siz - 1]));
}

inline int ShouldAddParenthesis(char ch)
{
	return ch == operators[0] || ch == operators[1];
}

#endif