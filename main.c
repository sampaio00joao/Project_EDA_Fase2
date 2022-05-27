#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "userInterfaceFunctions.h"


int main()
{
    // operation
    int machineQt = 0;
    operation* auxiliar;

    // default interface variables
    int option = 0;

    int operationQuantity = 0;
    int counter = 0; // temporary variable to count the jobs

    // job
    job* jobListHead = NULL; // Linked list
    job* jobTemporary;
    int sum = 0; // used to receive the return value from fjssp

    jobListHead = fileListCreation(jobListHead); // load the values from the file

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
            case 0:
                break;
            case 1: // add job
                jobListHead = insertNodeListJob(&jobListHead, createJob(jobListHead), NULL);
                break;
            case 2: // remove a job
                printf("Choose the job: ");
                if (scanf("%d", &option) > 0);
                deleteNodeJob(&jobListHead, findNodeJob(jobListHead, option));
                break;
            case 3: // Modify a job
                printf("Choose the job: ");
                if (scanf("%d", &option) > 0);
                jobTemporary = findNodeJob(jobListHead, option); // find the job choosen by the user
                system("cls");
                while (1) {
                    system("cls");
                    printf("Main Menu:\n");
                    printf("1. Add an Operation\n");
                    printf("2. Remove an Operation\n");
                    printf("3. Modify an Operation\n");
                    printf("5. Show the list\n");
                    printf("6. Maximum operation time\n");
                    printf("7. Minimum operation time\n");
                    printf("8. Average operation time\n");
                    printf("\nPress 0 to go back! \n");
                    if (scanf("%d", &option) > 0);
                    // check if the user wants to go back
                    if (option != 0 && option < 8) {
                        system("cls");
                        switch (option) {
                        default: // go back
                            system("cls");
                            break;
                        case 1: // add operation
                            userInterfaceAddOperation(&jobListHead, jobTemporary, option);
                            break;
                        case 2: // remove operation
                            counter++;
                            auxiliar = jobTemporary->operation;
                            // delete the node if only one operation is inside
                            if (jobTemporary->operation->previous != NULL) {
                                printOperationList(jobTemporary->operation);
                                printf("Choose the operation to delete.(Press 0 to go back)\n");
                                if (scanf("%d", &option) > 0);
                                if (option > 0) {
                                    while (auxiliar != NULL) { // used to restrict the user from choosing an operation that doenst exist
                                        counter++; // counts how many operations there are
                                        auxiliar = auxiliar->next;
                                    }
                                    if (option != 0 && option <= counter) { // cancel the operation if the number does not exist
                                        deleteNode(&jobTemporary->operation, findNodeOperation(&jobTemporary->operation, option));
                                    }
                                }
                            }
                            else {
                                printf("Only one operation existed, so the job was deleted\n");
                                printf("Press any key to go back!\n");
                                if (scanf("%d", &option) > 0) break;
                                deleteNodeJob(&jobListHead, jobTemporary);
                            }
                            break;
                        case 3: // modify operation
                            system("cls");
                            printOperationList(jobTemporary->operation);
                            printf("Choose the operation you want to modify: (Press 0 to go back)\n");
                            if (scanf("%d", &option) > 0);
                            userInterfaceModifyOperation(jobTemporary->operation, option);
                            break;
                        case 4:
                            break;
                        case 5: // show list
                            printOperationList(jobTemporary->operation);
                            printf("Press any key to go back!\n");
                            if (scanf("%d", &option) > 0) break;
                            break;
                        case 6: // maximum
                            printf("Maximum job time:\t%d\n", maximumOperationTime(jobTemporary->operation));
                            printf("Press any key to go back!\n");
                            if (scanf("%d", &option) > 0) break;
                            break;
                        case 7: // minimum
                            printf("Minimum job time:\t%d\n", minimumOperationTime(jobTemporary->operation));
                            printf("Press any key to go back!\n");
                            if (scanf("%d", &option) > 0) break;
                            break;
                        case 8: // average
                            printf("Average job time:\t%d\n", averageOperationTime(jobTemporary->operation));
                            printf("Press any key to go back!\n");
                            if (scanf("%d", &option) > 0) break;
                            break;
                        }
                    }
                    else break; // break infinite loop
                }
                break; // back to the job´s main menu
            case 4:// save changes
                option = 0;
                printf("Press 0 to go back!\n");
                if (scanf("%d", &option) > 0) break;
                break;
            case 5: // show the list
                option = 0;
                printLinkedListJob(jobListHead);
                printf("Press any key to go back!\n");
                if (scanf("%d", &option) > 0) break;
            case 6: // FJSSP
                fjssp(jobListHead);
                printf("\nPress any key to go back!\n");
                if (scanf("%d", &option) > 0) break;
                break;
            }
            system("cls"); // clear the screen after an operation
        } // scanf
    } // infinite loop
    system("pause");
    return 0;
}