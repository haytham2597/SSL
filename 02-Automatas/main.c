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

//Maxima línea para ficheros
#define MAX_BUFFER 65535

int Calculate(char* equation)
{
    //stack_ st{.content = {0}, .size = 0};
    char* gpi = get_polaca_inversa(equation);
    node_* tr = build_tree(gpi);
    int result = calculate_tree(tr);
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
	 * 02-Automatas.exe 012$fc81$3+4*8/2+3-5 pepe$2*4+3/9-2$516731$FBA51$juan$49719
	 * Cadena octal: 012
	 * Cadena hexadecimal: fc81
	 * Resultado de 3+4*8/2+3-5: 17
	 * Error lexico en 'pepe'
	 * Resultado de 2*4+3/9-2: 6
	 * Cadena octal: 516731
	 * Cadena hexadecimal: FBA51
	 * Error lexico en 'juan'
	 * Cadena decimal: 49719
	 * Cantidad de grupos :7
	 */
	int cnt_g = 0; //cantidad de grupo
	//Soporta múltiple argumentos
	for(int i=1;i<argc;i++) //i=1 porque el índice 0 es la ruta de llamada.
	{
		char* tok = strtok(argv[i], "$");
		while (tok != NULL)
		{
			const enum TipoDeCadena tipo =get_type(tok);
			if (tipo == none) {
				/*if (open_file(tok))
				{
					tok = strtok(NULL, "$");
					continue; //evito indentaciones a las condiciones
				}*/
				printf("Error lexico en '%s'\n", tok); //Si contiene parentesis va a arrojar error lexico tamb
				tok = strtok(NULL, "$");
				continue;
			}
			if (tipo == octal)
				printf("Cadena octal: %s\n", tok);
			if (tipo == decimal) //Calculate equation, primero valido si tiene operaciones
			{
				if (contain_operator(tok)) {
					if(!is_possible_calculate(tok))
					{
						printf("Error lexico en '%s' el programa no puede realizar calculos\n", tok);
						cnt_g--;
					}
					else {
						printf("Resultado de %s: %i\n", tok, Calculate(tok));
					}
				}else
				{
					printf("Cadena decimal: %s\n", tok);
				}
			}
			if (tipo == hexadecimal)
				printf("Cadena hexadecimal: %s\n", tok);
			tok = strtok(NULL, "$");
			cnt_g++;
		}
	}
	printf("Cantidad de grupos :%i\n", cnt_g);
}