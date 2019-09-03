#include <queue.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv){

/*	
	stack s;
	cout<<s.size()<<endl;
	s.push(1);
	s.push(1);
	s.push(1);
	s.push(1);
	s.push(1);
	s.push(1);
	cout<<s.size()<<endl;
        s.pop();
        s.pop();
        s.pop();
        s.pop();
        s.pop();
        s.pop();
	cout<<s.size()<<endl;
*/
	queue q;

	cout<<"11111111111111111111"<<endl;

	q.enqueue(1);
	cout<<"2222222222222222"<<endl;
	q.enqueue(2);
	cout<<"333333333333"<<endl;
	q.enqueue(3);

	cout<<q.dequeue()<<endl;
	cout<<q.dequeue()<<endl;
	cout<<q.dequeue()<<endl;
	//return main
	return (0);
}
