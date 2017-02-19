#include "DoubleLinkedList.h"
#include <iostream>

using namespace std;

int main(){
  DoubleLinkedList<char> * list = new DoubleLinkedList<char>();
  list->addToEnd('a');
  DoubleLinkedList<char> * list2 = new DoubleLinkedList<char>('b');

  list->printList();
  list2->printList();
  delete(list);
  delete(list2);

  return 0;
}
