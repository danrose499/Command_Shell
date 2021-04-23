
// This new command will print a list the last 4 commands to the terminal, a detailed list of all content of the current directory (like ls -l).
// Finally, it will wait for the user to hit the “return” key to terminate the shell and return the control to the original shell program on your machine.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void previousCommands(); // Prints a list the last 4 commands to the terminal
void lsDir();            // Prints a detailed list of all content of the current directory (like ls -l)
char returnCheck = '0';  // "return" key terminates shell

void Exit() {
    previousCommands();
    lsDir();
    while(returnCheck != 0x0A){     // 0x0A is ASCII for "return" key
        returnCheck = fgetc(stdin); // Get new user input until input is "return" key
    }
    exit(0);                        // After "return" key, terminate shell
}

void previousCommands(){

}
void lsDir(){
        char *argv[] = {"ls", "-l", 0};
        execvp(argv[0], argv);
        fprintf(stderr, "child ls -l failed!\n"); // Only prints if execvp fails
}
