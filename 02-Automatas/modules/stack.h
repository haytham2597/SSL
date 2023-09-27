#pragma once

#ifndef AUTOMATAS_MODULES_STACK_H
#define AUTOMATAS_MODULES_STACK_H

#ifndef AUTOMATAS_LIBS_COMMON_H
#include "../libs/common.h"
#endif

#define MAX_STACK 2000 //maximo tama�o

typedef struct stack
{
	char content[MAX_STACK]; //los char representan enteros de tabla ASCII 0-255
	int size; //tama�o de contenido pila
}stack_;

int pop(stack_* st, int* get_val);
void push(stack_* st, int value);

int pop(stack_* st, int* get_val)
{
	if (st->size == 0) //?? Si la pila es tama�o 0, para que quiere hacer pop... significa que est� vac�o
		return 0; //Est� vac�o, no puedo seguir haciendo pop
	//memcpy(get_val, &st->content[st->size - 1], 1); //Copio el valor del content[size-1] (�ltimo valor) y lo pego al par�metro de variable get_val. De esta forma no arroja excepci�n por referencia nula
	st->content[st->size - 1] = '\0'; //al �ltimo �ndice del tama�o actual de la pila inserto una terminaci�n nula
	st->size--; //decremento tama�o
	return 1; //Puedo continuar haciendo pop
}

void push(stack_* st, int value)
{
	if (st->size == MAX_STACK) //En todo caso deber�a imprimir error
		return;
	//Como el tama�o del array content est� definido por MAX_STACK. Se asigna el value en dicho �ndice del array, luego incremento el tama�o para permitir el siguiente push
	memcpy(&st->content[st->size], &value, 1); //Al igual que C++, C admite tambi�n la copia de memoria https://cplusplus.com/reference/cstring/memcpy/
	st->size++; //incremento tama�o de pila por asignar nuevo valor en la matriz
}
#endif