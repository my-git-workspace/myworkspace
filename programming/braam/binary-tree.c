#include "binary-tree.h"

tree_node *newtree_node(int val){
	tree_node *newtree_node=(tree_node *)malloc(sizeof(tree_node));
	newtree_node->left=NULL;	
	newtree_node->right=NULL;	
	newtree_node->d.key=val;
	//printf("newtree: %p %d\n", newtree_node, val);
	return newtree_node;
}

tree_node *insert(tree_node *root, int val){
	if(root==NULL)
		return newtree_node(val);
	if(val < root->d.key){
		root->left = insert(root->left, val);	
	}else if (val > root->d.key ){
		root->right = insert(root->right, val);	
	}
	
	return root;	
}
void inorder(tree_node *root){

	if(root){
		inorder(root->left);
		printf(" %d \n", root->d.key);
		inorder(root->right);
	}
}
void preorder(tree_node *root){
	if(root){
		printf(" %d \n", root->d.key);
		inorder(root->left);
		inorder(root->right);
	}
}
void postorder(tree_node *root){
	if(root){
		inorder(root->left);
		inorder(root->right);
		printf(" %d \n", root->d.key);
	}

}
void testtree(){
	
	tree_node *root=NULL;
	root = insert(root, 50);
	//inorder(root->left)
	insert(root, 30);
	//printf("root-data = %d\n",root->right->d.key);
	insert(root, 20);
	insert(root, 40);
	insert(root, 70);
	insert(root, 60);
	insert(root, 80);
	printf("inorder\n");
	inorder(root);
	printf("\npreorder\n");
	preorder(root);
	printf("\npostorder\n");
	postorder(root);
}
