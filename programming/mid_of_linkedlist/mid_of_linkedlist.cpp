#include <iostream>
using namespace std;
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
	list() {
		head_ = NULL;
	}
	
	void insert(int data){
		node *n = new node( NULL, data);
		if(!head_){
			head_ = n;
		}else{
			n->next_ = head_;
			head_ = n;
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
		cout<< slow->next_->data_ <<endl;

	}
private:	
	node *head_;
};

int main(int argc, char **argv){
	list l;

	for ( int i = 1; i <5 ; i++ ) {
		l.insert(i);
	}
	l.show();
	l.mid_of_list();
	//return 
	return 0;
}
