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

//INFO: Matemática Discreta Unidad 9 página 129. La notación usual o infija es el tipo de notación que usamos comunmente para escribir la fórmula matemática.
//META: Pasar la cadena a notación polaca inversa y luego la misma va a tener que pasarse a Arbol binario para resolver la ecuación matemática.
//https://www.omnicalculator.com/math/polish-notation
//https://www.andreinc.net/2010/10/05/converting-infix-to-rpn-shunting-yard-algorithm muestra el pseudocódigo

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
 * \param var Variables representa los números que compone la ecuación
 * \param sy Símbolos representa los símbolos que utiliza la ecuación; *,/,-,+, etc.
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