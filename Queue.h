#include <stdlib.h>
#include <stdio.h>

#define SIZE 4

typedef enum {
  SUCCESS = 0,
  ERR = 1
} Status;

//Node Declaration
typedef struct node{
  int range_data;
  int pos;
} Node;

Node *Buffer[SIZE];

int front = -1;
int back = 0;

typedef struct temp{
  int avg;
  int pos1;
  int pos2;
} Temp;

bool isFull() {
  return ((back + 1) % SIZE) == (front % SIZE);
}

bool isEmpty(){
  return (front == -1 || front == back);
}

int enqueue(int reading, int pos) {
    if(isFull()) return ERR;
    
    Buffer[back] = (Node*)malloc(sizeof(Node));
    Buffer[back]->pos = pos;
    Buffer[back]->range_data = reading;
    
    if(front == -1) front = 0;
    back = (back + 1) % SIZE;
    
    return SUCCESS;
}

Node* dequeue() {
  if (isEmpty()) {
      return NULL;
  }
  Node *temp = Buffer[front];
  Buffer[front] = NULL;  // Clear the pointer
  front = (front + 1) % SIZE;
  if (front == back) {
      front = -1;
      back = 0;
  }
  return temp;
}


Temp* dequeueAvg(){
  int count = 0;
  Temp *temp = (Temp*)malloc(sizeof(Temp));
  while(!isEmpty()){
    Node *temp2 = dequeue();
    if(count == 0){
      temp->pos1 = temp2->pos;
    }
    if(isEmpty()){
      temp->pos2 = temp2->pos;
    }
    temp->avg = temp2->range_data;
    count += 1;
    free(temp2);
  }
  temp->avg = temp->avg/count;
  if(count == 0){
    free(temp);
    return NULL;
  }
  return temp; 
}
