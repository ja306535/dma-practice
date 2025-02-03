#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{

    int data;
    struct node *next,*prev;
}node;

node *insert_front(node* head,int item){

node *temp=malloc(sizeof(node)); //create a node
temp->data=item; //fill nodes data with item
temp->prev=NULL; //set previous to NULL since you are inserting it into the front
temp->next=head; //set temp next to head

if(head){ //if head doesnt equal NULL (meaning there is already a head)
    head->prev=temp; //set the heads previous to temp 

}
head=temp; //set head to temp

return head; //return the list

}

node *insert_end(node *head,int item){

    node *temp=malloc(sizeof(node));
    temp->data=item;
    temp->next=NULL;

    if(head==NULL){
        head=temp;
        temp->prev=NULL;
    
    }
    else{
    node *walker=head;

    while(walker->next!=NULL){
    walker=walker->next;
    }

    walker->next=temp;
    temp->prev=walker;

    }
    return head;
}


node *insert_sorted(node *head, int item) {
    node *temp = malloc(sizeof(node));
    temp->data = item;
    temp->next = NULL;
    temp->prev = NULL;

    if (head == NULL || head->data > item) {
        temp->next = head;
        if (head != NULL) {
            head->prev = temp;
        }
        head = temp;
    } else {
        node *walker = head;
        while (walker->next != NULL && walker->next->data < item) {
            walker = walker->next;
        }

        temp->next = walker->next;
        if (walker->next != NULL) {
            walker->next->prev = temp;
        }
        walker->next = temp;
        temp->prev = walker;
    }
    return head;
}
node *delete_node(node *head, int item) {
    if (head == NULL) {
        return head;
    }

    node *walker = head;

    // Find the node to delete
    while (walker != NULL && walker->data != item) {
        walker = walker->next;
    }

    // If item is not found, return original head
    if (walker == NULL) {
        return head;
    }

    // If deleting the head node
    if (walker == head) {
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
    } else {
        walker->prev->next = walker->next;
        if (walker->next != NULL) {
            walker->next->prev = walker->prev;
        }
    }

    free(walker);
    return head;
}
void display(node* t)
{
    printf("\nPrinting your linked list.......");
    while (t != NULL)
    {
        printf("%d ", t->data);
        t = t->next;
    }
    printf("\n");
}

int main()
{
    node *root = NULL;  // Declare root appropriately
    int ch, ele, del;
    
    while (1)
    {
        printf("\nMenu: 1. insert at the front, 2. insert at the end, 3. Delete, 4. sorted insert, 5. exit: ");
        scanf("%d", &ch);
        
        if (ch == 5)
        {
            printf("\nGOOD BYE>>>>\n");
            break;
        }
        
        if (ch == 1)
        {
            printf("\nEnter data (an integer): ");
            scanf("%d", &ele);
            root = insert_front(root, ele);  // Call the function appropriately
            display(root);
        }
        
        if (ch == 2)
        {
            printf("\nEnter information (an integer): ");
            scanf("%d", &ele);
            root = insert_end(root, ele);  // Call the function appropriately
            display(root);
        }
        
        if (ch == 3)
        {
            printf("\nEnter info which you want to DELETE: ");
            scanf("%d", &del);
            root=delete_node(root,del);
            display(root);
        }
        
        if (ch == 4)
        {
            printf("\nEnter data (an integer): ");
            scanf("%d", &ele);
           root=insert_sorted(root,ele);
            display(root);
        }
    }
    return 0;
}