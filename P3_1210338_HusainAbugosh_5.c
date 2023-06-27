// Husain Abugosh/ حسين ابوغوش / 1210338 / sec:5

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

///////// BST Structure and main function ///////

 typedef struct tnode{

    int id;                //<-- will held the id in it.
    char stdName[20];     //<-- will held the student name in it.
    char city[20];       //<-- will held the city(address) name in it.
    int classId;        //<-- will held the classId in it.
    char date[20];     //<-- will held the date in it.

    struct tnode *right;   //<-- pointer that point to left sub nodes(children nodes).
    struct tnode *left;   //<-- pointer that point to right sub nodes(children nodes).

 }tnode;

// function to create a node with attributes, O(1): 
 tnode* createTnode(int id, char *stdName, char *city, int classId, char *date){

     tnode* newNode = (tnode*)malloc(sizeof(tnode)); //<-- will search about a space in the memo
     if (newNode == NULL){
        printf("memory allocation failed");
        return NULL;
     }

    newNode->id = id;                      //<-- set id attribute to be the insert id from the user.
    strcpy(newNode->stdName, stdName);    //<-- set stdName attribute to be the insert stdName from the user.
    strcpy(newNode->city, city);         //<-- set city attribute to be the insert city from the user.
    newNode->classId = classId;         //<-- set classId attribute to be the insert classId from the user.
    strcpy(newNode->date, date);       //<-- set date attribute to be the insert date from the user.
    newNode->left = NULL;             //<-- set the lift pointer to null temprorey.
    newNode->right = NULL;           //<-- set the right pointer to null temprorey.

    return(newNode);
 }


//function to insert the data inside the node: O(1)
 tnode* insertTnode(tnode* node, int id, char* stdName, char* city, int classId, char* date){
    
    // if the root is null then we will create a tree :
    if(node == NULL){
        return createTnode(id, stdName, city, classId, date);
    }else{
        // if the node is not null then insert the data by resurion 
        // resurion will used to reach the leafs (most left or right node ) to insert the data:

        if(id < node->id){
        // if the data is less than the node->id -> insert into the left subtree:
            node->left = insertTnode(node->left,id, stdName, city, classId, date);
        }else{
        // if the data is bigger than the node->id -> insert into the right subtree:
             node->right = insertTnode(node->right,id, stdName, city, classId, date);
        }
    }

   return node;
 }

// this function will use to Traversal in pre-order form(visit_Root,left, Right) , O(N):
void Traversal(tnode* root){
    
    // base case :
    if(root == NULL) {
        return;  
    }

    // visit the root and print the data in the pre-order form:
    printf("\n");
    printf("ID: %d\n", root->id);
    printf("Student Name: %s\n", root->stdName);
    printf("City: %s\n", root->city);
    printf("Class ID: %d\n", root->classId);
    printf("Date: %s\n", root->date);
    Traversal(root->left);                  //<--  move to the most left node .
    Traversal(root->right);                //<-- move to the right.
    
}

/*this function used for searching about an element(node) in the tree by:
1- checking if the target is larger or less than the root id
2- keep moving to the most left or right till found it 
 */ 
tnode* find(tnode* root, int targetId){

    if(root ==  NULL || root->id == targetId){
        return root;
    }else if(targetId < root->id) {
        return find(root->left, targetId);
    }else{
        return find(root->right, targetId);
    }

}

//getParent Function:
tnode* getParent(tnode* root, tnode* targetNode){
    if (root == NULL || root == targetNode) {
        return NULL;
    }

    tnode* current = root;
    tnode* parent = NULL;

    while (current != NULL && current != targetNode) {
        if (targetNode->id < current->id) {
            parent = current;
            current = current->left;
        } else {
            parent = current;
            current = current->right;
        }
    }

    return parent;
}

