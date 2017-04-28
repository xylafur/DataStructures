#ifndef HASHMAP
    #define HASHMAP

#include <stdlib.h>
#include <functional>

template <class K, class V>
struct node{
    K key;
    V value;
    node * next = NULL;
};


template<class K, class V>
class HashMap{
private:
    std::hash<K> hasher;
    int arraySize = 7;
    node<K, V> ** arr;
    
    void deleteLinkedList(node<K, V> * head){
        node<K, V> * temp = head;
        while(temp!=NULL){
            delete(head);
            head = temp->next;
            temp = head;
        }
    }
public:
    HashMap<K, V>(){
        arr = new node<K, V> * [arraySize];
    }
    ~HashMap<K, V>(){
        for(int i = 0; i < arraySize; i++)
            deleteLinkedList(arr[i]);
    }
    void addElement(K key, V value){
        int pos = (int)( hasher(key) % arraySize);
        if( arr[pos] == NULL){
            arr[pos] = new node<K, V>;
            arr[pos]->value = value;
            arr[pos]->key = key;
        }
        else{
            node<K, V> * temp = arr[pos];
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = new node<K, V>;
            temp = temp->next;
            temp->value = value;
            temp->key = key;
        }
    }
    V getValue(K key){

    }
    void print(){
        std::cout<<"{ ";
        for(int i = 0; i < arraySize; i++){
            node<K, V> * temp = arr[i];
            while(temp != NULL){
                std::cout<<temp->key<<":"<<temp->value<<", ";
                temp = temp->next;
            }
        }
        std::cout<<" }"<<std::endl;
    }
};



#endif
