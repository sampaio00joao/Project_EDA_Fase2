#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

job* readFile(job* headJob) {

    int saveAmountOp = 0, saveAmountMachine = 0;
    
    operation* createOp; // to record the data on the list / single job
    job* createJob;
    operation* auxiliar = (operation*)malloc(sizeof(operation));;
    job* temporary = (job*)malloc(sizeof(job) * 3);

    FILE* fileJob = fopen("saveJobInfo.txt", "r"); // open job info file
    if (fileJob == NULL) { // check if the file opened
        printf("Cannot open file."); // error
    }

    FILE* fileOp = fopen("saveSystem.txt", "r"); // open operation info file
    if (fileOp == NULL) { //check if the file opened
        printf("Cannot open file."); // error
    }

    // safety
    if (fileJob != 0); else return -1;
    if (fileOp != 0); else return -1;

    while (!feof(fileJob)) { // until the end of the file
        if (fscanf(fileJob, "%d ", &saveAmountOp) > 0); // read the amount of operations of the job
        temporary->operation = NULL;
        for (int i = 0; i < saveAmountOp; i++) {
            // reads the counter variable to know how many machines machines are in the operation
            if (fscanf(fileOp, "%d ", &saveAmountMachine) > 0);
            // allocating space
            auxiliar->valueReadMachine = (int*)malloc(sizeof(int) * saveAmountMachine);
            auxiliar->valueReadOpTime = (int*)malloc(sizeof(int) * saveAmountMachine);
            for (int i = 0; i < saveAmountMachine; i++) { // loops the amount of times needed to fill the operation
                fscanf(fileOp, "%d ", &auxiliar->valueReadMachine[i]);
                fscanf(fileOp, "%d ", &auxiliar->valueReadOpTime[i]);
            }
            // calls the function to create the list, with all the values and the counter
            createOp = createNodeFileOp(auxiliar->valueReadMachine, auxiliar->valueReadOpTime, saveAmountMachine);
            temporary->operation = insertNodeListOperation(&temporary->operation, createOp, NULL);
        }
        insertNodeListJob(&headJob, temporary, NULL); // create job
    }
    // closing the files in the end
    fclose(fileOp); 
    fclose(fileJob);
    return headJob; // return the updated list
}

job* fileListCreation(job* headJob) {

}

job* createJob(job* jobListHead)
{
    int machineNumber = 0, machineOpTime = 0;
    int operationQt = 0, machineAmount = 0;
    int counter = 0;
    job* temporary = (job*)malloc(sizeof(job));
    operation* auxiliar;

    printf("How many operations?.\n");
    if (scanf("%d", &operationQt) > 0);
    if (operationQt > 0) { // wont accept 0 operations
        // allocating space for the linked list of operations
        // temporary->operation = (operation*)malloc(sizeof(operation));
        temporary->operation = NULL; // linked list of operations
        for (int i = 0; i < operationQt; i++) { // ask for data
            printf("\nOperation %d:\nHow many machines?\n", i + 1);
            if (scanf("%d", &machineAmount) > 0);
            if (machineAmount > 0) { // wont accept 0 machines
                auxiliar = createNodeOperation(machineAmount);
                insertNodeListOperation(&temporary->operation, auxiliar, NULL);
            }//machineAmount scanf
        }//for loop operation quantity
    }
    return temporary;
}

operation* createNodeOperation(int machineAmount)
{
    operation* node = (operation*)malloc(sizeof(operation));
    int machineNumber = 0, machineOpTime = 0;

    node->machineNumber = (int*)malloc(sizeof(int) * machineAmount);
    node->machineOperationTime = (int*)malloc(sizeof(int) * machineAmount);
    node->counter = machineAmount;
    for (int i = 0; i < machineAmount; i++) {
        printf("Machine Number: \n");
        scanf("%d", &machineNumber);
        printf("Machine Operation Time: \n");
        scanf("%d", &machineOpTime);
        node->machineNumber[i] = machineNumber;  // adds a machine
        node->machineOperationTime[i] = machineOpTime;  // adds a machine
    }//node creation loop
    return node;
}

operation* createNodeFileOp(int* valueReadMachine, int* valueReadOpTime, int qt)
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

operation* insertNodeListOperation(operation** head, operation* node_to_insert, operation* position) {

    if (*head == NULL) { // if the list doesnt have anything yet
        *head = node_to_insert; // add that value to the hea of the list
        (*head)->next = NULL;
        (*head)->previous = NULL;
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
        node_to_insert->previous = lastNode;
    }
    return *head; // returns after adding the new node to the list
}

job* insertNodeListJob(job** headJob, job* node_to_insert, job* position) {

    // if head is NULL, the list is empty
    if (*headJob == NULL) {
        *headJob = node_to_insert; // add that value to the head of the list
        (*headJob)->next = NULL;
        (*headJob)->previous = NULL;
    }
    else if (position != NULL) { // insert node after node in the chosen position
        // shifts the value on the desired position, one position to the right, and inserts the new node
        node_to_insert->next = position->next;
        if (node_to_insert->next != NULL) {
            node_to_insert->next->previous = position;
        }
        node_to_insert->previous = position;
        position->next = node_to_insert;
        //return node_to_insert;
    }
    else { // if the list already as one value / and no position was specified
        job* lastNode = *headJob; // the last node points to the head of the list
        while (lastNode->next != NULL) { // goes through all the list
            lastNode = lastNode->next;
        }
        // until it reaches the end and puts the value on the last position of the list
        lastNode->next = node_to_insert;
        node_to_insert->next = NULL;
        node_to_insert->previous = lastNode;
    }
    return headJob; // returns after adding the new node to the list
}

void printLinkedListJob(job* headJob) {
    int counterJob = 0, counterOp = 0; // variables used to print the number of the job or operation
    int i = 1;
    job* temporary = headJob; // points to the head of the list of jobs
    while (temporary != NULL) { // goes through the list of jobs
        counterJob++;
        printf("Job %d:", counterJob);
        printf("\n");
        operation* auxiliar = temporary->operation; // pointer to the list
        //while (temporary->operation != NULL) {
          //temporary->operation = temporary->operation->previous;
        //}
        while (auxiliar != NULL) { // goes through the list of operations inside the job
            counterOp++;
            printf("  Operation %d: \n", counterOp);
            for (int i = 0; i < auxiliar->counter; i++) {  // prints all the machines inside the operation
                printf("\tMachine Number: %d\n", auxiliar->machineNumber[i]);
                printf("\tMachine Operation Time: %d\n", auxiliar->machineOperationTime[i]);
            }
            auxiliar = auxiliar->next; // goes to the next operation register
        }
        counterOp = 0; // reset
        temporary = temporary->next; // goes to the next job register
    }
    printf("\n");
}

