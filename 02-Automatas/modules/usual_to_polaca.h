#pragma once

#ifndef AUTOMATAS_MODULES_USUALTOPOLACA_H
#define AUTOMATAS_MODULES_USUALTOPOLACA_H

#include <stdbool.h>

#ifndef AUTOMATAS_LIBS_COMMON_H
#include "../libs/common.h"
#endif

#ifndef AUTOMATAS_MODULES_STACK_H
#include "stack.h"
#endif

//INFO: Matem�tica Discreta Unidad 9 p�gina 129. La notaci�n usual o infija es el tipo de notaci�n que usamos comunmente para escribir la f�rmula matem�tica.
//META: Pasar la cadena a notaci�n polaca inversa y luego la misma va a tener que pasarse a Arbol binario para resolver la ecuaci�n matem�tica.
//https://www.omnicalculator.com/math/polish-notation
//https://www.andreinc.net/2010/10/05/converting-infix-to-rpn-shunting-yard-algorithm muestra el pseudoc�digo

int is_right_associative(int val)
{
	return is_operator(val);
}

int should_pop(int prev, int val)
{
	int a = is_right_associative(val);
	int b = get_operator(prev) < get_operator(val);
	int c = is_right_associative(val);
	int d = get_operator(prev) <= get_operator(val);
	return ;
}

/**
 * \brief 
 * \param var Variables representa los n�meros que compone la ecuaci�n
 * \param sy S�mbolos representa los s�mbolos que utiliza la ecuaci�n; *,/,-,+, etc.
 * \param val valor
 */
void update_stack(stack_* var, stack_* sy, const int val)
{
	if (!is_operator(val)) {
		push(var, val);
	} 
	else
	{
		if (sy->size == 0) {
			push(sy, val);
			return;
		}
		while (sy->size > 0)
		{
			const int prev = sy->content[sy->size - 1];
			if (op_precedence(prev) >= op_precedence(val))
			{
				push(var, prev);
				pop(sy, NULL);
			}
			else
			{
				break;
			}
		}
		push(sy, val);
	}
}

char* get_polaca(const char* equation)
{
	stack_ v = { .size = 0, .content = {0} };
	stack_ s = { .size = 0, .content = {0} };
	for (size_t i = 0; i < strlen(equation);i++) //https://learn.microsoft.com/es-es/cpp/c-runtime-library/reference/strlen-wcslen-mbslen-mbslen-l-mbstrlen-mbstrlen-l?view=msvc-170
		update_stack(&v, &s, equation[i]);
	
	for (int i = s.size - 1; i >= 0; i--) {
		v.content[v.size] = s.content[i];
		v.size++;
	}
	for (int i = 0; i < v.size; i++)
		printf("%c ", v.content[i]);
	printf("\n");

	char* result = calloc(MAX_STACK, sizeof(char));
	memcpy(result, v.content, MAX_STACK);
	return result;
	//return NULL;
}

#endif