#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
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
	/*const char* nada = "07ds9";
	const char* octales = "046247105612";
	const char* decimales = "012934816";
	const char* hexadecimal = "48f6a02A2BECfd";

	//Arreglar resultado diferente a lo comentado
	printf("%i\n", get_type(nada)); //0
	printf("%i\n", get_type(octales)); //1
	printf("%i\n", get_type(decimales)); //2
	printf("%i\n", get_type(hexadecimal)); //3*/

	/*char* po = get_polaca_inversa("3+4*8/2+3-5"); //tiene que dar 17
    //char* po = get_polaca("2*4+3/9-2"); //Probando tiene que dar 6 ya que 3/9 al pasarlo como entero da 0 pero de double por ej: daria 0.33

	printf("La polaca inversa es: %s \n", po);
    printf("Resultado: %i\n", Calculate("3+4*8/2+3-5")); //tiene que dar 17
    printf("Resultado: %i\n", Calculate("2*4+3/9-2")); //Es una prueba tiene que dar 6 ya que 3/9 al pasarlo como entero da 0 pero de double por ej: daria 0.33*/
	//printf("%i\n", get_type("fc81")); //1

	/*
	 * 02-Automatas.exe 012$fc81$3+4*8/2+3-5 2*4+3/9-2$pepe$516731$FBA51$mujica$49719
	 * Cadena octal: 012
	 * Cadena hexadecimal: fc81
	 * Resultado de 3+4*8/2+3-5: 17
	 * Resultado de 2*4+3/9-2: 6
	 * Error lexico en 'pepe'
	 * Cadena octal: 516731
	 * Cadena hexadecimal: FBA51
	 * Error lexico en 'mujica'
	 * Cadena decimal: 49719
	 */
	//Si el primer argumento es -b implica binario las rutas de fichero abren al fichero como binario
	//const int read_b = (argc > 1) ? argv[1] == "bin" : 0;
	int cnt_g = 0;
	for(int i=1;i<argc;i++) //i=1 porque el índice 0 es la ruta de llamada
	{
		char* tok = strtok(argv[i], "$"); //strtok_s para no arrojar warnings, en caso de usar sin _s se necesita definir _CRT_SECURE_NO_WARNINGS
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
					
					printf("Resultado de %s: %i\n", tok, Calculate(tok));
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