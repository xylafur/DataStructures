#ifndef INFNUM_EVALUATOR
    #define INFNUM_EVALUATOR
#include "../InfNum/InfNum.h"
#include "stack.h"

/*
 *  so we need to invert the eval stack and then every time we get to an operand
 *  we need to evalute
 */

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


class Evaluator{
//to evaluate we need to get whatever is at the head of 
private:
    InfNum preformOperation(InfNum a, InfNum b, char oper){
        switch(oper){
            case'+':
                return a + b;
                break;
            case '-':
                return a - b;
                break;
            case '*':
                return a * b;
                break;
            case '/':
                return a / b;
                break;
            default:
                std::cout<<"unsupporeted operation"<<std::endl;
        };
        return a;
    }
    
public:
    Evaluator(){}

    InfNum evaluate(Stack<Eval> *inStack, int numOperators){
        Stack<Eval> *stack = new Stack<Eval>();
        while(!inStack->isEmpty())
            stack->push( inStack->pop() );
        Stack<InfNum> *holder = new Stack<InfNum>(); 
        
        while(!stack->isEmpty() && numOperators != 0){
            //std::cout<<"Running while loop"<<std::endl;
            //pop values from our reversed stack until we get an operator
            Eval temp = stack->pop();
            //std::cout<<"num operators = "<<numOperators<<std::endl; 
            if(temp.isNum){
                //std::cout<<"printingNum"<<std::endl;
                //temp.num.print();
                holder->push(temp.num);
            }
            else{
                InfNum a = holder->pop();
                InfNum b = holder->pop();
                InfNum result = preformOperation(a, b, temp.oper);
                //std::cout<<"printing result..";
                //result.print();
                holder->push(result);
                numOperators--;
                //std::cout<<"pushing result"<<std::endl;
            }
        }
        InfNum end = holder->pop();
        //end.print();
        delete(stack);
        delete(holder);
        return end;
    }
};
    
#endif
