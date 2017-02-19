#ifndef LINKED_LIST_NODES
  #define LINKED_LIST_NODES
  #include <stdlib.h>

template <class T> class LinkedListNode{
  protected:
    T value;
    LinkedListNode<T> * next;
  public:
    LinkedListNode(T val){
      this->value = val;
      this->next = NULL;
    }
    LinkedListNode * getNext(){
      return this->next;
    }
    void setNext(LinkedListNode * pNode){
      this->next = pNode;
    }
    T getValue(){
      return this->value;
    }
    void setValue(T val){
      this->value = val;
    }

};

template <class T> class DoubleLinkedListNode : public LinkedListNode<T>{
  protected:
    DoubleLinkedListNode * next;
    DoubleLinkedListNode * prev;
  public:
    DoubleLinkedListNode(T val) : LinkedListNode<T>(val){
      this->prev = NULL;
    }
    DoubleLinkedListNode * getNext(){
      return this->next;
    }
    void setNext(DoubleLinkedListNode * pNode){
      this->next = pNode;
    }
    DoubleLinkedListNode * getPrev(){
      return this->prev;
    }
    void setPrev(DoubleLinkedListNode * pNode){
      this->prev = pNode;
    }
};

#endif
