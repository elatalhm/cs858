#pragma once



class AuthQueue
{
public:
	AuthQueue(unsigned int size);
	~AuthQueue();

	void enqueue(int input);
	int dequeue();
	int peek();
	bool isfull();
	bool isempty();
	bool search(int input);
	

private:
	long *putPT;
	long *getPT;
	long *queue;
	long prev_head;
	unsigned int size;
};