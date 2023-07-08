// Husain Abugosh/ حسين ابوغوش / 1210338 / sec:5

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


/// Linked list Structrue ///

typedef struct  Node{
    char stdName[20];     //<-- will held the student name in it.
    int classId;         //<-- will held the classId in it.
     int id;             //<-- will held the id in it.
    struct Node* next;    //<--  will store the address of the next node (points on the NEXT NODE thats why its id is struct node).
}Node;


// to create a Node(object of struct):
Node* create_node(char* name, int classId, int id){
    Node* newNode = (Node*)malloc(sizeof(Node));

    // if there is no space in the memo:
    if(newNode == NULL){
      printf("Out of memory!\n");
      return NULL;
    }else{
    // to insert the id and set up the pointers:
        strcpy(newNode->stdName, name); 
        newNode->classId = classId;    
        newNode->id = id;
        newNode -> next = NULL;
        return newNode;
    }
}


// to insert a id in the linked list:
void insert(Node** head, char* name, int classId,int id){

    Node* new_node = create_node(name, classId, id);
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

// to dispaly the list :
void display(Node* head){

    // while is the current_node is not null then print the id that store in this node.
    Node*  current_node = head;
    while (current_node != NULL){
        printf("Student Name: %s \t id:%d \t ClassId:%d \n", current_node->stdName,current_node->id,current_node->classId);
        current_node = current_node->next;
    }
}

// to delete all the list:
void deleteList(Node** head) {
    
    Node* current_node = *head;
    Node* next_node;

    while (current_node != NULL) {
        next_node = current_node->next; // Save the next node before deleting the current node
        free(current_node); // Free the memory allocated for the current node
        current_node = next_node; // Move to the next node in the list
    }

    *head = NULL; // Set the head pointer to NULL, indicating the list is empty
}

// to Checks if the list is empty:
int isEmpty(Node* head){
    return head == NULL;
}

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


//function to insert the id inside the node: O(1)
 tnode* insertTnode(tnode* node, int id, char* stdName, char* city, int classId, char* date){
    
    // if the root is null then we will create a tree :
    if(node == NULL){
        return createTnode(id, stdName, city, classId, date);
    }else{
        // if the node is not null then insert the id by resurion 
        // resurion will used to reach the leafs (most left or right node ) to insert the id:

        if(id < node->id){
        // if the id is less than the node->id -> insert into the left subtree:
            node->left = insertTnode(node->left,id, stdName, city, classId, date);
        }else{
        // if the id is bigger than the node->id -> insert into the right subtree:
             node->right = insertTnode(node->right,id, stdName, city, classId, date);
        }
    }

   return node;
 }

// this function will use to Traversal in pre-order form(visit_Root,left, Right) , O(N):
void Traversal(tnode* root, Node** head){
    
    // base case :
    if(root == NULL) {
        return;  
    }
    
    // copy the tree node to be a list node:
    insert(head,root->stdName, root->classId, root->id);

    Traversal(root->left,head);                  //<--  move to the most left node .
    Traversal(root->right,head);                //<-- move to the right.
    
}

/*this function used for searching about an element(node) in the tree by:
1- checking if the target is larger or less than the root id
2- keep moving to the most left or right till found it 
*if the target ID is not found in the BST -> the function will return NULL*
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

tnode* findSuccessor(tnode* tNode){

    tnode* currenNode =  tNode->right;
    while (currenNode != NULL && currenNode->left != NULL){
         currenNode = currenNode->left; // Move to the maximum left leaf. //<--- reach the max Left leaf.
    }

    return currenNode;
}

//getParent Function:
tnode* getParent(tnode* root, tnode* targetNode){

    if (root == NULL || root == targetNode) {
            return NULL;
        }

        tnode* current = root;
        tnode* parent = NULL;

        while (current != NULL && current != targetNode) {
            if (targetNode->id< current->id) {
                parent = current;
                current = current->left;
            } else {
                parent = current;
                current = current->right;
            }
        }

        return parent;
}

// Function to delete a node from the binary tree
tnode* deleteNode( tnode* root, int id) {

     if (root == NULL) {
        return root;
    }

    tnode* targetNode  = find(root,id);
    tnode* parent = getParent(root,targetNode);
  
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
        targetNode->id = successor->id;
        strcpy(targetNode->stdName, successor->stdName);
        strcpy(targetNode->city, successor->city);
        targetNode->classId = successor->classId;
        strcpy(targetNode->date, successor->date);

        targetNode->right = deleteNode(targetNode->right, successor->id);
    }
        return root;
}



/// Functions ///

// like the Traversal:
void saveToFile(tnode* node, FILE* file) {

    if (node == NULL) {
        return;
    }
    saveToFile(node->left, file);
    fprintf(file, "%d %s %s %d %s\n", node->id, node->stdName, node->city, node->classId, node->date);
    saveToFile(node->right, file);
}


void FileOperations(tnode** tNode,int op){

    // assume the file data will be in this form: (Id StudentName City ClassId Date).

    switch (op){
    case 1 : {

        // read data from the file:
        FILE *file = fopen("studentsData.txt", "r"); //<-- will open the wanted file & put it on the reading mode.

        // this if-statment used to check if there any error with openning the file:
        if (file == NULL){
            printf("*ERROR: File couldn't be opened*\n");
        }

        printf("\nReading the File...\n ");
        // varibales will hold the data in it:
        int id;
        char stdName[20];
        char city[20];
        int classId;
        char date[20];

        /* the loop continues as long as fscanf successfully reads and assigns
           values to all five variables (which is when it returns 5): */
        while (fscanf(file, "%d %s %s %d %s\n", &id, stdName, city, &classId, date) == 5) {
        
            // cheack if there any id like the new one(the id must be unique):
            if(find(*tNode, id) == NULL){
                // insert the new student to the BST:
                *tNode = insertTnode(*tNode,id,stdName,city,classId,date);
                printf("Done\n");
            }else{
                printf("there is the same ID, please Try again");
            }
        }

        fclose(file); //<-- close the file.
        break;

    }

    case 2 : {
       //save id to the file:
        FILE* file = fopen("studentsData.txt", "w"); //<-- open the file in write mode

        if (file == NULL) {
            printf("Error opening file!\n");
            return;
        }

        saveToFile(*tNode,file); //<-- write the tree to file.
        fclose(file);
        break;
     }
    }
}



