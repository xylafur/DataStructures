#ifndef DOUBLE_LINKED_LIST
  #define DOUBLE_LINKED_LIST
  #include "LinkedList.h"

  template<class T> class DoubleLinkedList{
    protected:
      DoubleLinkedListNode<T> * head;
      DoubleLinkedListNode<T> * tail;
      int length;

      void findTail(){
        DoubleLinkedListNode<T> * temp = head;
        int tempL = 1;
        while(temp != NULL && temp->getNext()!= NULL){
          temp = temp->getNext();
          tempL++;
        }
        this->length = tempL;
        tail = temp;
      }
      void initializeList(DoubleLinkedListNode<T> * pNode){
        std::cout<<"init list"<<std::endl;
        this->head = pNode;
        int size = 0;
        DoubleLinkedListNode<T> *temp = this->head;
        while(temp!= NULL && temp->getNext() != NULL){
            temp = temp->getNext();
            size++;
        }
        this->tail = temp;
        this->length = size;
        std::cout<<"finished init list"<<std::endl;
      }

    public:
      DoubleLinkedList(){
        head = NULL;
        tail = NULL;
        length = 0;
      }
      DoubleLinkedList(T val){
        initializeList( new DoubleLinkedListNode<T>(val) );
        findTail();
      }
      DoubleLinkedList(DoubleLinkedListNode<T> * pNode){
        initializeList(pNode);
        findTail();
      }
      void addToBeg(T val){
        std::cout<<"add to beg triggered"<<std::endl;
        DoubleLinkedListNode<T> *temp = new DoubleLinkedListNode<T>(val);
        temp->setNext(NULL);
        temp->setPrev(NULL);
        addToBeg(temp );
      }
      void addToBeg(DoubleLinkedListNode<T> * pNode){
        if(this->head == NULL)
          initializeList(pNode);
        else{
          pNode->setNext(this->head);
          this->head->setPrev(pNode);
          this->head = pNode;
          this->length++;
        }
      }
      void addToEnd(T val){
        std::cout<<"add to end triggered"<<std::endl;
        DoubleLinkedListNode<T> *temp = new DoubleLinkedListNode<T>(val);
        temp->setNext(NULL);
        temp->setPrev(NULL);
        addToEnd( new DoubleLinkedListNode<T>(val) );
      }
      void addToEnd(DoubleLinkedListNode<T> * pNode){
        std::cout<<"overloaded addTOEnd"<<std::endl;
        if(this->head == NULL)
          initializeList(pNode);
        else{
          pNode->setPrev(this->tail);
          this->tail->setNext(pNode);
          this->tail = pNode;
          this->length++;
        }
      }

      DoubleLinkedListNode<T> * getHead(){
        return this->head;
      }
      DoubleLinkedListNode<T> * getTail(){
        DoubleLinkedListNode<T> *temp = this->head;
        while(temp!=NULL && temp->getNext()!=NULL)
            temp = temp->getNext();
        this->tail = temp;
        return this->tail;
      }
      DoubleLinkedListNode<T> * popHead(){
        DoubleLinkedListNode<T> * temp = this->head;
        this->head = temp->getNext();
        temp->setNext(NULL);
        return temp;
      } 
      DoubleLinkedListNode<T> * popTail(){
        DoubleLinkedListNode<T> * temp = this->tail();
        this->tail = temp->getNext();
        temp->setNext(NULL);
        return temp;
      }
      void printList(){
        DoubleLinkedListNode<T> * temp = head;
        for(int i = 0; i < length; i++)
          cout << "[" << i << "], \t";
        cout << endl;
        for( int i = 0; i < length; i++){
          cout << " " << temp->getValue() << "\t" ;
          temp = temp->getNext();
        }
        cout << endl;
      }
      void printListReverse(){
        DoubleLinkedListNode<T> * temp = this->tail;
        for(int i = 0; i < length; i++)
          cout << "[" << (length - 1 - i) << "], \t";
        cout << endl;
        for(int i = 0; i < length; i++){
          cout << " " << temp->getValue() << "\t" ;
          temp = temp->getPrev();
        }
        cout << endl;
      }
      bool isEmpty(){
        return head==NULL;
      }

  };
#endif
