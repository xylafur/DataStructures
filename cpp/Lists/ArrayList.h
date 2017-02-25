#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <exception>
#include <iostream>
#include <climits>

const int DEFAULT_ARRAYLIST_SIZE = 0x10; // 16
const int MAX_ARRAYLIST_SIZE = static_cast<int>(1 << 30);

template <class T> class ArrayList {

protected:
  int num_elems; // Number of elements
  int real_size; // Real Arraysize
  T *values = NULL;

  /**
    * Initializes member variables, serves as also a reset
    */
  void init(int size = DEFAULT_ARRAYLIST_SIZE) {
    if (values) delete[] values; //possibly unneeded

    values = new T[size];
    real_size = size;
    num_elems = 0;
  }

  /**
    * Checks if index < num_elems
    * if destructive is true, throws an exception
    */ 
  bool rangeCheck(int index, bool destructive = false) {
    bool inrange = 0 <= index && index < num_elems;
    if (destructive && !inrange) {
      std::cerr
          << "Array index out of bounds:[" << index << "] when size is " << num_elems
          << std::endl;
      throw std::exception();
    }
    return inrange;
  }

  /**
    * Copies T values over to another array dest
    * Should only be called if num_elems <= length of dest
    */
  void copyOver(T *dest) {
    for (int i = 0; i < num_elems; ++i)
      dest[i] = values[i];
  }

  /**
    * 
    */
  void reSize(int newsize) {
    if (newsize == real_size) return;
    T *newvalues = new T[newsize];
    copyOver(newvalues);
    delete[] values;
    values = newvalues;
    real_size = newsize;
  }

  bool sizeCheckPrep(int newSize) {
    if (num_elems >= MAX_ARRAYLIST_SIZE) {
      std::cerr << "Error: exceeded maximum size (2^31) <= " << num_elems << std::endl;
      throw std::exception();
    }
    if (newSize > real_size) {
      reSize(real_size * 2);
    }
    return true;
  }

  void slideBackward(int start, int slide_head) {
    // Because programmer might be idiot
    rangeCheck(start, true);

    int times = num_elems - slide_head, i;
    for (i = 0; i < times; ++i) 
      values[start + i] = values[slide_head + i];
    num_elems -= (slide_head - start);
  }

  /**
    * This function slides elements from (including) head
    * element a specified amount.
    * must! : 0 <= start < num_elems
    *         num_elems + amount < realsize
    */
  void slideForward(int start, int amount) {
    // Because programmer might be idiot
    rangeCheck(start, true);

    sizeCheckPrep(num_elems + amount);
    for (int i = num_elems - 1; i >= start; --i) {
      values[i + amount] = values[i];
    }
  }


public:

  ArrayList() { init(); }
  ~ArrayList() { delete[] values; }

  //Returns number of elements in this list
  int size() { return num_elems; }
  int actual_size() { return real_size; }

  //Deletes all elements by deleting[] values
  void clear() { init(); }
  
  inline bool isEmpty() { return this->num_elems == 0; }

  T remove(int index) { rangeCheck(index, true);
    T t = values[index];
    slideBackward(index, index + 1);

    if (num_elems < real_size / 2 && real_size > DEFAULT_ARRAYLIST_SIZE) {
      reSize(real_size / 2);
    }
    return t;
  }

  void append(T val) {
    sizeCheckPrep(num_elems + 1);
    values[num_elems++] = val;
  }

  void insert(T val, int index = 0) {
    if (index == num_elems) {
      append(val); return;
    }

    rangeCheck(index, true);
    slideForward(index, 1);
    values[index] = val;
    num_elems++;
  }

  void insert(T * vals, int len, int index = 0) {
    if (index != num_elems) rangeCheck(index, true);

    slideForward(index, len);
    for (int i = 0; i < len; ++i) {
      values[index + i] = vals[i];
    }
    num_elems += len;
  }

  void insert(const ArrayList &arr_list, int index = 0) {
    insert(index, arr_list.values, arr_list.num_elems);
  }

  T& operator [](int index) { 
    rangeCheck(index, true);
    return values[index];
  }

};

#endif
