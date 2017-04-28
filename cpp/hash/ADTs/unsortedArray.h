#ifndef UNSORTED_ARRAY
    #define UNSORTED_ARRAY
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std::chrono;

template <class T>
class UnsortedArray{
private:
    T * arr;
    int currentSize, realSize;
public:
    UnsortedArray(int size){
        arr = new T [size];
        realSize = size;
        currentSize = 0;
    }
    void insert(T elm){
       // auto start = high_resolution_clock::now();
        
        if(currentSize >= realSize)
            std::cout<<"Bruh this array is to tiny\n";
        else{
            arr[currentSize] = elm;
            currentSize++;
        }
        
       // auto stop = high_resolution_clock::now();
        
       // std::cout << "Time to insert: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << std::endl;
    }
    void deleteAtIndex(int i){
        //auto start = high_resolution_clock::now();
        
        if(i >= currentSize)
            std::cout<<"Not a valid location to delete\n";
        else{
            for(int o = i; o < currentSize; o++)
                arr[o] = arr[o+1];
            currentSize--;
        }

       // auto stop = high_resolution_clock::now();

        //std::cout << "Time to delete: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << std::endl;
        
        
    }
    //returns the index 
    int search(T val){
        //auto start = high_resolution_clock::now();
        
        for(int i = 0; i < currentSize; i++)
        {
            if( arr[i] == val )
                return i;
        }
        
        //auto stop = high_resolution_clock::now();
        //std::cout << "Time to search: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << std::endl;
       
        return -1; 
    }
    void print(){
        for(int i = 0; i < currentSize; i++)
            std::cout<<arr[i]<<" ";
        std::cout<<std::endl;
    }

};

#endif
