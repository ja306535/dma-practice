/*
COP 3502C Assignment 2
This progrm is written by:Jalil Fountain
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 12 //max number of queues

/*
struct for each customer
each customer has:name,number of tickets, line number and arrival time
*/
typedef struct customer {
    char name[16];
    int numTickets;
    int lineNum;
    int arrivalTime;
} customer;

/*
struct for each customer node
each node contains a customer and a pointer to the next
*/
typedef struct node {
    customer *c;
    struct node *next;
} node;
/*
struct for the queue
queue contains a front and back tracker
*/
typedef struct queue {
    node *front;
    node *back;
} queue;


//this function will create a customer node  and store all of the customers information and return the node
node *createCustomer(int arrivalTime, int lineNum, char *name, int numTickets) {
    node *temp = malloc(sizeof(node)); //create a node to store customer information
    temp->c = malloc(sizeof(customer)); //create space in the node to store a customer
    strcpy(temp->c->name, name); //store the name
    temp->c->numTickets = numTickets; //store the number of tickets
    temp->c->lineNum = lineNum; //store the line number
    temp->c->arrivalTime = arrivalTime; //store the arrival time
    temp->next = NULL; //set the next pointer to NULL
    return temp; //return the node
}


//this function will set the queue to be empty
void init(queue *qPtr) {
    //if both are NULL that means the queue is empty
    qPtr->front = NULL;
    qPtr->back = NULL;
    
}

//this function returns true if the queue pointed by qptr is empty
int empty(queue *qPtr) {
    return qPtr->front == NULL;
}

//this function adds a customer to the back of the queue
node *enqueue(queue* qPtr, node *n) { //enqueue adds to the back of the queue

    if(empty(qPtr)){ //if the queue is empty
    qPtr->front=n; //the front is pointing to node 
    qPtr->back=n; //the back is pointing to node
    return n; 

    } //if the queue is not empty 
    qPtr->back->next=n; //point the original back of the queue to the new item n
    qPtr->back=n; //make n the new back

    return n; 
}
//this function removes a customer from the front returns the data for later usage and frees the memory for the node
customer *dequeue(queue *qPtr) {
    if (empty(qPtr)) {
        return NULL; // return NULL if the queue is empty
    } 
    else {
        node *temp = qPtr->front;  // save the front node
        customer *customerData = temp->c;  // get the customer data

        qPtr->front = qPtr->front->next;  // move front pointer

        // if the queue becomes empty after removing the node
        if (qPtr->front == NULL) {
            qPtr->back = NULL;
        }

        // free the node 
        free(temp);

        return customerData;  // return the customer data 
    }
}
//this functoin checks the front without removing the customer at the front
node *peek(queue* qPtr) {
    if(qPtr->front != NULL){
        return qPtr->front; // return the front node
    }
    else {
        return NULL; // return NULL if queue is empty
    }
}
//this functoin processes the queues 
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
                node *front = peek(&lines[i]); //checks first customer and stores in front ptr
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
                    node *front = peek(&lines[i]); //checks first customer and stores in front ptr
                    if (front->c->arrivalTime < bestTime) {
                        temp = front; //store that customer into temp
                        queueNum = i; //save position
                        bestTime = front->c->arrivalTime; //saave the time
                    }
                }
            }
        }

        if (temp == NULL)
            return; // no more customers to process

        // dequeue and process the current customer
        customer *customer = dequeue(&lines[queueNum]);
        //if the current time is less than the customers arrival time update it
        if (currentTime < customer->arrivalTime) {
            currentTime = customer->arrivalTime;
        }
        // calculate checkout time
        currentTime += (20 + 10 * customer->numTickets);
        printf("%s left the counter at time %d from line %d.\n", customer->name, currentTime, customer->lineNum);
        //free customer 
        free(customer);
        
    }
}

int main() {
    int numTestCases, numCustomers, arrivalTime, lineNum, numTickets; 
    char name[16]; 
    queue lines[MAX]; //array of 12 queues 

    scanf("%d", &numTestCases); //scan the test cases
    //loop to scan each customer for each test case
    for (int i = 0; i < numTestCases; i++) {
        scanf("%d", &numCustomers);
       //set queues to empty
        for (int j = 0; j < MAX; j++) {
            init(&lines[j]);
        }
        // loop to get each customer information
        for (int k = 0; k < numCustomers; k++) {
            scanf("%d %d %s %d", &arrivalTime, &lineNum, name, &numTickets);
            node *newCustomer = createCustomer(arrivalTime, lineNum, name, numTickets);
            enqueue(&lines[lineNum - 1], newCustomer); //add the customer to their queue
        }
        //call the process function 
        processQueues(lines, MAX,numCustomers);
        printf("======\n");
    }

    return 0;
}

