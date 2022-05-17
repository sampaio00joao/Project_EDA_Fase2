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
    struct operation* previous; // previous position on the list
} operation;

typedef struct job
{
    operation* operation; // linked list of operations
    struct job* next; // next position on the list
    struct job* previous; // previous position on the list
}job;

job* readFile(job* headJob);

job* fileListCreation(job* headJob);

job* createJob(job* jobListHead);

operation* createNodeOperation(int machineAmount);

operation* createNodeFileOp(int* valueReadMachine, int* valueReadOpTime, int qt);

operation* insertNodeListOperation(operation** head, operation* node_to_insert, operation* position);

job* insertNodeListJob(job** headJob, job* node_to_insert, job* position);

void printLinkedListJob(job* headJob);
