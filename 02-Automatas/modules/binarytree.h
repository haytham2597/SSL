#pragma once

#ifndef AUTOMATAS_MODULES_BINARYTREE_H
#define AUTOMATAS_MODULES_BINARYTREE_H

#ifndef AUTOMATAS_LIBS_COMMON_H
#include "../libs/common.h"
#endif

//Implementar con pila, matemática discreta unidad 9 calculo de operaciones con pila
//Implementar arbol binario para operar las cuentas https://www.scaler.com/topics/binary-tree-in-c/
//TODO: Mejorar este algoritmo

typedef struct treenode
{
	char val;
	double result;
	int isOperator, level;
	struct treenode* left;
	struct treenode* right;
}treenode_;

treenode_* create(char value)
{
	treenode_* new_node = malloc(sizeof(treenode_));
	const int is_op = is_operator(value);
	new_node->val = value;
	new_node->result = 0;
	new_node->isOperator = is_op;
	new_node->result = !(is_op) ? char_to_int(value) : 0;
	new_node->level = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

treenode_* insert_left(treenode_* root, char value)
{
	
	root->left = create(value);
	if (root->isOperator)
		root->left->level += root->level;
	return root->left;
}
treenode_* insert_right(treenode_* root, char value)
{
	
	root->right = create(value);
	if (root->isOperator)
		root->right->level += root->level;
	return root->right;
}

int build_child(treenode_* child, size_t idx, const char* partial_equation)
{
	for(size_t i=idx;i< strlen(partial_equation);i++)
	{
		if (child == NULL)
			child = create(partial_equation[i]);
		if (child->right != NULL && child->left != NULL)
			return i-1;
		treenode_* n = NULL;
		if (child->right == NULL) {
			n = insert_right(child, partial_equation[i]);
		}
		else if (child->left == NULL) {
			n = insert_left(child, partial_equation[i]);
		}
		if (is_operator(partial_equation[i]))
			return build_child(n, i + 1, partial_equation);
	}
}

treenode_* empty_left(treenode_* root)
{
	for(;;)
	{
		if (root->left == NULL)
			return root;
		if (root->left != NULL)
			return empty_left(root->left);
	}
}
#ifdef GCC_COMPILER
//https://www.sololearn.com/Discuss/1350351/i-got-the-error-undefined-reference-to-strrev-how-could-i-remove-this
char* strrev(char* str)
{
	char* p1, * p2;
	if (!str || !*str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

#endif
treenode_* build_tree(char* equation)
{
#if defined(GCC_COMPILER)
	const char* rev = strrev(equation);
#elif defined(_MSC_VER)
	const char* rev = _strrev(equation); //https://www.geeksforgeeks.org/strrev-function-in-c/ el compilador falló por ser de uso sistema posix, así que se tuvo que invocar _strrev()
#endif
	if (!is_operator(rev[0])) {
		printf("Error o no es notacion polaca inversa o la raiz no es un operador"); //La raíz siempre tiene que ser operador
		return NULL;
	}
	treenode_* tree = NULL;
	int act_idx=0;
	size_t len = strlen(rev);
	for(size_t i=0;i< len;i++)
	{
		if (tree == NULL && i == 0) {
			tree = create(rev[i]);
			continue;
		}
		treenode_* act = NULL;
		if (tree->right == NULL)
			act = insert_right(tree, rev[i]);
		else if(tree->left == NULL)
			act = insert_left(tree, rev[i]);
		if (is_operator(rev[i])) //necesita agregar llenar hojas.
			act_idx = build_child(act, act_idx != 0 ? act_idx : i + 1, rev);
		if(act_idx != 0 && act_idx != len)
		{
			treenode_* emp = empty_left(tree); //busca el 1er vacío del subnodo izquierdo ya que se completaron derechos
			if(emp != NULL) //Lo encontró, lo trabajamos con ese subnodo a partir del último punto de ecuación que se pudo trabajar.
				act_idx = build_child(emp, act_idx+1, rev);
		}
	}
	return tree;
}

double operation_node(treenode_* node_operation)
{
	const double a = node_operation->left->result;
	const double b = node_operation->right->result;
	if (node_operation->val == '+')
		return a + b;
	if (node_operation->val == '-')
		return a - b;
	if (node_operation->val == '*')
		return  a * b;
	if (node_operation->val == '/') {
		if(b == 0)
		{
			printf("¡ERROR DIVISION DE CERO!");
			exit(EXIT_FAILURE);
		}
		return a / b;
	}
}

void iterate_over_tree(treenode_* tree)
{
	if (tree->left->isOperator)
		iterate_over_tree(tree->left);
	if (tree->right->isOperator)
		iterate_over_tree(tree->right);
	if((tree->left != NULL && tree->right != NULL) && (!tree->left->isOperator && !tree->right->isOperator)) 
	{
		tree->result = operation_node(tree);
		tree->left = NULL;
		tree->right = NULL;
		tree->isOperator = 0; //falso
	}
}

double calculate_tree(treenode_* tree)
{
	iterate_over_tree(tree);
	return tree->result; //base
}

#endif