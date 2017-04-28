#ifndef INFNUM_CLASS
    #define INFNUM_CLASS

    #include "../Lists/DoubleLinkedList.h"
class InfNum{
private:
    DoubleLinkedList<int *> * list;
    int length, numNodes, modo, numArrays;
    char sign;
    std::string str;
    bool zero;

    void upKeep(){
        if(this->str.length() > 0 && this->str.at(0) == '-'){
            this->sign = '-';
            this->str = this->str.substr(1);
        }
        else
            this->sign = '+';
        this->length = this->str.length();
    }
    
    void parseString(){
        this->modo = this->length  % numNodes;
        this->numArrays = modo == 0 ? this->length / numNodes : this->length / numNodes + 1;
        //special case for small numbers
        if(this->length <= this->numNodes){
            int * arr = new int[this->numNodes];
            for(int i = 0; i < this->length; i++){
                arr[this->numNodes - 1 - i] = this->str.at(this->str.length() - 1 - i);
            }
            this->list->addToEnd(arr);
            return;
        }
        int index = numArrays;
        if( modo != 0 ){
            int * temp = new int[this->numNodes];
            nodeCreator(this->str.substr(0, modo), temp, this->numNodes);
            this->list->addToEnd(temp);
            index--;
        }
        for( int i = 0; i < index; i++){
            int * temp = new int[this->numNodes];
            nodeCreator(
                    this->str.substr( (i * numNodes) + modo, numNodes),
                    temp, this->numNodes
            );
            this->list->addToEnd(temp);
        }
    }

    void nodeCreator(std::string s, int * arr, int size){
        int length = s.length();
        for(int i = 0; i < size; i++){
            if(length - i - 1 < 0)
                arr[size - 1 - i] = 0;
            else
                arr[size - 1 - i] = s.at( length - 1 - i ) - '0';
        }
    }
    bool greater(const InfNum & a){
        LinkedListNode<int *> * temp1 = this->list->getHead();
        LinkedListNode<int *> * temp2 = a.list->getHead();
        while(temp1 != NULL && temp2 != NULL){
            for( int i = 0; i < this->numNodes; i++){
                if(temp1->getValue()[i] > temp2->getValue()[i] )
                    return true;
                else if(temp1->getValue()[i] < temp2->getValue()[i])
                    return false;
            }
            temp1=temp1->getNext();
            temp2=temp2->getNext();
        }
        return false;
    }
    bool less(const InfNum & a){
        LinkedListNode<int *> * temp1 = this->list->getHead(), 
                *temp2 = a.list->getHead();
        while(temp1 != NULL && temp2 != NULL){
            for( int i = 0; i < this->numNodes; i++){
                if(temp1->getValue()[i] < temp2->getValue()[i] )
                    return true;
                else if(temp1->getValue()[i] > temp2->getValue()[i])
                    return false;
            }
            temp1=temp1->getNext();
            temp2=temp2->getNext();
        }
        return false;
    }


public:
    InfNum(std::string str, int numNodes){
        this->list = new DoubleLinkedList<int *>();
        this->numNodes = numNodes;
        this->str = str;
        if(this->str.length() == 1 && this->str[0] == '0')
            this->zero = true;
        else
            this->zero = false;
        upKeep();
        parseString();
    }
    InfNum(DoubleLinkedListNode<int *> *head, int numNodes){
        this->list = new DoubleLinkedList<int *>(head);
        this->numNodes = numNodes;
    }
    InfNum(){

    }
    void print(){
        if(this->zero){std::cout<<"0"<<std::endl;return;}
        DoubleLinkedListNode<int *> * temp = this->list->getHead();
        bool zeros = true;
        if(this->sign == '-')
            std::cout<<'-';
        while(temp != NULL){
            for(int i = 0; i < this->numNodes; i++){
                if(zeros && temp->getValue()[i] == 0)
                    continue;
                else if(zeros && temp->getValue()[i] != 0)
                    zeros = false;
                std::cout << temp->getValue()[i];
            }
            temp = temp->getNext();
        }
        std::cout << std::endl;
    }
    bool operator > (const InfNum & a){
        if(this->sign == '-' && a.sign != '-')
            return false;
        else if(this->sign != '-' && a.sign == '-')
            return true;
        else if(this->sign == '-' && a.sign == '-'){
            if(this->length > a.length)
                return false;
            else if(this->length < a.length)
                return true;
            else
                return !greater(a);
        }

        if(this->length > a.length)
            return true;
        else if(this->length < a.length)
            return false;
        return greater(a);
    }
    bool operator < (const InfNum & a){
        if(this->sign == '-' && a.sign != '-')
            return true;
        else if(this->sign != '-' && a.sign == '-')
            return false;
        else if(this->sign == '-' && a.sign == '-'){
            if(this->length > a.length)
                return true;
            else if(this->length < a.length)
                return false;
            else
                return !less(a);
        }

        if(this->length < a.length)
            return true;
        else if(this->length > a.length)
            return false;
        return less(a);
    }
    bool operator == (const InfNum & a){
        if(this->length != a.length)
            return false;
        LinkedListNode<int *> *temp1 = this->list->getHead(),
                *temp2 = a.list->getHead();
        while(temp1 != NULL && temp2 != NULL){
            for( int i = 0; i < this->numNodes; i++)
                if(temp1->getValue()[i] != temp2->getValue()[i] )
                    return false;
            temp1=temp1->getNext();
            temp2=temp2->getNext();
        }
        return true;
    }
    InfNum operator - (const InfNum & a){
        return a;
    }
    InfNum operator + (const InfNum & a){
        //if one is pos and the other is neg
        if(this->sign != a.sign){
            //one possible way we could do this is make another copy of the
            //negatve one and then just subtract that from the positive one
            return a;
            /*
            if(this->sign =='-'){
                this->sign = '+';
                InfNum ret = a - *this;
                this->sign = '-';
            }
            else{
                a.sign = '+';
                InfNum ret = *this-a;
                a.sign = '-';
            }
            return ret;
            */
        }
        DoubleLinkedListNode<int *> *thisTemp = this->list->getTail(),
                *aTemp = a.list->getTail(), *head = new DoubleLinkedListNode<int *>();
        bool carry = false;
        while(aTemp != NULL || thisTemp != NULL){
            int * arr = new int[this->numNodes];

            for( int i = this->numNodes - 1; i >= 0; i--){
                int tempNum;
                if(aTemp!=NULL && thisTemp != NULL)
                    tempNum = aTemp->getValue()[i] + thisTemp->getValue()[i];
                else if(aTemp != NULL)
                    tempNum = aTemp->getValue()[i];
                else
                    tempNum = thisTemp->getValue()[i];
                if(carry){
                    tempNum += 1;
                    carry = false;
                }
                if(tempNum >= 10){
                    tempNum -= 10;
                    carry = true;
                }
                arr[i] = tempNum;
            }
            head->setValue(arr);

            if(aTemp != NULL)
                aTemp = aTemp->getPrev();
            if(thisTemp != NULL)
                thisTemp = thisTemp->getPrev();

            if(aTemp != NULL && thisTemp != NULL){
                DoubleLinkedListNode<int *> *temp = new DoubleLinkedListNode<int *>();
                head->setPrev(temp); temp->setNext(head);
                head = temp;
            }
        }
        //meaning theres an extra digit
        //carry = false;
        if(carry){
            DoubleLinkedListNode<int *> *temp2 = new DoubleLinkedListNode<int*>();
            int * arr = new int[this->numNodes];
            arr[this->numNodes - 1] = 1;
            temp2->setValue(arr);
            temp2->setNext(head);   head->setPrev(temp2);
            head = temp2;
        }
        InfNum ret(head, this->numNodes);
        if(this->sign =='-')
            ret.sign = '-';
        return ret;
    }
    
