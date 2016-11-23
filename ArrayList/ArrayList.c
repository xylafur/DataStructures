#include <stdlib.h>
#include <stdio.h>


typedef struct ArrList{
  int *head;
  int length;
  int realLength;
} ArrList;

ArrList *newArrList(){
  ArrList *ret = malloc(sizeof(ArrList) );
  ret->length = 0;
  ret->realLength = 10;
  ret->head = malloc(sizeof(int) * ret->realLength);

  return ret;
}

void addElm(ArrList *pList, int newElm){
  int i;

  //if the actual size of the array is smaller than the size we
  //  will be using from it, we incease the array's actual size
  //  by 1.5
  if(pList->realLength < pList->length + 1){
    int *temp = malloc(sizeof(int) * (pList->length * 3 / 2));
    pList->realLength *= 3 / 2;

    //copies all old values into the new arr
    for(i = 0; i < pList->length; i++)
      *(temp + i) = *(pList->head + i);

    //adds in new value
    *(temp + pList->length) = newElm;

    free(pList->head);
    pList->head = temp;
  }
  //if the conditional above doesn't trigger our array is large
  //  enough to acomidate another value.
  else{
    *(pList->head + pList->length) = newElm;
  }

  pList->length++;
}

void delElm(ArrList *pList, int index){
  int *tempArr = calloc(pList->length - 1, sizeof(int) );
  int i;

  //add all elements up to index into new array
  for(i = 0; i < index; i++)
    *(tempArr + i) = *(pList->head + i);
  //add all elements from after index to end
  for(i = index + 1; i< pList->length ; i++)
    *(tempArr + i - 1) = *(pList->head + i );

  free(pList->head);
  pList->head = tempArr;
  pList->length--;
}

int getElm(ArrList *pList, int index){
  int ret = pList->head[index];
  return ret;
}

void printArr(ArrList *pList){
  int i;
  for(i = 0; i < pList->length; i++){
    printf("%d\n", getElm(pList, i));
  }
  printf("\n");
}

int indexOf(ArrList *pList, int element){
  int i;
  for(i = 0; i < pList->length; i++)
    if(*(pList->head + i) == element)
      return i;
  return -1;
}

void test(ArrList *pMyList){
  int i;
  for(i = 0; i < 10; i++)
    addElm(pMyList, i);

  printArr(pMyList);
  delElm(pMyList, pMyList->length - 1);
  printArr(pMyList);
  delElm(pMyList, 3);
  printArr(pMyList);
  printf("index of 3: %d\nindex of 2: %d", indexOf(pMyList, 3), indexOf(pMyList, 2));
}


int main(){
  ArrList *pMyList = newArrList();
  //test(pMyList);

  return 1;
}
