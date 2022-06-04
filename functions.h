#pragma once
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

void writeFile(job* head);

job* createJobFile(job** headJob, operation** headOp);

job* fileListCreation(job* headJob);

job* createJob(job* jobListHead);

job* insertNodeListJob(job** headJob, job* node_to_insert, job* position);

job* insertAtHeadJob(job** head, job* node_to_insert);

void deleteNodeJob(job** head, job* value);

job* findNodeJob(job** head, int position);

// print
void printLinkedListJob(job* head);

void printOperationList(operation* head);

//operations

operation* createNodeOperation(int machineAmount);

int verifyDuplicateMachine(int counter, int machineNumber, operation* node);

operation* createNodeFileOp(int* valueReadMachine, int* valueReadOpTime, int qt);

operation* insertNodeListOperation(operation** head, operation* node_to_insert, operation* position);

operation* insertAtHeadOperation(operation** head, operation* node_to_insert);

int maximumOperationTime(operation* head);
// calculate minimum operating time
int minimumOperationTime(operation* head);
// calculate average operating time
int averageOperationTime(operation* head);
// delete the node chosen by the user
void deleteNode(operation** head, operation* value);
// modify an operation / add a machine, delete a machine or change the operation time of a machine
void modifyOperation(operation** head, operation* nodeToModify, int addMachine, int addOpTime, int option);
// find the node chosen by the user
operation* findNodeOperation(operation** head, int position);

void fjssp(job* head);

void fileFjssp(int arrFjssp[][91]);