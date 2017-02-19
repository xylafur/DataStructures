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
    //printf("Index not used.  Adding %s at index %d\n", inKey, index);
    pD[index].key = inKey;
    pD[index].value = inVal;
    return 0;
  }
  //if the specific index has already been assigned a
  //  key and value then we must make sure that it is placed
  //  at the final node at that specific index
  dict *temp = &pD[index];    //temp pointer to go through linked list
  while(1){
    //printf("Comparing key %s with inKey %s\n", temp->key, inKey);

    //this means the key already exists
    if(strcmp(temp->key, inKey) == 0){
      //printf("same element found with key %s\n", inKey);
      temp->value = inVal;
      return 1;
    }
    if(temp->pNext == NULL)
      break;
    temp = temp->pNext;
  }//end while
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
    //printf("Key not found.. Exiting.");
    exit(8);
  }

  dict *temp = &pD[index];

  while(temp != NULL){
    if(strcmp(temp->key, inKey) == 0)
      return temp->value;
    temp = temp->pNext;
  }
  //printf("Key not found.. Exiting.");
  exit(8);
}

//returns the total number of elements in the array
int len(dict *pD){
  int i, count = 0;
  for(i = 0; i < DICTSIZE; i++){
    //if there is no item at the present index we go to the
    //  next index.  Otherwise increase count.
    if(pD[i].key ==NULL)
      continue;
    count++;

    //we use temp and the while loop to trancend the linked
    //  list that may exist at each index.
    dict *temp = &pD[i];
    while(temp->pNext !=NULL){
      count++;
      temp = temp->pNext;
    }
  }
  return count;
}

void printDict(dict *pD){
  //firstFoundBool is just a boolean used for formatting the output
  int i, firstFoundBool = 0;
  printf("{ ");
  for(i = 0; i < DICTSIZE; i++){
    if(pD[i].key ==NULL)
      continue;

    dict *temp = &pD[i];
    while(1){
      if(!firstFoundBool){
        printf("%s:%d", temp->key, temp->value);
        firstFoundBool = 1;
      }
      else
        printf(", %s:%d", temp->key, temp->value);

      if(temp->pNext == NULL)
        break;
      temp = temp->pNext;
    }
  }
  printf(" }\n");
}

//function to remove item by key
void removeItem(dict *pD, char *inKey){
  int index = hash(inKey);

  //elmBefore is needed because it is not a doubly linked list.
  //  To correctly remove the element we must ensure that we do not sever
  //  connection between elements that may come after it.
  dict *toDel = &pD[index];
  dict *elmBefore = toDel;
  while(1){
    //if were at the correct element of the linked list
    //  we break out of the loop to remove the element and fix the list
    if(strcmp(toDel->key, inKey) == 0)
      break;

    //meaning the key was not present
    if(toDel->key == NULL)
    {
      printf("Not a valid item to delete.. Exiting.\n");
      exit(8);
    }
    elmBefore = toDel;
    toDel = toDel->pNext;
  }

  //if elmBefore and toDel are equal to the same element that means
  //  that the element we are deleting was the first.
  if( strcmp(elmBefore->key, toDel->key ) == 0 ){
    printf("Deleting first Element in list\n");

    //meaning it is the only element in the linked list
    if(toDel->pNext == NULL){
      toDel->key = NULL;
      toDel->value = 0;
    }
    else{
      toDel->key = toDel->pNext->key;
      toDel->value = toDel->pNext->value;
      toDel->pNext = (toDel->pNext->pNext);
    }
  }
  else{
    elmBefore->pNext = toDel->pNext;
    free(toDel);
  }


}

void test(dict *D){
  printf("If 1 the element already existed: %d\n", assign(D, "Kesley", 7) );
  printf("If 1 the element already existed: %d\n", assign(D, "Keegan", 8) );
  printf("If 1 the element already existed: %d\n", assign(D, "Darla", 2) );

  printDict(D);

  removeItem(D, "Kesley");
  printDict(D);

}

int main(){

  dict *D = calloc(DICTSIZE, sizeof(dict));

  test(D);


  free(D);
  return 0;

}
