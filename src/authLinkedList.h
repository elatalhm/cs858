#pragma once

#include "linkedListNode.h"
using namespace std;

template <typename T>
class AuthLinkedList
{

   private:
   LinkedListNode<T> *first;
   //LinkedListNode *last;
   //LinkedListNode *middle;
   int size;
   int size_MAC;
   // register int id asm ("r0");
   int id;

   public:
   AuthLinkedList();
   ~AuthLinkedList();
   void insert_byIndx(T data, int index);
   void delete_byIndx(int index);
   T get_byIndx(int index);
   LinkedListNode<T>* search_byValue(T value);
   void update_byIndx(T data,int index);
   
   
   int calculateMACForSize(int left, int right);
   int calculateMACForElements(T left, const char* right);
   void calculateMACForPointers(LinkedListNode<T>* left, const char* right);
   void verifyMACForPointers(LinkedListNode<T>* left, const char* right);
};


