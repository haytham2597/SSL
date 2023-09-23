//#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h> //strtok
/*typedef struct EstructuraCadena
{
	
}cadena;*/

//Constants
//*, +, -, / respectivamente //https://elcodigoascii.com.ar/
int operaciones[] = { 42,43,45,47, };

//Header
int GetSize(const char* str);
int charToInt(char ch);
bool IsOperator(int ch);
enum TipoDeCadena GetType(const char* str);
enum TipoDeCadena { none, octal, decimal, hexadecimal };

//Func
bool IsOperator(int ascii)
{
	for (int j = 0; j < sizeof(operaciones); j++)
		if (operaciones[j] == ascii)
			return true;
	return false;
}
enum TipoDeCadena GetType(const char* str)
{
	const int len = GetSize(str);
	enum TipoDeCadena explicit_type = none;
	for(int i=0;i<len;i++)
	{
		const int low = tolower(str[i]); //https://www.programiz.com/c-programming/library-function/ctype.h/tolower
		if (IsOperator(low))
			continue;
		if (low < 48 || low > 102)
			return none;
		if (low >= 48 && low <= 55 && (int)explicit_type < octal)
			explicit_type = octal;
		if (low >= 55 && low <= 57 && (int)explicit_type < decimal)
			explicit_type = decimal;
		else if ((low >= 48 && low <= 57) || (low >= 97 && low <= 102) && (int)explicit_type < hexadecimal) //max
			explicit_type= hexadecimal;
	}
	return explicit_type;
}

int GetSize(const char* str)
{
	//https://stackoverflow.com/questions/48367022/c-iterate-through-char-array-with-a-pointer
	const char* cop_str = NULL;
	int siz = 0;
	for (cop_str = str; *cop_str != '\0'; cop_str++)
		siz++;
	return siz;
}

int charToInt(const char ch)
{
	//TODO: Implement fix
	return tolower(ch);
}

int main(int argc, char* argv[])
{
	for(int i=0;i<argc;i++)
	{
		char* tok = strtok_s(argv[i], "$", NULL); //strtok_s para no arrojar warnings, en caso de usar sin _s se necesita definir _CRT_SECURE_NO_WARNINGS
		while(tok != NULL)
		{
			tok = strtok_s(argv[i], "$", NULL);
			const enum TipoDeCadena tipo = GetType(tok);
			if (tipo == none)
				printf("Error lexico en %s", tok);

		}
	}
	const char* nada = "07ds9";
	const char* octales = "046247105612";
	const char* decimales = "012934816";
	const char* hexadecimal = "48f6a02A2BECfd";
	printf("%i", GetType(nada));
	printf("%i", GetType(octales));
	printf("%i", GetType(decimales));
	printf("%i", GetType(hexadecimal));
}
