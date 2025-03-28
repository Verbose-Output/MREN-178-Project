#include <stdlib.h>
#include <stdio.h>
#include <bool.h>

#define SIZE 5;

typedef enum {
  SUCCESS = 0,
  ERROR = 1
} Status;

//Node Declaration
typedef struct node{
  int range_data;
  int pos;
} Node;

Node *buffer[SIZE];

int front = -1;
int back = 0;

typedef struct temp{
  int avg;
  int pos1;
  int pos2;
} Temp;

bool isFull(){
  return (back + 1) % SIZE == front;
}

bool isEmpty(){
  return (front == -1 || front == back);
}

int enqueue(int reading, int pos){

  if(isFull()){
    return ERROR;
  }
  buffer[back]->pos = pos;
  buffer[back]->range_data = reading;
  if(front == -1){
    front == 0;
    return SUCCESS;
  }
  else
  back = (back + 1) % SIZE;
  
  return SUCCESS;
}

Node* dequeue(){
  if(isEmpty()){
    return ERROR;
  }
  Node *temp = buffer[front];
  if(front == back -1){
    front = -1;
    back = 0;
  }
  else{
    front = (front + 1) % SIZE;
  }
}

Temp* dequeueAvg(){
  int count = 0;
  Temp *temp = malloc(sizeof(Temp));
  while(!isEmpty()){
    Node *temp2 = dequeue();
    if(count = 0){
      temp->pos1 = temp2->pos;
    }
    if(isEmpty()){
      temp->pos2 = temp2->pos;
    }
    temp->avg = temp2->range_data;
    count += 1;
  }
  temp->avg = avg/count;
  return temp; 
}
