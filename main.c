#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"


int main()
{
    int option = 0;
    int operationQuantity = 0;
    int counter = 0; // temporary variable to count the jobs

    job* jobListHead = NULL; // Linked list

    jobListHead = readFile(jobListHead); // load the values from the file

    while (1) { // infinite cycle
        printf("Main Menu:\n");
        printf("1. Add a job\n");
        printf("2. Remove a Job\n");
        printf("3. Modify a Job\n");
        printf("4. Save Jobs List\n");
        printf("5. Show the list\n");
        printf("6. FJSSP Solution Proposal\n");

        if (scanf("%d", &option) > 0) {
            system("cls"); // clear before an operation
            switch (option) {
            case 0: // add a job
                break;
            case 1: // remove a job
                jobListHead = insertNodeListJob(&jobListHead, createJob(jobListHead), NULL);
                break;
            case 2:
                break;
            case 4:// save changes
                option = 0;
                printf("Press 0 to go back!\n");
                if (scanf("%d", &option) > 0) break;
                break;
            case 5: // show the list
                option = 0;
                printLinkedListJob(jobListHead);
                printf("Press 0 to go back!\n");
                if (scanf("%d", &option) > 0) break;
            case 6: // FJSSP
                break;
            case 3: // Modify a job
                break;
            } // switch
            system("cls"); // clear the screen after an operation
        } // scanf
    } // infinite loop
    system("pause");
    return 0;
}