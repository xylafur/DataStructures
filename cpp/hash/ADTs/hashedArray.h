//
// Created by Aaron on 4/5/2017.
//

#ifndef HASHEDARRAY
#define HASHEDARRAY
#include <iostream>
#include <stdlib.h>
#include <functional>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std::chrono;

template <class V>
struct hashedArrayNode{
    V value;
    hashedArrayNode * next = NULL;
};

template <class T>
class HashedArray{
private:
    std::hash<T> hasher;
    int arraySize = 7;
    hashedArrayNode<T> ** arr;

    void deleteLinkedList(hashedArrayNode<T> * head){
        hashedArrayNode<T> * temp = head;
        while(temp!=NULL){
            delete(head);
            head = temp->next;
            temp = head;
        }
    }

public:
    HashedArray<T>(){
        arr = new hashedArrayNode<T> * [this->arraySize];
        for(int i = 0; i < arraySize; i++)
            arr[i] = NULL;
    }
    ~HashedArray<T>(){
        for(int i = 0; i < arraySize; i++)
            deleteLinkedList(arr[i]);
    }
    void addElement(T value){
        //auto start = high_resolution_clock::now();

        int pos = (int)( hasher(value) % arraySize);
        if( arr[pos] == NULL){
            arr[pos] = new hashedArrayNode<T>;
            arr[pos]->value = value;
            arr[pos]->next = NULL;
        }
        else{
            hashedArrayNode<T> * temp = arr[pos];
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = new hashedArrayNode<T>;
            temp=temp->next;
			temp->value = value;
            temp->next = NULL;

        }

        /*auto stop = high_resolution_clock::now();

        std::cout << "Time to insert: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << std::endl;
	*/
    }
    void print(){
        std::cout<<"{ ";
        for(int i = 0; i < arraySize; i++){
            hashedArrayNode<T> * temp = arr[i];
            while(temp != NULL){
                std::cout << temp->value<<", ";
                temp = temp->next;
            }
        }
        std::cout<<" }"<<std::endl;
    }
    bool search(T val){
        //auto start = high_resolution_clock::now();
        
        int pos = (int)( hasher(val) % arraySize );
        hashedArrayNode<T> *node = arr[pos];
        while(node != NULL){
            if( node->value == val)
                return true;
            node = node->next;
        }
        //auto stop = high_resolution_clock::now();

        //std::cout << "Time to search: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << std::endl;
        
        return false;
    }
    void deleteByValue(T val){
        //auto start = high_resolution_clock::now();
        
        int pos = (int)( hasher(val) % arraySize );
        hashedArrayNode<T> *node = arr[pos];
        if(node->value == val){
            //case where the first value in the list is what we want to delete
            arr[pos] = node->next;
            delete(node);
        }

        while(node != NULL && node->next != NULL){
            if( node->next->value == val )
            {
                hashedArrayNode<T> *temp = node->next;
                node->next = temp->next;
                delete(temp);
            }
            node = node->next;
        }

        //auto stop = high_resolution_clock::now();

        //std::cout << "Time to delete: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << std::endl;
    }
};

#endif

