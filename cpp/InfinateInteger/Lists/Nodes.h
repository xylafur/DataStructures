
#ifndef NODES_H
#define NODES_H

#include <iostream>
template <class T> class Node {
protected:
  T value;
public:
  Node() {}
  ~Node() {}
  T& Value() { return &value; }
  T getValue(){
    return this->value;
  }
  void setValue(T val){
    this->value = val;
  }
};

#endif
