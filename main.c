#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 12

typedef struct customer{
    char name[15];
    int numTickets;
    int lineNum;
    int lineTime;
}customer;

typedef struct node{
    customer *c;
    node *next;
}node;

typedef struct queue{
int queue_array[MAX];    
 node *front;
 node *back;

}queue;

node *createCustomer(int lineTime,int lineNum,char *name,int numTickets){
    node *temp=malloc(sizeof(node)); //create a node that contains information on a customer and a next pointer
    temp->c=malloc(sizeof(customer)); //create space in node to store customer information
    strcpy(temp->c->name,name); //copy name 
    temp->c->numTickets=numTickets; //copy number of tickets
    temp->c->lineNum=lineNum; //copy line number
    temp->c->lineTime=lineTime; //copy line time
    temp->next=NULL; //set next to NULL

   return temp; //return the node
}

void init(queue* qPtr) {
qPtr->front=NULL; //if front is NULL
qPtr->back=NULL; //if back is NULL
//that means the queue is empty


}

int enqueue(queue* qPtr, node *n) { //enqueue adds to the back of the queue
node *temp=malloc(sizeof(node)); //create a node for the item 
if(temp){ //if malloc is sucessful
temp->data=n; //store item into temp
temp->next=NULL; //set temp next to NULL

if(empty(qPtr)){ //if the queue is empty
qPtr->front=temp; //the front is pointing to temp (new item)
qPtr->back=temp; //the back is pointing to temp (new item)
return 1; //return 1 indicating it was successful

}//if the queue is not empty 
qPtr->back->next=temp; //point the original back of the queue to the new item temp
qPtr->back=temp; //make temp the new back

return 1; //return 1 indicating it was sucessful
}

// No change to the queue was made because we couldn't find space for our
// new enqueue.
else{
    return 0;
}

}


int dequeue(queue* qPtr) { //removes from the front 
    
    if(empty(qPtr)){ //if the queue is empty 
        return EMPTY; //return -1
    }
    else{ //if the queue is not empty 
        int saveVal=qPtr->front->data; //save the value of the front 
        node *temp=qPtr->front; //create a temp variable to store the front 
        qPtr->front=qPtr->front->next; //make front the next spot
        free(temp); //free the temp variable 

        if(empty(qPtr)){ //if after removing the front the queue is empty that means there was only 1 item in the queue to start
            qPtr->back=NULL; //set back to NULL so front and back is NULL
        }
        return saveVal; //return the value that was removed

    }
    
    
}

    int peek(queue* qPtr) {
    if(qPtr->front !=NULL){
        return qPtr->front->data;
    }
    else{
        return -1;
    }
}

int empty(queue* qPtr) {
    return qPtr->front==NULL;
}

int main(){
char name[21];
int numTickets;
int lineNum;
int lineTime;
node *head=NULL;



}