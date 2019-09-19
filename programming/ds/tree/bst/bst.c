#include <bst.h>

node *newnode( int data ){

	node *n = (node *)malloc(sizeof(node));
	n->data_ = data;
	n->left_ = NULL;
	n->right_ = NULL;
	return n;
}

node *root = NULL;

void insert( node **n, int data ){
	if ( *n == NULL ){
		*n = newnode( data );
		return ;
	}
	if ( data < (*n)->data_ ){
		insert(&((*n)->left_), data);
	}else {
		insert(&((*n)->right_), data);
		
	}
	return ;


}

/*
 * preorder:
 * root
 * left_
 * right_
 */

void preorder( node *n ) {
	if ( n ){
		printf("data: %d\n", n->data_);	
		preorder( n->left_ );
		preorder( n->right_ );
	}
}
/*
 * inorder:
 * left_
 * root
 * right_
 */

void inorder( node *n ) {
	if ( n ){

		inorder( n->left_ );
		printf("data: %d\n", n->data_);	
		inorder( n->right_ );
	}
}

/*
 * postorder:
 * left_
 * right_
 * root
 */

void postorder( node *n ) {
	if ( n ){

		postorder( n->left_ );
		postorder( n->right_ );
		printf("data: %d\n", n->data_);	
	}
}

int main(int argc, char **argv){


	insert ( &root , 50 );
	insert ( &root , 30 );
	insert ( &root , 20 );
	insert ( &root , 40 );
	insert ( &root , 70 );
	insert ( &root , 60 );
	insert ( &root , 80 );

	printf("inorder\n");
	inorder( root );
	
	//printf("preorder\n");
	//preorder( root );
	
	//printf("postorder\n");
	//postorder( root );
	//return (0);
	return 0;
}
