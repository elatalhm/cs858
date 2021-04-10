#include "linkedListNode.h"
using namespace std;

template <typename T>
class AuthLinkedList
{

   private:
   LinkedListNode *first;
   LinkedListNode *last;
   //LinkedListNode *middle;
   long size;


   public:
   AuthLinkedList();
   ~AuthLinkedList();
   void insert_byIndx(T data, long index);
   void delete_byIndx(long index);
   T get_byIndx(long index);
   LinkedListNode<T>* search_byValue(T value);
   void update_byIndx(T data,long index);
};


