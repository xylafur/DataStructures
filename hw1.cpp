#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

/*
  Global Variables that I use to trigger all of my debug print statments.
  Make sure that it is set to false unless you want significant output.
*/
bool debug = false;

bool mulDebug = false;

/*
  Struct that I use to create a double linked-list insie the infinate number class.
  'pw' in this case is the power of the exponent.  Just has to do with the nature of
  how I represent the numbers.
*/
struct node{
  int val;
  int pw;
  struct node *prev;
  struct node *next;
};

/*******************************************************************************
********************************************************************************
**  infNum Class -- Used to represent a number of any size.  Has ablity to    **
**    add and multiply any number with exact percision.  (Only supports ints) **
********************************************************************************
********************************************************************************
**  Instance variables:                                                       **
**    - nodes : number of nodes in the infNum, nodes have a val of 1 or 2 dig **
**    - length : Length of the input string:: the number of digits in the num **
**    - head / tail : pointers to head and tail of the linked list            **
**    - number : the input number as a string                                 **
********************************************************************************
********************************************************************************
**  Member Functions (There are a whole fucking lot.. Like Jesus f'ing christ)**
********************************************************************************
**    private:                                                                **
**      calcLength : calculates the length of a string                        **
**        -returns (int)                                                      **
**      fillNode : fills the power and val to a node (called in incrementNode)**
**        -returns (void)                                                     **
**      incrementNode : fills a node with the specified values and then       **
**          returns the next node in the list.                                **
**        -returns (struct node pointer)                                      **
**      initFromNode : Used in overloaded constructor.  Creates a infNum from **
**          an already initialized linked list                                **
**        -returns (void)                                                     **
**      initList : used in the primary constructor.  Uses a char array to     **
**          create a linked-list for the object.                              **
**        -returns (void)                                                     **
**      addTwo : called by the addition operator                              **
**        -returns (infNum)                                                   **
**      mulTwo :called by multiplication operator                             **
**        -returns (infNum)                                                   **
**      tenPow : calculates 10 to the power of whatever                       **
**        -returns (int)                                                      **
**      makeChar : truns a string (or const char *) into a char array         **
**        -returns (char pointer)                                             **
********************************************************************************
**  public:                                                                   **
**    infNum : constructor and overloaded constructor (string and node)       **
**      -returns (void (technically i guess it would return infNum *))        **
**    ~infNum : destructor.  Frees up all allocated mem for linked list       **
**      -returns (void?)                                                      **
**    printNum : prints out the infNum to the colnsole as a string.           **
**      -returns (void)                                                       **
********************************************************************************
*******************************************************************************/

class infNum{
  private:
    int nodes, length;
    struct node * head;
    struct node * tail;
    string number;

    int calcLength(char* in){
      int count = 0;
      char * temp = in;
      while(*temp != '\0'){
        count++;
        temp++;
      }
      return count;
    }//end length
    int calcLength(const char* in){
      int count = 0;
      const char * temp = in;
      while(*temp != '\0'){
        count++;
        temp++;
      }
      return count;
    }//end length

    void fillNode(struct node * pNode, int valu, int power){
      pNode->val = valu;
      pNode->pw = power;
    }

    struct node * incrementNode(struct node * pNode, int valu, int power){
      if(debug)
        cout << "\n###\tStarting increment mode with val " << valu << "\t###" << endl;
      fillNode(pNode, valu, power);

      struct node * temp2 = (struct node *)malloc(sizeof(struct node *));
      temp2->prev = pNode;
      pNode->next = temp2;
      pNode = temp2;

      return pNode;
    }

    void initFromNode(struct node * in){
      head = in;
      int countN = 0, numberOfNodes = 0;

      struct node * temp = head;
      while(temp->next != NULL){
        countN++;
        temp = temp->next;
      }
      numberOfNodes = countN % 2 == 0 ? countN / 2 : countN / 2 + 1;
      tail = temp;
      nodes = numberOfNodes;
      length = countN + 1;


    }

