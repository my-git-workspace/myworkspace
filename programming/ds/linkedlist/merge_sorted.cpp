#include <linkedlist.h>
//move_node 
//src 1 2 3
//dest  4 5 6
//src  2 3
//dest 1 4 5 6
int move_node ( node **dest, node **src ) {
	node *temp = *src;
	*src = temp->next_;
	temp->next_ = *dest;
	*dest = temp;
	return 0;
}
int mergeSortedLists( list &alist, list &blist, list &result) {
	node dummy;
	dummy.next_ = NULL;
	node  *temp = &dummy;
	node *a = alist.head();
	node *b = blist.head();
	while (1) {
		if ( !a ) {
			temp->next_ = b;
			break;
		}else if ( !b ) {
			temp->next_ = a;
			break;
		}
		if( a->data_ <= b->data_ ){
			move_node( &(temp->next_), &a );
		}else{
			move_node( &(temp->next_), &b );
		}
		temp = temp->next_;

	}
	result.head(dummy.next_);
	printf("sorted merged !!!\n");
	result.show();
	return 0;
}

int mergeSortedLists ( node *a, node *b, node **result ){
	
	if( !a ) {
		(*result)=b;
		return 0;
	} else if (!b){
		(*result)=a;
		return 0;
	}
	if ( (a)->data_ <= (b)->data_ ) {
		move_node(result, &a);
	}else 
		move_node(result, &b);

	result=&((*result)->next_);

	mergeSortedLists(a,b,result);
	return 0;
}
