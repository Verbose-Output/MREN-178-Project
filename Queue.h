#include <stdlib.h>
#include <stdio.h>

//Node Declaration 
typedef struct node{
  int range_data;
  struct node* next;
} Node;

Node *front = NULL;
Node *back = NULL;

void enqueue(int reading){
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->range_data = reading;
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

int dequeue(){
  if(front == back){
    int range_data = front->range_data;
    Node *temp = front;
    front = NULL;
    back = NULL;
    free(temp);
    return range_data;
  }
  else{
    int range_data = front->range_data;
    Node *temp = front;
    front = front->next;
    free(temp);
    return range_data;
  }
}

int dequeueAvg(){
  int sum = 0;
  for(int i = 0; i<5; i++){
    sum += dequeue();
  }
  return (sum/5);
}