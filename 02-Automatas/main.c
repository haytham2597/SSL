//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h> //strtok

//Constants
//*, /, +, -  respectivamente //https://elcodigoascii.com.ar/ ordenado por precedencia de operadores
int operaciones[] = { 42,47,43,45, };

//Header
int GetSize(const char* str);
int charToInt(char ch);
int IsOperator(int ch);
int ContainOperator(const char* str);
//TODO: Implement with Node sgt
int Calculate(const char* equation);
enum TipoDeCadena GetType(const char* str);
enum TipoDeCadena { none, octal, decimal, hexadecimal };

//Func
int ContainOperator(const char* str)
{
	const int len = GetSize(str);
	for (int i = 0; i < len; i++)
		if(IsOperator(str[i]))
			return 1;
	return 0;
}

int IsOperator(const int ascii)
{
	for (int j = 0; j < sizeof(operaciones); j++)
		if (operaciones[j] == ascii)
			return 1;
	return 0;
}

enum TipoDeCadena GetType(const char* str)
{
	//WARNING: FIX
	const int len = GetSize(str);
	enum TipoDeCadena explicit_type = none;
	for(int i=0;i<len;i++)
	{
		const int low = tolower(str[i]); //https://www.programiz.com/c-programming/library-function/ctype.h/tolower
		if (IsOperator(low)) //Excluir los que contienen operaciones, ya que solo validamos cadena aunque la cadena tenga signo con decimal, retorna decimal igual.
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
	const char* cop_str = NULL; //Se asigna en for
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

//Implementar con pila, matemática discreta unidad 9 calculo de operaciones con pila
/*
 *
typedef struct tnodo
{
	int info;
	struct tnodo* sig;
}nodo;

typedef nodo* ptrNodo;

void push(ptrNodo* pila, int x)
{
	//armar un nodo y reservar memoria
	ptrNodo p = (ptrNodo)malloc(sizeof(nodo));
	//guarda la info
	p->info = x;
	p->sig = *pila;
	//apunta
	*pila = p;
}

int pop(ptrNodo* pila)
{
	int x = (*pila)->info;
	ptrNodo p = (*pila);
	//tengo la info
	(*pila) = p->sig;

	free(p);
	//delete p;
	return x;
}
 **/
int Calculate(const char* equation)
{
	//TODO: Implement, with node sgt???
	return 0;
}

int main(int argc, char* argv[])
{
	for(int i=0;i<argc;i++) //En caso de que en las cadenas ademas de contener $ para splitear, tambien se separo con argumento (espacio)
	{
		char* tok = strtok_s(argv[i], "$", NULL); //strtok_s para no arrojar warnings, en caso de usar sin _s se necesita definir _CRT_SECURE_NO_WARNINGS
		while(tok != NULL)
		{
			tok = strtok_s(argv[i], "$", NULL);
			const enum TipoDeCadena tipo = GetType(tok);
			if (tipo == none)
				printf("Error lexico en %s", tok); //Si contiene parentesis va a arrojar error lexico tamb
			if (tipo == decimal && ContainOperator(tok)) //Calculate equation, primero valido si tiene operaciones
				printf("Resultado de la ecuacion %i", Calculate(tok));
		}
	}
	const char* nada = "07ds9";
	const char* octales = "046247105612";
	const char* decimales = "012934816";
	const char* hexadecimal = "48f6a02A2BECfd";

	//Arreglar resultado diferente a lo comentado
	printf("%i", GetType(nada)); //0
	printf("%i", GetType(octales)); //1
	printf("%i", GetType(decimales)); //2
	printf("%i", GetType(hexadecimal)); //3
}