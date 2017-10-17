#ifndef binary_tree_h
#define binary_tree_h

#include "sorting-algo.h"

typedef struct tree_data{
	int key;
}tree_data;

typedef struct tree_node{
	tree_data d;
	struct tree_node *left;
	struct tree_node *right;
}tree_node; 

tree_node *newtree_node(int val);
tree_node *insert(tree_node *root, int val);
void inorder(tree_node *root);
void preorder(tree_node *root);
void postorder(tree_node *root);
void testtree();
#endif
