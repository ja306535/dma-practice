#include <stdio.h>
#include <stdlib.h>
// a node contains data and a pointer to the next node
typedef struct node{
int data; //data node stores
struct node *next; //pointer to the next node
}node;
//a stack has a top and a size 
typedef struct{
node *top;//pointer that will store the top of the node
int size; //size of the linked list
}stack;

//create a node
node *createNode(int value){
node *temp=malloc(sizeof(node)); //make space for the node
temp->data=value; //asign the data
temp->next=NULL; //set temp next to NULL 

return temp; //return the node
}
//initialize stack to be empty
void initStack(stack *s){
    s->top=-1; //set top to -1
    s->size=0; //size is 0
}
//push an item to the top of the stack (head)
void push(stack *s, int value){
    //Create a new node using createNode(value).
    node *newNode=createNode(value);
    //Set the new node’s next pointer to the current top.
    newNode->next=s->top;
   // Update s->top to point to the new node.
   s->top=newNode;
    //Increment the size
   s->size++;

} 
//pop an item from the top of the stack (head)
int pop(stack *s){

node *temp=s->top //save the current top node
int value=s->temp->data; //save the data of the node
s->top=s->top->next; //set top to the next node
free(temp); //free temp

return value; //return the value of the popped node 

}

//determine the value at the top of the stack
int peek(stack *s){
if(s->top==NULL) //if the list is empty 
return -1 //return -1
    return s->top->data; //else return the value
}
//check if the stack is empty
int isEmpty(stack *s){
if(s->size==0){ //its empty if the size is 0
    return 1; //return true
}
return 0; //else return false
}
//free the stack 
void freeStack(stack *s){
node *walker=s->top; //set a walker to the top 
while(walker!=NULL){ //while the walker is not NULL
node *temp=walker; //create a node to save the walker
walker=walker->next; //set the walker to the next position
free(temp); //free the temp node

}
s->top=NULL; //set top to NULL 
s->size=0; //set size to 0

}