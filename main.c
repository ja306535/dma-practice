#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 12


typedef struct customer {
    char name[15];
    int numTickets;
    int lineNum;
    int lineTime;
} customer;

typedef struct node {
    customer *c;
    struct node *next;
} node;

typedef struct queue {
    node *front;
    node *back;
} queue;

node *createCustomer(int lineTime, int lineNum, char *name, int numTickets) {
    node *temp = malloc(sizeof(node)); //create a node to store customer information
    temp->c = malloc(sizeof(customer)); //create space in the node to store a customer
    strcpy(temp->c->name, name); //store the name
    temp->c->numTickets = numTickets; //store the number of tickets
    temp->c->lineNum = lineNum; //store the line number
    temp->c->lineTime = lineTime; //store the line time
    temp->next = NULL; //set the next pointer to NULL
    return temp; //return the node
}

void init(queue *qPtr) {
    //if both are NULL that means the queue is empty
    qPtr->front = NULL;
    qPtr->back = NULL;
}

int empty(queue *qPtr) {
    return qPtr->front == NULL;
}

node *enqueue(queue* qPtr, node *n) { //enqueue adds to the back of the queue

    if(empty(qPtr)){ //if the queue is empty
    qPtr->front=n; //the front is pointing to temp (new item)
    qPtr->back=n; //the back is pointing to temp (new item)
    return n; //return 1 indicating it was successful

    } //if the queue is not empty 
    qPtr->back->next=n; //point the original back of the queue to the new item temp
    qPtr->back=n; //make temp the new back

    return n; //return 1 indicating it was sucessful
}

node *dequeue(queue* qPtr) { 
    if(empty(qPtr)){ 
        return NULL; // Return NULL if queue is empty
    }
    else{ 
        node *temp = qPtr->front; // Save the front node
        node *returnNode = temp; // Node to return
        
        qPtr->front = qPtr->front->next; // Move front pointer
        
        // If queue becomes empty after removing the node
        if(qPtr->front == NULL){ 
            qPtr->back = NULL; 
        }
        
        //remove the node from the queue
        returnNode->next = NULL;
        
        return returnNode; // Return the node
    }
}

node *peek(queue* qPtr) {
    if(qPtr->front != NULL){
        return qPtr->front; // Return the entire front node
    }
    else{
        return NULL; // Return NULL if queue is empty
    }
}


int main() {
    int numTestCases, numCustomers, lineTime, lineNum, numTickets;
    char name[25];
    queue lines[MAX];  
    int cashierTime=0;
    //scan the test cases
    scanf("%d",&numTestCases);
   //for each test case scan the number of customers
    for (int i=0;i<numTestCases;i++){
        scanf("%d",&numCustomers);
        //set queues to NULL
        for (int j=0;j<MAX;j++){
            init(&lines[j]);
        } //scan each customer and but them into the respective line 
            for(int k=0;k<numCustomers;k++){
                scanf("%d %d %s %d",&lineTime,&lineNum,name,&numTickets);
                node *newCustomer=createCustomer(lineTime,lineNum,name,numTickets);
                enqueue(&lines[lineNum-1],newCustomer); 



            }


    }

    

    return 0;
}
    


