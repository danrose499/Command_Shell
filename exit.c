// Daniel Rosenthal
// CSc 332 - Group Project
// Group A - Exit
// 28 April 2021

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define len 1024

char c1[len] = "", c2[len] = "", c3[len] = "", c4[len] = ""; // Four c strings to hold the four most recent commands
void logCommand(char newCommand[]);                          // Adds any command to the log after being called in shell
void printCommands();                                        // Prints a list the last 4 commands to the terminal
void lsDir();                                                // Prints a detailed list of all content of the current directory (like ls -l)
void waitForReturn();                                        // Waits for "return" input before returning
char returnCheck = '0';                                      // "return" key terminates shell

int Exit() {                                                 // Main function to be called be shell
    printCommands();
    lsDir();
    waitForReturn();
    return 0;                                                // After "return" key is entered, return 0 to shell to terminate
}

void logCommand(char newCommand[]){                          // Function:
    strcpy(c1, c2); strcpy(c2, c3); strcpy(c3, c4);          // Pushes each entry down the list, overwritting the oldest entry
    strcpy(c4, newCommand);                                  // Adds newest command to the end of the list
}
void printCommands(){                                        // Function: Prints a list the last 4 commands to the terminal 
    printf("\nPrevious four commands:\n");
    printf("%s\n%s\n%s\n%s\n\n", c4, c3, c2, c1);
}
void lsDir(){                                                // Function: Prints a detailed list of all content of the current directory (like ls -l)
        char *argv[] = {"ls", "-l", 0};
        execvp(argv[0], argv);
        fprintf(stderr, "child ls -l failed!\n");            // Only prints if execvp fails
}
void waitForReturn(){                                        // Function: Waits for "return" input before returning
    while(returnCheck != 0x0A){                              // 0x0A is ASCII for "return" key
        returnCheck = fgetc(stdin);                          // Get new user input until input is "return" key
    }
}
