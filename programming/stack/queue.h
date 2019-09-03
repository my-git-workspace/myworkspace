#ifndef QUEUE_H
#define QUEUE_H

#include <stack.h>

class queue{
	public:
		queue();
		void enqueue(int qVal);
		int dequeue();
		int size() { return queueStack_.size(); }
	private:
		stack queueStack_;  
		stack tempStack_;
};

#endif
