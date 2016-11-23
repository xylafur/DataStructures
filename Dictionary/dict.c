#include <stdio.h>
#include <stdlib.h>

#define DICTSIZE 10

/**************************************************
**********************HEADER***********************
***************************************************
* So the structure behind this will be similar to *
* how python handles dictionaries (though nowhere *
* near as advanced as python).  So collisions     *
* will be handled by linked lists.  The hashing   *
* algoritm was actually inspired by python and    *
* will simply sum up the key (which can only be   *
* a string in this case) and the preform modlo    *
* on the result with the DICTSIZE macro.          *
***************************************************
***************************************************
**************************************************/

//this will be an element in our dictionary array
typedef struct DictionaryNode{
  char *key;
  int value;
  struct DictionaryNode *pNext;
} dict;


int main(){

  dict *D = malloc( sizeof(dict) * DICTSIZE);
  return 0;

}
