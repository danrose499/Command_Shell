// Daniel Rosenthal
// CSc 332 - Group Project
// Group A - Exit
// 28 April 2021

#include <stdio.h>
#include <unistd.h>
#include <string.h>

const int len = 1024;                                        // Default value set for length of c strings declared below 
char c1[len] = "", c2[len] = "", c3[len] = "", c4[len] = ""; // Four c strings to hold the four most recent commands; Values are updated in logCommand() and printed in printCommands()
char returnCheck = '0';                                      // "return" key terminates shell with; Used in waitForReturn() function

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
    strcpy(c1, c2); strcpy(c2, c3); strcpy(c3, c4);          // Pushes each entry down the list, overwritting the oldest entry and freeing up c4...
    strcpy(c4, newCommand);                                  // ... and saves the newest command into c4
}
void printCommands(){                                        // Function: Prints a list the last 4 commands called in shell.c to the terminal 
    printf("\nPrevious four commands:\n");
    printf("%s\n%s\n%s\n%s\n\n", c4, c3, c2, c1);
}
void lsDir(){                                                // Function: Prints a detailed list of all content of the current directory (like ls -l)
    char *argv[] = {"ls", "-l", 0};
    execvp(argv[0], argv);
    fprintf(stderr, "child ls -l failed!\n");                // Only prints if execvp fails
}
void waitForReturn(){                                        // Function: Waits for "return" input before returning
    while(returnCheck != 0x0A){                              // 0x0A is ASCII for "return" key
        returnCheck = fgetc(stdin);                          // Get new user input until input is "return" key
    }
}
