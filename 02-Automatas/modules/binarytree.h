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
	int isOperator;
	struct node* left;
	struct node* right;
}node_;

node_* create(char value)
{
	node_* new_node = malloc(sizeof(node_));
	new_node->val = value;
	new_node->isOperator = is_operator(value);
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

node_* insert_left(node_* root, char value)
{
	root->left = create(value);
	return root->left;
}
node_* insert_right(node_* root, char value)
{
	root->right = create(value);
	return root->right;
}

void preorderTraversal(node_* root)
{
	if (root == NULL)
		return;
	printf("%c -> ", root->val);
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}
// Postorder traversal
void postorderTraversal(node_* root) {
	if (root == NULL) return;
	postorderTraversal(root->left);
	postorderTraversal(root->right);
	printf("%c ", root->val);
}

int build_child(node_* child, size_t idx, const char* partial_equation)
{
	for(size_t i=idx;i< strlen(partial_equation);i++)
	{
		
		/*if(i==10)
		{
			printf("deb here");
		}*/
		if (child == NULL)
			child = create(partial_equation[i]);
		//printf("Build: %c \n", child->val);
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
		/*if (child->right == NULL) {
			node_* n = insert_right(child, partial_equation[i]);
			if(is_operator(partial_equation[i]))
				build_child(n, i+1, partial_equation);
		}
		else if(child->left==NULL)
		{
			node_* n = insert_left(child, partial_equation[i]);
			if (is_operator(partial_equation[i]))
				build_child(n, i+1, partial_equation);
		}*/
	}
}

void pruebav1(node_* tree, const char* rev)
{
	tree = create(rev[0]); //agrego la raiz. (-)
	if(tree->right == NULL) //Siempre empiezo trabajando por la derecha ya que es notación inversa
	{
		if (isdigit(rev[1])) {
			insert_right(tree, rev[1]);
		}
	}
	if(isdigit(rev[1])) //evaluo si el siguiente es numero
	{
		//insert_right();
	}
}

node_* build_tree(const char* equation)
{
	const char* rev = _strrev(equation); //https://www.geeksforgeeks.org/strrev-function-in-c/ el compilador falló por ser de uso sistema posix, así que se tuvo que invocar _strrev()
	if (!is_operator(rev[0])) {
		printf("Error o no es notacion polaca inversa o la raiz no es un operador");
		return;
	}
	
	node_* tree = NULL;

	node_* actual_node = NULL;
	int prev_is_operator, post_is_operator;
	int act_idx=0;
	for(size_t i=0;i<strlen(rev);i++) 
	{
		printf("Work here: %c \n", rev[i]);
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
		{
			if(act_idx != 0)
			{
				printf("Actual idx %i \n", act_idx);
			}
			act_idx = build_child(act, act_idx != 0 ? act_idx : i + 1, rev);
		}
	}
	return tree;
}

#endif