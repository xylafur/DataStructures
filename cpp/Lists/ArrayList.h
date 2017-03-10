
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <exception>
#include <iostream>
#include <climits>

const int DEFAULT_ARRAYLIST_SIZE = 0x10;  // 16
const int MAX_ARRAYLIST_SIZE = static_cast<int>(1 << 30);

template <class T> class ArrayList {

protected:
  int num_elems;    // Number of elements
  int real_size;    // Real Arraysize
  T *values = NULL; // values

  /**
    * Initializes member variables, serves as also a reset
    */
  void init(int size = 0) {
    if (values) { 
      delete[] values; 
      values = NULL;
    }

    size = (size < DEFAULT_ARRAYLIST_SIZE) 
            ? DEFAULT_ARRAYLIST_SIZE : size;

    if (size >= MAX_ARRAYLIST_SIZE) {
      std::cerr << "Cannot initialize ArrayList with size >= "
                << MAX_ARRAYLIST_SIZE << std::endl;
      throw std::exception();
    }

    values = new T[size];
    real_size = size;
    num_elems = 0;
  }

  /**
    * Checks if  0 <= index < num_elems
    * if destructive is true, throws an exception
    */ 
  bool rangeCheck(int index, bool destructive = false) {
    bool inrange = ( 0 <= index && index < num_elems );
    if (destructive && !inrange) {
      std::cerr << "Array index out of bounds:[" << index 
                << "] when num_elems is " << num_elems << std::endl;
      throw std::exception();
    }
    return inrange;
  }

  /**
    * Copies T values over to another array dest
    * Should only be called if num_elems <= length of dest
    * 
    * @precondition: num_elems must be smaller than dest size!
    */
  void copyOver(T *dest) {
    for (int i = 0; i < num_elems; ++i)
      dest[i] = values[i];
  }

  /**
    * @param newsize : new size to resize values to
    * @precondition: newsize must be > 0
    */
  void reSize(int newsize) {
    if (newsize == real_size) return;
    T *newvalues = new T[newsize];
    copyOver(newvalues);
    delete[] values;
    values = newvalues;
    real_size = newsize;
  }
  
  /**
    * called when adding elements to the list. 
    * 
    * Ensures that there is enough space by checking if 
    * newSize you want to allocate to is within the realsize. 
    * If its bigger it reallocates allocates a bigger array 
    * and then copies values to it.
    * 
    * @param: newSize : the "bigger" size you want
    * @precondition: newSize must be positive
    */
  bool ensureCapacity(int newSize) {
    if (num_elems >= MAX_ARRAYLIST_SIZE) {
      std::cerr << "Error: exceeded MAX_ARRAYLIST_SIZE: "
                << MAX_ARRAYLIST_SIZE << ", size = "
                << num_elems << std::endl;
      throw std::exception();
    }
    if (newSize > real_size) {
      reSize(real_size * 2);
    }
    //No need to check for newSize < 0 since do nothing for that
    return true;
  }

  /**
    * precondition: 0 < start < num_elems
    * shifts elements from dest to  slide_head
    * decreases num_elems accordingly
    *
    * before:
    *                      * <<------------*-------*---*--
    * values:|...|...|...|dest|...|...|slide_head|...|...|...|end
    * index :  0   1  ... dest   ...   slide_head ... ... ...|num_elems
    *
    * after:
    *
    * values:|...|...|...|slide_head|...|...|...|end
    * index :  0   1  ... dest           ...    |num_elems
    *                                             ^   
    *                      reduced num_elems now _|
    *
    */
  void slideBackward(int dest, int slide_head) {
    int times = num_elems - slide_head, i;
    for (i = 0; i < times; ++i) 
      values[dest + i] = values[slide_head + i];
    num_elems -= (slide_head - dest);
  }

  /**
    * This function slides elements from (including) head
    * element a specified amount.
    * must! : 0 <= start < num_elems
    *         num_elems + amount < realsize
    *
    *
    */
  void slideForward(int start, int amount) {
    ensureCapacity(num_elems + amount);
    for (int i = num_elems - 1; i >= start; --i) {
      values[i + amount] = values[i];
    }
  }


public:

  ArrayList() { init(); }
  ArrayList(const ArrayList<T> &copy) {
    init(copy.real_size);
    for (int i = copy.num_elems; --i >= 0; values[i] = copy.values[i]);
    num_elems = copy.num_elems;
  }

  ArrayList(int size) {
    init(size);
  }
  ~ArrayList() { delete[] values; }

  int size() { return num_elems; }
  int actual_size() { return real_size; }

  void purgeAll() { init(); }


  /**
    * removes entries from [start, end-1]
    * end is non inclusive
    */
  void purge(int start, int end = -1) {
    rangeCheck(start);
    if (end == -1 || end == start + 1) { 
      pop(start); return;
    } 

    if (start >= end) {
      std::cerr << "ArrayList.purge(start:" << start << ", end:" 
                << end << "), start must be less than end." 
                << std::endl;
    }
    
    if (end == num_elems) { 
      if (start == 0) {
        init(); return;
      }
      num_elems = start + 1;
      return;
    }

    slideBackward(start, end + 1);
  }
  
  inline bool isEmpty() { return this->num_elems == 0; }

  T pop(int index) { 
    rangeCheck(index, true);
    T t = values[index];
    slideBackward(index, index + 1);

    if (num_elems < real_size / 2 && real_size > DEFAULT_ARRAYLIST_SIZE) {
      reSize(real_size / 2);
    }
    return t;
  }
  

  void append(T val) {
    ensureCapacity(num_elems + 1);
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

  void insert(T * vals, unsigned int len, int index = 0) {
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

  int indexOf(const T& compare) {
    int ind = -1;
    for (int i = 0; i < num_elems; ++i) {
      if (values[i] == compare) { ind = i; break; }
    }
    return ind;
  }
  
  bool contains(const T& compare) { return indexOf(compare) != -1; }
  
  T& operator [](int index) { 
    rangeCheck(index, true);
    return values[index];
  }

  T& get(int &index) {
    return (*this)[index];
  }
};

#endif
