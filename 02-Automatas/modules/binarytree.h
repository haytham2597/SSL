#pragma once

#ifndef AUTOMATAS_MODULES_BINARYTREE_H
#define AUTOMATAS_MODULES_BINARYTREE_H

#ifndef AUTOMATAS_LIBS_COMMON_H
#include "../libs/common.h"
#endif

//Implementar con pila, matemática discreta unidad 9 calculo de operaciones con pila
//Implementar arbol binario para operar las cuentas https://www.scaler.com/topics/binary-tree-in-c/


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


#endif