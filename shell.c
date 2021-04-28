// Yasiris Ortiz
// CSc 332 - Group Project
// Group A - Shell
// 28 April 2021

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

// include files for customized commands
#include "tree.c"
#include "list.c"
#include "path.c"
#include "exit.c"

int main(int argc, char *argv[])
{

    // int cont = 1;
    pid_t pid;

    while (1) // while true
    {
        char commandInput[1000]; // buffer size 
        printf("# ");

        /* read input until EXIT is pressed */
        // %[^\n]s : it is an edit conversion code that can be an alternative of gets(), and terminates with a newline
        scanf(" %[^\n]s", commandInput); // scanf allow us to scan input from standard in pr keyboard. it will read all characters until \n is reached

        logCommand(commandInput);
        // strcmp :  function used to compare string arguments character by character 
        if (!strcmp(commandInput, "tree"))
        {
            Tree();
        }
        else if (!strcmp(commandInput, "list"))
        {
            List();
        }
        else if (!strcmp(commandInput, "path"))
        {
            Path();
        }
        else if (!strcmp(commandInput, "exit"))
        {
            return Exit();
        }
        else
        {
            // continue the program if not quit is pressed!
            char *arg[100], *token, *status = NULL;
            int i = 0;

            // array pointer going to the next token, or NULL if there are not more tokens
            for (token = strtok_r(commandInput, " ", &status); token != NULL; token = strtok_r(NULL, " ", &status))
            {
                arg[i] = token; // arguments store in array arg
                i++;
            }
            arg[i] = NULL; // clear array

            pid = fork(); // fork child process to be executed

            if (pid == 0)
            {
                execvp(arg[0], arg); // replaces the current process with a new one specified by the file
                printf("File/command NOT Found\n");
                return 0;
            }

            else
            {
                wait(NULL); // parent waits until child finishes
            }
        }
    }
    return 0;
}
