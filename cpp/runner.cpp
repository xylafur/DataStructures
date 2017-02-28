
#include <iostream>
#include "./Lists/LinkedLists/DoubleLinkedList.h"
#include "./Lists/LinkedLists/LinkedList.h"
#include "./Lists/ArrayList.h"
#include "./Lists/ArrayListUtil.h"


using namespace std;

void printForArrTester(const char * s, ArrayList<int> &arrlist) {
  if (s != NULL) cout << s << endl;

  for (int i = 0; i < arrlist.size(); ++i) {
    cout << "arrlist["<< i << "] = " << arrlist[i] << endl;
  }
  cout << endl;
}

void ArrayListTester() {
  const int times = 20;

  ArrayList<int> myints;
  cout << "constructed myints" << endl;
  for (unsigned int i = 0; i < times; ++i) {
    myints.append(i);
  }
  printForArrTester("After appending: ", myints);


  cout << "Deleting index 2" << endl;
  myints.pop(2);
  printForArrTester("After Deleting index 2: ", myints);

  
  cout << "Attempting to insert value of 2 at index 2: " << endl;
  myints.insert(2, 2);
  printForArrTester("After insert value of 2 at index 2: ", myints);

  int * arr = new int[6]{-1, -2, -3, -4, -5, -6};
  cout << "Attempting to insert pointer array of values into index 3" << endl;
  myints.insert(arr, 6, 3);
  printForArrTester("After insertion of array at index 3", myints);
  delete[] arr;


  for (int i = 0; i < 12; ++i) {
    myints.pop(myints.size()-1);
  }
  printForArrTester("After Deleting last 12: ", myints);
  

  int appval = -35;
  cout << "Appending manually: " << endl;
  cout << "using arr.insert(" << appval<< ", arr.size()) "<< endl; 
  myints.insert(appval--, myints.size());
  printForArrTester("After inserting manually", myints);

  cout << "Purging half from " << myints.size()/2 << endl;
  myints.purge(myints.size()/2, myints.size());
  printForArrTester("After purging half", myints);
  
  cout << "Purging 0 to size" << endl;
  myints.purge(0, myints.size());
  printForArrTester("After purging all", myints);
  
  cout << "arr.isEmpty() : " << myints.isEmpty() << endl;

  cout << endl << "Error Tests: " << endl;
  myints.insert(5, 0);
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