    void initList(char * in){
      if(debug)
        cout << "\n###\tinitList starting\t###" << endl;

      struct node * curr = head;
      int power = curr->pw;

      //it is a number of even length
      if(length % 2 == 0){
        if(debug)
          cout << "running even length conditional in initList\nInput string -> "
              << in << endl;
        //loop through and assign size of 2
        for(int i = 0; i < length; i+=2){
          if(debug)
            cout << "*(in + i) == " << *(in + i)
                <<". And *(in + i + 1) == " << *(in + i + 1) << endl;

          int temp = (*(in + i) - '0' )* 10;
          temp += (*(in + i + 1) - '0');

          if(debug)
            cout << "temp has a value of " << temp << endl;

          curr = incrementNode(curr, temp, power);
          power--;
        }//end for
      }//end if

      // a number of odd length
      else{
        if(debug)
          cout << "running odd length conditional\nInput string -> "
              << in << endl;
        for(int i = 0; i < length; i+=2){
          if(i == 0){
            if(debug)
              cout << "*(in + i) == " << *(in + i)
                  << endl;
            curr = incrementNode(curr, (*(in + i) - '0'), power);
            i++;
            if(i >= length)
              break;
          }
          if(debug)
            cout << "*(in + i) == " << *(in + i)
                <<". And *(in + i + 1) == " << *(in + i + 1) << endl;

          int temp = (*(in + i) - '0') * 10;
          temp += (*(in + i + 1) - '0');

          if(debug)
            cout << "Temp has a value of " << temp << endl;

          curr = incrementNode(curr, temp, power);
          power--;
        }
      }
      tail = curr->prev;
      tail->next = NULL;
      curr = NULL;

    }

    infNum addTwo(infNum& other){
      if(debug)
        cout << "\nstarting addTow method" << endl;

      int numNodes = max(nodes, other.nodes), carry = 0, power = 1;
      struct node * ret = (struct node *)malloc(sizeof(struct node));
      ret->next = NULL;

      struct node * shorter;
      struct node * longer;

      /*  Just a block to assign the longer number to
          longer and the shorter number to shorter for
          simplicity.                                   */
      if(nodes == numNodes){
        longer = tail;
        shorter = other.tail;
      }
      else{
        shorter = tail;
        longer = other.tail;
      }


      /*  This is a loop to actually add individual nodes
          of the number.  Starts from the very end and
          moves towards the front.                        */
      while(longer !=NULL){
        if(shorter == NULL){
          int tempNum = (longer->val + carry);
          carry = 0;

          while(tempNum >= 100){
            tempNum-=100;
            carry++;
          }//end while temp > 100

          if(debug)
            cout << "***Shorter == NULL***\ttemp val == " << tempNum  <<
                "\tcurrent node (longer) has a value of -> "<< longer->val << endl;

          ret->val = tempNum;
          ret->pw = power;
          ret->prev = (struct node *)malloc(sizeof(struct node));
          ret->prev->next = ret;
          ret = ret->prev;

          longer = longer->prev;

        }
        else{
          int tempNum = (shorter->val + longer->val + carry);
          carry = 0;
          //this loop is needed for overflow of 2 digit nodes
          while(tempNum >= 100){
            tempNum-=100;
            carry++;
          }//end while temp > 100
          //tempNum *= tenPow(power);
          if(debug)
            cout << "***Shorter != NULL***\ttemp val == " << tempNum <<
                "\tcurrent short node -> " << shorter->val << "\tcurent long node -> " <<
                  longer->val << endl;

          ret->val = tempNum;
          ret->pw = power;
          ret->prev = (struct node *)malloc(sizeof(struct node));
          ret->prev->next = ret;
          ret = ret->prev;

          longer = longer->prev;
          shorter = shorter->prev;
        }
        power++;
      }//end longer while

      if(carry > 0){
        if(debug)
          cout << "***Carry != 0***\tCarry = " << carry
              << endl;
        ret->val = carry;
        ret->pw = power;
        ret->prev = (struct node *)malloc(sizeof(struct node));
        ret->prev->next = ret;
        ret = ret->prev;
      }

      ret = ret->next;
      ret->prev = NULL;

      if(debug)
        cout << "\n\n" << endl;
      return infNum(ret);
    }

