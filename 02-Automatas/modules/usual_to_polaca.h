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

/**
 * \brief 
 * \param var Variables representa los números que compone la ecuación
 * \param sy Símbolos representa los símbolos que utiliza la ecuación; *,/,-,+, etc.
 * \param val valor
 */
void update_stack(stack_* var, stack_* sy, char val) //https://github.com/stephenwashington/convert/blob/master/src/infix_to_rpn.c
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
			const char prev = sy->content[sy->size - 1];
			if (op_precedence(prev) >= op_precedence(val)) //https://github.com/karimo94/infix-to-rpn/blob/0225cc8b508fb02a8b8b1d87965076c88a174ae8/Program.cs#L38C20-L38C77
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

char* get_polaca_inversa(char* equation)
{
	stack_ v = { .size = 0, .content = {0} };
	stack_ s = { .size = 0, .content = {0} };
	for (size_t i = 0; i < strlen(equation);i++) 
		update_stack(&v, &s, equation[i]);
	for (int i = s.size - 1; i >= 0; i--) {
		v.content[v.size] = s.content[i];
		v.size++;
	}
	char* result = (char*)malloc(MAX_STACK);
	strcpy(result, v.content);
	return result;
}

#endif