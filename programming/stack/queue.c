#include <stack.h>
#include <queue.h>

queue::queue(){
	
}

void queue::enqueue(int qVal){
	if( queueStack_.size() ){
		while( queueStack_.size() > 0 ){
			tempStack_.push(queueStack_.pop());
		}
	}
	tempStack_.push(qVal);
	while( tempStack_.size() > 0 ) {
			queueStack_.push(tempStack_.pop());
	}
}

int queue::dequeue(){
	return queueStack_.pop();
}
