#ifndef INFNUM_CONVERTER
    #define INFNUM_CONVERTER
#include "../InfNum/InfNum.h"
#include "stack.h"
#include <string>
#include "evaluator.h"

#ifndef EVAL_STRUCT
    #define EVAL_STRUCT
typedef struct Eval{
    bool isNum;
    InfNum num;
    char oper;
} Eval;
void printEval(Eval in){
    if(in.isNum)
        in.num.print();
    else
        std::cout<<in.oper<<std::endl;
}
void printEvalStack(Stack<Eval> *in){
    std::cout <<"Print Eval" << std::endl;
    while(!in->isEmpty())
        printEval(in->pop());
}
#endif

class Converter{
    /*
     *  This class should take a string and conver it into two sperate stacks
     *  One for operators and another for operands(which are InfNum type in this
     *          case)
     *
     */
private:
    Stack<char> *operators;
    Stack<InfNum> *operands;
    Stack<Eval> *eval;
    Evaluator *evaluator;
    int stringIndex, digPerNode, depth, numOperators;

    bool isOperator(char input){
        //uses a switch statement to idetify if the character is an operator
        switch(input){
            case '+':
            case '-':
            case '*':
            case '/':
                numOperators++;
            case '(':
            case ')':
                return true;
            default:
                return false;
        };
    }
    bool higherPrecedence(char oper){
        if(oper == '*' || oper == '/'){
            char currentOper = operators->peek();
            if(currentOper =='+' || currentOper == '-')
                return true;
        }
        return false;
    }
    void flushTillParenth(){
        //basically pop off all values will we get closing parenth
        while(!operators->isEmpty() && operators->peek() != '('){
            Eval temp;
            temp.isNum = false;
            temp.oper = operators->pop();
            eval->push(temp);
        }
    }
    void flushOperands(){
        while(!operands->isEmpty()){
            operands->peek().print();
            Eval temp;
            temp.isNum = true;
            temp.num = operands->pop();
            eval->push(temp);
        }
    }
    void flushOperators(){
        while(!operators->isEmpty() ){
            Eval temp;
            temp.isNum = false;
            temp.oper = operators->pop();
            if(temp.oper == '(')
                continue;
            eval->push(temp);
        }
    }
public:
    Converter(int digPerNode){
        operators = new Stack<char>();
        operands = new Stack<InfNum>();
        eval = new Stack<Eval>();
        evaluator = new Evaluator();
        stringIndex = 0, depth = 0, numOperators = 0;
        this->digPerNode = digPerNode;
    }
    ~Converter(){
        delete(operators);
        delete(operands);
        delete(eval);
        delete(evaluator);
    }
    void parseLine(std::string input){
        //This function will take in a line in infix form, convert it and then
        //evaluate it
        int len = input.length();
        std::string buff = "";
        std::cout << "len="<<len<<std::endl;
        while(stringIndex < len){
            std::cout<<"current char = " << input.at(stringIndex) << std::endl;
            if(isOperator(input.at(stringIndex)) ){
                //flush buffer to oparands stack if not empty 
                if(buff.length() > 0){
                    std::cout<<"creating infnum with the value "<<buff<<std::endl;
                    InfNum temp(buff, this->digPerNode);
                    std::cout<<"created temp with value=";
                    temp.print();
                    std::cout<<"pushing to stack"<<std::endl;
                    operands->push(temp);
                }
                buff = "";
                if(!operators->isEmpty() && input.at(stringIndex) == ')'){
                    std::cout<<"operatros not empty"<<std::endl;
                    depth--;
                    flushOperands();
                    flushTillParenth();
                    stringIndex++;
                    continue;
                }
                else if(!depth && !operators->isEmpty() && higherPrecedence(input.at(stringIndex))){
                    std::cout<<"higher precedence found"<<std::endl;
                    Eval temp;
                    temp.isNum = false;
                    temp.oper = operators->pop();
                    if(temp.oper != '(')
                        eval->push(temp);
                }
                if(input.at(stringIndex) == '(')
                    depth++;
                std::cout<<"pushing to operators stack"<<std::endl;
                operators->push(input.at(stringIndex));
                std::cout<<"finished this branch"<<std::endl;
            }
            else if (input.at(stringIndex) == ' ')
            {stringIndex++;continue;}    
            else{
                //add the character to buffer because its part of a num
                buff = buff + input.at(stringIndex);
            }
            stringIndex++;
            std::cout<<"flushing operands"<<std::endl;
            flushOperands();
            std::cout<<"finished flush"<<std::endl;
        }
        if(buff.length() > 0){
            //std::cout<<"creating InfNum with value: " << buff << std::endl;
            InfNum temp(buff, this->digPerNode);
            operands->push(temp);
        }
        flushOperands();
        flushOperators();

       /*std::cout << "Operators: ";
       operators->print();
       std::cout << "Operands: ";
       operands->objectPrint();*/
        //printEvalStack(eval);
        InfNum result = evaluator->evaluate(eval, numOperators);
        //std::cout<<"printing holder"<<std::endl;
        result.print();
    }

};
#endif
