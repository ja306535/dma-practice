#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 12


typedef struct customer {
    char name[15];
    int numTickets;
    int lineNum;
    int arrivalTime;
} customer;

typedef struct node {
    customer *c;
    struct node *next;
} node;

typedef struct queue {
    node *front;
    node *back;
    int size;
} queue;

node *createCustomer(int arrivalTime, int lineNum, char *name, int numTickets) {
    node *temp = malloc(sizeof(node)); //create a node to store customer information
    temp->c = malloc(sizeof(customer)); //create space in the node to store a customer
    strcpy(temp->c->name, name); //store the name
    temp->c->numTickets = numTickets; //store the number of tickets
    temp->c->lineNum = lineNum; //store the line number
    temp->c->arrivalTime = arrivalTime; //store the line time
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

void processQueues(queue lines[], int numLines, int total_customers) {
    int current_time = 0; // Tracks the global time

    for (int processed = 0; processed < total_customers; processed++) {
        node *bestNode = NULL;
        int bestQueue = -1;
        int bestTime=9999999;
        int fewestTickets=9999999;

        // Step 1: Find the candidate queue
        for (int i = 0; i < numLines; i++) {
            if (!empty(&lines[i])) {
                node *front = peek(&lines[i]);  // Look at the front customer

                if (front->c->arrivalTime <= current_time) {
                    // Among customers who arrived before current time, find the one with fewest tickets
                    if (front->c->numTickets < fewestTickets) {
                        bestNode = front;
                        bestQueue = i;
                        fewestTickets = front->c->numTickets;
                    }
                } else if (bestNode == NULL) {
                    // If no one is available before current_time, pick the earliest arrival
                    if (front->c->arrivalTime < bestTime) {
                        bestNode = front;
                        bestQueue = i;
                        bestTime = front->c->arrivalTime;
                    }
                }
            }
        }

        if (bestNode == NULL) return; // No more customers to process

        // Step 2: Dequeue and process the selected customer
        node *selectedNode = dequeue(&lines[bestQueue]);
        customer *cust = selectedNode->c;

        if (current_time < cust->arrivalTime) {
            current_time = cust->arrivalTime;
        }

        // Calculate checkout time
        current_time += (20 + 10 * cust->numTickets);
        printf("%s left the counter at time %d from line %d.\n", cust->name, current_time, cust->lineNum);

        free(cust);
        free(selectedNode);
    }
}


int main() {
    int numTestCases, numCustomers, arrivalTime, lineNum, numTickets;
    char name[15];
    queue lines[MAX];

    scanf("%d", &numTestCases);

    for (int i = 0; i < numTestCases; i++) {
        scanf("%d", &numCustomers);

        for (int j = 0; j < MAX; j++) {
            init(&lines[j]);
        }

        for (int k = 0; k < numCustomers; k++) {
            scanf("%d %d %s %d", &arrivalTime, &lineNum, name, &numTickets);
            node *newCustomer = createCustomer(arrivalTime, lineNum, name, numTickets);
            enqueue(&lines[lineNum - 1], newCustomer);
        }

        processQueues(lines, MAX,numCustomers);
        printf("======\n");
    }

    return 0;
}

