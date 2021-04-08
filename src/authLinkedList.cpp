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


