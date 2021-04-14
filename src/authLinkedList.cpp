#include "linkedListNode.h"
#include "authLinkedList.h"
using namespace std;


template <typename T>
AuthLinkedList<T>::AuthLinkedList(){
    size = 0;
    id = rand() % 10000;
    size_MAC = calculateMACForSize(size, id);
    first = nullptr;
    calculateMACForPointers(first, (id.str()+"0").c_str());

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
    verifyMACForPointers(first, (id.str()+"0").c_str());
    //traverse and verify each
    int counter = 1;
    LinkedListNode * currentElement = first;
    LinkedListNode * previouselement = first;
    if(currentElement->m_MAC != calculateMACForElements(currentElement->data, (first.str() + currentElement->nextElement.str()).c_str())){
            throw(std::string("error: verification fail"));
        }
    while(counter < index){
        //TODO: verify MAC
        if(currentElement->nextElement->m_MAC != calculateMACForElements(currentElement->nextElement->data, (currentElement->nextElement.str() + currentElement->nextElement->nextElement.str() ).c_str())){
            throw(std::string("error: verification fail"));
        }
        previouselement = currentElement;
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    currentElement->nextElement = &LinkedListNode(data, currentElement->nextElement);
    currentElement->nextElement->m_MAC = calculateMACForElements(currentElement->nextElement->data, (currentElement->nextElement.str() + currentElement->nextElement->nextElement.str()).c_str() );
    currentElement->m_MAC = calculateMACForElements(currentElement->data, (previouselement->nextElement.str() + currentElement->nextElement.str()).c_str() );
    size += 1;
    size_MAC = calculateMACforSize(size, id);
    }
    else if (index == 1){
        verifyMACForPointers(first, (id.str()+"0").c_str());
        LinkedListNode * currentElement = first;
        if(first->m_MAC != calculateMACForElements(first->data,  (first.str() + first->nextElement.str() ).c_str())){
            throw(std::string("error: verification fail"));
        }
        currentElement->nextElement = &LinkedListNode(data, currentElement->nextElement);
        currentElement->nextElement->m_MAC = calculateMACForElements(currentElement->nextElement->data, (currentElement->nextElement.str() + currentElement->nextElement->nextElement.str()).c_str()  );
        currentElement->m_MAC = calculateMACForElements(currentElement->data, (first.str() + currentElement->nextElement.str()).c_str() );
        size += 1;
        size_MAC = calculateMACforSize(size, id);
    }
    else if (index == 0){
            verifyMACForPointers(first, (id.str()+"0").c_str());
            LinkedListNode* previous = first; 
            first = &LinkedListNode(data, previous);
            calculateMACForPointers(first, (id.str()+"0").c_str());
            first->m_MAC = calculateMACForElements(first->data, (first.str() + previous.str()).c_str());
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
    verifyMACForPointers(first, (id.str()+"0").c_str());
    //traverse and verify each
    if(index == 0){
        
        first = first->nextElement;
        calculateMACForPointers(first, (id.str()+"0").c_str());
        size -= 1;
        size_MAC = calculateMACforSize(size, id);
    }
    if(index == 1){
        if(first->m_MAC != calculateMACForElements(first->data, (first.str() + first->nextElement.str() ).c_str())){
            throw(std::string("error: verification fail"));
        }
        first->nextElement = first->nextElement->nextElement;
        calculateMACForElements(first->nextElement->data, (first.str() + first->nextElement->nextElement.str()).c_str());
        size -= 1;
        size_MAC = calculateMACforSize(size, id);
    }
    else{
    int counter = 1;
    LinkedListNode * currentElement = first;
    LinkedListNode * previousElement = first;
    if(first->m_MAC != calculateMACForElements(first->data, (first.str() + first->nextElement.str() ).c_str())){
            throw(std::string("error: verification fail"));
        }
    while(counter < index){
        //TODO: verify MAC
        if(currentElement->nextElement->m_MAC != calculateMACForElements(currentElement->nextElement->data, (currentElement->nextElement.str() + currentElement->nextElement->nextElement.str()).c_str())){
            throw(std::string("error: verification fail"));
        }
        previouselement = currentElement;
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    currentElement->nextElement = currentElement->nextElement->nextElement;
    currentElement->m_MAC = calculateMACForElements(currentElement->data,  (previousElement->nextElement.str() + currentElement->nextElement.str()).c_str());
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
        if(first->m_MAC != calculateMACForElements(first->data, (first.str() + first->nextElement.str()).c_str() )){
            throw(std::string("error: verification fail"));
        }
        first->data = data;
        first->m_MAC = calculateMACForElements(first->data, (first.str() + first->nextElement.str()).c_str() );
    }
    else{
   //traverse and verify each
    int counter = 1;
    LinkedListNode * currentElement = first;
    LinkedListNode * previousElement = first;
    if(first->m_MAC != calculateMACForElements(first->data, (first.str() + first->nextElement.str()).c_str() )){
            throw(std::string("error: verification fail"));
        }
    while(counter <= index){
        //TODO: verify MAC
        if(counter != size){
        if(currentElement->nextElement->m_MAC != calculateMACForElements(currentElement->nextElement->data, (currentElement->nextElement.str() + currentElement->nextElement->nextElement.str()).c_str() )){
            throw(std::string("error: verification fail"));
        }}
        previouselement = currentElement;
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    currentElement->data = data;
    currentElement->m_MAC = calculateMACForElements(currentElement->data, (previousElement->nextElement.str() + currentElement->nextElement.str()).c_str());
    
}   }

template <typename T>
LinkedListNode<T>* AuthLinkedList<T>::search_byValue(T value){
    if(size_MAC != calculateMACForSize(size, id)){
        throw(std::string("error: verification fail"));
    }
    verifyMACForPointers(first, id);
    //traverse and verify each
    int counter = 1;
    LinkedListNode * currentElement = first;
    if(first->m_MAC != calculateMACForElements(first->data, (first.str() + first->nextElement.str()).c_str() )){
            throw(std::string("error: verification fail"));
        }
    while(counter <= size){
        //TODO: verify MAC
        if(counter != size){
        if(currentElement->nextElement->m_MAC != calculateMACForElements(currentElement->nextElement->data, (currentElement->nextElement.str() + currentElement->nextElement->nextElement.str()).c_str() )){
            throw(std::string("error: verification fail"));
        }}
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