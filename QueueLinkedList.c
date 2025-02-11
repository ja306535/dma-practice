// Example of how to implement a queue with a linked list.
#include <stdio.h>
#include<stdlib.h>
#define EMPTY -1
// Stores one node of the linked list.
typedef struct node {
int data;
struct node* next;
}node;
// Stores our queue.
typedef struct queue {
struct node* front;
struct node* back;
}queue;

void init( queue* qPtr);
int enqueue( queue* qPtr, int val);
int dequeue( queue* qPtr);
int empty( queue* qPtr);
int front( queue* qPtr);
void displayQueue( queue* MyQueuePtr);


int main() {
// Allocate space for our queue and initialize it.
 queue* MyQueuePtr=malloc(sizeof(queue));
init(MyQueuePtr);
int choice;
int data;
int i;
while (1)
{
printf("\n1.Insert element to queue \n");
printf("2.Delete element from queue \n");
printf("3. Display all elements of queue \n");
printf("4.Quit \n");
printf("Enter your choice : ");
scanf("%d", &choice);
switch (choice)
{
case 1:
printf("\nWhat data you want to put in the queue?: ");
scanf("%d", &data);
enqueue(MyQueuePtr, data);
displayQueue(MyQueuePtr);
break;
case 2:
data = dequeue(MyQueuePtr);
if(data!=EMPTY)
{
printf("\n%d deleted from queue\n", data);
displayQueue(MyQueuePtr);
}
else
printf("Empty queue\n");
break;
case 3:
displayQueue(MyQueuePtr);
break;
case 4:
exit(1);
default:
printf("Wrong choice \n");
} /*End of switch*/
} /*End of while*/
return 0;
} /*End of main()*/
void displayQueue(queue* MyQueuePtr)
{
struct node *t = MyQueuePtr->front;
while(t)
{
printf("%d ", t->data);
t = t->next;
}
}
// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: The struct that qPtr points to will be set up to represent an
// empty queue.
void init(queue* qPtr) {
qPtr->front=NULL; //if front is NULL
qPtr->back=NULL; //if back is NULL
//that means the queue is empty


}
// Pre-condition: qPtr points to a valid struct queue and val is the value to
// enqueue into the queue pointed to by qPtr.
// Post-condition: If the operation is successful, 1 will be returned, otherwise
// no change will be made to the queue and 0 will be returned.

int enqueue(queue* qPtr, int item) { //enqueue adds to the back of the queue
node *temp=malloc(sizeof(node)); //create a node for the item 
if(temp){ //if malloc is sucessful
temp->data=item; //store item into temp
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
// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: If the queue pointed to by qPtr is non-empty, then the value
// at the front of the queue is deleted from the queue and
// returned. Otherwise, -1 is returned to signify that the queue
// was already empty when the dequeue was attempted.
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
// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: returns true iff the queue pointed to by pPtr is empty.
int empty(queue* qPtr) {
    return qPtr->front==NULL;
}
// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: if the queue pointed to by qPtr is non-empty, the value
// stored at the front of the queue is returned. Otherwise,
// -1 is returned to signify that this queue is empty.
int peek(queue* qPtr) {
    if(qPtr->front !=NULL){
        return qPtr->front->data;
    }
    else{
        return EMPTY;
    }
}

void processQueues(queue lines[], int numLines, int numCustomers) {
    int currentTime = 0; // tracks the global time
  //loop that iterates through every customer
    for (int i = 0; i < numCustomers; i++) {
        node *temp = NULL; //create a temp node to store customer
        int queueNum = -1; //tracker for customer
        int fewestTickets = 9999999; //fewest tickets
        
         //loop to check if customer arrived
        for (int i = 0; i < numLines; i++) {
            if (!empty(&lines[i])) {
                node *front = peek(&lines[i]); //checks first customer and stores in front
                if (front->c->arrivalTime <= currentTime) {
                    if (front->c->numTickets < fewestTickets) {
                        temp = front; //stores that customer into temp
                        queueNum = i; //saves poition
                        fewestTickets = front->c->numTickets; //save the number of tickets
                    }
                }
            }
        }

        // loop to pick the one with the earliest arrival if none have showed up yet
        if (temp == NULL) {
            int bestTime = 9999999; //tracker for earliest time
            for (int i = 0; i < numLines; i++) {
                if (!empty(&lines[i])) {
                    node *front = peek(&lines[i]);
                    if (front->c->arrivalTime < bestTime) {
                        temp = front; //store that customer into temp
                        queueNum = i; //save position
                        bestTime = front->c->arrivalTime; //saave the time
                    }
                }
            }
        }

        if (temp == NULL)
            return; // No more customers to process

        // dequeue and process the current customer
        customer *customer = dequeue(&lines[queueNum]);
          //if the current time is less than the customers arrival time update it
        if (currentTime < customer->arrivalTime) {
            currentTime = customer->arrivalTime;
        }
        // Calculate checkout time
        currentTime += (20 + 10 * customer->numTickets);
        printf("%s left the counter at time %d from line %d.\n", customer->name, currentTime, customer->lineNum);

        free(customer);
        
    }
}