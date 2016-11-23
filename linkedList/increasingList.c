#include <stdio.h>
#include <stdlib.h>

/*****************************************
* Program Variables                      *
*****************************************/

/*Value is the data the list holds.             **
**The struct is just a link to the nextElement. */
typedef struct S_IncreasingLinkedList{
  int value;
  struct S_IncreasingLinkedList *nextElement;
} IncreasingList;

IncreasingList *pHead;

/*****************************************
* Program Functions                      *
*****************************************/

/*Data is the number to add to list             **
**pInsert is a pointer to the head of the list. */
void addElement(IncreasingList *pInsert, int data){
  IncreasingList *pTempPointer = pInsert;
  IncreasingList *newElement;

  //edge case if new element is less than head
  if(data < pTempPointer->value){
    newElement = malloc(sizeof(IncreasingList));
    newElement->nextElement = pTempPointer;
    pHead = newElement;
    newElement->value = data;
  }
  //meaning its either in the middle or the end
  else{
    while(1){
      //next value is bigger
      if(pTempPointer->nextElement != NULL && pTempPointer->nextElement->value > data){

        /*********************************
        *ALWAYS REMEMBER NULL CHECK!!!!!!*
        *********************************/

        newElement = malloc(sizeof(IncreasingList));
        //puts behind bigger element
        newElement->nextElement = pTempPointer->nextElement;
        //links smaller element to new
        pTempPointer->nextElement = newElement;

        newElement->value = data;
        break;
      }
      //meaning we have a new biggest element
      else if(pTempPointer->nextElement == NULL){
        newElement = malloc(sizeof(IncreasingList));
        //put at end of list
        newElement->nextElement = NULL;
        //have smaller value point to new value
        pTempPointer->nextElement = newElement;

        newElement->value = data;
        break;
      }
    }
  }//end else
  printf("Add successful, value: %d\n", data);
}

void printList(IncreasingList *pInsert){
  IncreasingList *pTempPointer = pInsert;

  //will keep looping and printing current index
  //until we hit the end (null)
  while(pTempPointer != NULL){
    printf("%d\t", pTempPointer->value);
    pTempPointer = pTempPointer->nextElement;
  }
}


/*****************************************
* Main                                   *
*****************************************/

int main(){
  pHead = malloc(sizeof(IncreasingList));
  pHead->value = 3;
  pHead->nextElement = NULL;


  for(int i = 10; i > 0; i--)
    addElement(pHead, i);

  printList(pHead);

  return (0);
}
