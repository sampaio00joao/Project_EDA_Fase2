#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "functions.h"
#include "userInterfaceFunctions.h"

// updates the file
void writeFile(job* head){

    int counter = 0;
    job* auxiliar = head;
    operation* temporary;

    FILE* fileOp = fopen("saveSystem.txt", "w"); // open file in writing mode
    if (fileOp == NULL) {
        printf("Cannot open file."); // error if it fails to open
    }
    FILE* fileJob = fopen("saveJobInfo.txt", "w"); // open file in writing mode
    if (fileJob == NULL) {
        printf("Cannot open file."); // error if it fails to open
    }
    // safety
    if (fileJob != 0); else return -1;
    if (fileOp != 0); else return -1;

    while (auxiliar != NULL) {
        temporary = auxiliar->operation; // access the data from the linked list 
        while (temporary != NULL) {
            counter++; // to save the amount of operations
            fprintf(fileOp, "%d ", temporary->counter); // used as a reference when reading
            for (int i = 0; i < temporary->counter; i++) {
                // prints all the machines and their operation time inside every operation/node
                fprintf(fileOp, "%d ", temporary->machineNumber[i]);
                fprintf(fileOp, "%d ", temporary->machineOperationTime[i]);
            }
            fprintf(fileOp, "\n", '\n');
            temporary = temporary->next; // continues through the list
        }
        fprintf(fileJob, "%d \n", counter);
        counter = 0; // reset
        auxiliar = auxiliar->next;
    }
    fclose(fileOp); // closes the file in the end
    fclose(fileJob);
}

// allocate space for the job registers
job* createJobFile(job** headJob, operation** headOp) {

    job* temporary = (job*)malloc(sizeof(job));
    operation* auxiliar = (operation*)malloc(sizeof(operation));
    temporary->operation = *headOp;
    insertNodeListJob(headJob, temporary, NULL);
    
    return *headJob; // return the updated list
}
// creation of the list from the file
job* fileListCreation(job* headJob) {

    int saveAmountOp = 0, saveAmountMachine = 0;
    operation* createOp; // to record the data on the list / single job
    operation* auxiliar = (operation*)malloc(sizeof(operation));
    job* temporary = (job*)malloc(sizeof(job));

    FILE* fileJob = fopen("saveJobInfo.txt", "r"); // open job info file
    FILE* fileOp = fopen("saveSystem.txt", "r"); // open operation info file

    // check if the file opened
    if (fileJob == NULL) printf("Cannot open file."); // error
    if (fileOp == NULL) printf("Cannot open file."); // error

    // safety
    if (fileJob != 0); else return -1;
    if (fileOp != 0); else return -1;

    while (!feof(fileJob)) { // until the end of the file
        temporary->operation = NULL;
        if (fscanf(fileJob, "%d ", &saveAmountOp) > 0); // read the amount of operations of the job
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
            createOp = createNodeFileOp(auxiliar->valueReadMachine, auxiliar->valueReadOpTime, saveAmountMachine);
            temporary->operation = insertNodeListOperation(&temporary->operation, createOp, NULL);
        }
        createJobFile(&headJob, &temporary->operation);
    }
    fclose(fileOp);
    fclose(fileJob);
    return headJob;
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
        // declaring the linked list
        temporary->operation = NULL; // linked list of operations
        for (int i = 0; i < operationQt; i++) { // ask for data
            printf("\nOperation %d:\nHow many machines?\n", i + 1);
            if (scanf("%d", &machineAmount) > 0);
            if (machineAmount > 0) { // wont accept 0 machines
                auxiliar = createNodeOperation(machineAmount);
                insertNodeListOperation(&temporary->operation, auxiliar, NULL);
            }
        }
    }
    temporary->next = NULL;
    temporary->previous = NULL;
    return temporary;
}

