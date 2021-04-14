#include "authqueue.h"

#include <iostream>
#include <cstdlib>
#include <cstring>

AuthQueue::AuthQueue(unsigned int size)
{
	queue = new long[size+1];
	size = size;
	putPT = queue;
	getPT = queue;
	
	// set a random number as initial prev_head
	srand (time(NULL));
	prev_head = rand();
	// TODO: previous head in secure register
	// add PAC(tail, prev_head) to putPT, since we don't have tail yet we use tail = prev_head
	putPT = calculatePACForPutPT(putPT, prev_head & prev_head);

}

AuthQueue::~AuthQueue()
{
	// TODO: zero queue
	//delete[] queue;
}

bool AuthQueue::isfull()
{
	if(putPT+1 == getPT)
		return true;
	if(putPT-size == getPT)
		return true;
	return false;
}

bool AuthQueue::isempty()
{
	if(getPT == putPT)
		return true;
	return false;
	
}

int AuthQueue::dequeue()
{
	// check that queue is not empty
	if(getPT == putPT){
		throw(std::string("error: queue is empty"));
		return 0;
	}

	long out = *getPT; 
	// remove MAC from out (or clean 32 upper bits)
	long temp = ((out >> 32) << 32); 
	int out_value = (int)(out - temp);

	// verify integrity:
	if (calculateMACForElement(out_value, prev_head) != out){
		throw(std::string("error: verification fail"));
		return 0;
	}

	getPT ++;
	if(getPT>queue+size)
		getPT = queue;
	// put the prev_head in secure register
	prev_head = out; // TODO: in secure reg
	return out_value;
}

int AuthQueue::peek()
{
	// check that queue is not empty
	if(getPT == putPT){
		throw(std::string("error: queue is empty"));
		return 0;
	}

	long out = *getPT; 
	// remove MAC from out (or clean 32 upper bits)
	long temp = ((out >> 32) << 32); 
	int out_value = (int)(out - temp);

	// verify integrity:
	if (calculateMACForElement(out_value, prev_head) != out){
		throw(std::string("error: verification fail"));
		return 0;
	}

	
	return out_value;
}

void AuthQueue::enqueue(int input)
{
	// check that queue is not full
	if(putPT+1 == getPT)
		return;
	if(putPT-size == getPT)
		return;
	int tail;
	if(putPT == queue)
		tail = *(queue+size);
	else
		tail = *(putPT-1);
	// verify putPT using tail and prev_head
	if (putPT != calculatePACForPutPT(putPT, prev_head & tail)){
		throw(std::string("error: verification fail"));
		return;
	}

	long new_tail = calculateMACForElement(input, tail); // calculate MAC using tail and add to input
	*putPT = new_tail;

	putPT++; // update putPT and recompute PAC
	if(putPT>queue+size)
		putPT = queue;
	putPT = calculatePACForPutPT(putPT, prev_head & new_tail);

	return;
}

bool AuthQueue::search(int input)
{
	// check that queue is not empty
	if(getPT == putPT){
		return false;
	}

	long* iterator;
	long prev_element;
	int element;
	prev_element = prev_head;
	iterator = getPT;
	while (iterator!=putPT){

		// remove MAC (or clean 32 upper bits)
		long temp = ((*iterator >> 32) << 32); 
		element = (int)(*iterator - temp);


		// verify integrity:
		if (calculateMACForElement(element, prev_element) != *iterator){
			throw(std::string("error: verification fail"));
			return 0;
		}

		if (element==input){
			return true;
		}

		iterator++; // update putPT and recompute PAC
		if(iterator>queue+size)
			iterator = queue;

		prev_element = *iterator;

	}
	
	return false;
}

__attribute__ ((always_inline))
long* calculatePACForPutPT(long *putPT, long tail_prev_head){
   

	// return H(left || right)
	register long* l asm ("x20") = putPT;
	register long r asm ("x21") = tail_prev_head;
	register long* result asm ("x22");

	__asm__ volatile (
		"pacga %[result], %[l], %[r]"
		: [result] "=r" (result)
		: [l] "r" (l), [r] "r" (r)
		:
	);

	return result;

}

__attribute__ ((always_inline))
long calculateMACForElement(int value, long prev_element){
   

	// return H(left || right)
	register int l asm ("x20") = value;
	register long r asm ("x21") = prev_element;
	register long result asm ("x22");

	__asm__ volatile (
		"pacga %[result], %[l], %[r]"
		: [result] "=r" (result)
		: [l] "r" (l), [r] "r" (r)
		:
	);

	return result;

}