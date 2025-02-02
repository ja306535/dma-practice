#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node{
    int data;
    struct node* next;
}node;

node *create_node(int item){
    node *temp = malloc(sizeof(node)); // Make space for a node 
    temp->data = item; // Initialize the node data to the item
    temp->next = NULL; // Set node next to NULL 
    return temp; // Return the node
}

// This function takes an item and inserts it in the linked list pointed by root.
node* insert_front(node* root, int item)
{
    node *temp = create_node(item); //create the node
    //check if root is NULL meaning the list is empty
    if (root == NULL){
        root = temp;
        return root;
    }
    else{//if the list is not empty
        temp->next = root; //insert temp before the root
        root = temp; //temp becomes the new head
        return root; //return the list
    }
}

// This function takes an item and inserts it at the end of the linked list.
node* insert_end(node* root, int item)
{
    node *temp = create_node(item); //create node
    //check if the root is NULL meaning the list is empty
    if (root == NULL){
        root = temp;
        return root;
    }
    else{ //if the list is not empty
        node *walker = root; //create a walker pointer to traverse the list
        while (walker->next != NULL){ //while walker next does not equal NULL
            walker = walker->next; //traverse the list
        }
        walker->next = temp; //once you get to the spot before NULL insert temp into the next spot
        return root; //return the list
    }
}

node* insert_sorted(node* root,int item){

    node *temp=create_node(item);
    //if the list is empty or the first node's data is bigger than the item you want to insert
    if(root==NULL||root->data>item){

        temp->next=root;
        root=temp;
        
        return root;
    }
    else{

        node *walker=root;
        while(walker->next!=NULL&&walker->next->data<item){
            walker=walker->next;
        }
        temp->next=walker->next;
        walker->next=temp;

        return root;
    }
}  // <-- Missing bracket added here

node *delete_node(node *root,int item){
    node *temp=create_node(item);
    if(root==NULL||root->data==item){
        node *t=root;
        root=root->next;
        free(t);
        return root;
    }
    else 
    {
        node *walker=root;
        while(walker->next!=NULL&&walker->next->data!=item){
            walker=walker->next;
        }
        if(walker->next==NULL){
            return root;
        }
        else{
            node *w=walker->next;
            walker->next=walker->next->next;
            free(w);
        }
    
    }
    return root;
}

// Display the linked list
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