    friend InfNum operator * (const InfNum & a, const InfNum & b);

    InfNum operator / (const InfNum & a){
        if( this->greater(a) ){
            //this->print();
            std::string zero = "0";
            InfNum temp(zero, this->numNodes);
            int count = 0;
            while( this->greater(temp) ){
                temp.print();
                temp = temp + a;
                count++;
            }
            std::string ret = "";
            while( count > 0 ){
                ret = char(((count % 10) + '0')) + ret;
                count /= 10;
            }
            InfNum b(ret, this->numNodes);
            return b;
        }
        else if(this->less(a)){
           std::string zero = "0";
           InfNum o(zero, this->numNodes);
           return o;
        }
        else{
            std::string one = "1";
            InfNum o(one, this->numNodes);
            return o;
        }
    }
};
void printArr(int * arr, int size){
    for( int i = 0; i < size; i++){
        std::cout << arr[i];
    }
    std::cout<<std::endl;
}
std::string convertArrToStr(int * arr, int size){
    std::string s = "";
    for(int i = size - 1; i >= 0; i--){
        s = char(arr[i] + '0') + s;
    }
    return s;
}

void checkOverflow(int * arr, int size);
InfNum operator * (const InfNum & a, const InfNum & b){
/*
         *      Steps:
         *          -Multiply each number at each index of each node together
         *                  while keeping track of the offset.
         *          -Move said number to the correct index of the result array.
         *          -Check result array for overflow
         *          -Turn the contents of the result array into a string.
         *          -Create an InfNum based on said string and return it.
         *          ***(Make sure that if one sign is negative to make the result
         *                  negative as well)
         */
        int len = b.length + a.length;
        int aOff = 0, bOff = 0, index = len - aOff - bOff - 1;
        int * result = new int [len];

        DoubleLinkedListNode<int *> *tempa = a.list->getTail(), *tempb = b.list->getTail();
        //need to access every element in each linked list
        int aDepth = 0;
        int iter = 1;
        while(tempa != NULL){
            int bDepth = 0;
            int *aVal = tempa->getValue();
            
            while(tempb != NULL){
                int temp = 0;
                int *bVal = tempb->getValue();
                aOff = aDepth;
                bOff = bDepth;
                for(int i = a.numNodes - 1; i >= 0; i--){
                    for(int j = a.numNodes -1; j >= 0; j--){
                        if(aVal[i]==0||bVal[j]==0){
                            bOff++;continue;
                        }
                        index = len - aOff - bOff - 1;
                        temp = aVal[i] * bVal[j];

                        result[index] += temp;

                        printArr(result, len);
                        checkOverflow(result, len);
                        bOff++;
                    }
                    bOff = bDepth;
                    aOff++;
                }
                tempb = tempb->getPrev();
                bDepth += a.numNodes;
            }
            bOff = 0;
            tempb = b.list->getTail();
            tempa = tempa->getPrev();
            aDepth += a.numNodes;
            aOff = aDepth;
        }
        std::string s = convertArrToStr(result, len);
        InfNum ret(s, a.numNodes);
        if(a.sign == '-' ^ b.sign =='-')
            ret.sign = '-';
        return ret;
}
void checkOverflow(int * arr, int size){
        //function to ensure that all ints in an array are only length 1
        int temp = 0;
        for(int i = size - 1; i >= 0; i--){
            arr[i] += temp;
            if(arr[i] >= 10){
                temp = arr[i] / 10;
                arr[i] = arr[i] % 10;
            }
            else
                temp = 0;
        }
    }

#endif
