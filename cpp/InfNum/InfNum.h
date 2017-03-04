#ifndef INFNUM_CLASS
    #define INFNUM_CLASS

    #include "../Lists/LinkedLists/LinkedList.h"
class InfNum{
private:
    LinkedList<int *> * list;
    int length, numNodes, modo, numArrays;
    char sign;
    std::string str;

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
        this->list = new LinkedList<int *>();
        this->numNodes = numNodes;
        this->str = str;
        upKeep();
        parseString();
    }
    void print(){
        LinkedListNode<int *> * temp = this->list->getHead();
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

        if(this->length	> a.length)
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
};
#endif