// function will take the BST then get the id from the user then isert it to tree.
void insertaion(tnode** tNode){

    //varibales:
    int id;               
    char stdName[20];    
    char city[20];   
    int classId;       
    char date[20];     

    printf("Please enter student id:\n");
    printf("Student ID: ");
    scanf("%d", &id);
    printf("Student Name: ");
    scanf("%s", stdName); 
    printf("Home Address: ");
    scanf("%s", city); 
    printf("Class ID: ");
    scanf("%d", &classId);
    printf("Date Enrollment (format: dd-mm-yyyy): ");
    scanf("%s", date);
    
    // cheack if there any id like the new one(the id must be unique):
    if(find(*tNode, id) == NULL){
        // insert the new student to the BST:
        *tNode = insertTnode(*tNode,id,stdName,city,classId,date);
        printf("Done\n");
    }else{
        printf("there is the same ID, please Try again");
    }
}


void updateId(tnode** tNode){

    int id; 
    printf("Please enter student ID you want to update: ");
    scanf("%d", &id);

    tnode* studentToUpdate = find(*tNode, id);  //<-- will save the target root(base on ID).

    //check if student with wanted ID exists:
    if(studentToUpdate == NULL){
        printf("No student found with this ID\n");
        return;
    }

    int exitFlag = 0;
    while (!exitFlag){

        printf("\n_______Update Menu_______\n\n");
        printf("1. View Current Student id.\n");
        printf("2. Update Student Name.\n");
        printf("3. Update Student City.\n");
        printf("4. Update Student Class ID.\n");
        printf("5. Update Student Enrollment Date.\n");
        printf("6. Exit.\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        char newInfo[20];    //<-- will save the new string info.
        int newClassId;     //<-- will save the new class id.
        
        switch(choice){
            case 1:
                //print the current student id:
                printf("\nCurrent Student id: \n");
                printf("ID: %d\n", studentToUpdate->id);
                printf("Student Name: %s\n", studentToUpdate->stdName);
                printf("City: %s\n", studentToUpdate->city);
                printf("Class ID: %d\n", studentToUpdate->classId);
                printf("Date: %s\n", studentToUpdate->date);
                break;
            case 2:
                //update student name:
                printf("Enter new name: ");
                scanf("%s", newInfo);
                strcpy(studentToUpdate->stdName, newInfo);
                printf("Updated!\n");
                break;
            case 3:
                //update student city:
                printf("Enter new city: ");
                scanf("%s", newInfo);
                strcpy(studentToUpdate->city, newInfo);
                printf("Updated!\n");
                break;
            case 4:
                //update student class ID:
                printf("Enter new class ID: ");
                scanf("%d", &newClassId);
                studentToUpdate->classId = newClassId;
                printf("Updated!\n");
                break;
            case 5:
                // update student enrollment date:
                printf("Enter new enrollment date (format: dd-mm-yyyy): ");
                scanf("%s", newInfo);
                strcpy(studentToUpdate->city, newInfo);
                printf("Updated!\n");
                break;
            case 6:
                // exit from the update menu:
                printf("Returning to main menu...\n");
                exitFlag = 1;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    }
}


void CityTraversal(tnode* root, Node** head,char* city){
    
    // base case :
    if(root == NULL) {
        return;  
    }
     
    // we will insert the student name ONLY if he live in the SELECTED city.
    if(strcmp(root->city, city) == 0){
      insert(head,root->stdName, root->classId, root->id);
    }
    CityTraversal(root->left,head,city);                  //<--  move to the most left node .
    CityTraversal(root->right,head,city);                //<-- move to the right.
     
}

// this function will splits the given linked list into two halves:
void frontBackSplit(Node* source, Node** frontRef,Node** backRef ){

    Node* p1;
    Node* p2;
    p2 = source;
    p1 = source->next;
  
  // Move 'p1' two nodes, and 'p2' one node:
    while (p1 != NULL){
        p1 = p1->next;
        if (p1 != NULL){
            p2 = p2->next;
            p1 = p1->next;
        }
    }

    // 'p2' is before the midpoint in the list -> so split it in two at that point.
    *frontRef = source;
    *backRef = p2->next;
    p2->next = NULL;
}

// function merges two sorted linked lists into one(by taking 2 likned list nodes), O(nLogn): 
Node* sortedMerge( Node* a,  Node* b, int op){

    Node* result = NULL;
   
    // Base cases: if first list is empty, return second list:
    if (a == NULL){
         return(b);
    }else if (b==NULL){
    // if second list is empty, return first list:
        return(a);
    }

   
    switch (op) {
    case 1:
        // compare base on the  students names:
        if (strcmp(a->stdName,b->stdName) <= 0){
            // if student name in  node 'a' is lexicographically smaller or equal.
            result = a;  
            result->next = sortedMerge(a->next, b ,op);  //<-- merge the remaining.
        }else{
            // if student name in  node 'b' is lexicographically smaller:
            result = b;
            result->next = sortedMerge(a, b->next,op);  //<-- merge the remaining.
        }
        break;
    case 2:
        // compare base on the students classid:
        if (a->classId <= b->classId){ 
            result = a;
            result->next = sortedMerge(a->next, b, op);
        }else{
            result = b;
            result->next = sortedMerge(a, b->next, op);
        }

        break;
    }

    return(result);  //<-- return the new head.
}

// MergeSort function that sorts the linked list(op=1-> name, op=2 -> classId):
void mergeSort( Node** headRef, int op){


    struct Node* head = *headRef;
    struct Node* a;
    struct Node* b;
  
    //base case: length of the linkedList is 0 or 1
    if ((head == NULL) || (head->next == NULL)){
        return;
    }

    // split head into 'a' and 'b' sublists:
    frontBackSplit(head, &a, &b); 
    // sort the subtitiles:
    mergeSort(&a,op);
    mergeSort(&b,op);

    *headRef = sortedMerge(a, b ,op);
}


// classIdList: will list all the student in the clasess:
void classIdList(Node* list){

    Node* temp = list;
    Node* subList = NULL; //<-- a list will contain all the students name in the same class. 

    mergeSort(&temp,2);  //<-- to sort the list that contain all the tnode (sortrd by clasId).

    while (temp != NULL){

        // insert the current node to subList.
        insert(&subList,temp->stdName,temp->classId,temp->id);

        // check if temp->next is NULL to avoid zsh.
        if (temp->next == NULL || temp->classId != temp->next->classId){
            mergeSort(&subList,1);                  //<-- sort the subList.
            printf("\nClassId_%d: \n",subList->classId);   //<-- print the classId.
            display(subList);                     //<-- display sorted student names in the smae class.
            deleteList(&subList);                //<-- delete the list.
            subList = NULL;                     //<-- reset the subList after deleting it.
        }

        temp = temp->next;                   //<-- move to the next node.
    } 
}


int main(){

    int choice;              //<-- will store the choice of the user.
    int exitFlag = 0;        //<-- if the user rise the flag(exitFlag = 1) th loop will stop and close the programe.
    int didRead = 0;         //<-- the user shoud first choice th first choice to can select the operation.

    tnode* root = NULL;    //<-- the tree that will contain the Students id.
    Node* head  = NULL;   //<-- linked list will contain all the students name.
    Node* CityList  = NULL;   //<-- linked list will contain stdNames of specific city.

    FileOperations(&root,1);
    

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
                // insert student:
                insertaion(&root);
                break;
            case 2:
                printf("\n");
                updateId(&root);
                break;
            case 3:
                printf("\n");
                // List all students in lexicographic order:
                Traversal(root,&head);  //<-- to convert from tree node to list node.
                mergeSort(&head,1);      //<-- to sort the list in lexicographic order.
                display(head);        //<-- display the list.
                deleteList(&head);    //<-- delete the list and make it clear.
                break;
            case 4:
                printf("\n");
                // Search for a city and list all students from that city in lexicographic order:
                char city[20];
                printf("Please, enter the city name: ");
                scanf("%s", city);
                CityTraversal(root,&CityList,city);  //<-- will return the stdNames in the wanted city.
                if(isEmpty(CityList)){
                    printf("\n*There is no students in this city.*\n");
                    break;
                }
                mergeSort(&CityList,1);               //<-- to sort the list in lexicographic order.
                display(CityList);                 //<-- display the list.
                deleteList(&CityList);             //<-- delete the list and make it clear.
                break;
            case 5:
                printf("\n");
                // List all students by their classId in lexicographic order:6
                Traversal(root,&head);  //<-- to convert from tree node to list node.
                classIdList(head);     //<-- will lest the student names
                break;
            case 6:
                printf("\n");
                // Delete a student by ID.
                int id;
                printf("Please, enter the ID number you want to delete: ");
                scanf("%d", &id);
                deleteNode(root,id);
                printf("Done\n");
                break;
            case 7:
               // Save all students to file:
               FileOperations(&root,2);
               printf("Saved..");
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
