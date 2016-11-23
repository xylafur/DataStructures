#include <stdio.h>
#include <stdlib.h>

/*******************************************
* Variables                                *
********************************************/
typedef struct S_linkedList{
  int data;
  struct S_linkedList* pNextElement;
  struct S_linkedList* pPreviousElement;
} LinkedList;

/*******************************************
* Functions                                *
********************************************/
void addElement(LinkedList *pHead, int value){
  LinkedList *pInsert = pHead;

  while(1){
    pInsert=pInsert->pNextElement;
    //end of list
    if(pInsert==NULL){
      break;
    }
    //found correct spot since ordered
    else if(value >= pInsert->data){
      break;
    }
  }//end of while loop

  LinkedList *newElement = malloc( sizeof( LinkedList));

  newElement->pNextElement = pInsert;
  newElement->pPreviousElement = pInsert->pPreviousElement;
  newElement->data = value;

  pInsert->pPreviousElement->pNextElement = newElement;
  pInsert->pPreviousElement = newElement;
}

void printList(LinkedList *pBeginning){
  LinkedList *pCurrentElement = malloc(sizeof(LinkedList));
  pCurrentElement = pBeginning;
  while(pCurrentElement != NULL){
    printf("%d\t", pCurrentElement->data);
    pCurrentElement = pCurrentElement->pNextElement;
  }
  printf("\n\n");
  free(pCurrentElement);
}

/*******************************************
* Main                                     *
********************************************/

//Initialize the first element of the linked list
LinkedList *pHead = NULL;
int main(){
  pHead = malloc(sizeof(LinkedList));
  LinkedList *pSecondElement = malloc(sizeof(LinkedList));

  pHead->data = 10;
  pHead->pNextElement = pSecondElement;
  pHead->pPreviousElement = NULL;

  pSecondElement->data = 2;
  pSecondElement->pNextElement = NULL;
  pSecondElement->pPreviousElement = pHead;

  printList(pHead);

  addElement(pHead, 7);
  addElement(pHead, 5);
  addElement(pHead, 6);
  addElement(pHead, 8);

  printList(pHead);



  return 0;
}
