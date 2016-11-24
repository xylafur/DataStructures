#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//if we go the rout of % we should use a prime # for size
#define DICTSIZE 7

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
*                                                 *
* If you want to actually use this dictinary be   *
* aware that if you search for a key that is not  *
* present then the program will exit.             *
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
int assign(dict* pD, char *inKey, int inVal){
  int index = hash(inKey);
  //if the dict has not been assigned the key will have
  //  a value == to NULL
  if(pD[index].key == NULL){
    //printf("Does not contain key\n");

    pD[index].key = inKey;
    pD[index].value = inVal;
    return 0;
  }
  //if the specific index has already been assigned a
  //  key and value then we must make sure that it is the
  //  final node at that specific index

  dict *temp = &pD[index];    //temp pointer to go through linked list
  while(temp->pNext != NULL){

    //this means the key already exists
    if(strcmp(temp->key, inKey) == 0){
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

//returns boolean telling if the key is present
int contains(dict* pD, char *inKey){
  int index = hash(inKey);

  if(pD[index].key == NULL)
    return 0;
  dict *temp = &pD[index];
  while(temp != NULL){
    //printf("Temp contains: %s\n", temp->key);
    //printf("Comparing against: %s\n", inKey);
    if(strcmp(temp->key, inKey) == 0)
      return 1;
    temp = temp->pNext;
  }
  return 0;
}

//this function assumes that the dict
//  actually contains the key and will throw
//  an error and exit otherwise
int value(dict *pD, char *inKey){
  int index = hash(inKey);

  if(pD[index].key == NULL)
  {
    printf("Key not found.. Exiting.");
    exit(8);
  }

  dict *temp = &pD[index];

  while(temp != NULL){
    if(strcmp(temp->key, inKey) == 0)
      return temp->value;
    temp = temp->pNext;
  }
  printf("Key not found.. Exiting.");
  exit(8);
}

int main(){

  dict *D = calloc(DICTSIZE, sizeof(dict));
  //printf("%d%d%d%d\n", hash("Kesley"), hash("e"), hash("f"), hash("a") );

  assign(D, "Kesley", 7);

  printf("Dict contains Kesley: %d\n", contains(D, "Kesley"));
  printf("This value of Kesley is %d\n", value(D, "Kesley"));
  printf("This value of Keegan is %d\n", value(D, "Keegan"));



  return 0;

}
