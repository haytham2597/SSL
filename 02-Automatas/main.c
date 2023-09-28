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

double Calculate(char* equation)
{
    //stack_ st{.content = {0}, .size = 0};
    char* gpi = get_polaca_inversa(equation);
    treenode_* tr = build_tree(gpi);
	double result = calculate_tree(tr);
    free(tr);
    return result;
}

int main(int argc, char* argv[])
{
	/*
	 * main.exe 012$51tyia6$fc81$3+4*8/2+3-5 pepe$2*4+3/9-2$516731$0xFBA51$juan$49719$4++9-3*6$-971
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
	 * Cadena: decimal de '-971'
	 * Cantidad de grupo error lexico: 5
	 * Cantidad de grupo octal: 2
	 * Cantidad de grupo decimal: 2
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
				if (!is_possible_calculate(tok) && contain_operator(&tok[1]))  //&tok[1] offset al primer caracter
				{
					//TODO: Comprobar que sólo hay un operador en el 1er caracter y no en el resto. Si es el caso entonces es decimal
					groups[none]++;
					printf("Error lexico en '%s' el programa no puede realizar calculos\n", tok);
				}
				else if(contain_operator(&tok[1])) {
					printf("Resultado de %s: %f\n", tok, Calculate(tok));
				}
				else
				{
					//Solo tiene operador en el 1er caracter y es un + o - queda comprobar con automata
					if(tok[0] == '+' ^ tok[0] == '-' && verify_string(tok) == decimal) //https://www.wolframalpha.com/input?i=truth+table+p+xor+q+and+n&lang=es
					{
						groups[decimal]++;
						printf("Cadena: %s de '%s'\n", name_groups[decimal], tok);
					}
					else
					{
						groups[none]++;
						printf("Error lexico en '%s'\n", tok);
					}
				}
				tok = strtok(NULL, "$");
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