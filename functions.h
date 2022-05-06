#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct operation
{
    // used on the file reading process
    int* valueReadMachine;
    int* valueReadOpTime;
    int counter; // to count the number of machines inside an operation
    // actual machines and operation time
    int* machineOperationTime;
    int* machineNumber;
    struct operation* next; // next position on the list
} operation;

typedef struct job
{
    int operationCounter;
    operation* operation; // linked list of operations
    struct job* next; // next position on the list
    struct job* previous; // previous position on the list
}job;

// brings all the data from the file
job* readFile(job** jobListHead);
// create nodes at run time
operation* createNode(int qt);
// create the list from the file
operation* createNodeFile(int* valueReadMachine, int* valueReadOpTime, int qt);
// insert at the head
operation* insertNodeList(operation** head, operation* node_to_insert, operation* position);

void printLinkedList(operation** headOp);
// updates the file
void writeFile(operation* head);

//JOBS
void newJobUserInput(job* jobListHead);

job* createNewJob(int operationQt);

job* insertNodeListJob(job** headJob, job* node_to_insert, job* position);

void printLinkedListJob(job* headJob);
