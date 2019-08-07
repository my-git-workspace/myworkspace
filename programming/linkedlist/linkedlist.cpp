#include <iostream>
using namespace std;


//input 1 2 3 4 5
//stack 5 4 3 2 1
//queue 1 2 3 4 5
class node{
	public:
	node( node *next = NULL, int data = 0 ){
		next_ = next;
		data_ = data;
	}
	int data_;
	node *next_;
};

class list {
public:
	list(bool isStack = false ) {
		head_ = NULL;
		isStack_ = isStack;
	}
	
	void insert(int data){
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
	void show(){
		node *curr = head_;
		while(curr){
			cout<< curr->data_ <<" ";
			curr = curr->next_;
		}
		cout<<endl;
	}
	void mid_of_list(){
		node *slow = head_;
		node *fast = head_->next_;		
		while ( slow->next_ && fast->next_ && fast->next_->next_ ) {
			slow = slow->next_;
			fast = fast->next_->next_;
		}
		cout<<__func__<<endl;
		cout<<"node: "<<slow->next_->data_ <<endl;

	}
	void getnode_n( int index ){
		node *n = head_;	
		int i = 0;
		while ( n && i < index ){
			i++;
			n = n->next_;
		}
		cout<<__func__<<"( "<<index<<" )"<<endl;
		cout<<"node: "<<n->data_ <<endl;
	}
	void getnode_n_from_last(int index){
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
	void getnode_n_from_last_using_pointers( int index ){
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
	void delete_list_data(){
		node *temp;
		cout<<__func__<<" "<<head_<<endl;
		while(head_){
			temp = head_->next_;	
			delete head_;
			head_ = temp;
		}	
		cout<<__func__<<" "<<head_<<endl;
	}
	void data_occurences(int data){
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
	void reverse_list(){
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
	void is_loop(){
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
	void makeLoop(){
		node *curr = head_;
		while ( curr->next_ ){
			curr = curr->next_;
		}
		curr->next_ = head_->next_;
	}
private:	
	node *head_;
	bool isStack_;
};

int main(int argc, char **argv){
	bool isStack_ = false;
	list l( isStack_ );

	for ( int i = 1; i < 6 ; i++ ) {
		l.insert(i);
	}
	l.show();
	
	//l.mid_of_list();
	//l.getnode_n(4);
	//l.getnode_n_from_last(0);
	//l.getnode_n_from_last_using_pointers(1);
	//l.delete_list_data();
	//l.data_occurences(9);
	//l.reverse_list();
	//l.makeLoop();
	//l.is_loop();
	//l.show();
	//return 
	return 0;
}
