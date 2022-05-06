#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

// builds the linked list
job* readFile(job** jobListHead)
{
    int saveAmountMachine = 0, saveJobNum = 0, saveAmountOperation = 0;
    operation* temporary = (operation*)malloc(sizeof(operation));
    job* createPro = (job*)malloc(sizeof(job));
    int qtJob = 0;
    int qtOp = 0;
    int opCounter = 0;

    FILE* fileOperation = fopen("saveSystem.txt", "r");
    if (fileOperation == NULL) {
        printf("Cannot open file.");
    }
    FILE* fileJob = fopen("saveSystem.txt", "r");
    if (fileJob == NULL) {
        printf("Cannot open file.");
    }

    if (fileOperation != 0) { // safety / file could be 0
        if (fileJob != 0) { // safety / file could be 0
            while (!feof(fileOperation) && !feof(fileJob)) { // until the end of the file
                if (fscanf(fileJob, "%d", &saveJobNum) > 0) {
                    if (saveJobNum == 0) {
                        // create new job when the previous is finished
                        createPro = createNewJob(qtJob);
                        *jobListHead = insertNodeListJob(jobListHead, createPro, NULL);
                        createPro->next = NULL;
                        qtJob++;
                    }
                    else {
                        // reads the counter variable to know how many machines machines are in the operation
                        if (fscanf(fileJob, "%d ", &saveAmountOperation) > 0);
                        if (fscanf(fileOperation, "%d ", &saveAmountMachine) > 0);
                        // allocating space
                        createPro->operation = (operation*)malloc(sizeof(operation) * saveAmountOperation);
                        createPro->operation = NULL;
                        createPro->operation->valueReadMachine = (int*)malloc(sizeof(int) * saveAmountMachine);
                        createPro->operation->valueReadOpTime = (int*)malloc(sizeof(int) * saveAmountMachine);
                        for (int i = 0; i < saveAmountMachine; i++) { // loops the amount of times needed to fill the operation
                            fscanf(fileOperation, "%d ", &createPro->operation->valueReadMachine[i]);
                            fscanf(fileOperation, "%d ", &createPro->operation->valueReadOpTime[i]);
                        }
                        opCounter++;
                        // calls the function to create the list, with all the values and the counter
                        temporary = createNodeFile(createPro->operation->valueReadMachine, createPro->operation->valueReadOpTime, saveAmountMachine);
                        createPro->operation = insertNodeList(&createPro->operation, temporary, NULL);
                        temporary->next = NULL;
                    }
                }
            }
        }
        //free(createPro->operation->valueReadMachine);
        //free(createPro->operation->valueReadOpTime);
    }
    fclose(fileOperation);
    fclose(fileJob);
    return *jobListHead;
}

// save the changes on the list
void writeFile(operation* head){
}

// operation functions
operation* createNode(int qt)
{
    operation* node = (operation*)malloc(sizeof(operation));

    int inputMachine, inputOpTime;
    int previousMachine = 0;
    int counter = 0;

    //aloccating space for the machines and their operation time.
    node->machineNumber = (int*)malloc(sizeof(int) * qt);
    node->machineOperationTime = (int*)malloc(sizeof(int) * qt);

    for (int i = 0; i < qt; i++) {
        printf("Choose the machine to insert in the operation.\n");
        if (scanf("%d", &inputMachine) > 0) { // check if the same number was chosen
            if (previousMachine == inputMachine) {
                printf("Machine already in use!\n");// block message
                i--; // go back 
            }
            else { // if the number is different
                printf("Choose the time of operation of machine %d:\n", inputMachine);
                if (scanf("%d", &inputOpTime) > 0) {
                    if (inputOpTime != 0) { // blocks the user from choosing a null time
                        // adds the new node to the linked list
                        node->machineNumber[i] = inputMachine;  // adds a machine
                        node->machineOperationTime[i] = inputOpTime; //adds a operation time for the machine
                        counter++;
                        node->counter = counter;
                        previousMachine = inputMachine; //update the previous machine to block if the same machine is chosen again
                    }
                    else {
                        printf("Operation time cant be 0. Starting Over.\n"); // block message
                        i--; // go back
                    }
                }
            }
        }
    }
    return node;
} // createNode

operation* createNodeFile(int* valueReadMachine, int* valueReadOpTime, int qt)
{
    operation* node = (operation*)malloc(sizeof(operation));
    int counter = 0;

    //aloccating space for the machines and their operation time.
    node->machineNumber = (int*)malloc(sizeof(int) * qt);
    node->machineOperationTime = (int*)malloc(sizeof(int) * qt);

    for (int i = 0; i < qt; i++) {
        //printf("%p\n", valueReadMachine[i]);
        //printf("%p\n", valueReadOpTime[i]);
        node->machineNumber[i] = valueReadMachine[i];  // adds a machine
        node->machineOperationTime[i] = valueReadOpTime[i]; //adds a operation time for the machine
        //printf("%p\n", node->machineNumber[i]);
        //printf("%p\n", node->machineOperationTime[i]);
        counter++;
    }
    node->counter = counter;
    free(valueReadMachine);
    free(valueReadOpTime);
    return node;
} // createNode

