#ifndef bst_h
#define bst_h

#include <stdio.h>
#include <stdlib.h>

/*
 * BST : binary search tree
 * 
 * Max nodes per level ==>  2^(level-1)
 *
 * Max number of nodes in a binary tree with height h (2^h - 1 )
 * 
 */

typedef struct node {
	int data_;
	struct node *left_;
	struct node *right_;

}node;


node *newnode( int data );

void insert( node **n, int data );
void preorder( node *n );

#endif

