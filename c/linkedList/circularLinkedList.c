#include <stdlib.h>
#include <stdio.h>

struct node {
    char val;
    struct node * next;
};

struct CircularLinkedList{
    struct node * head;
    struct node * tail;
};


// *  Function that creates a new CircularlinkedList struct and returns it.
// *      Send in the initial value as the parameter.
struct CircularLinkedList * createCircularList(char value);


//   Calculates the length of a circular linked list.
int calcLengthList(struct CircularLinkedList * list);
 

// *  Adds a char value to the end of a circular linked list 
void addToList(struct CircularLinkedList * list, char value);


// *  removes and return the value from CircularLinkedList at specified index
struct node * popAtIndex(int index, struct CircularLinkedList * list);


// *  Prints out a circular linked list for debugging
void printList(struct CircularLinkedList * list);


// *  deletes the entire list, call before freeing the CirculiarLinkedList struct
void deleteList(struct CircularLinkedList * list);


// *  Initializes and returns a CircularLinkedList * from a const char * 
// *  (I used that instead of string because I'm coding this in c lol)
struct CircularLinkedList * createListFromConstChar(const char * in, int length);


/*
 *      MAIN
 */

int main(){
    const char * str = "I Love Computer Science";
    struct CircularLinkedList * list = createListFromConstChar(str, 23);
    printList(list);

    deleteList(list);
    free(list);
    
    return 0;
}



/*
 *
 *
 *      IMPLEMENTATION
 *
 */

/*
 *  Function that creates a new CircularlinkedList struct and returns it.
 *      Send in the initial value as the parameter.
 */
struct CircularLinkedList * createCircularList(char value){
    struct CircularLinkedList * list = calloc(1, sizeof(struct CircularLinkedList) );
    struct node * tempNode = calloc(1, sizeof(struct node) );
    tempNode-> val = value;
    tempNode->next = NULL;

    list->head = tempNode;
    list->tail = tempNode;

    return list;
}

/*
 *  Calculates the length of a circular linked list.
 *      
 */
int calcLengthList(struct CircularLinkedList * list){
    struct node * temp = list->head->next;
    int count = 1;
    while(temp != list->head){
        temp = temp->next;
        count++;
    }
    return count;
}

/*
 *  Adds a char value to the end of a circular linked list 
 */
void addToList(struct CircularLinkedList * list, char value){
    struct node * temp = calloc(1, sizeof(struct node ) );
    temp->val = value;
    temp->next = list->head;
    list->tail->next = temp;
    list->tail = temp;
}


/*
 *  removes and return the value from CircularLinkedList at specified index
 */
struct node * popAtIndex(int index, struct CircularLinkedList * list){
    //meaning were removing the head.
    if(index == 0){
        struct node * temp = list->head;
        list->head = list->head->next;
        list->tail->next = list->head;
        temp->next = NULL;
        return temp;
    }   
    //if its not the first element 
    struct node * elmBefore = list->head;
    for(int i = 0; i < index - 1; i++){
        elmBefore = elmBefore->next;
    }
    struct node * toRemove = elmBefore->next;
    elmBefore->next = toRemove->next;
    toRemove->next = NULL;

    //special case for if we remove the last element.  Needed to keep the circle
    if(index == calcLengthList(list) )
        list->tail = elmBefore;

    return toRemove;
}

/*
 *  Prints out a circular linked list for debugging
 */
void printList(struct CircularLinkedList * list){
    printf("%c ", list->head->val);
    struct node * temp = list->head->next;
    while(temp != list->head){
        printf("%c ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

/*
 *  deletes the entire list, call before freeing the CirculiarLinkedList struct
 */
void deleteList(struct CircularLinkedList * list){
    list->tail->next = NULL;
    struct node * temp1 = list->head;
    struct node * temp2 = temp1;
    while(temp1 != NULL){
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    }
}


/*
 *  Initializes and returns a CircularLinkedList * from a const char * 
 *  (I used that instead of string because I'm coding this in c lol)
 */
struct CircularLinkedList * createListFromConstChar(const char * in, int length){
    if(length <= 0)
        printf("Invalid length for const char *.. Something went wrong\n");

    struct CircularLinkedList * list = createCircularList(in[0]);
    for( int i = 1; i < length; i++){
        addToList(list, in[i] );
    }
    return list;
}

