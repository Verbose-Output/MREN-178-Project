//Include Standard libraries
#include <stdlib.h>
#include <stdio.h>

//Buffer size
#define SIZE 2

//Enum definitions
typedef enum {
  SUCCESS = 0,
  ERR = 1
} Status;

//Node Declaration
typedef struct node{
  float range_data;
  int pos;
} Node;

//Declaring array of nodes
Node *Buffer[SIZE];

//Initializing front and back trackers
int front = -1;
int back = 0;

//temp struct to deliver information
typedef struct temp{
  float avg;
  int pos1;
  int pos2;
} Temp;

//Checks if queue/buffer is full
bool isFull() {
  return ((back + 1) % SIZE) == (front % SIZE);
}

//Checks if queue/buffer is empty
bool isEmpty(){
  return (front == -1 || front == back);
}

//Enqueue fucntion
int enqueue(float reading, int pos) {
    if(isFull()) return ERR;
    
    //Allocate memory and insert data
    Buffer[back] = (Node*)malloc(sizeof(Node));
    Buffer[back]->pos = pos;
    Buffer[back]->range_data = reading;
    
    //Update indecies
    if(front == -1) front = 0;
    back = (back + 1) % SIZE;
    
    return SUCCESS;
}

//Dequeue function
Node* dequeue() {
  if (isEmpty()) {
      return NULL;
  }
  //Set temp pointer to front
  Node *temp = Buffer[front];
  //clear pointer
  Buffer[front] = NULL;
  //Update indicies
  front = (front + 1) % SIZE;
  if (front == back) {
      front = -1;
      back = 0;
  }
  return temp;
}


Temp* dequeueAvg() {
  if (isEmpty()) {
    return NULL;
  }

  //Allocate temp node and check is succseful
  Temp *temp = (Temp*)malloc(sizeof(Temp));
  if (!temp) {
    return NULL;  // Handle malloc failure
  }

  //Initialize variables
  float sum = 0.0f;
  int count = 0;
  int first_pos = -1;
  int last_pos = -1;

  //While queue is not empty, dequeue data
  while (!isEmpty()) {
    Node *temp2 = dequeue();
    if (temp2) {
      //Store first position in temp
      if (count == 0) {
        first_pos = temp2->pos;  // Track first position
      }
      //Store last positions
      last_pos = temp2->pos;     // Track last position
      sum += temp2->range_data;  // Accumulate sum
      count++;
      free(temp2);
    }
  }

  //if nothing was dequeued
  if (count == 0) {
    free(temp);
    return NULL;
  }

  //Store data in temp struct
  temp->avg = sum / count; 
  temp->pos1 = first_pos;
  temp->pos2 = last_pos;

  return temp;
}