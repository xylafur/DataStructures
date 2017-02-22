#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <exception>
#include <iostream>
#include <climits>

const unsigned int DEFAULT_ARRAYLIST_SIZE = 0x10; // 16
const unsigned int MAX_ARRAYLIST_SIZE = static_cast<unsigned int>(1 << 31);

template <class T> class ArrayList {

protected:
  unsigned int num_elems; // Number of elements
  unsigned int real_size; // Real Arraysize
  T *values = NULL;

  /**
    * Initializes member variables, serves as also a reset
    */
  void init(unsigned int size = DEFAULT_ARRAYLIST_SIZE) {
    if (values) delete[] values; //possibly unneeded
    //Initialize members
    values = new T[size];
    real_size = size;
    num_elems = 0;
  }

  /**
    * Checks if index < num_elems
    * if destructive is true, throws an exception
    */ 
  bool RangeCheck(unsigned int index, bool destructive = false) {
    bool inrange = index < num_elems;
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
    for (unsigned int i = 0; i < num_elems; ++i) dest[i] = values[i];
  }

  /**
    * 
    */
  void reSize(unsigned int newsize) {
    if (newsize == real_size) return;
    T *newvalues = new T[newsize];
    copyOver(newvalues);
    delete[] values;
    values = newvalues;
    real_size = newsize;
  }

  bool sizeCheck(unsigned int newSize) {
    if (num_elems >= MAX_ARRAYLIST_SIZE) {
      std::cerr << "Error: exceeded maximum size (2^31) <= " << num_elems << std::endl;
      throw std::exception();
    }
    if (newSize > real_size) {
      reSize(real_size * 2);
    }
    return true;
  }

  void slideBack(unsigned int start, unsigned int slide_head) {
    unsigned int times = num_elems - slide_head, i;
    for (i = 0; i < times; ++i) 
      values[start + i] = values[slide_head + i];
    num_elems -= (slide_head - start);
  }

public:

  ArrayList() { init(); }
  ~ArrayList() { delete[] values; }

  //Returns number of elements in this list
  unsigned int size() { return num_elems; }
  unsigned int real_size() { return real_size; }

  //Deletes all elements by deleting[] values
  void clear() { init(); }

  T remove(unsigned int index) { RangeCheck(index, true);
    T t = values[index];
    slideBack(index, index + 1);
    if (num_elems < real_size / 2 && real_size > DEFAULT_ARRAYLIST_SIZE) {
      reSize(real_size / 2);
    }
    return t;
  }

  void append(T val) {
    sizeCheck(num_elems + 1);
    values[num_elems++] = val;
  }

  T& operator [](unsigned int index) { RangeCheck(index, true);
    return values[index];
  }

};

#endif
