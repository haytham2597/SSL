#pragma once

#ifndef AUTOMATAS_MODULES_BINARYTREE_H
#define AUTOMATAS_MODULES_BINARYTREE_H

#ifndef AUTOMATAS_LIBS_COMMON_H
#include "../libs/common.h"
#endif

//Implementar con pila, matemática discreta unidad 9 calculo de operaciones con pila
//Implementar arbol binario para operar las cuentas https://www.scaler.com/topics/binary-tree-in-c/
//TODO: Mejorar este algoritmo

typedef struct node
{
	char val;
	int result;
	int isOperator, level;
	struct node* left;
	struct node* right;
}node_;

node_* create(char value)
{
	node_* new_node = malloc(sizeof(node_));
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

node_* insert_left(node_* root, char value)
{
	
	root->left = create(value);
	if (root->isOperator)
		root->left->level += root->level;
	return root->left;
}
node_* insert_right(node_* root, char value)
{
	
	root->right = create(value);
	if (root->isOperator)
		root->right->level += root->level;
	return root->right;
}
// Postorder traversal
void postorderTraversal(node_* root) {
	if (root == NULL) 
		return;
	postorderTraversal(root->left);
	postorderTraversal(root->right);
	printf("%c ", root->val);
}

int build_child(node_* child, size_t idx, const char* partial_equation)
{
	for(size_t i=idx;i< strlen(partial_equation);i++)
	{
		if (child == NULL) {
			child = create(partial_equation[i]);
			/*if (!is_operator(partial_equation[i]))
				child->result = char_to_int(partial_equation[i]);*/
		}
		if (child->right != NULL && child->left != NULL) {
			return i-1;
		}
		node_* n = NULL;
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

node_* empty_left(node_* root)
{
	for(;;)
	{
		if (root->left == NULL)
			return root;
		if (root->left != NULL)
			return empty_left(root->left);
	}
}

node_* build_tree(const char* equation)
{
	const char* rev = _strrev(equation); //https://www.geeksforgeeks.org/strrev-function-in-c/ el compilador falló por ser de uso sistema posix, así que se tuvo que invocar _strrev()
	if (!is_operator(rev[0])) {
		printf("Error o no es notacion polaca inversa o la raiz no es un operador");
		return NULL;
	}
	node_* tree = NULL;
	int act_idx=0;
	for(size_t i=0;i<strlen(rev);i++) 
	{
		if (tree == NULL && i == 0) {
			tree = create(rev[i]);
			continue;
		}
		node_* act = NULL;
		if (tree->right == NULL)
			act = insert_right(tree, rev[i]);
		else if(tree->left == NULL)
			act = insert_left(tree, rev[i]);
		if (is_operator(rev[i]))//necesita agregar llenar hojas.
			act_idx = build_child(act, act_idx != 0 ? act_idx : i + 1, rev);
		if(act_idx != 0 && act_idx != strlen(rev))
		{
			node_* emp = empty_left(tree);
			if(emp != NULL)
				act_idx = build_child(emp, act_idx+1, rev);
		}
	}
	return tree;
}

int operation_node(node_* node_operation)
{
	const int a = node_operation->left->result;
	const int b = node_operation->right->result;
	if (node_operation->val == '+')
		return a + b;
	if (node_operation->val == '-')
		return a - b;
	if (node_operation->val == '*')
		return  a * b;
	if (node_operation->val == '/')
		return a / b;
}

void iterate_over_tree(node_* tree)
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
		tree->isOperator = 0;
	}
}

int calculate_tree(node_* tree)
{
	iterate_over_tree(tree);
	return tree->result; //base
}

#endif