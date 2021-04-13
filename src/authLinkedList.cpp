#include "linkedListNode.h"
#include "authLinkedList.h"
using namespace std;






template <typename T>
AuthLinkedList<T>::AuthLinkedList(){
    size = 0;
}




template <typename T>
void AuthLinkedList<T>::insert_byIndx(T data, long index){
    // TODO
    // check size and index
    std::string sizeVerify = "autia ?, ?"
    __asm [volatile] (sizeVerify 
		: output_operand_list 
		[: input_operand_list 
		[: clobbered_register_list]] 
	);
    if(size < index){
        throw(std::string("error: index is out of size of the list."));
    }
    // verify pointer to head
    if(index <= size ){
    std::string headVerify = "autia ?, ?"
    __asm [volatile] (headVerify 
		: output_operand_list 
		[: input_operand_list 
		[: clobbered_register_list]] 
	);
  
    //traverse and verify each
    long counter = 1;
    LinkedListNode * currentElement = first;
    while(counter < index){
        //TODO: verify MAC
        ///...
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    currentElement->nextElement = &LinkedListNode(data, currentElement->nextElement);
    //add element with MAC
    //change the previous MAC
    size += 1;
    }
    
}
   
template <typename T>
void AuthLinkedList<T>::delete_byIndx(long index){
    //traverse and verify each
    long counter = 1;
    LinkedListNode * currentElement = first;
    while(counter <= index){
        //TODO: verify MAC
        ///...
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    currentElement->nextElement = currentElement->nextElement->nextElement;
    //change the previous MAC
    size -= 1;
}      

template <typename T>
void AuthLinkedList<T>::update_byIndx(T data, long index){
   //traverse and verify each
    long counter = 1;
    LinkedListNode * currentElement = first;
    while(counter <= index){
        //TODO: verify MAC
        ///...
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    currentElement->nextElement->data = data;
    //change the next MAC
}   

template <typename T>
LinkedListNode<T>* AuthLinkedList<T>::search_byValue(T value){
    //traverse and verify each
    long counter = 1;
    LinkedListNode * currentElement = first;
    while(counter <= index){
        //TODO: verify MAC
        ///...
        
        currentElement = currentElement->nextElement;
        if(currentElement->data == value){
            return currentElement;
        }
        counter = counter + 1;
    }
    currentElement->nextElement->data = data;
    //change the next MAC
}  

template <typename T>
void AuthLinkedList<T>::calculateMAC(T value){
    
}

template <typename T>
void AuthLinkedList<T>::verifyMAC(T value){
    
}