    infNum mulTwo(infNum& other){
      //nested for loop
      //multiply each node to each node of the other
      //keep track of the power to shift it over.
      //create an infinate number for the product of each node and add them together

      //rather than adding the numbers maybe new inf nums should be generated with sets of (00) at the end
      //    equal to the power of that node
      //This would probebly be the best approach just because the entire point of this class is to not rely on ints
      //Could easily overflow and become lowest possible value

      if(debug)
        cout << "\n$$$\tStarting the multiplication method\t$$$" << endl;


      struct node * temp1 = tail;
      struct node * temp2 = other.tail;
      int inPow = 0, outPow = 0;
      infNum * tempRet = new infNum("0");
      infNum toRet = *tempRet;

      if(mulDebug){
        cout << "In the beginning toRet = ";
        toRet.printNum();
      }

      while(temp1 != NULL){
        if(mulDebug)
          cout << "Excecuting the outer while loop " << endl;
        int tempNum = 0;

        while(temp2 != NULL){
          tempNum += temp1->val * temp2->val * tenPow(inPow) * tenPow(outPow);

          if(mulDebug)
            cout << "temp1->val (" << temp1->val << ") * temp2->val ("
                << temp2->val << ")= "<< temp1->val * temp2->val * tenPow(inPow) * tenPow(outPow)
                << " and tempNum = (" << tempNum << ")" <<
                "\ninPow: " << inPow << "\toutPow: " << outPow << endl;

          if(debug)
            cout << "Temp1->val = " << temp1->val << "\ttemp2->val = "
                << temp2->val << "\ttempNum = " << tempNum << endl;

          inPow +=2;
          temp2 = temp2->prev;
        }
        string s = to_string(tempNum);
        infNum * tempInfNum = new infNum(s.c_str() );


        if(mulDebug){
          cout << "string s has value of: " << s << "\nAdding Inf Nums (tempInfNum)" ;
          tempInfNum->printNum();
          cout << " and (toRet)";
          toRet.printNum();
        }

        infNum fuckingFuckShit = toRet + *tempInfNum;
        if(mulDebug){
          cout << "fuckingFuckShit temp val has a fucking value of : " ;
          fuckingFuckShit.printNum();
        }
        toRet = fuckingFuckShit;

        if(mulDebug){
          cout << "inside the function toRet currently = ";
          toRet.printNum();
          printf("\n");
        }

        delete(tempInfNum);
        outPow += 2;
        inPow = 0;
        temp2 = other.tail;
        temp1 = temp1->prev;
      }

      return toRet;
    }

    int tenPow(int powa){
      int temp = 1;
      for(int i = 0; i < powa ; i++)
        temp *= 10;
      return temp;
    }

    char * makeChar(const char * in, int length){
      char * temp = (char *)malloc(sizeof(length));
      for( int i = 0; i < length; i++){
        *(temp + i) = *(in + i);
      }
      return temp;


      /*
          Step1: get the linked list for each number and assign variables to keep track of the current power (actually the struct has that built in)
          Step2: Have an outer loop that goes through each node of the first number
              inside of that loop, have another loop that goes through each node of the other number
                multiply each node by each other node and keep track of the power
          Step3: ??? this is the tricky part, how am I going to combine this number and ensure that there will not be an overflow
          Step4:
      */
    }

  public:

    infNum(const char * inp){
      if(debug)
        cout << "###\tconstructor begin\t###" << endl ;

      number = inp;

      char * in = makeChar(inp, calcLength(inp));

      length = calcLength(in);
      nodes = length % 2 == 0 ? length / 2 : length / 2 + 1;

      head = (struct node *)malloc(sizeof(struct node));
      head->prev = NULL;
      head->pw = nodes;
      initList(in);

      if(debug)
        cout << "###constructor ending###\n\n" << endl;
    }

    infNum(struct node * in){
      initFromNode(in);
      number = "Sum number";
    }

    ~infNum(){
      if(debug)
        cout << "###\tdestructor starting for " <<
            number << "\t###" << endl;
      struct node * temp = head;

      while(temp !=NULL ){
        temp = head->next;
        free(head);
        head = temp;
      }
    }

    infNum operator +( infNum& other){
      if(debug)
        cout << "Running plus operator method inside infNum" <<endl;

      return addTwo(other);
    }

    infNum operator *(infNum& other){
      if(debug)
        cout << "Running mult operator method inside infNum" << endl;

      return mulTwo(other);
    }


    void printNum(){
      struct node * temp = head;
      int count = 0;
      //printf("infNum = ");
      while(true){
        if(count == 0 || temp->val >= 10)
          printf("%d", temp->val);
        else
          printf("0%d", temp->val);
        if(temp->next==NULL)
          break;
        count++;
        temp=temp->next;
      }
      printf("\n");
    }

};

int main(int argc, char** argv){

  infNum * myNum = new infNum("1234");
  infNum * myNum2 = new infNum("9876");
  infNum * zero = new infNum("0");
  infNum * threeSomethin = new infNum("11851200");

  myNum->printNum();
  myNum2->printNum();

  infNum  newNum = *myNum * *myNum2;

  infNum addNum = *zero + *threeSomethin;

  newNum.printNum();

  cout << "When i add those two nums: ";
  addNum.printNum();

  delete(myNum);
  delete(myNum2);

  return 0;
}
