#include "sorting-algo.h"
#include "linked-list.h"

node *createnode(int val){
	node *temp=(node *)malloc(sizeof(node));
	temp->d.int_val=val;
	temp->next=NULL;
	//printf("createnode: %p : data: %d\n", temp, temp->d.int_val);
	return temp;
}

void printlist(node *head, const char *str){
	printf("%s", str);
	node *temp=head;
	while(temp){
		printf("node: %p : data: %d\n", temp, temp->d.int_val);
		temp=temp->next;
	}
}
void deletenode(node *head, node *n){
	if(head==n && head->next){
		head->d.int_val=head->next->d.int_val;
		n=head->next;
		head->next=head->next->next;
		free(n);
		return;
	}
	while(head->next && head->next != n){
		head=head->next;			
	}
	if(head->next==NULL)	{
		printf("node : %p not present\n", head->next);
		return;
	}
		head->next=head->next->next;		
		free(n);
}

#ifndef PUSH_ASC 
void pushnode(node **head, int val){
	if(*head==NULL){
		*head=createnode(val);
		return;	
	}
	node *firstnode=*head;
	while(firstnode->next){
		firstnode=firstnode->next;
	}
	firstnode->next=createnode(val);	
	
}
#endif



#ifdef PUSH_ASC
void pushnode(node **head, int val){
	node *newnode=createnode(val);
	node *headref=*head;
	if(*head==NULL || headref->d.int_val > newnode->d.int_val){
		newnode->next=*head;
		*head=newnode;
	}else{
		/* //without prev 
		headref=*head;		
		while(headref->next && headref->next->d.int_val < newnode->d.int_val){
			headref=headref->next;
		}
		newnode->next=headref->next;
		headref->next=newnode;
		*/
		//with prev
		headref=*head;
		node *prev=NULL;
		while(headref && headref->d.int_val < newnode->d.int_val){
			prev=headref;
			headref=headref->next;
		}
		prev->next=newnode;
		newnode->next=headref;
		
		


	}
}
#endif


node *mergelist(node *list_1, node *list_2){
	node *head=NULL;
	if(list_1)
		head=list_1;	
	while(list_1->next){
		list_1=list_1->next;	
	}
	if(list_2)
		list_1->next=list_2;	
	return head;		
}
void swapval(int *n1, int *n2){
	int temp=*n1;
	*n1=*n2;
	*n2=temp;
}
void sortlist(node *head){
	int swapped=0;	
	node *temp=head;
	node *valid=NULL;	
	do {	
		swapped=0;
		temp=head;	
		while(temp->next !=valid){
			if(temp->d.int_val > temp->next->d.int_val){
				swapval(&(temp->d.int_val), &(temp->next->d.int_val));
				swapped=1;
			}	
			temp=temp->next;
		}	
		valid=temp;
	}while(swapped);


}
void reverselist(node **head){
	node *headref=*head;
	node *current=headref;
	node *prev=NULL;
	node *next=NULL;
	while(current){
		next=current->next;  //take next copy
		current->next=prev; //make reverse here 
		prev=current;       //make prev as current
		current=next;       //make current as next
			
	}
	*head=prev;
}
void testlinkedlist(){

	node *list_1=NULL;	
	node *list_2=NULL;	

	pushnode(&list_1, 5);
	pushnode(&list_1, 34);
	pushnode(&list_1, 19);
	pushnode(&list_1, -4);
	printlist(list_1, "@@@ list-1 @@@\n");
	//reverselist(&list_1);
	//printlist(list_1, "@@@ reverse list-1 @@@\n");

	//deletenode(list_1, list_1);	
	//printlist(list_1, "@@@ delete node @@@\n");
	pushnode(&list_2, 42);
	pushnode(&list_2, 23);
	pushnode(&list_2,11);
	pushnode(&list_2, 54);
	printlist(list_2, "\n@@@ list-2 @@@\n");
	
	node *mergedlist=mergelist(list_1, list_2);
	printlist(mergedlist, "\n@@@ marged list @@@\n");
	sortlist(mergedlist);
	printlist(mergedlist, "\n@@@ sorted list @@@\n");
	
}
