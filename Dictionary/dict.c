#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//function to hash our key
int hash(char *inputS){
  int sum = 0;
  while(*inputS != '\0'){
    sum += (*inputS - '0');
    inputS++;
  }
  return (sum % DICTSIZE);
}

//function to assign a value to our dict array
//  returns 1 if the element already existed, 0
//  if the element had to be added
int assign(dict* pD, int index, char *inKey, int inVal){
  //if the dict has not been assigned the key will have
  //  a value == to NULL
  if(pD[index].key == NULL){
    pD[index].key = inKey;
    pD[index].value = inVal;
    return 0;
  }
  //if the specific index has already been assigned a
  //  key and value then we must make sure that it is the
  //  final node at that specific index

  dict *temp = &pD[index];    //temp to go through linked list
  while(temp->pNext != NULL){

    //this means the key already exists
    if(strcmp(temp->key, inKey) == 1){
      temp->value = inVal;
      return 1;
    }
    temp = temp->pNext;
  }
  temp->pNext = malloc(sizeof(dict));
  temp = temp->pNext;

  temp->value = inVal;
  temp->key = inKey;

  return 1;
}


int main(){

  dict *D = calloc(DICTSIZE, sizeof(dict));

  assign(D, hash("Kesley"), "Kesley", 7);

  printf("%s", D->key);
  printf("%d", D->key==NULL);



  return 0;

}
