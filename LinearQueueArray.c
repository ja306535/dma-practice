#include <stdlib.h>
#include <stdio.h>
#define MAX 5
#define EMPTY -9999

typedef struct queue {
    int queue_array[MAX];
    int front;
    int rear;
} queue;

void enqueue(queue *q, int item) { // Adding item to the rear of the queue
    if (q->rear == MAX) { // If the rear of the queue is at the same index of the last index of the array, the queue is full
        printf("Queue is full\n");
        return;
    } else { // If the queue is not full
        q->queue_array[q->rear] = item; // Add item to the rear
        (q->rear)++; // Move the rear one step forward
    }
}

int dequeue(queue *q) { // Removing item from the front of the queue
    if (q->front == q->rear) { // If the front equals the rear, the queue is empty
        printf("QUEUE EMPTY\n");
        return EMPTY;
    } else {
        int frontItem = q->queue_array[q->front];
        (q->front)++; // Move the front one step forward
        return frontItem;
    }
}

void displayQueue(queue *q) { // Display the elements of the queue
    if (q->front == q->rear) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue elements: ");
        for (int i = q->front; i < q->rear; i++) {
            printf("%d ", q->queue_array[i]);
        }
        printf("\n");
    }
}

int main() {
    // Allocate space for our queue and initialize it
    queue *MyQueuePtr = malloc(sizeof(queue));
    MyQueuePtr->front = 0;
    MyQueuePtr->rear = 0;

    int choice;
    int data;

    while (1) {
        printf("\n1. Insert element to queue\n");
        printf("2. Delete element from queue\n");
        printf("3. Display all elements of queue\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nWhat data you want to put in the queue?: ");
                scanf("%d", &data);
                enqueue(MyQueuePtr, data);
                displayQueue(MyQueuePtr);
                break;
            case 2:
                data = dequeue(MyQueuePtr);
                if (data != EMPTY) {
                    printf("\n%d deleted from queue\n", data);
                    displayQueue(MyQueuePtr);
                } else {
                    printf("Empty queue\n");
                }
                break;
            case 3:
                displayQueue(MyQueuePtr);
                break;
            case 4:
                exit(0);
            default:
                printf("Wrong choice\n");
        }
    }

    return 0;
}