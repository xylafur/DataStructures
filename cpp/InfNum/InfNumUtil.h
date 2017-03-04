#ifndef INFNUM_HELPER
    #define INFNUM_HELPER
#include <string>
#include <fstream>
#include "InfNum.h"
#include <math.h>
//-pedantic
//
struct stats {
    std::string filename;
    std::string output;
    std::string algorithm;
    int numElements;
    int numCompare = 0;
    int numSwaps = 0;
    int digPerNode;
    int bigOCompare = 0;
    int bigOSwaps = 0;
};
void printInfNumArr(InfNum * arr, struct stats * myStats){
    for( int i = 0; i < myStats->numElements; i++){
        arr[i].print();
    }
}
void fileWriter(struct stats * myStats){
    fstream file;
    file.open(myStats->output, std::fstream::in | std::fstream::out
            | std::fstream::app);
    if(!file){
        
    }
    if(file.is_open()){
        file << "algoritm\t#numbers(2)\t#comparisons\t#swaps\t#bigOComparisons\t#bigOSwaps\n";
        file << myStats->algorithm << "\t\t" << myStats->numElements << "\t\t" <<
                myStats->numCompare << "\t\t" << myStats->numSwaps << "\t" << 
                myStats->bigOCompare << "\t" << myStats->bigOSwaps << "\n\n";
    }
    file.close();
}

template <class T>
void infNumBubbleSort(T arr [], int size){
    for( int i = 1; i < size; i++){
        int v = i;
        while(v > 0 && arr[v-1] > arr[v]){
            T temp = arr[v];
            arr[v] = arr[v-1];
            arr[v-1] = temp;
            v--;
        }
    }
}
template <class T>
void swapElms(T * arr, int a, int b){
    T temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void quickSortHelper(InfNum * arr, struct stats * myStats, int left, int right){
    int i = left, j = right;
    InfNum tmp = arr[i];
    InfNum pivot = arr[(left + right) / 2];

    //partition
    while(i<=j){
        while(arr[i] < pivot){
            i++;
            myStats->numCompare++;
        }
        while(arr[j] > pivot){
            j--;
            myStats->numCompare++;
        }
        if(i <= j){
            myStats->numSwaps++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    if(left < j)
        quickSortHelper(arr, myStats,left, j);
    if(i < right)
        quickSortHelper(arr, myStats, i, right);
}

int rayPartition(InfNum * arr, int left, int right, struct stats * myStats) {
    int next = left;
    for (; left < right; ++left) {
        if (arr[left] < arr[right]) {
            swapElms(arr, left, next++);
        }
    }
    swapElms(arr, right, next);
    return next;
}
void rayQuickSort(InfNum * arr, int left, int right,struct stats * myStats) {
    if (left < right) {
        int p = rayPartition(arr, left, right, myStats);
        rayQuickSort(arr, left, p - 1, myStats);
        rayQuickSort(arr, p + 1, right, myStats);
    }
}

void kesQuickSort(InfNum * arr, struct stats * myStats){
    //quickSortHelper(arr, myStats, 0, myStats->numElements - 1);
    rayQuickSort(arr, 0, myStats->numElements - 1, myStats);
}
void bubbleUp(InfNum * arr, struct stats * myStats, int current, int lastIndex){
    int left = (current*2)+1, right = (current*2)+2; 
    bool hasLeft = left <= lastIndex; 
    bool hasRight = right <= lastIndex; 
    if(hasLeft)
        bubbleUp(arr, myStats, left, lastIndex);
    if(hasRight)
        bubbleUp(arr, myStats, right, lastIndex);

    if(hasLeft){
        if(arr[current] <  arr[left])
            swapElms(arr, current, left);
        if(hasRight && arr[current] < arr[right] )
            swapElms(arr, current, right);
    }
}

void kesHeapSort(InfNum * arr, struct stats * myStats){
    for(int i = myStats->numElements - 1; i >= 0; i--){
        bubbleUp(arr, myStats, 0, i);
        swapElms(arr, 0, i);
    }
}
void kesSelectSort(InfNum * arr, struct stats * myStats){
    for(int i = 0; i < myStats->numElements; i++){
        InfNum min = arr[i];
        for(int j = i; j < myStats->numElements; j++){
            myStats->numCompare++;
            if(arr[j] < min){
                swapElms(arr, i, j);
                min = arr[i];
                myStats->numSwaps++;
            }
        }
    }
}
void kesInsertSort(InfNum * arr, struct stats * myStats){
    for( int i = 1; i < myStats->numElements; i++){
        for( int j = i; j < myStats->numElements; j++){
            while(j > 0 && arr[j] < arr[j-1]){
                myStats->numCompare++;
                swapElms(arr, j, j-1);
                j--;
            }
        }
    }
}
void merge(InfNum * arr, struct stats * myStats, int low, int high, int mid){
    int i, j, k;
    InfNum * arr2 = (InfNum *)calloc(sizeof(InfNum), myStats->numElements);

    i = low;
    k = low;
    j = mid+1;
    while(i <= mid && j <= high){
        myStats->numCompare++;
        if(arr[i] < arr[j]){
            arr2[k] = arr[i];
            k++;
            i++;
            myStats->numSwaps++;
        }
        else{
            arr2[k] = arr[j];
            k++;
            j++;
            myStats->numSwaps++;
        }
    }
    while(i <= mid){
        arr2[k] = arr[i];
        k++;
        i++;
    }
    while(j <= high){
        arr2[k] = arr[j];
        k++;
        j++;
    }
    for( i = low; i < k; i++)
        arr[i] = arr2[i];
    free(arr2);
}
void mergeSortHelper(InfNum * arr, struct stats * myStats, int low, int high){
    int mid;
    if(low < high){
       mid = (low + high) / 2;
       mergeSortHelper(arr, myStats, low, mid);
       mergeSortHelper(arr, myStats, mid+1, high);
       merge(arr, myStats, low, high, mid);
    }
    return;
}
void kesMergeSort(InfNum * arr, struct stats * myStats){
    mergeSortHelper(arr, myStats, 0, myStats->numElements - 1);
}

void sortingCaller(InfNum * arr, struct stats * myStats){
    std::string algo = myStats->algorithm;
    if(!algo.compare("heap")){
        kesHeapSort(arr, myStats);
    }
    else if(!algo.compare("quick")){
        kesQuickSort(arr, myStats);
        myStats->bigOSwaps = myStats->numElements * log(myStats->numElements);
        myStats->bigOCompare = myStats->bigOSwaps;
    }
    else if(!algo.compare("select")){
        kesSelectSort(arr, myStats);
        myStats->bigOSwaps = myStats->numElements * myStats->numElements;
        myStats->bigOCompare = myStats->bigOSwaps;
    }
    else if(!algo.compare("insert")){
        kesInsertSort(arr, myStats);
        myStats->bigOCompare = myStats->numElements*myStats->numElements;
    }
    else if(!algo.compare("merge")){
        kesMergeSort(arr, myStats);
        myStats->bigOSwaps = myStats->numElements * log(myStats->numElements);
        myStats->bigOCompare = myStats->bigOSwaps;
    }

    fileWriter(myStats);
    printInfNumArr(arr, myStats);
    delete(myStats);
}       

#endif
