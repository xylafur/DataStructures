#ifndef DOUBLE_LINKED_LIST
  #define DOUBLE_LINKED_LIST
  #include "LinkedList.h"

  template<class T> class DoubleLinkedList : public LinkedList<T>{
    protected:
      DoubleLinkedListNode<T> * head;
      DoubleLinkedListNode<T> * tail;

      void findTail(){
        DoubleLinkedListNode<T> * temp = head;
        int tempL = 1;
        while(temp != NULL && temp->getNext()!= NULL){
          temp = temp->getNext();
          tempL++;
        }
        this->length = tempL;
        tail = temp;
      }

    public:
      DoubleLinkedList() : LinkedList<T>(){

      }
      DoubleLinkedList(T val) : LinkedList<T>(val){
        head = new DoubleLinkedListNode<T>(val);
        findTail();
      }
      DoubleLinkedList(DoubleLinkedListNode<T> * pNode) : LinkedList<T>(pNode){
        head = pNode;
        findTail();
      }

  };
#endif
