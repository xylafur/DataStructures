#include "InfNum/InfNumUtil.h"
#include "ArgumentManager.h"
#include <fstream>
#include "Converter/converter.h"

struct node {
    std::string val;
    struct node * next;
};

int readFileToList(std::string filename, struct node * head){
    struct node * temp = head;
    fstream file;
    file.open(filename);
    int length = 0;
    if(file.is_open()){
        std::string str;
        while(getline(file, str)){
            temp->val = str;
            temp->next = new struct node;
            temp = temp->next;
            length++;
        }
        file.close();
    }
    return length;
}

void deleteLinkedList(struct node * head){
    struct node * temp = head;
    while(head != NULL){
        temp = head->next;
        delete(head);
        head = temp;
    }
}

void parseListToArray(std::string * arr, struct node * head, int size){
    struct node * temp = head;
    for(int i = 0; i < size; i++, temp = temp->next)
        arr[i] = temp->val;
    deleteLinkedList(head);
}

void doComputations(std::string * arr, int size, int digPerNode){
    Converter * c = new Converter(digPerNode);
    for(int i = 0; i < size; i++){
        std::cout << "current line =" << arr[i] << std::endl;
        c->parseLine(arr[i]);
    }
}
int main(int argc, char ** argv){
    ArgumentManager am(argc, argv);
    
    std::string filename = am.get("input");
    int digPerNode = am.get("digitsPerNode")[0] - '0';
   
    struct node * head = new struct node;
    int size = readFileToList(filename, head);
    std::string * arr = new std::string[size];
    parseListToArray(arr, head, size);

    doComputations(arr, size, digPerNode);
}
