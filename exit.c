// Daniel Rosenthal
// CSc 332 - Group Project
// Group A - Exit
// 28 April 2021

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define len 1024                                             // Default value set for length of c strings declared below 

char c1[len] = "", c2[len] = "", c3[len] = "", c4[len] = ""; // Four c strings to hold the four most recent commands; Values are updated in logCommand() and printed in printCommands()                                           

void logCommand(char newCommand[]);                          // Called in shell.c after shell.c executes a command adding that command to the command log
void printCommands();                                        // Prints a list the last 4 commands to the terminal
void lsDir();                                                // Prints a detailed list of all content of the current directory (like ls -l)
void waitForReturn();                                        // Waits for "return" input before returning

int Exit() {                                                 // Exit function to be called by shell.c
    printCommands();
    lsDir();
    waitForReturn();
    return 0;                                                // After "return" key is entered, return 0 to shell to terminate
}

void logCommand(char newCommand[]){                          // Function: Called in shell.c after shell.c executes a command adding that command to the command log
    strcpy(c1, c2); strcpy(c2, c3); strcpy(c3, c4);          // Pushes each entry down the list, overwritting the oldest entry and freeing up c4
    strcpy(c4, newCommand);                                  // Saves the newest command into c4
}
void printCommands(){                                        // Function: Prints a list the last 4 commands called in shell.c to the terminal 
    printf("\nPrevious four commands:\n");
    printf("%s\n%s\n%s\n%s\n\n", c4, c3, c2, c1);
}
void lsDir(){                                                // Function: Prints a detailed list of all content of the current directory (like ls -l)
    int pid = fork();  
	if(pid == 0) {                                           // Child case of fork calls ls -l
		char *argv[] = {"ls", "-l", NULL};
		execvp(argv[0],argv);
		printf("EXECVP Failed\n");	                         // Prints if execvp fails
	}
	else {                                                   // Parent case of fork waits for child
        wait(NULL);		
	}
}
void waitForReturn(){                                        // Function: Waits for "return" input before returning
    char returnCheck = 0x00;                                 // Variable to store user input key and check for "return"
    while(returnCheck != 0x0A){                              // Wait for "return" (0x0A is ASCII for "return" key)
        printf("\nPress RETURN to return the control to the original shell program:\n");
        returnCheck = getchar();                             // Get new user input until input is "return" key
    }
    return;
}
