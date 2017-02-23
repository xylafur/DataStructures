
#include "./Lists/ArrayList.h"
#include <iostream>
#include "./Lists/LinkedLists/DoubleLinkedList.h"
#include "./Lists/LinkedLists/LinkedList.h"


using namespace std;

const unsigned int times = 20;

void ArrayListTester() {
  ArrayList<int> myints;
  cout << "constructed myints" << endl;

  for (unsigned int i = 0; i < times; ++i) {
    myints.append(i);
    cout << "ArrayList["<< i << "] = " << myints[i] << endl;
  }


  cout << "Deleting index 2" << endl;
  myints.remove(2);
  for (int i = 0; i < myints.size(); ++i) {
    cout << "ArrayList["<< i<< "] = " << myints[i] << endl;
  }

  for (int i = 0; i < 12; ++i) {
    myints.remove(myints.size()-1);
  }
  cout << endl << "Deleted last 12" << endl;
  for (int i = 0; i < myints.size(); ++i) {
    cout << "ArrayList["<< i<< "] = " << myints[i] << endl;
  }

}

void LinkedListTester(){
  cout << "LinkedList Test starting..\n" << endl;

  LinkedList<int> * list1 = new LinkedList<int>();
  list1->addToBeg(2);
  list1->addToBeg(1);
  list1->addToEnd(3);
  cout << "should equal 1 2 3 : " << endl;
  list1->printList();
  delete(list1);

  LinkedList<char> * list2 = new LinkedList<char>('b');
  list2->addToBeg('a');
  list2->addToEnd('c');
  cout << "should equal a b c : " << endl;
  list2->printList();
  delete(list2);

  LinkedList<double> * list3 = new LinkedList<double>(new LinkedListNode<double>(2.2) );
  list3->addToBeg(1.1);
  list3->addToEnd(3.3);
  cout << "should equal 1.1 2.2 3.3 : " << endl;
  list3->printList();
  delete(list3);

  cout << "LinkedList Test has completed.\n\n" << endl;

}

void DoubleLinkedListTester(){
  DoubleLinkedList<int> * list1 = new DoubleLinkedList<int>(2);
  list1->addToBeg(1);
  list1->addToEnd(3);
  cout << "should be equal to : 1 2 3" <<endl;
  list1->printList();
  cout << "should be equal to 3 2 1" << endl;
  list1->printListReverse();
  delete(list1);
  cout << endl;

  DoubleLinkedList<char> * list2 =
      new DoubleLinkedList<char>(new DoubleLinkedListNode<char>('b') );
  list2->addToBeg('a');
  list2->addToEnd('c');
  cout << "should be equal to : a b c" <<endl;
  list2->printList();
  cout << "should be equal to c b a" << endl;
  list2->printListReverse();
  delete(list2);
  cout << endl;

  DoubleLinkedList<double> * list3 = new DoubleLinkedList<double>();
  list3->addToBeg(2.2);
  list3->addToBeg(1.1);
  list3->addToEnd(3.3);
  cout << "should be equal to : 1.1 2.2 3.3" <<endl;
  list3->printList();
  cout << "should be equal to 3.3 2.2 1.1" << endl;
  list3->printListReverse();
  delete(list3);

}

int main(){
  //LinkedListTester();
  //DoubleLinkedListTester();
  
  ArrayListTester();
  return 0;
}
