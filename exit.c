// Daniel Rosenthal
// CSc 332 - Group Project
// Group A - Exit
// 28 April 2021

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define len 1024

char c1[len] = "", c2[len] = "", c3[len] = "", c4[len] = ""; // Four strings to hold the four most recent commands
void logCommand(char newCommand[]);                          // Adds any command to the log after being called in shell
void printCommands();                                        // Prints a list the last 4 commands to the terminal
void lsDir();                                                // Prints a detailed list of all content of the current directory (like ls -l)
char returnCheck = '0';                                      // "return" key terminates shell



int Exit() {
    printCommands();
    lsDir();
    while(returnCheck != 0x0A){     // 0x0A is ASCII for "return" key
        returnCheck = fgetc(stdin); // Get new user input until input is "return" key
    }
    return 0;                       // After "return" key, return 0 to shell to terminate
}

void logCommand(char newCommand[]){
    strcpy(c1, c2);
    strcpy(c2, c3);
    strcpy(c3, c4);
    strcpy(c4, newCommand);
}
void printCommands(){
    printf("%s\n%s\n%s\n%s\n", c4, c3, c2, c1);
}
void lsDir(){
        char *argv[] = {"ls", "-l", 0};
        execvp(argv[0], argv);
        fprintf(stderr, "child ls -l failed!\n"); // Only prints if execvp fails
}
