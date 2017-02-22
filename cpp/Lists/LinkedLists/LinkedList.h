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
        if(head==NULL)return;
        LinkedListNode<T> * temp = head;
        while(temp->getNext()!= NULL){
          temp = temp->getNext();
          this->length++;
        }
        tail = temp;
      }
      void initializeList(LinkedListNode<T> * pNode){
        this->head = pNode;
        this->tail = pNode;
        length = 1;
      }

    public:
      LinkedList(){
         head = NULL;
         tail = NULL;
         length = 0;
      }
      LinkedList(T val){
        initializeList( new LinkedListNode<T>(val) );
        findTail();
      }
      LinkedList(LinkedListNode<T> * pNode){
         initializeList(pNode);
         findTail();
      }
      ~LinkedList(){
        if(head == NULL)
          return;
        LinkedListNode<T> * temp = head->getNext();
        delete( head);
        while(temp!= NULL){
           head = temp;
          temp = temp->getNext();
          delete(head);
        }

      }
      void addToBeg(T val){
        addToBeg(new LinkedListNode<T>(val) );
      }
      void addToBeg(LinkedListNode<T> * pNode ){
        if(head == NULL)
          initializeList(pNode);
        else{
          pNode->setNext(this->head);
          this->head = pNode;
          this->length++;
        }
      }
      void addToEnd(T i){
        addToEnd(new LinkedListNode<T>(i) );
      }
      void addToEnd(LinkedListNode<T> * pNode){
        if(head==NULL)
          initializeList(pNode);
        else{
          this->tail->setNext(pNode);
          this->tail = pNode;
          this->tail->setNext(NULL);
          this->length++;
        }
      }

      LinkedListNode<T> * getHead(){
        return  this->head;
      }
      LinkedListNode<T> * getTail(){
        return  this->tail;
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
