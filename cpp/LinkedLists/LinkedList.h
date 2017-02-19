#ifndef LINKED_LIST_CLASS
  #define LINKED_LIST_CLASS
  #include "LinkedListNodes.h"
  #include <string>
  #include <iostream>

  using namespace std;

  template <class T> class LinkedList{
    protected:
      LinkedListNode<T> * head;
      LinkedListNode<T> * tail;
      int length;

      void findTail(){
        LinkedListNode<T> * temp = head;
        int tempL = 1;
        while(temp != NULL && temp->getNext()!= NULL){
          temp = temp->getNext();
          tempL++;
        }
        length = tempL;
        tail = temp;
      }


    public:
      LinkedList(){
         head = NULL;
         tail = NULL;
         length = 0;
      }
      LinkedList(LinkedListNode<T> * node){
         length = 1;
         head = node;
         findTail();
      }
      ~LinkedList(){
        LinkedListNode<T> * temp = head->getNext();
        delete( head);
        while(temp!= NULL){
           head = temp;
          temp = temp->getNext();
          delete(head);
        }

      }
      void addToBeg(T i){
        addToBeg(new LinkedListNode<T>(i) );
      }
      void addToBeg(LinkedListNode<T> * pNode ){
        findTail();
        pNode->setNext( head);
         head = pNode;
         length++;
      }
      void addToEnd(T i){
        addToEnd(new LinkedListNode<T>(i) );
      }
      void addToEnd(LinkedListNode<T> * pNode){
        findTail();
        if(tail == NULL){
          if(head ==NULL)
            head = pNode;
          tail = pNode;
          findTail();
          return;
        }
         tail->setNext(pNode);
         tail = pNode;
         length++;
      }

      LinkedListNode<T> * getHead(){
        return  head;
      }
      LinkedListNode<T> * getTail(){
        return  tail;
      }
      void printList(){
        LinkedListNode<T> * temp = head;
        for(int i = 0; i < length; i++)
          cout << "[" << i << "], \t";
        cout << endl;
        for( int i = 0; i < length; i++){
          cout << " " << temp->getValue() << "\t" ;
          temp = temp->getNext();
        }
        cout << endl;
      }

  };


#endif
