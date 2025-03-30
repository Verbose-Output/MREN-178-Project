#include <stdlib.h>
#include <stdio.h>

#define SIZE 5

typedef enum {
  SUCCESS = 0,
  ERR = 1
} Status;

//Node Declaration
typedef struct node{
  float range_data;
  int pos;
} Node;

Node *Buffer[SIZE];

int front = -1;
int back = 0;

typedef struct temp{
  float avg;
  int pos1;
  int pos2;
} Temp;

bool isFull() {
  return ((back + 1) % SIZE) == (front % SIZE);
}

bool isEmpty(){
  return (front == -1 || front == back);
}

int enqueue(float reading, int pos) {
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


Temp* dequeueAvg() {
  if (isEmpty()) {
    return NULL;
  }

  Temp *temp = (Temp*)malloc(sizeof(Temp));
  if (!temp) {
    return NULL;  // Handle malloc failure
  }

  float sum = 0.0f;
  int count = 0;
  int first_pos = -1;
  int last_pos = -1;

  while (!isEmpty()) {
    Node *temp2 = dequeue();
    if (temp2) {
      if (count == 0) {
        first_pos = temp2->pos;  // Track first position
      }
      last_pos = temp2->pos;     // Track last position
      sum += temp2->range_data;  // Accumulate sum
      count++;
      free(temp2);
    }
  }

  if (count == 0) {
    free(temp);
    return NULL;
  }

  temp->avg = sum / count;  // Correct average calculation
  temp->pos1 = first_pos;
  temp->pos2 = last_pos;

  return temp;
}