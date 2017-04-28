#ifndef LINKED_LIST_NODES
  #define LINKED_LIST_NODES
  #include <stdlib.h>
  #include "Nodes.h"
    #include <iostream>

template <class T> class LinkedListNode : public Node<T> {
protected:
  LinkedListNode<T> * next;
public:
  LinkedListNode(T val){
    this->value = val;
    this->next = NULL;
  }
  LinkedListNode(){
    this->next = NULL;
  }
  LinkedListNode * getNext(){
    return this->next;
  }
  void setNext(LinkedListNode * pNode){
    this->next = pNode;
  }
};

template <class T> class DoubleLinkedListNode : public LinkedListNode<T>{
  protected:
    DoubleLinkedListNode<T> * next;
    DoubleLinkedListNode<T> * prev;
  public:
    DoubleLinkedListNode(T val) : LinkedListNode<T>(val){
      this->prev = NULL;
    }
    DoubleLinkedListNode() : LinkedListNode<T>(){
        this->prev = NULL;
    }
    DoubleLinkedListNode * getNext(){
      return this->next;
    }
    void setNext(DoubleLinkedListNode * pNode){
      if(pNode==NULL)return;
      this->next = pNode;
      pNode->prev = this;
    }
    DoubleLinkedListNode * getPrev(){
      return this->prev;
    }
    void setPrev(DoubleLinkedListNode * pNode){
      if(pNode==NULL)return;
      this->prev = pNode;
      pNode->next = this;
    }

};

#endif
