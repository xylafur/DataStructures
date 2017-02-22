//#include "./Lists/LinkedLists/DoubleLinkedList.h"

#include "./Lists/ArrayList.h"
#include <iostream>

using namespace std;

const unsigned int times = 20;

void testArrayList() {
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

int main() {
  testArrayList();
  return 0;
}
