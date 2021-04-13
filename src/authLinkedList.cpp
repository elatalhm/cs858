#include "linkedListNode.h"
#include "authLinkedList.h"
using namespace std;


template <typename T>
AuthLinkedList<T>::AuthLinkedList(){
    size = 0;
    id = rand() % 10000;
    size_MAC = calculateMACForSize(size, id);
    first = nullptr;
    calculateMACForPointers(first, id);

}



template <typename T>
void AuthLinkedList<T>::insert_byIndx(T data, int index){
    
    // check size and index
    if(size_MAC != calculateMACForSize(size, id)){
        throw(std::string("error: verification fail"));
    }
    if(size < index){
        throw(std::string("error: index is out of size of the list."));
    }
    if(index >= 2){    // verify pointer to head
    verifyMACForPointers(first, id);
    //traverse and verify each
    int counter = 1;
    LinkedListNode * currentElement = first;
    LinkedListNode * previouselement = first;
    while(counter < index){
        //TODO: verify MAC
        if(currentElement->nextElement->m_MAC != calculateMAC(currentElement->nextElement->data, currentElement->nextElement->nextElement + currentElement->nextElement)){
            throw(std::string("error: verification fail"));
        }
        previouselement = currentElement;
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    currentElement->nextElement = &LinkedListNode(data, currentElement->nextElement);
    currentElement->nextElement->m_MAC = calculateMAC(currentElement->nextElement->data, currentElement->nextElement->nextElement + currentElement->nextElement );
    currentElement->m_MAC = calculateMAC(currentElement->data, currentElement->nextElement + previouselement->nextElement);
    size += 1;
    size_MAC = calculateMACforSize(size, id);
    }
    else if (index == 1){
        verifyMACForPointers(first, id);
        LinkedListNode * currentElement = first;
        currentElement->nextElement = &LinkedListNode(data, currentElement->nextElement);
        currentElement->nextElement->m_MAC = calculateMAC(currentElement->nextElement->data, currentElement->nextElement->nextElement + currentElement->nextElement );
        currentElement->m_MAC = calculateMAC(currentElement->data, currentElement->nextElement + first);
        size += 1;
        size_MAC = calculateMACforSize(size, id);
    }
    else if (index == 0){
        
            LinkedListNode* previous = first; 
            first = &LinkedListNode(data, previous);
            first->m_MAC = calculateMAC(first->data, first + previous);
            size += 1;
            size_MAC = calculateMACforSize(size, id);
        
    }
}
   
template <typename T>
void AuthLinkedList<T>::delete_byIndx(int index){
    // check size and index
    if(size_MAC != calculateMACForSize(size, id)){
        throw(std::string("error: verification fail"));
    }
    if(size <= index){
        throw(std::string("error: index is out of size of the list."));
    }
    verifyMACForPointers(first, id);
    //traverse and verify each
    if(index == 0){
        first = first->nextElement;
        calculateMACForPointers(first, id);
    }
    else{
    int counter = 1;
    LinkedListNode * currentElement = first;
    LinkedListNode * previousElement = first;
    while(counter < index){
        //TODO: verify MAC
        if(currentElement->nextElement->m_MAC != calculateMAC(currentElement->nextElement->data, currentElement->nextElement->nextElement + currentElement->nextElement)){
            throw(std::string("error: verification fail"));
        }
        previouselement = currentElement;
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    currentElement->nextElement = currentElement->nextElement->nextElement;
    currentElement->m_MAC = calculateMAC(currentElement->data, currentElement->nextElement + previousElement->nextElement);
    size -= 1;
    size_MAC = calculateMACforSize(size, id);
    }
}      

template <typename T>
void AuthLinkedList<T>::update_byIndx(T data, int index){
    if(size_MAC != calculateMACForSize(size, id)){
        throw(std::string("error: verification fail"));
    }
    if(size <= index){
        throw(std::string("error: index is out of size of the list."));
    }
    verifyMACForPointers(first, id);
    if(index == 0){
        first->data = data;
        first->m_MAC = calculateMAC(first->data, first->nextElement + first);
    }
    else{
   //traverse and verify each
    int counter = 1;
    LinkedListNode * currentElement = first;
    LinkedListNode * previousElement = first;
    while(counter <= index){
        //TODO: verify MAC
        if(currentElement->nextElement->m_MAC != calculateMAC(currentElement->nextElement->data, currentElement->nextElement->nextElement + currentElement->nextElement)){
            throw(std::string("error: verification fail"));
        }
        previouselement = currentElement;
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    currentElement->data = data;
    currentElement->m_MAC = calculateMAC(currentElement->data, currentElement->nextElement + previousElement->nextElement);
    
}   }

template <typename T>
LinkedListNode<T>* AuthLinkedList<T>::search_byValue(T value){
    if(size_MAC != calculateMACForSize(size, id)){
        throw(std::string("error: verification fail"));
    }
    //traverse and verify each
    int counter = 1;
    LinkedListNode * currentElement = first;
    while(counter <= size){
        //TODO: verify MAC
        if(currentElement->nextElement->m_MAC != calculateMAC(currentElement->nextElement->data, currentElement->nextElement->nextElement + currentElement->nextElement)){
            throw(std::string("error: verification fail"));
        }
        currentElement = currentElement->nextElement;
        if(currentElement->data == value){
            return currentElement;
        }
        counter = counter + 1;
    }
   
    return nullptr;
}  

 
template <typename T>
__attribute__ ((always_inline))
int AuthLinkedList<T>::calculateMACForElements(T left, const char* right){
   

	// return H(left || right)
	register T l asm ("x20") = left;
	register const char* r asm ("x21") = right;
	register int result asm ("x22");

	__asm__ volatile (
		"pacga %[result], %[l], %[r]"
		: [result] "=r" (result)
		: [l] "r" (l), [r] "r" (r)
		:
	);

	return result;

}

template <typename T>
__attribute__ ((always_inline))
int AuthLinkedList<T>::calculateMACForSize(int left, int right){
   

	// return H(left || right)
	register int l asm ("x20") = left;
	register int r asm ("x21") = right;
	register int result asm ("x22");

	__asm__ volatile (
		"pacga %[result], %[l], %[r]"
		: [result] "=r" (result)
		: [l] "r" (l), [r] "r" (r)
		:
	);

	return result;

}

template <typename T>
__attribute__ ((always_inline))
void AuthLinkedList<T>::calculateMACForPointers(LinkedListNode<T>* left, const char* right){
   

	// return H(left || right)
	register int l asm ("x20") = left;
	register const char* r asm ("x21") = right;
	register int result asm ("x22");

	__asm__ volatile (
		"pacix %[l], %[r]"
		: [l] "r" (l), [r] "r" (r)
		:
	);

	

}

template <typename T>
__attribute__ ((always_inline))
void AuthLinkedList<T>::verifyMACForPointers(LinkedListNode<T>* left, const char* right){
   

	// return H(left || right)
	register int l asm ("x20") = left;
	register const char* r asm ("x21") = right;
	register int result asm ("x22");

	__asm__ volatile (
		"autix %[l], %[r]"
		: [l] "r" (l), [r] "r" (r)
		:
	);

	

}