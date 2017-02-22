
#ifndef NODES_H
#define NODES_H

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