job* insertNodeListJob(job** headJob, job* node_to_insert, job* position) {


    // if head is NULL, the list is empty
    if (*headJob == NULL) {
        *headJob = node_to_insert; // add that value to the head of the list
        (*headJob)->next = NULL;
        (*headJob)->previous = NULL;
    }
    else if (position != NULL) { 
        // insert node after node in the chosen position
        // shifts the value on the desired position, one position to the right, and inserts the new node
        node_to_insert->next = position->next;
        if (node_to_insert->next != NULL) {
            node_to_insert->next->previous = position;
        }
        node_to_insert->previous = position;
        position->next = node_to_insert;
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
    return *headJob; // returns after adding the new node to the list
}

job* insertAtHeadJob(job** head, job* node_to_insert)
{
    // swap method
    node_to_insert->next = *head;
    (*head)->previous = node_to_insert;
    // by passing a pointer to a pointer to the function, we are able to change the head value inside the function
    *head = node_to_insert;
    return node_to_insert; // returns the node inserted at the head of the list
}

void deleteNodeJob(job** head, job* value) {
    job* temporary; //temporary is used to free the memory
    //key found on the head node / move to head node to the next node, and free the head.
    if ((*head)->operation->machineNumber == value->operation->machineNumber)
    {
        temporary = *head;    //backup to free the memory
        *head = (*head)->next;
        free(temporary); // memory is free
    }
    else
    {
        job* current = *head;
        while (current->next != NULL) // goes through all the list
        {
            //if true, we need to delete the current->next node
            if (current->operation->machineNumber == value->operation->machineNumber) // comparing the node chosen by the user with the one on the list
            {
                temporary = current->next;
                //node will be disconnected from the linked list.
                current->next = current->next->next;
                free(temporary); // free the memory and delete the node
                break;
            }
            //Otherwise, proceed through the list
            else {
                current = current->next;
            }
        }
    }
}

job* findNodeJob(job** head, int position)
{
    job* temporary = *head;
    // receives the head / no need for double pointer since we dont need to apply changes to the head.
    int counter = 0; // counter used to count repeat the loop until it reaches the operation

    // it will repeat until the return value, and its only true when temporary is allocated
    while (temporary != NULL)
    {
        if ((counter + 1) == position) {
            return temporary; // returns the operation when it reaches the position/operation inputed by the user
        }
        counter++; //if false, keeps counting
        temporary = temporary->next; // and passing to the next node/operation in the list
    }
    return NULL; // if nothing was found return NULL/error
}

// print
void printLinkedListJob(job* headJob) {
    int counterJob = 0, counterOp = 0; // variables used to print the number of the job or operation
    int i = 1;
    job* temporary = headJob; // points to the head of the list of jobs
    while (temporary != NULL) { // goes through the list of jobs
        counterJob++;
        printf("Job %d:", counterJob);
        printf("\n");
        printOperationList(temporary->operation);
        temporary = temporary->next; // goes to the next job register
    }
    printf("\n");
}

void printOperationList(operation* head) {
    int counterOp = 0;
    operation* auxiliar = head; // pointer to the list
    while (auxiliar != NULL) { // goes through the list of operations inside the job
        counterOp++;
        printf("  Operation %d: \n", counterOp);
        for (int i = 0; i < auxiliar->counter; i++) {  // prints all the machines inside the operation
            printf("\tMachine Number: %d\n", auxiliar->machineNumber[i]);
            printf("\tMachine Operation Time: %d\n", auxiliar->machineOperationTime[i]);
        }
        auxiliar = auxiliar->next; // goes to the next operation register
    }
}

// operations 
operation* createNodeOperation(int machineAmount)
{
    operation* node = (operation*)malloc(sizeof(operation));
    int machineNumber = 0, machineOpTime = 0;
    int block = 0, counter = 0;

    node->machineNumber = (int*)malloc(sizeof(int) * machineAmount);
    node->machineOperationTime = (int*)malloc(sizeof(int) * machineAmount);
    node->counter = machineAmount;
    for (int i = 0; i < machineAmount; i++) {
        printf("Machine Number: \n");
        if(scanf("%d", &machineNumber) > 0);
        block = verifyDuplicateMachine(counter, machineNumber, node);

        if (block == 0) {
            printf("Machine Operation Time: \n");
            if (scanf("%d", &machineOpTime) > 0);
            if (machineOpTime != 0) {
                node->machineNumber[i] = machineNumber;  // adds a machine
                node->machineOperationTime[i] = machineOpTime;  // adds a machine
                counter++; // update the counter, for the amount of machines accepted
            }
            else {
                printf("Operation time cant be 0. Starting Over.\n");
                i--; // go back
            }
        }
        else i--; // go back
    }//node creation loop
    return node;
}

int verifyDuplicateMachine(int counter, int machineNumber, operation* node)
{
    int verifyDuplicate = 0;
    while (verifyDuplicate < counter) { 
        if (node->machineNumber[verifyDuplicate] == machineNumber) { // checks for duplicate machines
            printf("Machine already in use!\n");// block message
            printf("Choose again!\n");// block message
            return 1; // there is a duplicate, so activate the block variable
        }
        verifyDuplicate++;
    }
    return 0; // no duplicate
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

operation* insertAtHeadOperation(operation** head, operation* node_to_insert)
{
    // swap method
    node_to_insert->next = *head;
    (*head)->previous = node_to_insert;
    // by passing a pointer to a pointer to the function, we are able to change the head value inside the function
    *head = node_to_insert;
    return node_to_insert; // returns the node inserted at the head of the list
}

void deleteNode(operation** head, operation* value) {

    operation* auxiliar; //temporary is used to free the memory
    operation* temporary; //temporary is used to free the memory
    //key found on the head node / move to head node to the next node, and free the head.
    if ((*head)->machineNumber == value->machineNumber)
    {
        temporary = *head;    //backup to free the memory
        *head = (*head)->next;
        free(temporary); // memory is free
    }
    else
    {
        operation* current = *head;
        while (current->next != NULL) // goes through all the list
        {
            //if true, we need to delete the current->next node
            if (current->next->machineNumber == value->machineNumber) // comparing the node chosen by the user with the one on the list
            {
                temporary = current->next;
                //node will be disconnected from the linked list.
                current->next = current->next->next;
                free(temporary); // free the memory and delete the node
            }
            //Otherwise, proceed through the list
            else {
                current = current->next;
            }
        }
    }
}

operation* findNodeOperation(operation** head, int position)
{
    operation* temporary = *head;
    // receives the head / no need for double pointer since we dont need to apply changes to the head.
    int counter = 0; // counter used to count repeat the loop until it reaches the operation

    // it will repeat until the return value, and its only true when temporary is allocated
    while (temporary != NULL)
    {
        if ((counter + 1) == position) {
            return temporary; // returns the operation when it reaches the position/operation inputed by the user
        }
        counter++; //if false, keeps counting
        temporary = temporary->next; // and passing to the next node/operation in the list
    }
    return NULL; // if nothing was found return NULL/error
}

void modifyOperation(operation** head, operation* nodeToModify, int addMachine, int addOpTime, int option) {

    int pos = 0, size = 0;
    int bufferMachine[100]; // save the values for machines
    int bufferOpTime[100];  // save the values for the operation time
    int counter = 0; // for the loops and to update the counter variable in the structure
    int previousMachine = 0;
    int optionRemove = 0;
    int ref = 0;
    int blockCounter = 0;
    int blockFlag = 0;
    int optionId = 0;
    
    switch (option) {
    case 1: // add new item
        //adds the new machine and operation time, to the last position inside the operation
        counter = 0;
        if (nodeToModify->counter < 8) {
            while (counter < nodeToModify->counter) { // verification to block the existence of the same machine in the same operation
                if (addMachine == nodeToModify->machineNumber[counter]) {
                    ref++;
                    counter++;
                }
                else {
                    counter++;
                }
            }
            if (ref == 0) { // if the machine the user wants to input doesnt exist, add the machine to the operation
                nodeToModify->machineNumber[nodeToModify->counter] = addMachine;
                nodeToModify->machineOperationTime[nodeToModify->counter] = addOpTime;
                nodeToModify->counter++; // update the counter variable
            }
        }
        else printf("Operation Full!\n");
        printf("Press any key to go back!\n");
        if (scanf("%d", &option) > 0) break;
        break;
    case 2: // remove machine 
        counter = 0;
        option = 0;
        printf("Machine to delete: ");
        while (counter < nodeToModify->counter) {
            printf("{%d} ", nodeToModify->machineNumber[counter]);
            counter++;
        }
        counter = 0; // reset counter
        printf("\n");
        if (scanf("%d", &option) > 0) {
            while (counter < nodeToModify->counter) { // save the node in a buffer / machine and operation time
                bufferMachine[counter] = nodeToModify->machineNumber[counter];
                bufferOpTime[counter] = nodeToModify->machineOperationTime[counter];
                if (nodeToModify->machineNumber[counter] == option) { // saves the position of the machine to delete
                    pos = counter;
                }
                counter++;
            }
            // starts on the position to delete, and reorganizes the arrays 
            if (pos != 0) {
                for (counter = pos; counter < nodeToModify->counter; counter++) {
                    bufferMachine[counter] = bufferMachine[counter + 1];
                    bufferOpTime[counter] = bufferOpTime[counter + 1];
                }
                nodeToModify->counter = counter - 1; // decrease one number on the operation counter variable
                counter = 0;
                while (counter < nodeToModify->counter) { // fill the node again without the deleted machine and op. time
                    nodeToModify->machineNumber[counter] = bufferMachine[counter];
                    nodeToModify->machineOperationTime[counter] = bufferOpTime[counter];
                    counter++;
                }

                // make sure to delete the operation if we delete the last machine available
                if (nodeToModify->counter != 0) { // true if the operation as one or more machines available
                    printf("Machine deleted\n");
                }
                else { // delete the operation since there is no machines left
                    printf("Last machine available deleted.\n");
                    printf("Operation deleted.\n");
                    deleteNode(head, nodeToModify); // function call to delete, sending nodeToModify, as the node to delete parameter.
                }
            }
            else break;
        }
        break;

    case 3: // modify the operation time from a machine
        counter = 0;
        option = 0;
        for (int i = 0; i < nodeToModify->counter; i++) {
            if (nodeToModify->machineNumber[i] == option) { // identify the machine chosen by the user
                printf("\nPrevious operation time: %d\n", nodeToModify->machineOperationTime[i]);
                printf("New operation time: ");
                if (scanf("%d", &option) > 0) // reutilizing the option variable
                    nodeToModify->machineOperationTime[i] = option; // update the operation time of said machine
            }
            else if (option == 0) { // only choosing an available machine is permited
                printf("Machine to mofify: ");
                while (counter < nodeToModify->counter) { // prints all the machines available
                    printf("{%d} ", nodeToModify->machineNumber[counter]);
                    counter++;
                }
                counter = 0;
                option = 0;
                printf("\n");
                if (scanf("%d", &option) > 0) // user input
                    i--;
            }
        }
        break;
    case 4: // modify machine Id
        counter = 0;
        pos = 0;
        printf("Choose a machine:");
        while (counter < nodeToModify->counter) { // print all the machines available
            printf("{%d} ", nodeToModify->machineNumber[counter]);
            counter++;
        }
        printf("\n");
        if (scanf("%d", &optionId) > 0) {
            counter = 0; // reset counter
            while (counter < nodeToModify->counter) {
                if (nodeToModify->machineNumber[counter] == optionId) { // identify the machine chosen by the user
                    printf("New Machine:\n");
                    if (scanf("%d", &optionId) > 0) { // reutilizing the option variable
                        blockCounter = 0;
                        while (blockCounter < nodeToModify->counter) { // search for duplicate
                            if (optionId == nodeToModify->machineNumber[blockCounter]) { // if there is one
                                printf("Machine already in use!\n");
                                blockFlag = 1; // block the option
                            }
                            blockCounter++;
                        }
                        pos = counter;
                        if (blockFlag != 0) { // blocking the same machine
                            break;
                        }
                        else { // else, replace the id of the machine
                            nodeToModify->machineNumber[pos] = optionId; // update the operation time of said machine
                            break;
                        }
                    }
                }
                counter++;
            }
        }
        break;
    }
}

int maximumOperationTime(operation* head) {
    int sum = 0, max = 0;
    operation* temporary = head;
    while (temporary != NULL) { // go through the list
        for (int i = 0; i < temporary->counter; i++) {
            if (i == 0) { //updates the max variable in the beggining as a reference
                max = temporary->machineOperationTime[i];
            }
            else if (max <= temporary->machineOperationTime[i]) {
                // when it finds a higher value it will update the variable max
                max = temporary->machineOperationTime[i];
            }
        }
        sum += max; // sum all the highest values of all the operations
        temporary = temporary->next;
    }
    return sum; // return the sum to print
}

int minimumOperationTime(operation* head) {
    int sum = 0, min = 0;
    operation* temporary = head;
    while (temporary != NULL) {
        for (int i = 0; i < temporary->counter; i++) {
            if (i == 0) { //updates the min variable in the beggining as a reference
                min = temporary->machineOperationTime[i];
            }
            else if (min >= temporary->machineOperationTime[i]) {
                // when it finds a lower value it will update the variable min
                min = temporary->machineOperationTime[i];
            }
        }
        sum += min; // sum all the lowest values of all the operations
        temporary = temporary->next;
    }
    return sum; // return the sum to print
}

int averageOperationTime(operation* head) {
    int sum = 0;
    int count = 0;
    operation* temporary = head;
    while (temporary != NULL) {
        for (int i = 0; i < temporary->counter; i++) {
            sum += temporary->machineOperationTime[i];
        }
        count += temporary->counter;
        temporary = temporary->next;
    }
    sum = sum / count;
    return(sum);
}

// user interface
void userInterfaceAddOperation(job** head, job* jobNode, int option) {
    bool breakLoop = false; // breaks the infinite loop
    int machineQuantity = 0;
    int counter = 0; // counts the machines inside the operation
    operation* temporary;
    operation* auxiliar = jobNode->operation;
    while (auxiliar != NULL) {
        counter++;
        auxiliar = auxiliar->next;
    }
    if (counter < 8) {
        while (breakLoop != true) {
            switch (option)
            {
            default:
                system("cls");
                break;
            case 1: // add operation
                option = 0;
                while (breakLoop != true) {
                    system("cls");
                    printf("Choose the option: (Press 0 to cancel)\n");
                    printf("1. Insert at the tail of the list.\n");
                    printf("2. Insert at the head of the list.\n");
                    printf("3. Insert on a specified position.\n");
                    if (scanf("%d", &option) > 0) {
                        switch (option) {
                        default:
                            system("cls");
                            break;
                        case 0:
                            breakLoop = true; // break the loop
                            break;
                        case 1: // Insert at the tail of the list
                            system("cls");
                            printf("(Choose between 1 and 8, or the program will reset)\n");
                            printf("How many machines?.\n");
                            if (scanf("%d", &machineQuantity) > 0) {
                                if (machineQuantity > 0 && machineQuantity < 8) {
                                    temporary = createNodeOperation(machineQuantity); // creates the node and returns it
                                    /*
                                    Function parameters:
                                        1. The address of the operation list inside the specified job register;
                                        2. The node returned previously;
                                        3. NULL because im not specifying a position to put the new node.
                                    */
                                    insertNodeListOperation(&jobNode->operation, temporary, NULL); // inserts the node on the list / last position
                                    system("cls");
                                }
                                else break; // resets if and ivalid number was inputed
                            }
                            break;
                        case 2: // Insert at the head of the list
                            system("cls");
                            printf("How many machines?.\n");
                            if (scanf("%d", &machineQuantity) > 0) {
                                if (machineQuantity > 0) {
                                    if (machineQuantity > 0 && machineQuantity < 8) {
                                        temporary = createNodeOperation(machineQuantity); // creates the node and returns it
                                        /*
                                        Function parameters:
                                            1. The address of the operation list inside the specified job register;
                                            2. The node returned previously;
                                            I use a special function to add to the head of the list, since i cant do it
                                            by specifying a position.
                                        */
                                        insertAtHeadOperation(&jobNode->operation, temporary);
                                        system("cls");
                                    }
                                    else break; // resets if and ivalid number was inputed
                                }
                            }
                            break;
                        case 3: // Insert on a specified position
                            system("cls");
                            //MUDAR8
                            temporary = jobNode;
                            printf("Job info:\n");
                            printOperationList(jobNode->operation); // show the operation list to help the user
                            printf("\nChoose the position?.\n");
                            if (scanf("%d", &option) > 0);
                            printf("How many machines?.\n");
                            if (scanf("%d", &machineQuantity) > 0) {
                                if (machineQuantity > 0) {
                                    if (machineQuantity > 0 && machineQuantity < 8) {
                                        temporary = createNodeOperation(machineQuantity); // creates the node and returns it
                                        /*
                                        Function parameters:
                                            1. The address of the operation list inside the specified job register;
                                            2. The node returned previously;
                                            3. Find the node in the specified position, and the return value is the node found.
                                        */

                                        insertNodeListOperation(&jobNode->operation, temporary, findNodeOperation(&jobNode->operation, option - 1)); // inserts the node on the list / last position
                                        system("cls");
                                    }
                                    else break; // resets if and ivalid number was inputed
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    else {
        printf("Cant add more operations!");
    }
}

void userInterfaceModifyOperation(operation* head, int option)
{
    int addMachine = 0, addOpTime = 0;
    int optionInput = 0;
    int counterOperation = 0;
    operation* auxiliar = head;

    // count the amount of operations
    while (auxiliar != NULL) {
        counterOperation++;
        auxiliar = auxiliar->next;
    }

    if (option != 0 && option <= counterOperation) { // if the value isnt 0 or higher than the valid operations
        system("cls");
        printf("1. Insert new machine\n");
        printf("2. Remove an existing machine\n");
        printf("3. Change the operation time from a machine\n");
        printf("4. Switch machines inside an operation\n");
        printf("(Press 0 to cancel)\n");
        if (scanf("%d", &optionInput) > 0);

        switch (optionInput) {
        default:
            system("cls");
            break; // back to menu
        case 1: // Insert a machine to add
            printf("Machine to add to the operation: ");
            if (scanf("%d", &addMachine) > 0)
                printf("Machine operation time: ");
            if (scanf("%d", &addOpTime) > 0)
                // sends as parameters the head, the node the user wants and the variables to update the operation
                modifyOperation(&head, findNodeOperation(&head, option), addMachine, addOpTime, optionInput);
            break;
        case 2:
            // Remove a machine
            addMachine = 0;
            addOpTime = 0;
            // sends as parameters the head, the node the user wants and the variables to update the operation
            modifyOperation(&head, findNodeOperation(&head, option), addMachine, addOpTime, optionInput);
            break;
        case 3:
            // Modify the time from a machine
            addMachine = 0;
            addOpTime = 0;
            // sends as parameters the head, the node the user wants and the variables to update the operation
            modifyOperation(&head, findNodeOperation(&head, option), addMachine, addOpTime, optionInput);
            break;
        case 4: // modify machine id
            addMachine = 0;
            addOpTime = 0;
            // sends as parameters the head, the node the user wants and the variables to update the operation
            modifyOperation(&head, findNodeOperation(&head, option), addMachine, addOpTime, optionInput);
            break;
        }//switch
    }
}

// fjssp
void fjssp(job* head)
{
    job* temporary = head;
    int arrFjssp[8][100]; // array with the fjssp solution
    int arrLastPosition[8][2]; // always record the last position with a value for every machine
    int lastMachineTime = 0; // used to update the array arrLastPosition 
    int minTime = 0;
    int saveMachine = 0; // store the machine choosen by the algoritm
    int operationCounter = 0, jobCounter = 0;

    operation* auxiliar; // get though the linked list of operations, for every job

    // set all the positions in the array to 0
    // helps when comparing is needed 
    memset(arrFjssp, 0, sizeof(arrFjssp));
    memset(arrLastPosition, 0, sizeof(arrLastPosition));

    // every line is a machine 
    for (int i = 0; i < 8; i++) {
        arrFjssp[i][0] = i + 1; // put all possible machines in the beggining of every line
        arrLastPosition[i][0] = i + 1;
    }
    while (temporary != NULL) {
        auxiliar = temporary->operation; // update the operation address in the new job register
        operationCounter = 0; // reset the counter of operations
        jobCounter++;
        while (auxiliar != NULL) {
            // all used to save the data on the arrays 
            minTime = 0; // reset minimum time info variable
            lastMachineTime = 0; // reset the last machine info variable
            operationCounter++; // counter of operations
            for (int i = 0; i < auxiliar->counter; i++) {
                if (minTime >= auxiliar->machineOperationTime[i]) {
                    // if the is a lower value it will update the variable min
                    minTime = auxiliar->machineOperationTime[i];
                    saveMachine = auxiliar->machineNumber[i];
                }
                else if (minTime == 0) {
                    // first time updating the min value / creating the reference
                    minTime = auxiliar->machineOperationTime[i];
                    saveMachine = auxiliar->machineNumber[i];
                }
            }
            // insert the value choosen in the arrays / first time
            if (arrLastPosition[saveMachine - 1][1] == 0) {
                arrLastPosition[saveMachine - 1][1] = minTime+2; // plus 2 because of the job and operation number
                arrFjssp[saveMachine - 1][1] = jobCounter; // save the operation number
                arrFjssp[saveMachine - 1][2] = operationCounter; // save the operation number
                for (int i = 0; i < minTime; i++) {
                    arrFjssp[saveMachine - 1][3 + i] = minTime;
                }
            }
            else { // second time and so on
                lastMachineTime = arrLastPosition[saveMachine - 1][1];
                arrFjssp[saveMachine - 1][lastMachineTime+1] = jobCounter; // save the operation number
                arrFjssp[saveMachine - 1][lastMachineTime+2] = operationCounter; // save the operation number
                lastMachineTime = arrLastPosition[saveMachine - 1][1] + 2; // plus 2 because of the job and operation number
                for (int i = 1; i < minTime+1; i++) {
                    arrFjssp[saveMachine - 1][lastMachineTime + i] = minTime;
                }
                lastMachineTime = minTime + arrLastPosition[saveMachine - 1][1]+2; // plus 2 because of the job and operation number
                arrLastPosition[saveMachine - 1][1] = lastMachineTime; // update with the new last position
            }
            // doesnt allow the array to overwrite the data previously stored
            auxiliar = auxiliar->next; // next register / operation list
        }
        temporary = temporary->next; // next register / job list
    }
    fileFjssp(head, arrFjssp);
}

void fileFjssp(job* head, int arrFjssp[8][100]) {

    FILE* file = fopen("fjsspSolution.txt", "w"); // open job info file
    // check if the file opened
    if (file == NULL) printf("Cannot open file."); // error
    // safety
    if (file != 0); else return -1;

    operation* auxiliar;
    job* temporary = head;
    int counterOpTime = 0;
    int value = 0, valueOpNumber = 0, valueJobNumber = 0;
    int j = 0;
    int counter = 0;
    // print the solution on the file
    fprintf(file, "\t\t");
    for (int i = 0; i <= 100; i++) {
        fprintf(file, "T%d\t\t\t", i);
    }
        
    for (int i = 0; i<8; i++){
        j = 1;
        counter = 0;
        fprintf(file, "\n\nM%d", i+1);
        while (counter < 100) {
            counterOpTime = 0;
            valueJobNumber = arrFjssp[i][j]; // first value is the job number
            if (valueJobNumber == 0){
                fprintf(file, "\t\t...\t"); // 0 means there is an empty space in that memory address
            }
            else {
                j++;
                valueOpNumber = arrFjssp[i][j]; // second value is the operation number
                j++;
                value = arrFjssp[i][j]; // checks the operation time and repeats according to that value
                while (counterOpTime < value) {
                    fprintf(file, "\t\tJ%d", valueJobNumber);
                    fprintf(file, "Op%d", valueOpNumber);
                    counterOpTime++;
                    j++;
                }
            }
            counter++;
        }
    }
    fclose(file);
}
