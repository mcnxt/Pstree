/*
Authors: Marcus Cureton and Corey Shafer
Date of Submission:07/30/2022
Name of this file:mypstree.c
Short description of contents:
The user enters a pid and this program will traverse through the proc
    file system, track the parent and child processes, and output
    a hierarchy of all the processes in the system in a tree-like format.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
Function Name:main
Input to the method: aargc is the number of arguments being passed
    into your program from the command line and argv is the array of arguments.
Output(Return value): The output is a hierarchy of all the processes of the users's pid
    in a tree-like format
Brief description of the task:main()first takes in a requested pid from the user and then
    traverses through the proc file system to track the parent and child processes. main then
    outputs the tree to the user.
*/
void main(int argc, char **argv)
{
    int pid;
    sscanf(argv[1], "%d", &pid);

    // goes into the proc folder to get the children of the original parent
    char filename[1000];
    sprintf(filename, "/proc/%d/task/%d/children", pid, pid);
    FILE *f = fopen(filename, "r");

    int parent[1000];
    char comm[1000];
    int ppid;
    int numProc = 0;
    // creates the first array of child processes
    while (fscanf(f, "%d", &ppid) != EOF)
    {
        parent[numProc] = ppid;
        numProc++;
    }
    // if the pid doesn't exist then it won't run
    if (numProc == 0)
    {
        printf("PID: %d does not exist\n", pid);
        exit(0);
    }
    // prints out the child process of the original process
    printf("The Child Processes of %d are: ", pid);
    for (int i = 0; i < numProc; i++)
    {
        printf("%d ", parent[i]);
    }
    printf("\n");
    int i = 0;
    // checks if the parent has a child
    while (i < numProc)
    {
        printf("\tChild Process: %d", parent[i]);
        sprintf(comm, "/proc/%d/task/%d/children", parent[i], parent[i]);
        FILE *cf = fopen(comm, "r");
        int cpid = 0;
        int cProc = 0;
        int cpArr[2000];
        while (fscanf(cf, "%d", &cpid) != EOF)
        {
            cpArr[cProc] = cpid;
            cProc++;
        }
        int tab = 2;

        // if the parent has a child it will check
        // if the child has a child and then after that
        while (cProc > 0)
        {
            int y = 0;
            char child[1000];
            printf("\n");
            // tabs the correct amount of times for each child process
            for (int x = tab; x > 0; x--)
            {
                printf("\t");
            }
            // prints out the current child process
            printf("Child Processes: %d", cpArr[y]);
            // checks if the child has a child
            sprintf(child, "/proc/%d/task/%d/children", cpArr[y], cpArr[y]);
            FILE *ccf = fopen(child, "r");
            int ccpid = 0;
            // checks if the child has a child
            if (fscanf(ccf, "%d", &ccpid) != EOF)
            {
                cpArr[0] = ccpid;
                tab++;
            }
            else
            {
                cProc--;
            }
        }

        printf("\n");
        i++;
    }
    fclose(f);
}
