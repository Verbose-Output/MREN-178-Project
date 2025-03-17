#include <stdlib.h>
#include <stdio.h>


//Node Declaration 
typedef struct node{
  int range_data;
  int pos;
  struct node* next;
} Node;

typedef struct temp{
  int avg;
  int pos1;
  int pos2;
} Temp;

Node *front = NULL;
Node *back = NULL;

void enqueue(int reading, int pos){
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->range_data = reading;
  temp->pos = pos;
  if(front == NULL){
    front = temp;
    temp->next = NULL;
    back = temp;
  }
  else{
    back->next = temp;
    temp->next = NULL;
    back = temp;
  }
}

Node* dequeue(){
  if(front == back){
    int range_data = front->range_data;
    Node *temp = front;
    front = NULL;
    back = NULL;
    return temp;
  }
  else{
    int range_data = front->range_data;
    Node *temp = front;
    front = front->next;
    return temp;
  }
}

Temp* dequeueAvg(){
  Temp *temp = (Temp*)malloc(sizeof(Temp));
  for(int i = 0; i < 5; i++){
    Node *temp2 = dequeue();
    if(i == 0){
      temp->pos1 = temp2->pos;
    }
    if(i == 4){
      temp->pos2 = temp2->pos;
    }
    temp->avg += temp2->range_data;
    free(temp2);
  }
  temp->avg = ((temp->avg)/5);
  return temp;
}