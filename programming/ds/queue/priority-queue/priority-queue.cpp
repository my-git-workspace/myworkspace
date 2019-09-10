#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class int_pqueue {

	public:
		void enqueue(int i){
			q_.push_back(i);
			push_heap(q_.begin(), q_.end(), c_);
		}

		bool dequeue(int *out){
			if(q_.size()>0){
				std::pop_heap( q_.begin(), q_.end(), c_ );
				*out=q_.back();
				q_.pop_back();
				return true;
			}
			return false;		
		}
		
	protected:

		class comparator {
			public:
				bool operator() (int &i1, int &i2){
					if(i1>i2){
						return true;
					}
					return false;
				} 
		};

	private:
		std::vector <int> q_;
		comparator c_;	
};

int main(int argc, char **argv){
	int_pqueue iq;
	iq.enqueue(10);
	iq.enqueue(1);
	iq.enqueue(20);
	iq.enqueue(3);
	iq.enqueue(2);

	int i;

	iq.dequeue(&i);
	cout<<i<<endl;
	
	iq.dequeue(&i);
	cout<<i<<endl;


	iq.dequeue(&i);
	cout<<i<<endl;
	
	iq.dequeue(&i);
	cout<<i<<endl;

	//return 0
	return (0);
}
