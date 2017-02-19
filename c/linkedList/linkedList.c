#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
**  Module for Linked list                                                    **
*******************************************************************************/

struct node{
  int value;
  struct node * next;
};

void printList(struct node head){
  struct node *temp = &head;
  printf("Start List\n");
  while( temp != NULL ){
    printf("%d\n", temp->value);
    temp = temp->next;
  }
  printf("End list\n\n");
}

//this function assumes that the head node has allready been allocated from memory
//  the function will overwrite the value of whatever head node you pass in.
//  correct usage is " struct node head; fillList(&head, someArray, lengthOfArray);"
void fillList(struct node * head, int arr[], int arrlen){
  struct node *temp = head;
  int i;
  for( i = 0; i < arrlen - 1; i++){
    temp->value = arr[i];
    temp->next = (struct node *)malloc(sizeof(struct node));
    temp=temp->next;
  }
  temp->value = arr[i];
  temp->next = NULL;
}

void addValToEnd(struct node * head, int val){
  struct node * temp = head;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = (struct node *)malloc(sizeof(struct node));
  temp->next->value = val;
  temp->next->next = NULL;
}

void addValToFront(struct node * head, int val){
  struct node * temp = (struct node *)malloc(sizeof(struct node));
  temp->value = head->value;
  temp->next = head->next;
  head->value = val;
  head->next = temp;
}

//1 for true and 0 for false
int contains(struct node * head, int val){
  struct node * temp = head;
  while(temp != NULL){
    if(temp->value == val)
      return 1;
    temp = temp->next;
  }
  return 0;
}

int main(int argc, char** argv){
  struct node head;

  int fill[] = {2,3,4,5};
  fillList(&head, fill, 4);

  printf("The list contains the value %d: %d", 3, contains(&head, 3));



  return 0;
}
