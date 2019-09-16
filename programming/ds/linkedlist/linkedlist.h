#ifndef linkedlist_h
#define linkedlist_h
#include <iostream>
using namespace std;

class node;
class list;

class node {
	public:
	node( node *next = NULL, int data = 0 );
	int data_;
	node *next_;
};

class list {

public:
	list ( bool isStack = false );
	void insert(int data );
	void show();
	void mid_of_list();
	void getnode_n( int index );
	void getnode_n_from_last(int index);
	void getnode_n_from_last_using_pointers( int index );
	void delete_list_data();
	void data_occurences( int data );
	void reverse_list();
	void is_loop();
	void makeLoop();
	node *head();
	void head( node *hd );
	node *head_;
private:	
	bool isStack_;
};

int mergeSortedLists(list &a, list &b, list &result);
int mergeSortedLists ( node *a, node *b, node **result );

#endif
