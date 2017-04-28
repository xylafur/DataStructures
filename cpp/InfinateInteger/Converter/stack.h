#ifndef LINKEDLIST_STACK
    #define LINKEDLIST_STACK

#include "../Lists/DoubleLinkedList.h"

template <class T>
class Stack{
private:
    DoubleLinkedList<T> * list;

public:
    Stack(){
        this->list = new DoubleLinkedList<T>();
    }
    ~Stack(){
        delete(list);
    }
    void push(T val){
        list->addToBeg(val);
    }
    T pop(){
        DoubleLinkedListNode<T> * temp = list->popHead();
        T tempVal = temp->getValue();
        delete(temp);
        return tempVal;
    }
    T peek(){
        return list->getHead()->getValue();
    }
    void print(){
        std::cout<<"Head"<<std::endl;
        DoubleLinkedListNode<T> * temp = this->list->getHead();
        while(temp!=NULL){
            std::cout << temp->getValue() << std::endl;
            temp=temp->getNext();
        }
    }
    void objectPrint(){
        std::cout<<"Head"<<std::endl;
        DoubleLinkedListNode<T> * temp = this->list->getHead();
        while(temp!=NULL){
            temp->getValue().print();
            temp=temp->getNext();
        }
    }
    bool isEmpty(){
        return this->list->getHead() == NULL;
    }
    int size(){
        DoubleLinkedListNode<T> * temp = this->list->getHead();
        int count = 0;
        while(temp!=NULL){
            count++;
            temp=temp->getNext();
        }
        return count;
    }

};

#endif
