#include <stdio.h>
#include <iostream>
#include <string>
#include "ADTs/sortedArray.h"
#include "ADTs/hasMap.h"
#include "ADTs/hashedArray.h"
#include "ADTs/unsortedArray.h"
#include "filereader.h"
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <iomanip>

/*
 *  Need a has map, a sorted array and an unsorted array.
 *
 *  Read from a file with 20 different integers
 *  Place those numbers into all 3 data types and insert them 
 *          all into the different storage containers
 *      time all of the inserts
 *  After inserting, delete elements from all three containers
 *      record time to do this as well.
 *
 */
struct stats{
    std::string operation;
    double timeTaken;
};
//function to take in a function pointer and return how long it took to complete
/*
double timerWrapper( void (*func)(void) ){
    func();
}


void otherFunction(){
    std::cout<<"calling functionction pointer"<<std::endl;
}
*/

void callHashFunctions(int size, fileNode *head){
    std::cout<<"Calling hash functions"<<std::endl;
    HashedArray<int> *arr = new HashedArray<int>();
    auto start = high_resolution_clock::now();
    for(int i = 0; i < size; i++, head=head->next)
        arr->addElement(head->val);
    auto stop = high_resolution_clock::now();

    std::cout << "Time to insert: " << duration_cast<nanoseconds>(stop - start).count() 
            << " nanoseconds" << std::endl;
    
    arr->print();

    start = high_resolution_clock::now();
    for(int i = 0; i < 16; i++)
        arr->search(i);
    stop = high_resolution_clock::now();
    std::cout << "Time to search: " << duration_cast<nanoseconds>(stop - start).count() 
            << " nanoseconds" << std::endl;

    start = high_resolution_clock::now();
    for(int i = 0; i < 33; i++)
        arr->deleteByValue(i);
    stop = high_resolution_clock::now();
    std::cout << "Time to delete: " << duration_cast<nanoseconds>(stop - start).count() 
            << " nanoseconds" << std::endl;

    std::cout<<std::endl;
}

void callSortedArrayFunctions(int size, fileNode *head){
    std::cout<<"Calling sorted Array Functions\n";
    SortedArray<int> arr(size);
    auto start = high_resolution_clock::now();
    for(int i = 0; i < size; i++, head=head->next)
        arr.insert(head->val);
    auto stop = high_resolution_clock::now();
    std::cout << "Time to insert: " << duration_cast<nanoseconds>(stop - start).count() 
            << " nanoseconds" << std::endl;
    arr.print();
    //std::cout<<"searching for 5.. index = " << arr.search(5) <<std::endl;
    //std::cout<<"searching for 11.. index = " << arr.search(11) <<std::endl;
    //std::cout<<"deleting index 5..\n";
    start = high_resolution_clock::now();
    for (int i = 10; i > 0; i--)
    {
        arr.deleteAtIndex(i);
    }
    stop = high_resolution_clock::now();
    std::cout << "Time to delete: " << duration_cast<nanoseconds>(stop - start).count() 
            << " nanoseconds" << std::endl;
    //arr.deleteAtIndex(5);
    
    start = high_resolution_clock::now();
    for(int i = 0; i < 10; i++)
        arr.search(i);
    stop = high_resolution_clock::now();
    std::cout << "Time to search: " << duration_cast<nanoseconds>(stop - start).count() 
            << " nanoseconds" << std::endl;
    
    arr.print();
    std::cout<<"\n\n";

}

void callUnsortedArrayFunctions(int size, fileNode *head){
    std::cout<<"Calling unsorted Array functions\n";
    UnsortedArray<int> arr(size);
    
    auto start = high_resolution_clock::now();
    for(int i = 0; i < size; i++, head=head->next)
        arr.insert(head->val);
    auto stop = high_resolution_clock::now();

    std::cout << "Time to insert: " << duration_cast<nanoseconds>(stop - start).count() 
            << " nanoseconds" << std::endl;
    arr.print();
    start = high_resolution_clock::now();
    for(int i = 10; i > 0; i--)
        arr.deleteAtIndex(i);
    stop = high_resolution_clock::now();

    std::cout << "Time to delete: " << duration_cast<nanoseconds>(stop - start).count() 
            << " nanoseconds" << std::endl;

    start = high_resolution_clock::now();
    for(int i = 0; i < 33; i++)
        arr.search(i);
    stop = high_resolution_clock::now();

    std::cout << "Time to search: " << duration_cast<nanoseconds>(stop - start).count() 
            << " nanoseconds" << std::endl;

    std::cout<<"\n\n";
}

int main(){
    std::cout.setf(ios::fixed | ios::showpoint);
    std::cout.precision(20);

    std::string filename = "test.txt";
    fileNode *head = new fileNode;
    int size = readFileToList(filename, head);

    callSortedArrayFunctions(size, head);
    callUnsortedArrayFunctions(size, head);
    callHashFunctions(size, head);
}

