#include <stdlib.h>
#include <stdio.h>



typedef struct queue{

int *elements; //the array (use pointer so you can malloc and realloc)
int front; //starting point
int numElements; //number of elements
int queueSize; //size of the array

}queue;


void init(queue *qptr){
qPtr->elements=malloc(10*sizeof(int)); //creates the array that can hold ints 
qPtr->front=0; //front is set to 0
qPtr->numElements=0; //number of elements is set to 0
qPtr->queueSize=10; //size of the array is 10


}
int empty(queue *qPtr){
return qPtr->numElements==0;
}

int enqueue(queue *qPtr,int val){
//if number of elements are less then size
if(qPtr->numElements<qPtr->queueSize){
//store the value at the end of the queue using the formula
qPtr->elements[(qPtr->front+qPtr->numElements)%qPtr->queueSize]=val;
//update number of elements
(qPtr->numElements)++;

return 1;
}
else{ //meaning the queue is full
//realloc the array to add more space 
qPtr->elements=realloc(qPtr->elements,(qPtr->queueSize)*2*sizeof(int)); //the original pointer,what you want to increase,by how much and what type
//loop to add the values at the index before front to the back 
for(int i=0;i<=qPtr->front-1;i++){
qPtr->elements[queueSize+i]=qPtr->elements[i]; //copy the values stored at 0 to front -1 to their correct locations
}

//enqueue the new value 
qPtr->elements[i+qPtr->queueSize]=val;
//update number of elements
(qPtr->numElements)++;
//update size
(qPtr->queueSize)*=2; //after realloc the size has doubled


return 1;
}

}

int dequeue(queue *qPtr, int val){
//if the queue is empty
if(empty(qPtr)){
return 0;
}
//if the queue is not empty
else{
//save the front item    
int frontItem=qptr->elements[qptr->front];
//set front to the next index
qptr->front=(qPtr->front+1)%qPtr->queueSize;
//decrease number of elements by 1
qPtr->numElements--;
//return the item
return frontItem;


}

}