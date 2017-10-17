#ifndef linked_list_h
#define linked_list_h

#define STR_LEN 32
typedef union data{
	int int_val;
	char str_val[STR_LEN];
}data;

typedef struct node{
	data d;
	struct node *next;	
}node;

//#define PUSH_ASC
node *createnode(int val);
void printlist(node *head, const char *str);
void deletenode(node *head, node *n);
void pushnode(node **head, int val);
node *mergelist(node *list_1, node *list_2);
void sortlist(node *head);
void reverselist(node **head);
void testlinkedlist();
#endif
