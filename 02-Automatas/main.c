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

int Calculate(const char* equation)
{
	//TODO: Implement, with node sgt???
	return 0;
}

void memoryreference(int* mem)
{
	*mem = 9;
}
int main(int argc, char* argv[])
{
	/*ptrNodo pila = NULL;
	push(&pila, 'x');
	push(&pila, 'y');
	for(ptrNodo i=&pila;i /= NULL;i++)
	{
		
	}
	int v = pop(&pila);
	printf("%c ", v);
	v = pop(&pila);
	printf("%c ", v);*/



	printf("%i \n", 3 < 4);
	printf("%i \n", 3 > 4);
	char* po = get_polaca("3+4*8/2+3-5");
	printf("LA POLACA ES: %s \n", po);
	int l = 3;
	//int* l = malloc(sizeof(int));
	printf("%i", l);
	memoryreference(&l);
	printf("%i", l);
	printf("%i", is_possible_calculate("+541*"));

	node_* root = create('/');
	insert_left(root, '*');
	insert_right(root, '+');
	insert_right(root->left, '6');
	insert_left(root->left, '^');
	insert_right(root->left->left, '2');
	insert_left(root->left->left, '-');
	insert_left(root->left->left->left, '5');
	insert_right(root->left->left->left, '3');

	insert_right(root->right, '8');
	insert_left(root->right, '*');
	insert_left(root->right->left, '2');
	insert_right(root->right->left, '8');
	preorderTraversal(root);

	/*for(int i=0;i<argc;i++) //En caso de que en las cadenas ademas de contener $ para splitear, tambien se separo con argumento (espacio)
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
	printf("%i", GetType(hexadecimal)); //3*/
}

//pto3 (planteado solamente)
/*
int charToInt(char c){
    int i = c;
    return i - 48;
}

struct Nodo {
    char c;
    struct Nodo* izq;
    struct Nodo* der;
};

//crea la raiz del arbol poniendo el caracter X como identificador que recien se creo
struct Nodo* crearArbol(){
    struct Nodo* ret = malloc(sizeof(struct Nodo));
    ret->c = 'X';
    ret->der = NULL;
    ret->izq = NULL;
    return ret;
}

//crea una hoja del arbol asignandole el caracter leido
struct Nodo* crearNodo(char c){
    struct Nodo* ret = malloc(sizeof(struct Nodo));
    ret->c = c;
    ret->der = NULL;
    ret->izq = NULL;
    return ret;
}

//lee la cadena y va armando el arbol (ni cerca de terminarlo)
void desarrollarArbol(struct Nodo* arbol, char str[20]){
    char izq, der, c;
    struct Nodo* aux = arbol;
    for(int i=0; str[i] /= '\0'; i++){
        c = str[i];
        //para identificar si es el primer caracter leido o no (se podria hacer de alguna manera mas linda pero no se me ocurrio)
        if( aux->c == 'X'){
            aux->c = c;
        }
        else{
            if(charToInt(c) < 0 || charToInt(c) > 9){
                struct Nodo* n = crearNodo(c);
            }
            else{
            }
        }

    }
}

//recorre el arbol y da el resultado final
int resultadoArbol(struct Nodo* arbol){
    int resultado = 0;
    return resultado;
}

int main()
{
    char str[20];
    printf("escriba la operacion");
    scanf("%s", &str);
    struct Nodo* arbol = crearArbol();
    desarrollarArbol(arbol, str);
    int resultado = resultadoArbol(arbol);
    printf("el resultado es: %i", resultado);
    system("pause");
    return 0;
}
*/   
