#pragma once

#ifndef AUTOMATAS_MODULES_STACK_H
#define AUTOMATAS_MODULES_STACK_H

#ifndef AUTOMATAS_LIBS_COMMON_H
#include "../libs/common.h"
#endif

#define MAX_STACK 2000 //maximo tamaño

typedef struct stack
{
	char content[MAX_STACK]; //los char representan enteros de tabla ASCII 0-255
	int size; //tamaño de contenido pila
}stack_;

int pop(stack_* st, int* get_val);
void push(stack_* st, int value);

int pop(stack_* st, int* get_val)
{
	if (st->size == 0) //?? Si la pila es tamaño 0, para que quiere hacer pop... significa que está vacío
		return 0; //Está vacío, no puedo seguir haciendo pop
	//memcpy(get_val, &st->content[st->size - 1], 1); //Copio el valor del content[size-1] (último valor) y lo pego al parámetro de variable get_val. De esta forma no arroja excepción por referencia nula
	st->content[st->size - 1] = '\0'; //al último índice del tamaño actual de la pila inserto una terminación nula
	st->size--; //decremento tamaño
	return 1; //Puedo continuar haciendo pop
}

void push(stack_* st, int value)
{
	if (st->size == MAX_STACK) //En todo caso debería imprimir error
		return;
	//Como el tamaño del array content está definido por MAX_STACK. Se asigna el value en dicho índice del array, luego incremento el tamaño para permitir el siguiente push
	memcpy(&st->content[st->size], &value, 1); //Al igual que C++, C admite también la copia de memoria https://cplusplus.com/reference/cstring/memcpy/
	st->size++; //incremento tamaño de pila por asignar nuevo valor en la matriz
}
#endif