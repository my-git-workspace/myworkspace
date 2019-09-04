#include <iostream>

using namespace std;
#define BUFFER_SIZE 4

class TwoStacks{

	public:
		TwoStacks(){
			topOne_=-1;
			topTwo_=BUFFER_SIZE;
		}
		void push(int val, bool isTwo = false ){
			if( !isTwo ){ //stack one
				if( topOne_ < topTwo_ - 1 ){
					buffer_[++topOne_]=  val;		
				}else
					cout<<"Push:Not sufficient space"<<endl;		
			}else { 
			
				if( topOne_ < topTwo_ - 1 ){
					
					buffer_[--topTwo_]=  val;		
				}else
					cout<<"Push:Not sufficient space"<<endl;		
			}
		}
		int pop(bool isTwo=false ){
		        int val=-1;	
			if( !isTwo ){ //stack one
				if( topOne_ >= 0 ){
					val = buffer_[ topOne_-- ];		
				}else
					cout<<"Pop:Not sufficient space"<<endl;		
			}else { 
			
				if( topTwo_ < BUFFER_SIZE  ){
					
					 val = buffer_[topTwo_++] ;		
				}else
					cout<<"Pop:Not sufficient space"<<endl;		
			}
		
			return val;	
		}

		
	private:
		int topOne_;
		int topTwo_;
		int buffer_[BUFFER_SIZE];
};


int main( int argc, char **argv ){
	TwoStacks s;
	s.push(1);
	s.push(2);
	s.push(3,true);
	s.push(3,true);
	cout<<s.pop()<<endl;
	cout<<s.pop()<<endl;
	cout<<s.pop(true)<<endl;
	cout<<s.pop(true)<<endl;

	return (0);
}
