
#ifndef STACK_H
#define STACK_H

#include "arraylist.h"

template <class T> class Stack {
protected:
  ArrayList<T> values;

public:
  Stack() {}
  ~Stack() {}

  void push(T elem) {
    values.append(elem);
  }

  T pop() {
    return values.pop();
  }

  T peek() {
    return values[values.size() - 1];
  }
  
  bool isEmpty() {
    return values.isEmpty();
  }

  int size() {
    return values.size();
  }

  void purgeAll() {
    values.purgeAll();
  }
}

#endif
