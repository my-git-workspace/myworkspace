#include <iostream>
#include <linkedlist.h>
using namespace std;


//input 1 2 3 4 5
//stack 5 4 3 2 1
//queue 1 2 3 4 5
node::node( node *next , int data ){
		next_ = next;
		data_ = data;
}

list::list ( bool isStack ) {
	head_ = NULL;
	isStack_ = isStack;
}

void list::insert( int data ) {
	cout << "insert: " <<data<<endl;
	node *n = new node( NULL, data);
	if (!head_) {
		head_ = n;
	} else {
		if ( isStack_ ){
		   n->next_ = head_;
		   head_ = n;
		} else {
			node *tmp=head_;		
			while ( tmp->next_ ) {
				tmp = tmp->next_;
			}	
			tmp->next_=n;	
		}
	}	


}
void list::show () {
	node *curr = head_;
	while(curr){
		cout<< curr->data_ <<" ";
		curr = curr->next_;
	}
	cout<<endl;
}
void list::mid_of_list(){
	node *slow = head_;
	node *fast = head_->next_;		
	while ( slow->next_ && fast->next_ && fast->next_->next_ ) {
		slow = slow->next_;
		fast = fast->next_->next_;
	}
	cout<<__func__<<endl;
	cout<<"node: "<<slow->next_->data_ <<endl;

}
void list::getnode_n( int index ){
	node *n = head_;	
	int i = 0;
	while ( n && i < index ){
		i++;
		n = n->next_;
	}
	cout<<__func__<<"( "<<index<<" )"<<endl;
	cout<<"node: "<<n->data_ <<endl;
}
void list::getnode_n_from_last(int index){
	node *n =  head_;
	int len = 0;
	while (n){
		n = n->next_;
		len++;
	}
	cout<<"len: "<<len<<endl;
	n = head_;
	int i = len;
	while ( n && (i-1)  > index ){
		n = n->next_;
		i--;
	}
	cout<<__func__<<"( "<<index<<" )"<<endl;
	cout<<"node: "<<n->data_ <<endl;

}
void list::getnode_n_from_last_using_pointers( int index ){
	node *refptr =  head_;
	node *mainptr =  head_;
	int i = 0;
	while ( refptr ){
		refptr = refptr->next_;
		if ( i == index )
			break;
		i++;	
	}
	while( refptr ){
		refptr = refptr->next_;
		mainptr = mainptr->next_;
	}
	cout<<__func__<<"( "<<index<<" )"<<endl;
	cout<<"node: "<<mainptr->data_ <<endl;
}
void list::delete_list_data(){
	node *temp;
	cout<<__func__<<" "<<head_<<endl;
	while(head_){
		temp = head_->next_;	
		delete head_;
		head_ = temp;
	}	
	cout<<__func__<<" "<<head_<<endl;
}
void list::data_occurences(int data){
	node *temp = head_;
	int count = 0;
	while(temp){
		if( temp->data_ == data ){
			count++;
		}
		temp = temp->next_;
	}
	
	cout<<__func__<<endl;
	cout<<"data: "<<data<<" "<<count<<" occurence."<<endl;
}
void list::reverse_list(){
	cout<<__func__<<endl;
	node *prev = NULL;
	node *curr = head_;
	node *next = NULL;
	while(curr){
		next = curr->next_;
		curr->next_ = prev;
		prev = curr;
		curr = next;
	}
	head_ = prev;	
}
void list::is_loop(){
	node *r1 = head_;
	node *r2 = head_->next_;
	node *r3 = head_->next_->next_;
	bool isLoop = false;
	while ( r1 && r2 && r3 ){
		if ( r1 == r2 || r1==r3 ){
			isLoop = true;	
			break;
		}
		r1 = r1->next_;
		r2 = r2->next_;
		if( r3->next_ )
			r3 = r3->next_->next_;

	}
	cout<<__func__<<endl;
	cout <<"is_loop: "<<isLoop<<endl;


}
void list::makeLoop(){
	node *curr = head_;
	while ( curr->next_ ){
		curr = curr->next_;
	}
	curr->next_ = head_->next_;
}
node *list::head(){ return head_; }
void list::head( node *hd ){ head_=hd; }

int main(int argc, char **argv){
	list a;
	list b;

	a.insert(1);
	a.insert(3);
	//a.show();
	b.insert(2);
	b.insert(4);
	b.insert(6);
	b.insert(7);
	b.insert(8);
	b.insert(18);
	//b.show();
	
	//list result;
	//mergeSortedLists( a, b, result );

	node *temp=NULL;
	node **sort = &temp;
	mergeSortedLists( (a.head_), (b.head_), sort );
	list res;
	res.head(temp);
	res.show();

	node *curr=res.head();
	node *prev=NULL;
	node *next=NULL;
	reverseList(&curr,&prev,&next);

	list rev;
	rev.head(curr);
	rev.show();
		
	return 0;
}
