#ifndef FILEREADER
    #define FILEREADER
//this class if supposed to read a file into a linked list.  Each node of the
//  linked list should contain one line of the file.

//just something i use for a linked list

#include <string>
#include <fstream>
using namespace std;
//beacause the file should only contain ints im gonna go ahead and parse them
struct fileNode{
    std::string strVal;
    int val;
    fileNode *next = NULL;
};

void createNode(std::string line, fileNode *head){
    //find tail
    fileNode *temp = head;
    while(temp != NULL){
        std::cout<<temp->strVal<<" "<<std::endl;
        temp = temp->next;
    }
    temp = new fileNode;
    temp-> strVal = line;
    temp->next = NULL;
    
}

int parseStrToInt(std::string str){
    int ret = 0;
    for( unsigned int i = 0; i < str.length(); i++){
        ret *= 10;
        int temp = str.at(i) - '0';
        ret+= temp;
    }
    return ret;
}

void parseNodesToInts(fileNode *head){
    fileNode *temp = head;
    while( temp != NULL){
        temp->val = parseStrToInt(temp->strVal);
        temp = temp->next;
    }
}
void deleteFileLinkedList( fileNode *head){
    fileNode * temp = head;
    while(head != NULL){
        temp = head->next;
        delete(head);
        head = temp;
    }
}

void printAllLines(fileNode *head){
    fileNode *temp = head;
    std::cout<<"printing str vals\n";
    while(temp != NULL){
        std::cout<<temp->strVal<<"\t";
        temp = temp->next;
    }
    temp = head;
    std::cout<<"\nprinting int values\n";
    while(temp != NULL){
        std::cout<<temp->val<<"\t";
        temp = temp->next;
    }
    std::cout<<std::endl;
}


int readFile(std::string filename, fileNode *head){
    fstream file(filename);
    int count = 0;
    if(file.is_open() ){
        std::string line;
        while( getline( file, line )){
            createNode(line, head);
            count++;
        }
        file.close();
    }
    return count;
}


int readFileToList(std::string filename, fileNode * head){
    struct fileNode * temp = head;
    fstream file;
    file.open(filename);
    int length = 0;
    if(file.is_open()){
       std::string str;
       while(getline(file, str)){
       temp->strVal = str;
          temp->next = new fileNode;
          temp = temp->next;
          length++;
       }
       file.close();
    }
    parseNodesToInts(head);
    return length;
}


#endif