// findPredecessor Funtion: Predecessor is maximum node in left subtree. O(logN)
tnode* findPredecessor(tnode* tNode){

    tnode* currenNode =  tNode->left;
    while (currenNode != NULL && currenNode->right != NULL){
       currenNode =  currenNode->right; //<--- reach the max right leaf.
    }
    return currenNode;
}


// Function to delete a node from the binary tree by the id 
tnode* deleteNode(tnode* root, int id) {

     if (root == NULL) {
        return root;
    }

    tnode* targetNode  = find(root, id);
    tnode* parent = getParent(root, targetNode);
  
    // Case 1: No child or only right child
    if (targetNode->left == NULL) {
        tnode* grandSon = targetNode->right;
        targetNode->right = NULL;
        if (parent == NULL) {
            root = grandSon;
        } else if (parent->left == targetNode) {
            parent->left = grandSon;
        } else {
            parent->right = grandSon;
        }
        free(targetNode);
        return grandSon;
    }
    // Case 2: Only left child
    else if (targetNode->right == NULL) {
        tnode* grandSon = targetNode->left;
        targetNode->left = NULL;
        if (parent == NULL) {
            root = grandSon;
        } else if (parent->left == targetNode) {
            parent->left = grandSon;
        } else {
            parent->right = grandSon;
        }
        free(targetNode);
        return grandSon;
    }
    // Case 3: Two children
    else {
        tnode* successor = findSuccessor(targetNode);
        targetNode->id = successor->id; // Copying only id, assuming id is a unique key
        strcpy(targetNode->stdName, successor->stdName); // Copying the student name
        strcpy(targetNode->city, successor->city); // Copying the city
        targetNode->classId = successor->classId; // Copying the class id
        strcpy(targetNode->date, successor->date); // Copying the date
        targetNode->right = deleteNode(targetNode->right, successor->id);
    }
    return root;
}

/// Linked list Structrue ///

typedef struct  Node{
    int data;              //<--  will store the data in the node.
    struct Node* next;    //<--  will store the address of the next node (points on the NEXT NODE thats why its data is struct node).
}Node;


// to create a Node(object of struct):
Node* create_node(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));

    // if there is no space in the memo:
    if(newNode == NULL){
      printf("Out of memory!\n");
    }else{
    // to insert the data and set up the pointers:
        newNode -> data = data;
        newNode -> next = NULL;
        return newNode;
    }
}


// to insert a data in the linked list:
void insert(Node** head, int data){

    Node* new_node = create_node(data);
    if (*head == NULL){
        *head = new_node;
    }else{
        Node* current_node = *head;
        while (current_node->next !=NULL){
           current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}





int main(){

    int choice;              //<-- will store the choice of the user.
    int exitFlag = 0;        //<-- if the user rise the flag(exitFlag = 1) th loop will stop and close the programe.
    int didRead = 0;         //<-- the user shoud first choice th first choice to can select the operation.

    //  this loop use for showing the menu:
    while (!exitFlag){

        printf("\n_______Menu_______\n\n");
        printf("1. Insert a student.\n");
        printf("2. Find a student by ID and update information.\n");
        printf("3. List all students in lexicographic order.\n");
        printf("4. Search for a city and list all students from that city in lexicographic order.\n");
        printf("5. List all students by their class in lexicographic order.\n");
        printf("6. Delete a student by ID.\n");
        printf("7. Save all students to file.\n");
        printf("8. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n");
                // insert student
                break;
            case 2:
                printf("\n");
                //find a student
                break;
            case 3:
                printf("\n");
                // List all students in lexicographic order
                break;
            case 4:
                printf("\n");
                // Search for a city and list all students from that city in lexicographic order
                break;
            case 5:
                printf("\n");
                // List all students by their class in lexicographic order.
                break;
            case 6:
                printf("\n");
                // Delete a student by ID.
                break;
            case 7:
               // Save all students to file.
                break;
            case 8:
                // exit:
                exitFlag = 1;
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    }
    return 1;
}






