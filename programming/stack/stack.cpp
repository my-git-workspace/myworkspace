#include <iostream>
#include <stack.h>

using namespace std;
stack::stack(){
	index=-1;
}

void stack::push( int dVal ){
	//cout<<"push("<< dVal <<")"<<endl;
	if ( index == BUFFER_SIZE - 1 ){
		cout<<"stack full !!!"<<endl;
		return ;
	}
	data[++index] =  dVal;
}
int stack::pop(){
	if( index <= -1 ){
		cout<<"stack empty !!!"<<endl;
		return -1;
	}
	int pVal=data[index--];
	//cout<<"pop("<< pVal <<")"<<endl;
	return pVal;
}
void stack::show(){
	cout<<"stack:"<<endl;
	for ( int i=0; i<=index;i++ ){
		cout<<"["<<data[i]<<"] " <<endl;
	}
}
/*
int main(int argc, char **argv){
	stack s;
	for (int i=0;i<=BUFFER_SIZE;i++){
		s.push((i+1)*100);
	}
	s.show();
	for(int i=0;i<=BUFFER_SIZE;i++){
		s.pop();	
	}
	//return main
	return (0);
}

*/
