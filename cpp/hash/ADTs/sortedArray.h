

#ifndef SORTED_ARRAY
#define SORTED_ARRAY
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std::chrono;


template <class T>
class SortedArray{
private:
    int size, realSize;
    T * arr;
    void bubbleUp(T val, int index){
        T temp = arr[index];
        arr[index] = val;
        for(index++; index < realSize; index++){
            T otherTemp = arr[index];
            arr[index] = temp;
            temp = otherTemp;
        }

    }
public:
    SortedArray<T>(int size){
        this->size = size;
        this->realSize = 0;
        arr = new T[size];
    }
    ~SortedArray<T>(){
        delete(arr);
    }
    void insert(T val){
        //auto start = high_resolution_clock::now();

        if(realSize >= size)
            std::cout<<"trying to put to many elements in your sorted array..\n";
        else{
            int index = 0;
            while( arr[index] < val ){
                //new element is the greatest value
                if(index == realSize){
                    arr[index] = val;
                    return;
                }
                index++;
            }//end while
            realSize++;
            bubbleUp(val, index);
        }//end else

       // auto stop = high_resolution_clock::now();

        //std::cout << "Time to insert: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << std::endl;

    }//end insert
    void deleteAtIndex(int index){
        //auto start = high_resolution_clock::now();

        if( index > realSize )
            std::cout<<"Invalid index to delete bruh\n";
        else{
            for( int i = index; i < realSize; i++)
                arr[i] = arr[i+1];
            realSize--;
        }

        //auto stop = high_resolution_clock::now();

        //std::cout << "Time to delete: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << std::endl;
    }
    int searchHelper(T val, int hi, int lo){
        if(hi < lo)
            return -1;
        int mid = (hi - lo) / 2;
        std::cout<<"current hi: "<<hi<<" current lo: "<<lo<<" current val: "<<arr[mid]<<std::endl;
        if( arr[mid] == val )
            return mid;
        else if( arr[mid] < val)
            return searchHelper(val, hi, mid+1);
        else
            return searchHelper(val, mid, lo);

    }
    int iterativeBinSearch(T val) {
        int lo = 0, hi = realSize, mid = (lo + hi) / 2;
        while (lo != mid && hi != mid) {
            if (arr[mid] == val) {
                return mid;
            }
            if (val < arr[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
            mid = (lo + hi) / 2;
        }
        // will stop when hi or lo is mid
        if (arr[hi] == val) {
            return hi;
        }
        if (arr[lo] == val) {
            return lo;
        }
        return -1;
    }
    int search(T val){
       // auto start = high_resolution_clock::now();

        //return searchHelper(val, realSize, 0);

       // auto stop = high_resolution_clock::now();

       // std::cout << "Time to search: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds" << std::endl;
        return iterativeBinSearch(val);
    }
    void print(){
        for(int i = 0; i < size; i++){
            std::cout<<arr[i]<<" ";
        }
        std::cout<<std::endl;
    }
};


#endif

