#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_SIZE 10
#define MAX_CARS 4
#define INPUT_SIZE 15


/****************************************/
/*************INITIAL VARIABLES*********/
/**************************************/
typedef struct S_RacingCar{
  char name[NAME_SIZE];
  int speed;
  struct S_RacingCar *pNextCar;
} RacingCar;

static RacingCar* pFirstCar = NULL;

/***************************************/
/************FUNCTIONS******************/
/***************************************/
void listCars(void){
  RacingCar *pCurrentPointer = pFirstCar;
  while(pCurrentPointer != NULL){
    printf("%s\n", pCurrentPointer->name);
    pCurrentPointer = pCurrentPointer->pNextCar;
  }
}

void appendCarToList(char *newName, int newSpeed){
  RacingCar *pNewCar = malloc(sizeof(RacingCar));
  strcpy(pNewCar->name, newName);
  pNewCar->speed = newSpeed;
  pNewCar->pNextCar = pFirstCar;
  pFirstCar = pNewCar;
}

void addCar(){
  char carName[INPUT_SIZE];
  int carSpeed;
  char userInput[INPUT_SIZE];

  printf("Enter the Name and Speed of car:");
  fgets(userInput, INPUT_SIZE, stdin);

  //numElements equals how many elements the user entered (seperated by space)
  int numElements = sscanf(userInput, "%s %d", carName, &carSpeed);
  if(numElements == 2){
    printf("New car of name: %s, with speed: %d\n\n", carName, carSpeed);
    appendCarToList(carName, carSpeed);
  }else{
    printf("Not a valid input.  Seperate name and speed by a space.\n\n");
  }

}

/***************************************/
/***************MAIN********************/
/***************************************/
int main(){

  char userInput[INPUT_SIZE];
  char command[INPUT_SIZE];

  printf("Enter Commands!\n");
  while(fgets(userInput, INPUT_SIZE, stdin)){
    sscanf(userInput, "%s", command);

    if( strcmp(command, "list") ==0 ){
      listCars();
    }
    else if(strcmp(command, "add") ==0){
      addCar();
    }
    else if(strcmp(command, "quit") == 0){
      printf("quitting...\n");
      break;
    }
  }


  return (0);
}