operation* insertAtHead(operation** head, operation* node_to_insert, int qt)
{
    // swap method
    node_to_insert->next = *head;
    // by passing a pointer to a pointer to the function, we are able to change the head value inside the function
    *head = node_to_insert;
    return node_to_insert; // returns the node inserted at the head of the list
}

operation* insertNodeList(operation** head, operation* node_to_insert, operation* position) {

    operation* lastNode = *head; // the last node points to the head of the list

    if (*head == NULL) { // if the list doesnt have anything yet
        *head = node_to_insert; // add that value to the hea of the list
    }
    else if (position != NULL) { //insert node after node in the chosen position
        // shifts the value on the desired position one position to the right, and inserts the new node
        node_to_insert->next = position->next;
        position->next = node_to_insert;
        return node_to_insert;
    }
    else { // if the list already as one value / and no position was specified
        operation* lastNode = *head; // the last node points to the head of the list
        while (lastNode->next != NULL) { // goes through all the list
            lastNode = lastNode->next;
        }
        // until it reaches the end and puts the value on the last position of the list
        lastNode->next = node_to_insert;
        node_to_insert->next = NULL; // the next element is NULL / end of the list
    }
    return *head; // returns after adding the new node to the list
}

void printLinkedList(operation** headOp)
{
    operation* temporary = headOp;
    printf("%p", temporary);
    int counter = 0;
    int i = 0;
    //printf("Process %d:\n", counter);
    while (temporary != NULL)
    { // while its not at the end of the list
        counter++; // used to show what is the actual operation
        printf("\tOperation %d:\n", counter);
        for (int i = 0; i < temporary->counter; i++) { // prints all the machines of the list
            printf("\t\tMachine: %d \n", temporary->machineNumber[i]);
            printf("\t\tOperation Time: %d \n", temporary->machineOperationTime[i]);
        }
        temporary = temporary->next;
    }
    printf("\n");
}

// jobs functions
void newJobUserInput(job* jobListHead) {

    int machineNumber = 0, machineOpTime = 0;
    int operationQt = 0;
    job* temporary;

    printf("How many operations?.\n");
    if (scanf("%d", &operationQt) > 0);
    if (operationQt > 0) { // wont accept 0

        for (int i = 0; i < operationQt; i++) { // ask for data
            printf("Operation %d machine number %d:", i, i);
            if (scanf("%d", &machineNumber) > 0);
            printf("Operation time for machine %d:", machineNumber);
            if (scanf("%d", &machineOpTime) > 0);
            // create the node in the operation
            temporary = createNewJob(operationQt); // creates the node
            insertNodeListJob(&jobListHead, temporary, NULL); // inserts the node on the list / last position
        }
    }
    free(temporary);
}

job* createNewJob(int operationQt) {
    //create a new node / allocate space for it
    job* node = malloc(sizeof(job));
    node->operation = malloc(sizeof(operation) * operationQt);
    node->next = NULL;
    return node;
}

job* insertNodeListJob(job** headJob, job* node_to_insert, job* position) {

    // if head is NULL, the list is empty
    if (*headJob == NULL) { 
        *headJob = node_to_insert; // add that value to the head of the list
    }
    else if (position != NULL) { // insert node after node in the chosen position
        // shifts the value on the desired position, one position to the right, and inserts the new node
        node_to_insert->next = position->next;
        position->next = node_to_insert;
        return node_to_insert;
    }
    else { // if the list already as one value / and no position was specified

        job* lastNode = *headJob; // the last node points to the head of the list

        while (lastNode->next != NULL) { // goes through all the list
            lastNode = lastNode->next;
        }
        // until it reaches the end and puts the value on the last position of the list
        lastNode->next = node_to_insert;
    }
    return *headJob; // returns after adding the new node to the list
}

void printLinkedListJob(job* headJob) {
    job* temporary = headJob; // temporary holds the address of the linked list, for every position
    int counter = 0;
    while (temporary != NULL) { // goes through the list
        counter++;
        temporary = temporary->next; // goes to the next register
    }
    printf("\n");
}

/*
operation* auxiliar = &temporary->operation;

while (auxiliar != NULL) {
            counter++; // used to show what is the actual operation
            printf("\tOperation %d:\n", counter);
            for (int i = 0; i < auxiliar->counter; i++) { // prints all the machines of the list
                printf("\t\tMachine: %d \n", auxiliar->machineNumber[i]);
                printf("\t\tOperation Time: %d \n", auxiliar->machineOperationTime[i]);
            }
            auxiliar = auxiliar->next;
        }
*/