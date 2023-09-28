#define _CRT_SECURE_NO_WARNINGS

#if defined(__GNUC__) || defined(__GNUG__)
#define GCC_COMPILER
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h> //strtok
#ifndef AUTOMATAS_LIBS_COMMON_H
#include "libs/common.h"
#endif

#ifndef AUTOMATAS_MODULES_BINARYTREE_H
#include "modules/binarytree.h"
#endif

#ifndef AUTOMATAS_MODULES_USUALTOPOLACA_H
#include "modules/usual_to_polaca.h"
#endif

#ifndef AUTOMATAS_MODULES_AUTOMATA_H
#include "modules/automata.h"
#endif


//Maxima línea para ficheros
#define MAX_BUFFER 65535

double Calculate(char* equation)
{
    //stack_ st{.content = {0}, .size = 0};
    char* gpi = get_polaca_inversa(equation);
    treenode_* tr = build_tree(gpi);
	double result = calculate_tree(tr);
    free(tr);
    return result;
}

/*int open_file(const char* path)
{
	//Reutilizando código de 00-CHelloworld
	FILE* fptr = fopen(path,"r"); //r read abrir como lectura
	if (fptr == NULL) //O no puede abrir o no es un fichero
	{
		printf("Error con la cadena %s el programa no puede abrir como lectura o no es una ruta de fichero\n", path);
		return 0;
	}
	char buffer[MAX_BUFFER];
	while (fgets(buffer, MAX_BUFFER, fptr)) {
		size_t l = strlen(buffer);
		char* tok = (char*)malloc(l);
		memcpy(tok, buffer, l);
		//char* tok = &buffer[0];
		//printf("Strlen: %i", strlen(buffer));
		const enum TipoDeCadena tipo = get_type(tok);
		if (tipo == none)
			printf("Error lexico en '%s'\n", tok); //Si contiene parentesis va a arrojar error lexico tamb
		if (tipo == octal)
			printf("Cadena octal: %s\n", tok);
		if (tipo == decimal) //Calculate equation, primero valido si tiene operaciones
		{
			if (contain_operator(buffer)) {

				printf("Resultado de %s: %i\n", tok, Calculate(tok));
			}
			else
			{
				printf("Cadena decimal: %s\n", tok);
			}
		}
		if (tipo == hexadecimal)
			printf("Cadena hexadecimal: %s\n", tok);
		//buffer = strtok(NULL, "$");
		//printf("%s", buffer);
	}
	fclose(fptr);
	return 1;
}*/

int main(int argc, char* argv[])
{
	/*
	 * main.exe 012$51tyia6$fc81$3+4*8/2+3-5 pepe$2*4+3/9-2$516731$0xFBA51$juan$49719$4++9-3*6
	 * Cadena: octal de '012'
	 * Error lexico en '51tyia6'
	 * Error lexico en 'fc81'
	 * Resultado de 3+4*8/2+3-5: 17.000000
	 * Error lexico en 'pepe'
	 * Resultado de 2*4+3/9-2: 6.333333
	 * Cadena: octal de '516731'
	 * Cadena: hexadecimal de '0xFBA51'
	 * Error lexico en 'juan'
	 * Cadena: decimal de '49719'
	 * Error lexico en '4++9-3*6' el programa no puede realizar calculos
	 * Cantidad de grupo error lexico: 4
	 * Cantidad de grupo octal: 2
	 * Cantidad de grupo decimal: 4
	 * Cantidad de grupo hexadecimal: 1
	*/
	char name_groups[][20] = {"error lexico", "octal", "decimal", "hexadecimal"};
	int groups[] = { 0,0,0,0 };
	//Soporta múltiple argumentos
	for(int i=1;i<argc;i++) //i=1 porque el índice 0 es la ruta de llamada.
	{
		char* tok = strtok(argv[i], "$");
		while (tok != NULL)
		{
			if (get_type(tok) == decimal && contain_operator(tok))
			{
				if (!is_possible_calculate(tok))
				{
					//TODO: Comprobar que sólo hay un operador en el 1er caracter y no en el resto. Si es el caso entonces es decimal
					printf("Error lexico en '%s' el programa no puede realizar calculos\n", tok);
				}
				else {
					printf("Resultado de %s: %f\n", tok, Calculate(tok));
				}
				tok = strtok(NULL, "$");
				groups[2]++;
				continue;
			}
			const enum TipoDeCadena tipo = verify_string(tok);
			if (tipo == none) {
				printf("Error lexico en '%s'\n", tok);
			}
			else
			{
				printf("Cadena: %s de '%s'\n", name_groups[tipo], tok);
			}
			groups[tipo]++;
			tok = strtok(NULL, "$");
		}
	}
	for (size_t i = 0; i < sizeof(groups) / sizeof(int); i++)
		printf("Cantidad de grupo %s: %i\n", name_groups[i], groups[i]);
}