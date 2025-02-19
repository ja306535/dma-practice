//Stack implementation using array skeleton code
#include <stdio.h>
// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.
#define SIZE 6
#define EMPTY -1
#define FULL 0

typedef struct stack {
int items[SIZE]; //an array used for the stack
int top; //top variable
}stack;

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, int value);
int empty(struct stack* stackPtr);
int pop(struct stack* stackPtr);
int peek(struct stack* stackPtr);
void display(struct stack* stackPtr);


int main() {
int i;
//declare a stack
stack st1;
// Set up the stack and push a couple items, then pop one.
initialize(&st1); //call this function appropriately
stack st2;
initialize(&st2);
int ele;
int ch;
while(1)
{
printf("\nMenu:\n 1: Stack 1 push\n 3: Stack 1 Pop\n \n 5: Stack 1 display\
n 7: Exit\nEnter your choice: ");
scanf("%d",&ch);
if(ch==7)
{
printf("<<EXIT>>");
break;
}
else if (ch==1)
{
printf("Enter an element to PUSH in the stack1: ");
scanf("%d",&ele);
push(&stack1, ele);
display(&stack1);
}
else if (ch==2)
{
printf("Enter an element to PUSH in the stack2: ");
scanf("%d",&ele);
push(&stack2, ele);
display(&stack2);
}
else if (ch==3)
{
ele = pop(&stack1);
if(ele!=0 )
{
printf(" ITEM POPPED from Stack 1: %d ",ele);
display(&stack1);
}
}
else if (ch==4)
{
ele = pop(&stack2);
if(ele!=0 )
{
printf(" ITEM POPPED from Stack 2: %d ",ele);
display(&stack2);
}
}
else if(ch==5)
{
display(&stack1);
}
else if(ch==6)
{
display(&stack2);
}
}
return 0;
}

void initialize(struct stack* stackPtr) {
stackPtr->top = -1;
}
// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int push(struct stack* stackPtr, int value) {
    if(full(stackPtr)){

        printf("Stack overflow\n");
        return FULL;
    }
    
    //put the value on the top of the stack
    stackPtr->items[stackPtr->top+1]=value;
   //update top
    stackPtr->top++;
    return 1;

}
// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack* stackPtr) {
return (stackPtr->top == SIZE - 1);
}

// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack* stackPtr) {
return (stackPtr->top == -1);
}
// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
int pop(struct stack* stackPtr) {
   if(empty(stackPtr)){

    printf("Stack underflow\n");
    return EMPTY;
   }
   
    //save the top value (because its being returned)
    int topItem=stackPtr->items[stackPtr->top];
    //deincrement top
    stackPtr->top--;
    return topItem;
}
// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
int peek(struct stack* stackPtr) {
// Take care of the empty case.
if (empty(stackPtr))
return EMPTY;
// Return the desired item.
return stackPtr->items[stackPtr->top];
}

void display(struct stack* stackPtr) {
printf("\nPrinting the Current stack...");
for(int i=0; i<=stackPtr->top; i++)
printf("%d ", stackPtr->items[i]);
}