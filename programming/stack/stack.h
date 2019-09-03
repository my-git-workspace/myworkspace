#ifndef STACK_H
#define STACK_H
#define BUFFER_SIZE 5
class stack {
	public:
		stack();
		void push( int dVal );
		int pop();
		void show();
		int size(){ return index==-1?0:index+1; }
	private:		
		int index;	
		int data[BUFFER_SIZE];
};
#endif
