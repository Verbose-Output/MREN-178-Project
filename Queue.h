#include <stdlib.h>

//Node Declaration 
typdedef struct node{
  int range_data;
  *struct node next;
} node;

node *front = NULL;
node *back = NULL;

void enqueue(int reading){
  node *temp = malloc(sizeof(node));
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
    node *temp = front;
    front = NULL;
    back = NULL;
    free(temp);
    return range_data;
  }
  else{
    int range_data = front->range_data;
    node *temp = front;
    front = front->next;
    free(temp);
    return range_data;
  }
}
