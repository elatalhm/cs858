#include "linkedListNode.h"
#include "authLinkedList.h"
using namespace std;


#define do_inline_asm(asm_string, pre, post) do {           \
        uint64_t start;                                     \
        uint64_t end;                                       \
        register unsigned long a asm ("r13") = UINT64_MAX;  \
        register unsigned long b asm ("r12") = 3;           \
        do {                                                \
            start = rdtscp();                               \
            for (int i = 0 ; i < r; ++i) {                  \
                register long rax asm ("rax") = a;          \
                asm volatile(                               \
                    pre                                     \
                    repeat100(asm_string"       ;\n")       \
                    post                                    \
                    : [a] "+r" (a)                          \
                    : [b] "r" (b)                           \
                    : "rax", "rdx");                        \
                a = rax;                                    \
            }                                               \
            end = rdtscp();                                 \
        } while(f);                                         \
    } while(0)




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
    if(index < size ){
    std::string headVerify = "autia ?, ?"
    __asm [volatile] (headVerify 
		: output_operand_list 
		[: input_operand_list 
		[: clobbered_register_list]] 
	);}
    else{// verify pointer to tail
        std::string tailVerify = "autia ?, ?"
    __asm [volatile] (tailVerify 
		: output_operand_list 
		[: input_operand_list 
		[: clobbered_register_list]] 
	);
    }
    //traverse and verify each
    long counter = 1;
    LinkedListNode * currentElement = first;
    while(counter < index){
        //TODO: verify MAC
        ///...
        currentElement = currentElement->nextElement;
        counter = counter + 1;
    }
    //add element with MAC
    //change the previous
    //
    
}
   
template <typename T>
void AuthLinkedList<T>::delete_byIndx(long index){
    
}      

template <typename T>
void AuthLinkedList<T>::update_byIndx(T data, long index){

}   

template <typename T>
LinkedListNode<T>* AuthLinkedList<T>::search_byValue(T value){
    
}  


